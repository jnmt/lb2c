package lb2c

import scala.collection.mutable.HashMap

object QueryInterpreter extends OpParser {
  val defaultFieldDelimiter = ','

  case class Record(values: Values, schema: Schema) {
    def apply(key: String): Value = values(schema.indexWhere(_.name == key))
    def apply(keys: Seq[String]): Values = keys.map(this apply _).toVector
  }

  def processCSV(filename: String, schema: Schema, delimiter: Char)(callback: Record => Unit): Unit = {
    val s = new Scanner(filename)
    val last = schema.last
    def nextRecord = Record(schema.map{
      _ match {
        case x: IntAttribute => IntValue(s.next(if (x == last) '\n' else delimiter).toInt)
        case x: DoubleAttribute => DoubleValue(s.next(if (x == last) '\n' else delimiter).toDouble)
        case x: StringAttribute => StringValue(s.next(if (x == last) '\n' else delimiter))
      }
    }, schema)
    while (s.hasNext) callback(nextRecord)
    s.close
  }

  def printSchema(schema: Seq[String]) = println(schema.mkString(defaultFieldDelimiter.toString))

  //def printFields(values: Values) = printf(values.map{_ => "%s"}.mkString("", defaultFieldDelimiter.toString, "\n"), values: _*)
  def printFields(values: Values) = printf(values.map(_.value.toString).mkString("", defaultFieldDelimiter.toString, "\n"), values: _*)

  def getSchema(o: Operator): Seq[String] = o match {
    case ScanOp(_, schema, _) => schema.map(_.name)
    case ProjectOp(_, schema) => schema
    case FilterOp(child, _)   => getSchema(child)
    case NestedLoopJoinOp(left, right, _, _) => getSchema(left) ++ getSchema(right)
    case AggregateOp(_, keys, functions) => keys ++ functions.map(_.toString)
  }

  def evalPredicate(predicate: Predicate, record: Record): Boolean = predicate match {
    case Eq(attr, value) => record(attr) == value
      /*
    case Gte(Attribute(attr), Value(v)) => record(attr) == v.toString
    case Lte(Attribute(attr), Value(v)) => record(attr) == v.toString
    case Gt(Attribute(attr), Value(v)) => record(attr) == v.toString
    case Lt(Attribute(attr), Value(v)) => record(attr) == v.toString
       */
  }

  def execAggFunc(func: AggregateFunction, record: Record, hm: HashMap[String, Value]): Unit = {
    val x = func match {
      case Count()    => IntValue(0)
      case Max(attribute: String) => record(attribute)
      case Min(attribute: String) => record(attribute)
      case Sum(_)     => IntValue(0)
      case Average(_) => DoubleValue(0.0)
    }
    val y = hm.getOrElseUpdate(func.toString, x)
    func match {
      case Count() => y match {
        case y: IntValue => hm.update(func.toString, IntValue(y.value+1))
      }
      case Max(_)  => (x, y) match {
        case (x: IntValue, y: IntValue) => if (x.value > y.value) hm.update(func.toString, x)
        case (x: DoubleValue, y: DoubleValue) => if (x.value > y.value) hm.update(func.toString, x)
      }
      case Min(_)  => (x, y) match {
        case (x: IntValue, y: IntValue) => if (x.value < y.value) hm.update(func.toString, x)
        case (x: DoubleValue, y: DoubleValue) => if (x.value < y.value) hm.update(func.toString, x)
      }
      case Sum(attribute: String) =>
        val z = record(attribute)
        (y, z) match {
          // FIXME: Much better way for handling data types?
          case (y: IntValue, z: IntValue) => hm.update(func.toString, IntValue(y.value+z.value))
          case (y: IntValue, z: DoubleValue) => hm.update(func.toString, DoubleValue(y.value+z.value))
          case (y: DoubleValue, z: DoubleValue) => hm.update(func.toString, DoubleValue(y.value+z.value))
        }
      case Average(attribute: String) =>
        val z = record(attribute)
        val count = hm("_counter_")
        (y, z, count) match {
          // FIXME: Much better way for handling data types?
          case (y: DoubleValue, z: IntValue, count: IntValue) =>
            hm.update(func.toString, DoubleValue((y.value*count.value+z.value)/(count.value+1)))
          case (y: DoubleValue, z: DoubleValue, count: IntValue) =>
            hm.update(func.toString, DoubleValue((y.value*count.value+z.value)/(count.value+1)))
        }
    }
  }

  def execOp(o: Operator)(callback: Record => Unit): Unit = o match {
    case ScanOp(filename, schema, delimiter) =>
      processCSV(filename, schema, delimiter)(callback)

    case ProjectOp(child, attributeNames) =>
      execOp(child) { record => {
        callback(Record(record(attributeNames), Schema(attributeNames)))
      } }

    case FilterOp(child, predicates) =>
      execOp(child) { record => {
        if ( predicates.forall { evalPredicate(_, record) } ) callback(record)
      } }

    case NestedLoopJoinOp(left, right, leftAttr, rightAttr) =>
      execOp(left) { leftRecord => {
        execOp(right) { rightRecord => {
          if (leftRecord(leftAttr).value == rightRecord(rightAttr).value)
            callback(Record(leftRecord.values ++ rightRecord.values, Schema(getSchema(left) ++ getSchema(right))))
        } }
      } }

    case AggregateOp(child, keys, functions) =>
      val hashMap = new HashMap[Seq[Value], HashMap[String, Value]]
      execOp(child) { record => {
        val valuesAsKey = record(keys)
        val funcMap = hashMap.getOrElse(valuesAsKey, new HashMap[String, Value])
        val count: IntValue = funcMap.getOrElseUpdate("_counter_", IntValue(0)) match {
          case x: IntValue => x
          case _ => IntValue(0)
        } // FIXME: Only needed for calculating average ... Not cool!
        functions.foreach(execAggFunc(_, record, funcMap))
        funcMap.update("_counter_", IntValue(count.value+1))
        hashMap.update(valuesAsKey, funcMap)
      } }
      hashMap foreach {
        case (valuesAsKey, funcMap) =>
          callback(Record(Value(valuesAsKey) ++ Value(functions.map(_.toString).map(funcMap(_))), Schema(keys ++ functions.map(_.toString))))
      }

    case PrintOp(child) =>
      val schema = getSchema(child)
      printSchema(schema)
      execOp(child) { rec => printFields(rec.values) }
  }

  def execQuery(query: String): Unit = {
    this.apply(query) match {
      case Right(op: Operator) => execOp(op){ _ => }
      case Left(errorMessage: String) => println(errorMessage)
    }

  }

}
