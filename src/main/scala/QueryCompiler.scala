package lb2c

import scala.collection.mutable.HashMap

object QueryCompiler extends OpParser {
  val defaultFieldDelimiter = ','

  type Fields = Vector[Field]
  def Fields(fields: Seq[Field]): Fields = fields.toVector

  abstract class Field {
    val value: Any
    def eq(o: Field): Boolean
  }
  case class IntField(value: Int) extends Field {
    def eq(o: Field) = o match { case IntField(v) => value == v }
  }
  case class DoubleField(value: Double) extends Field {
    def eq(o: Field) = o match { case DoubleField(v) => value == v }
  }
  case class StringField(value: String) extends Field {
    def eq(o: Field) = o match { case StringField(v) => value == v }
  }

  case class Record(fields: Fields, schema: Schema) {
    def apply(key: String): Field = fields(schema.indexWhere(_.name == key)) // get a field in the vector
    def apply(keys: Seq[String]): Fields = keys.map(this apply _).toVector
  }

  def processCSV(filename: String, schema: Schema, delimiter: Char)(callback: Record => Unit): Unit = {
    val s = new Scanner(filename)
    val last = schema.last
    def nextRecord = Record(schema.map{
      _ match {
        case x: IntAttribute => IntField(s.next(if (x == last) '\n' else delimiter).toInt)
        case x: DoubleAttribute => DoubleField(s.next(if (x == last) '\n' else delimiter).toDouble)
        case x: StringAttribute => StringField(s.next(if (x == last) '\n' else delimiter))
      }
    }, schema)
    while (s.hasNext) callback(nextRecord)
    s.close
  }

  def printSchema(schema: Seq[String]) = println(schema.mkString(defaultFieldDelimiter.toString))

  //def printFields(values: Values) = printf(values.map{_ => "%s"}.mkString("", defaultFieldDelimiter.toString, "\n"), values: _*)
  def printFields(fields: Fields) = printf(fields.map(_.value.toString).mkString("", defaultFieldDelimiter.toString, "\n"), fields: _*)

  def getSchema(o: Operator): Seq[String] = o match {
    case ScanOp(_, schema, _) => schema.map(_.name)
    case ProjectOp(_, schema) => schema
    case FilterOp(child, _)   => getSchema(child)
    case NestedLoopJoinOp(left, right, _, _) => getSchema(left) ++ getSchema(right)
    case AggregateOp(_, keys, functions) => keys ++ functions.map(_.toString)
  }

  def evalPredicate(predicate: Predicate, record: Record): Boolean = predicate match {
    case Eq(attr, value) => record(attr.name) eq evalTerm(value, record)
  }

  def evalTerm(term: Term, record: Record): Field = term match {
    case Value(x: Int) => IntField(x)
    case Value(x: Double) => DoubleField(x)
    case Value(x: String) => StringField(x)
  }

  def execAggFunc(func: AggregateFunction, record: Record, hm: HashMap[String, Field]): Unit = {
    val x = func match {
      case Count()    => IntField(0)
      case Max(attribute: String) => record(attribute)
      case Min(attribute: String) => record(attribute)
      case Sum(_)     => IntField(0)
      case Average(_) => DoubleField(0.0)
    }
    val y = hm.getOrElseUpdate(func.toString, x)
    func match {
      case Count() => y match {
        case y: IntField => hm.update(func.toString, IntField(y.value+1))
      }
      case Max(_)  => (x, y) match {
        case (x: IntField, y: IntField) => if (x.value > y.value) hm.update(func.toString, x)
        case (x: DoubleField, y: DoubleField) => if (x.value > y.value) hm.update(func.toString, x)
      }
      case Min(_)  => (x, y) match {
        case (x: IntField, y: IntField) => if (x.value < y.value) hm.update(func.toString, x)
        case (x: DoubleField, y: DoubleField) => if (x.value < y.value) hm.update(func.toString, x)
      }
      case Sum(attribute: String) =>
        val z = record(attribute)
        (y, z) match {
          // FIXME: Much better way for handling data types?
          case (y: IntField, z: IntField) => hm.update(func.toString, IntField(y.value+z.value))
          case (y: IntField, z: DoubleField) => hm.update(func.toString, DoubleField(y.value+z.value))
          case (y: DoubleField, z: DoubleField) => hm.update(func.toString, DoubleField(y.value+z.value))
        }
      case Average(attribute: String) =>
        val z = record(attribute)
        val count = hm("_counter_")
        (y, z, count) match {
          // FIXME: Much better way for handling data types?
          case (y: DoubleField, z: IntField, count: IntField) =>
            hm.update(func.toString, DoubleField((y.value*count.value+z.value)/(count.value+1)))
          case (y: DoubleField, z: DoubleField, count: IntField) =>
            hm.update(func.toString, DoubleField((y.value*count.value+z.value)/(count.value+1)))
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
          if (leftRecord(leftAttr) eq rightRecord(rightAttr))
            callback(Record(leftRecord.fields ++ rightRecord.fields, Schema(getSchema(left) ++ getSchema(right))))
        } }
      } }

    case AggregateOp(child, keys, functions) =>
      val hashMap = new HashMap[Seq[Field], HashMap[String, Field]]
      execOp(child) { record => {
        val valuesAsKey = record(keys)
        val funcMap = hashMap.getOrElse(valuesAsKey, new HashMap[String, Field])
        val count: IntField = funcMap.getOrElseUpdate("_counter_", IntField(0)) match {
          case x: IntField => x
          case _ => IntField(0)
        } // FIXME: Only needed for calculating average ... Not cool!
        functions.foreach(execAggFunc(_, record, funcMap))
        funcMap.update("_counter_", IntField(count.value+1))
        hashMap.update(valuesAsKey, funcMap)
      } }
      hashMap foreach {
        case (valuesAsKey, funcMap) =>
          callback(Record(Fields(valuesAsKey) ++ Fields(functions.map(_.toString).map(funcMap(_))), Schema(keys ++ functions.map(_.toString))))
      }

    case PrintOp(child) =>
      val schema = getSchema(child)
      printSchema(schema)
      execOp(child) { rec => printFields(rec.fields) }
  }

  def execQuery(query: String): Unit = {
    this.apply(query) match {
      case Right(op: Operator) => execOp(op){ _ => }
      case Left(errorMessage: String) => println(errorMessage)
    }

  }

}
