package lb2c

import java.util.Calendar

import scala.lms.common._

trait QueryCompiler extends Dsl with OpParser with CLibraryBase {
  val defaultFieldDelimiter = ','

  class Scanner(name: Rep[String]) {
    val fd = open(name)
    val fileLength = filelen(fd)
    val data = mmap[Char](fd, fileLength)
    var pos = 0
    var end = fileLength

    def next(d: Rep[Char]) = {
      val start = pos: Rep[Int] // force read
      while (data(pos) != d) pos += 1
      val len = pos - start
      pos += 1
      StringField(stringFromCharArray(data, start, len), len)
    }

    def nextInt(d: Rep[Char]) = {
      val start = pos: Rep[Int] // force read
      var num = 0
      while (data(pos) != d) {
        num = num * 10 + (data(pos) - '0').toInt
        pos += 1
      }
      pos += 1
      IntField(num)
    }

    def nextDouble(d: Rep[Char]) = {
      val start = pos: Rep[Int] // force read
      var num = 0.0
      var decimal = 10.0
      while (data(pos) != '.' && data(pos) != d) {
        num = num * 10 + (data(pos) - '0').toInt
        pos += 1
      }
      if (data(pos) != d) {
        // This number has decimal part
        pos += 1
        while (data(pos) != d) {
          num = num + (data(pos) - '0').toInt / decimal
          decimal = decimal * 10
          pos += 1
        }
      }
      pos += 1
      DoubleField(num)
    }

    def nextDate(d: Rep[Char]) = {
      val start = pos: Rep[Int] // force read
      var year = 0
      var month = 0
      var day = 0
      while (data(pos) != '-') {
        year = year * 10 + (data(pos) - '0').toInt
        pos += 1
      }
      pos += 1
      while (data(pos) != '-') {
        month = month * 10 + (data(pos) - '0').toInt
        pos += 1
      }
      pos += 1
      while (data(pos) != d) {
        day = day * 10 + (data(pos) - '0').toInt
        pos += 1
      }
      pos += 1
      DateField(year, month, day)
    }

    def hasNext = pos < end

    def done = close(fd)
  }

  class ParScanner(name: Rep[String], threadId: Rep[Int]) {
    val fd = open(name)
    val fileLength = filelen(fd)
    val partitionSize = fileLength/4
    val data = mmap[Char](fd, fileLength)
    var pos = 0
    var end = fileLength
    setSection(threadId)

    def setSection(i: Rep[Int]) = {
      pos = i * partitionSize
      end = (i + 1) * partitionSize
      if (i > 0) {
        while (data(pos) != '\n' && pos < fileLength) {
          pos = pos + 1
        }
        pos = pos + 1
      }
      while (data(end) != '\n' && end < fileLength) {
        end += 1
      }
      end += 1
    }

    def next(d: Rep[Char]) = {
      val start = pos: Rep[Int] // force read
      while (data(pos) != d) pos += 1
      val len = pos - start
      pos += 1
      StringField(stringFromCharArray(data, start, len), len)
    }

    def nextInt(d: Rep[Char]) = {
      val start = pos: Rep[Int] // force read
      var num = 0
      while (data(pos) != d) {
        num = num * 10 + (data(pos) - '0').toInt
        pos += 1
      }
      pos += 1
      IntField(num)
    }

    def nextDouble(d: Rep[Char]) = {
      val start = pos: Rep[Int] // force read
      var num = 0.0
      var decimal = 10.0
      while (data(pos) != '.' && data(pos) != d) {
        num = num * 10 + (data(pos) - '0').toInt
        pos += 1
      }
      if (data(pos) != d) {
        // This number has decimal part
        pos += 1
        while (data(pos) != d) {
          num = num + (data(pos) - '0').toInt / decimal
          decimal = decimal * 10
          pos += 1
        }
      }
      pos += 1
      DoubleField(num)
    }

    def nextDate(d: Rep[Char]) = {
      val start = pos: Rep[Int] // force read
      var year = 0
      var month = 0
      var day = 0
      while (data(pos) != '-') {
        year = year * 10 + (data(pos) - '0').toInt
        pos += 1
      }
      pos += 1
      while (data(pos) != '-') {
        month = month * 10 + (data(pos) - '0').toInt
        pos += 1
      }
      pos += 1
      while (data(pos) != d) {
        day = day * 10 + (data(pos) - '0').toInt
        pos += 1
      }
      pos += 1
      DateField(year, month, day)
    }

    def hasNext = pos < fileLength && pos < end

    def done = close(fd)
  }

  /*
    Schema is a Vector of Attribute.
    Attribute is a class that holds its name and type of attribute as a sub class (e.g., IntAttribute).
    Value is a class that holds single value parsed by OpParser.
    Field is a class that holds single value parsed by Scanner.
    TODO: Value and Field can be unified?
   */

  type Fields = Vector[Field]

  def Fields(fields: Seq[Field]): Fields = fields.toVector

  abstract class Field {
    val value: Any

    def print()

    def hash(): Rep[Long]

    def plus(o: Field): Field

    def minus(o: Field): Field

    def multipliedBy(o: Field): Field

    def dividedBy(o: Field): Field

    def isEquals(o: Field): Rep[Boolean]

    def isNotEquals(o: Field): Rep[Boolean]

    def isGte(o: Field): Rep[Boolean]

    def isLte(o: Field): Rep[Boolean]

    def isGt(o: Field): Rep[Boolean]

    def isLt(o: Field): Rep[Boolean]
  }

  case class IntField(value: Rep[Int]) extends Field {
    def print() = printf("%d", value)

    def hash() = value.asInstanceOf[Rep[Long]]

    def plus(o: Field) = o match {
      case IntField(v) => IntField(value + v)
      case DoubleField(v) => DoubleField(value + v)
    }

    def minus(o: Field) = o match {
      case IntField(v) => IntField(value - v)
      case DoubleField(v) => DoubleField(value - v)
    }

    def multipliedBy(o: Field) = o match {
      case IntField(v) => IntField(value * v)
      case DoubleField(v) => DoubleField(value * v)
    }

    def dividedBy(o: Field) = o match {
      case IntField(v) => IntField(value / v)
      case DoubleField(v) => DoubleField(value / v)
    }

    def isEquals(o: Field) = o match {
      case IntField(v) => value == v
    }

    def isNotEquals(o: Field) = !(this isEquals o)

    // TODO: Implement all methods for IntField
    def isGte(o: Field): Rep[Boolean] = o match {
      case IntField(v) => value >= v
    }

    def isLte(o: Field): Rep[Boolean] = o match {
      case IntField(v) => value <= v
    }

    def isGt(o: Field): Rep[Boolean] = o match {
      case IntField(v) => value > v
    }

    def isLt(o: Field): Rep[Boolean] = o match {
      case IntField(v) => value < v
    }
  }

  case class DoubleField(value: Rep[Double]) extends Field {
    def print() = printf("%f", value)

    def hash() = value.asInstanceOf[Rep[Long]]

    def plus(o: Field) = o match {
      case IntField(v) => DoubleField(value + v)
      case DoubleField(v) => DoubleField(value + v)
    }

    def minus(o: Field) = o match {
      case IntField(v) => DoubleField(value - v)
      case DoubleField(v) => DoubleField(value - v)
    }

    def multipliedBy(o: Field) = o match {
      case IntField(v) => DoubleField(value * v)
      case DoubleField(v) => DoubleField(value * v)
    }

    def dividedBy(o: Field) = o match {
      case IntField(v) => DoubleField(value / v)
      case DoubleField(v) => DoubleField(value / v)
    }

    def isEquals(o: Field) = o match {
      case IntField(v) => value == v
      case DoubleField(v) => value == v
    }

    def isNotEquals(o: Field) = !(this isEquals o)

    // TODO: Implement all methods for DoubleField
    def isGte(o: Field): Rep[Boolean] = o match {
      case IntField(v) => value >= v
      case DoubleField(v) => value >= v
    }

    def isLte(o: Field): Rep[Boolean] = o match {
      case IntField(v) => value <= v
      case DoubleField(v) => value <= v
    }

    def isGt(o: Field): Rep[Boolean] = o match {
      case IntField(v) => value > v
      case DoubleField(v) => value > v
    }

    def isLt(o: Field): Rep[Boolean] = o match {
      case IntField(v) => value < v
      case DoubleField(v) => value < v
    }
  }

  case class DateField(value: Rep[Int], month: Rep[Int], day: Rep[Int]) extends Field {
    // TODO: value field has year but it is a bit misleading...
    def print() = printf("%d-%02d-%02d", value, month, day)

    def hash() = (value * 10000 + month * 100 + day).asInstanceOf[Rep[Long]]

    def plus(o: Field): Field = this

    def minus(o: Field): Field = this

    def multipliedBy(o: Field): Field = this

    def dividedBy(o: Field): Field = this

    def isEquals(o: Field) = o match {
      case DateField(y, m, d) => value == y && month == m && day == d
    }

    def isNotEquals(o: Field) = !(this isEquals o)

    // TODO: Implement all methods for DateField
    def isGte(o: Field): Rep[Boolean] = o match {
      case DateField(y, m, d) =>
        val a = value * 10000 + month * 100 + day
        val b = y * 10000 + m * 100 + d
        a >= b
    }

    def isLte(o: Field): Rep[Boolean] = o match {
      case DateField(y, m, d) =>
        val a = value * 10000 + month * 100 + day
        val b = y * 10000 + m * 100 + d
        a <= b
    }

    def isGt(o: Field): Rep[Boolean] = o match {
      case DateField(y, m, d) =>
        val a = value * 10000 + month * 100 + day
        val b = y * 10000 + m * 100 + d
        a > b
    }

    def isLt(o: Field): Rep[Boolean] = o match {
      case DateField(y, m, d) =>
        val a = value * 10000 + month * 100 + day
        val b = y * 10000 + m * 100 + d
        a < b
    }
  }

  case class AverageField(value: Rep[Double], count: Rep[Int]) extends Field {
    def print() = printf("%f", value / count)

    def hash() = (value / count).asInstanceOf[Rep[Long]]

    def plus(o: Field): Field = this

    def minus(o: Field): Field = this

    def multipliedBy(o: Field): Field = this

    def dividedBy(o: Field): Field = this

    def isEquals(o: Field) = o match {
      case AverageField(v, c) => value / count == v / c
    }

    def isNotEquals(o: Field) = !(this isEquals o)

    // TODO: Implement all methods for AverageField
    def isGte(o: Field): Rep[Boolean] = true

    def isLte(o: Field): Rep[Boolean] = true

    def isGt(o: Field): Rep[Boolean] = true

    def isLt(o: Field): Rep[Boolean] = true
  }

  case class StringField(value: Rep[String], length: Rep[Int]) extends Field {
    def print() = prints(value)

    def hash(): Rep[Long] = value.HashCode(length)

    def plus(o: Field): Field = this

    def minus(o: Field): Field = this

    def multipliedBy(o: Field): Field = this

    def dividedBy(o: Field): Field = this

    def isEquals(o: Field) = o match {
      case StringField(operandValue, operandLength) =>
        if (length != operandLength)
          false
        else {
          // TODO: we may or may not want to inline this (code bloat and icache considerations).
          var i = 0
          while (i < length && value.charAt(i) == operandValue.charAt(i)) {
            i += 1
          }
          i == length
        }
    }

    def isNotEquals(o: Field) = !(this isEquals o)

    // TODO: Implement all methods for StringField
    def isGte(o: Field): Rep[Boolean] = true

    def isLte(o: Field): Rep[Boolean] = true

    def isGt(o: Field): Rep[Boolean] = true

    def isLt(o: Field): Rep[Boolean] = o match {
      case StringField(operandValue, operandLength) =>
        var i = 0
        while (i < length && i < operandLength && value.charAt(i) == operandValue.charAt(i)) {
          i += 1
        }
        value.charAt(i) < operandValue.charAt(i) // TODO: Need to consider length? e.g., XXX is less than XXXX
    }
  }

  case class Record(fields: Fields, schema: Schema) {
    def apply(key: String): Field = fields(schema.indexWhere(_.name == key)) // get a field in the vector
    def apply(keys: Seq[String]): Fields = keys.map(this apply _).toVector
  }

  def processCSV(filename: Rep[String], schema: Schema, delimiter: Char)(callback: RecordCallback): Rep[Unit] = {
    val s = new Scanner(filename)
    val last = schema.last

    def nextDelimiter(attribute: Attribute) = if (attribute == last) '\n' else delimiter

    def nextRecord = Record(schema.map {
      _ match {
        case x: IntAttribute => s.nextInt(nextDelimiter(x))
        case x: DoubleAttribute => s.nextDouble(nextDelimiter(x))
        case x: DateAttribute => s.nextDate(nextDelimiter(x))
        case x: StringAttribute => s.next(nextDelimiter(x))
      }
    }, schema)

    while (s.hasNext) callback(nextRecord)
    s.done
  }

  val numberOfThreads = 4
  def parProcessCSV(filename: Rep[String], schema: Schema, delimiter: Char)(threadCallback: ThreadCallback): Rep[Unit] = {
    parallel {
      for (i <- 0 until numberOfThreads) {
        threadCallback(i)((callback: RecordCallback) => {
          val s = new ParScanner(filename, i)
          val last = schema.last

          def nextDelimiter(attribute: Attribute) = if (attribute == last) '\n' else delimiter

          def nextRecord = Record(schema.map {
            _ match {
              case x: IntAttribute => s.nextInt(nextDelimiter(x))
              case x: DoubleAttribute => s.nextDouble(nextDelimiter(x))
              case x: DateAttribute => s.nextDate(nextDelimiter(x))
              case x: StringAttribute => s.next(nextDelimiter(x))
            }
          }, schema)

          while (s.hasNext)
            callback(nextRecord)

          s.done
        })
      }
    }
  }

  def printSchema(schema: Schema) = println(schema.map(_.name).mkString(defaultFieldDelimiter.toString))

  def printFields(fields: Fields) = {
    if (fields.nonEmpty) {
      fields.head.print
      fields.tail.foreach { x => printf(defaultFieldDelimiter.toString); x.print }
    }
    println("")
  }

  def getAggregateKeysSchema(child: Operator, keys: Seq[String]): Schema = {
    keys.foldLeft(Vector.empty[Attribute]) {
      (result, attr) => result ++ getSchema(child).find(_.name == attr)
    }
  }

  def getAggregateFunctionsSchema(child: Operator, functions: Seq[AggregateFunction]): Schema = {
    functions.map {
      _ match {
        case Count() => IntAttribute("count")
        case Max(attr) =>
          getSchema(child).find(_.name == attr) match {
            case Some(IntAttribute(name)) => IntAttribute(s"max_${name}")
            case Some(DoubleAttribute(name)) => DoubleAttribute(s"max_${name}")
            case Some(AnyAttribute(name)) => AnyAttribute(s"max_${name}")
          }
        case Min(attr) =>
          getSchema(child).find(_.name == attr) match {
            case Some(IntAttribute(name)) => IntAttribute(s"min_${name}")
            case Some(DoubleAttribute(name)) => DoubleAttribute(s"min_${name}")
            case Some(AnyAttribute(name)) => AnyAttribute(s"min_${name}")
          }
        case Sum(attr) =>
          getSchema(child).find(_.name == attr) match {
            case Some(IntAttribute(name)) => IntAttribute(s"sum_${name}")
            case Some(DoubleAttribute(name)) => DoubleAttribute(s"sum_${name}")
            case Some(AnyAttribute(name)) => AnyAttribute(s"sum_${name}")
          }
        case Average(attr) =>
          getSchema(child).find(_.name == attr) match {
            case Some(IntAttribute(name)) => AverageAttribute(s"avg_${name}")
            case Some(DoubleAttribute(name)) => AverageAttribute(s"avg_${name}")
            case Some(AnyAttribute(name)) => AnyAttribute(s"avg_${name}")
          }
      }
    }.toVector
  }

  def getArithmeticOperatorSchema(rootArithmeticOperators: Seq[RootArithmeticOp]): Schema = {
    rootArithmeticOperators.map { op =>
      DoubleAttribute(op.alias) // TODO: Use appropriate types for arithmetic operators
    }.toVector
  }

  def getSchema(o: Operator): Schema = o match {
    case ScanOp(_, schema, _) => schema
    case CalculateOp(child, attributeExpList) => getSchema(child) ++ getArithmeticOperatorSchema(attributeExpList)
    case ProjectOp(child, attributes) =>
      attributes.foldLeft(Vector.empty[Attribute]) { (result, attr) => result ++ getSchema(child).find(_.name == attr) }
    case FilterOp(child, _) => getSchema(child)
    case NestedLoopJoinOp(left, right, _, _) => getSchema(left) ++ getSchema(right)
    case HashJoinOp(left, right, _, _) => getSchema(left) ++ getSchema(right)
    case AggregateOp(child, keys, functions) => getAggregateKeysSchema(child, keys) ++ getAggregateFunctionsSchema(child, functions)
    case SortOp(child, _) => getSchema(child)
  }

  def evalPredicate(predicate: Predicate, record: Record): Rep[Boolean] = predicate match {
    case Eq(attr, value) => record(attr.name) isEquals evalTerm(value, record)
    case Gte(attr, value) => record(attr.name) isGte evalTerm(value, record)
    case Lte(attr, value) => record(attr.name) isLte evalTerm(value, record)
    case Gt(attr, value) => record(attr.name) isGt evalTerm(value, record)
    case Lt(attr, value) => record(attr.name) isLt evalTerm(value, record)
  }

  def evalTerm(term: Term, record: Record): Field = term match {
    case Value(x: Int) => IntField(x)
    case Value(x: Double) => DoubleField(x)
    case Value(x: String) => StringField(x, x.toString.length)
    case Value(x: Calendar) => DateField(x.get(Calendar.YEAR), x.get(Calendar.MONTH) + 1, x.get(Calendar.DAY_OF_MONTH))
  }

  def getInitFields(functions: Seq[AggregateFunction]): Fields = {
    functions.map {
      _ match {
        case Count() => IntField(0)
        case Max(_) => IntField(0)
        case Min(_) => IntField(2147483647) // FIXME: Int.MaxValue is not implemented in LMS...
        case Sum(_) => IntField(0)
        case Average(_) => AverageField(0.0, 0)
      }
    }.toVector
  }

  def execAggregation(functions: Seq[AggregateFunction], currentFields: Fields, record: Record): Fields = {
    (functions, currentFields).zipped.map { (func, current) =>
      func match {
        case Count() =>
          current match {
            case current: IntField => IntField(current.value + 1)
          }
        case Max(attribute) =>
          val field = record(attribute)
          (current, field) match {
            // TODO: Why we cannot write like this? "=> if (current.value < field.value) field else current"
            case (current: IntField, field: IntField) =>
              IntField(if (current.value < field.value) field.value else current.value)
            case (current: IntField, field: DoubleField) =>
              val x = DoubleField(current.value) // TODO: Good way to cast?
              DoubleField(if (x.value < field.value) field.value else x.value)
            case (current: DoubleField, field: DoubleField) =>
              DoubleField(if (current.value < field.value) field.value else current.value)
          }
        case Min(attribute) =>
          val field = record(attribute)
          (current, field) match {
            case (current: IntField, field: IntField) =>
              IntField(if (current.value > field.value) field.value else current.value)
            case (current: IntField, field: DoubleField) =>
              val x = DoubleField(current.value) // TODO: Good way to cast?
              DoubleField(if (x.value > field.value) field.value else x.value)
            case (current: DoubleField, field: DoubleField) =>
              DoubleField(if (current.value > field.value) field.value else current.value)
          }
        case Sum(attribute: String) =>
          val field = record(attribute)
          (current, field) match {
            // FIXME: Much better way for handling data types?
            case (current: IntField, field: IntField) => IntField(current.value + field.value)
            case (current: IntField, field: DoubleField) => DoubleField(current.value + field.value)
            case (current: DoubleField, field: DoubleField) => DoubleField(current.value + field.value)
          }
        case Average(attribute: String) =>
          val field = record(attribute)
          (current, field) match {
            case (current: AverageField, field: IntField) => AverageField(current.value + field.value, current.count + 1)
            case (current: AverageField, field: DoubleField) => AverageField(current.value + field.value, current.count + 1)
          }
      }
    }.toVector
  }

  def execArithmeticOp(aop: ArithmeticOperator, record: Record): Field = aop match {
    case RootArithmeticOp(child, _) => execArithmeticOp(child, record)
    case AddOp(leftChild, rightChild) =>
      val a = execArithmeticOp(leftChild, record)
      val b = execArithmeticOp(rightChild, record)
      a plus b
    case SubOp(leftChild, rightChild) =>
      val a = execArithmeticOp(leftChild, record)
      val b = execArithmeticOp(rightChild, record)
      a minus b
    case MultiplyOp(leftChild, rightChild) =>
      val a = execArithmeticOp(leftChild, record)
      val b = execArithmeticOp(rightChild, record)
      a multipliedBy b
    case DivideOp(leftChild, rightChild) =>
      val a = execArithmeticOp(leftChild, record)
      val b = execArithmeticOp(rightChild, record)
      a dividedBy b
    case ParenthesizedOp(child) => execArithmeticOp(child, record)
    case AttributeOp(name) => record(name)
    case ValueOp(value) =>
      value match {
        case Value(x: Int) => IntField(x)
        case Value(x: Double) => DoubleField(x)
      }
  }

  def execOp(o: Operator)(callback: RecordCallback): Rep[Unit] = o match {
    case ScanOp(filename, schema, delimiter) =>
      processCSV(filename, schema, delimiter)(callback)

    case CalculateOp(child, attributeExpList) =>
      execOp(child) { record =>
        val fields = attributeExpList.map { o => execArithmeticOp(o, record) }
        val schema = getArithmeticOperatorSchema(attributeExpList)
        callback(Record(record.fields ++ fields, record.schema ++ schema))
      }

    case ProjectOp(child, attributeNames) =>
      execOp(child) { record =>
        callback(Record(record(attributeNames), getSchema(o)))
      }

    case FilterOp(child, predicates) =>
      execOp(child) { record =>
        //  We cannot do like below because LMS seems not to support forall method.
        //  ```
        //  if ( predicates.forall { evalPredicate(_, record) } ) callback(record)
        //  ```
        // So, use foreach with Rep[Boolean] flag.
        var flag: Rep[Boolean] = true
        predicates.foreach { predicate =>
          flag = flag && evalPredicate(predicate, record)
        }
        if (flag) callback(record)
      }

    case NestedLoopJoinOp(left, right, leftAttr, rightAttr) =>
      execOp(left) { leftRecord =>
        execOp(right) { rightRecord =>
          if (leftRecord(leftAttr) isEquals rightRecord(rightAttr))
            callback(Record(leftRecord.fields ++ rightRecord.fields, leftRecord.schema ++ rightRecord.schema))
        }
      }

    case HashJoinOp(left, right, leftAttr, rightAttr) =>
      val keySchema = getAggregateKeysSchema(left, Vector(leftAttr))
      val valueSchema = getSchema(left)
      val hashMap = new LB2HashMultiMap(keySchema, valueSchema)
      execOp(left) { leftRecord =>
        hashMap.add(Vector(leftRecord(leftAttr)), leftRecord)
      }
      execOp(right) { rightRecord =>
        hashMap(Vector(rightRecord(rightAttr))) foreach { leftRecord =>
          callback(Record(leftRecord.fields ++ rightRecord.fields, leftRecord.schema ++ rightRecord.schema))
        }
      }

    case AggregateOp(child, keys, functions) =>
      val keySchema = getAggregateKeysSchema(child, keys)
      val valueSchema = getAggregateFunctionsSchema(child, functions)
      val hashMap = new LB2HashMap(keySchema, valueSchema)
      execOp(child) { record =>
        val valuesAsKey = record(keys)
        val initFields = getInitFields(functions)
        hashMap.update(valuesAsKey, initFields) { currentFields => execAggregation(functions, currentFields, record) }
      }
      hashMap foreach {
        callback(_)
      }

    case SortOp(child, keys) =>
      val result = new SortBuffer(getSchema(child), 1 << 16)
      execOp(child) { record =>
        result.add(record)
      }
      result.sort(keys)
      result foreach {
        callback(_)
      }

    case PrintOp(child) =>
      val schema = getSchema(child)
      printSchema(schema)
      execOp(child) { rec => printFields(rec.fields) }
  }

  def execQueryOld(query: String): Unit = execOp(parseQuery(query)) { _ => }

//  def execQuery(query: String): Unit = {
//    val queryProcessor = getForeachFunction(parseQuery(query))
//    queryProcessor{ _ => }
//  }

  def execQuery(query: String): Unit = {
    val queryProcessor = execParOp(parseQuery(query))
    queryProcessor{ _ => _ => }
  }

  type RecordCallback = Record => Unit
  type DataLoop = RecordCallback => Unit
  type ThreadCallback = Rep[Int] => (DataLoop => Unit)
  type ParallelSection = ThreadCallback => Unit
  def getForeachFunction(o: Operator): DataLoop = o match {
    case ScanOp(filename, schema, delimiter) =>
      (callback: RecordCallback) => {
        processCSV(filename, schema, delimiter)(callback)
      }

    case CalculateOp(child, attributeExpList) =>
      val foreachRecord = getForeachFunction(child)
      (callback: RecordCallback) => {
        foreachRecord { record =>
          val fields = attributeExpList.map { o => execArithmeticOp(o, record) }
          val schema = getArithmeticOperatorSchema(attributeExpList)
          callback(Record(record.fields ++ fields, record.schema ++ schema))
        }
      }

    case ProjectOp(child, attributeNames) =>
      val foreachRecord = getForeachFunction(child)
      (callback: RecordCallback) => {
        foreachRecord { record =>
          callback(Record(record(attributeNames), getSchema(o)))
        }
      }

    case FilterOp(child, predicates) =>
      val foreachRecord = getForeachFunction(child)
      (callback: RecordCallback) => {
        foreachRecord { record =>
          //  We cannot do like below because LMS seems not to support forall method.
          //  ```
          //  if ( predicates.forall { evalPredicate(_, record) } ) callback(record)
          //  ```
          // So, use foreach with Rep[Boolean] flag.
          var flag: Rep[Boolean] = true
          predicates.foreach { predicate =>
            flag = flag && evalPredicate(predicate, record)
          }
          if (flag) callback(record)
        }
      }

    case NestedLoopJoinOp(left, right, leftAttr, rightAttr) =>
      val foreachLeftRecord = getForeachFunction(left)
      val foreachRightRecord = getForeachFunction(right)
      (callback: RecordCallback) => {
        foreachLeftRecord { leftRecord =>
          foreachRightRecord { rightRecord =>
            if (leftRecord(leftAttr) isEquals rightRecord(rightAttr))
              callback(Record(leftRecord.fields ++ rightRecord.fields, leftRecord.schema ++ rightRecord.schema))
          }
        }
      }

    case HashJoinOp(left, right, leftAttr, rightAttr) =>
      val keySchema = getAggregateKeysSchema(left, Vector(leftAttr))
      val valueSchema = getSchema(left)
      val hashMap = new LB2HashMultiMap(keySchema, valueSchema)
      val foreachLeftRecord = getForeachFunction(left)
      val foreachRightRecord = getForeachFunction(right)
      (callback: RecordCallback) => {
        foreachLeftRecord { leftRecord =>
          hashMap.add(Vector(leftRecord(leftAttr)), leftRecord)
        }
        foreachRightRecord { rightRecord =>
          hashMap(Vector(rightRecord(rightAttr))) foreach { leftRecord =>
            callback(Record(leftRecord.fields ++ rightRecord.fields, leftRecord.schema ++ rightRecord.schema))
          }
        }
      }

    case AggregateOp(child, keys, functions) =>
      val keySchema = getAggregateKeysSchema(child, keys)
      val valueSchema = getAggregateFunctionsSchema(child, functions)
      val hashMap = new LB2HashMap(keySchema, valueSchema)
      val foreachRecord = getForeachFunction(child)
      (callback: RecordCallback) => {
        foreachRecord { record =>
          val valuesAsKey = record(keys)
          val initFields = getInitFields(functions)
          hashMap.update(valuesAsKey, initFields) { currentFields => execAggregation(functions, currentFields, record) }
        }
        hashMap foreach {
          callback(_)
        }
      }

    case SortOp(child, keys) =>
      val result = new SortBuffer(getSchema(child), 1 << 16)
      val foreachRecord = getForeachFunction(child)
      (callback: RecordCallback) => {
        foreachRecord { record =>
          result.add(record)
        }
        result.sort(keys)
        result foreach {
          callback(_)
        }
      }

    case PrintOp(child) =>
      val schema = getSchema(child)
      printSchema(schema)
      val foreachRecord = getForeachFunction(child)
      (_: RecordCallback) => { foreachRecord { rec => printFields(rec.fields) } }
  }

  // TODO: Almost same as execAggregation except for count() and average()
  def execMerge(functions: Seq[AggregateFunction], attributes: Schema, currentFields: Fields, record: Record): Fields = {
    (functions, attributes, currentFields).zipped.map { (func, attribute, current) =>
      val name = attribute match {
        case IntAttribute(n) => n
        case DoubleAttribute(n) => n
        case AverageAttribute(n) => n
        case AnyAttribute(n) => n
      }
      val field = record(name)
      func match {
        case Count() =>
          (current, field) match {
            // FIXME: Much better way for handling data types?
            case (current: IntField, field: IntField) => IntField(current.value + field.value)
            case (current: IntField, field: DoubleField) => DoubleField(current.value + field.value)
            case (current: DoubleField, field: DoubleField) => DoubleField(current.value + field.value)
          }
        case Max(_) =>
          (current, field) match {
            // TODO: Why we cannot write like this? "=> if (current.value < field.value) field else current"
            case (current: IntField, field: IntField) =>
              IntField(if (current.value < field.value) field.value else current.value)
            case (current: IntField, field: DoubleField) =>
              val x = DoubleField(current.value) // TODO: Good way to cast?
              DoubleField(if (x.value < field.value) field.value else x.value)
            case (current: DoubleField, field: DoubleField) =>
              DoubleField(if (current.value < field.value) field.value else current.value)
          }
        case Min(_) =>
          (current, field) match {
            case (current: IntField, field: IntField) =>
              IntField(if (current.value > field.value) field.value else current.value)
            case (current: IntField, field: DoubleField) =>
              val x = DoubleField(current.value) // TODO: Good way to cast?
              DoubleField(if (x.value > field.value) field.value else x.value)
            case (current: DoubleField, field: DoubleField) =>
              DoubleField(if (current.value > field.value) field.value else current.value)
          }
        case Sum(_) =>
          (current, field) match {
            // FIXME: Much better way for handling data types?
            case (current: IntField, field: IntField) => IntField(current.value + field.value)
            case (current: IntField, field: DoubleField) => DoubleField(current.value + field.value)
            case (current: DoubleField, field: DoubleField) => DoubleField(current.value + field.value)
          }
        case Average(_) =>
          (current, field) match {
            // FIXME: Average of average is not always same as average of fields
            case (current: AverageField, field: IntField) => AverageField(current.value + field.value, current.count + 1)
            case (current: AverageField, field: DoubleField) => AverageField(current.value + field.value, current.count + 1)
            case (current: AverageField, field: AverageField) => AverageField(current.value + field.value, current.count + field.count)
          }
      }
    }.toVector
  }

  def execParOp(o: Operator): ParallelSection = o match {
    case ScanOp(filename, schema, delimiter) =>
      (threadCallback: ThreadCallback) => {
        parProcessCSV(filename, schema, delimiter)(threadCallback)
      }

    case CalculateOp(child, attributeExpList) =>
      val parallelSection = execParOp(child)
      (threadCallback: ThreadCallback) => {
        parallelSection { threadId: Rep[Int] => foreachRecord: DataLoop =>
          foreachRecord { record =>
            val fields = attributeExpList.map { o => execArithmeticOp(o, record) }
            val schema = getArithmeticOperatorSchema(attributeExpList)
            threadCallback(threadId)((callback: RecordCallback) =>
              callback(Record(record.fields ++ fields, record.schema ++ schema)))
          }
        }
      }

    case ProjectOp(child, attributeNames) =>
      val parallelSection = execParOp(child)
      (threadCallback: ThreadCallback) => {
        parallelSection { threadId: Rep[Int] => foreachRecord: DataLoop =>
          foreachRecord { record =>
            threadCallback(threadId)((callback: RecordCallback) =>
              callback(Record(record(attributeNames), getSchema(o))))
          }
        }
      }

    case FilterOp(child, predicates) =>
      val parallelSection = execParOp(child)
      (threadCallback: ThreadCallback) => {
        parallelSection { threadId: Rep[Int] => foreachRecord: DataLoop =>
          foreachRecord { record =>
            //  We cannot do like below because LMS seems not to support forall method.
            //  ```
            //  if ( predicates.forall { evalPredicate(_, record) } ) callback(record)
            //  ```
            // So, use foreach with Rep[Boolean] flag.
            var flag: Rep[Boolean] = true
            predicates.foreach { predicate =>
              flag = flag && evalPredicate(predicate, record)
            }
            if (flag) threadCallback(threadId)((callback: RecordCallback) => callback(record))
          }
        }
      }

    case AggregateOp(child, keys, functions) =>
      val parallelSection = execParOp(child)
      val keySchema = getAggregateKeysSchema(child, keys)
      val valueSchema = getAggregateFunctionsSchema(child, functions)
      val hashMap = new LB2HashMap(keySchema, valueSchema)
      val parHashMap = new LB2ParHashMap(numberOfThreads, keySchema, valueSchema)
      (threadCallback: ThreadCallback) => {
        parallelSection { threadId: Rep[Int] => foreachRecord: DataLoop =>
          foreachRecord { record =>
            val valuesAsKey = record(keys)
            val initFields = getInitFields(functions)
            parHashMap.update(threadId)(valuesAsKey, initFields) { currentFields =>
              execAggregation(functions, currentFields, record) }
          }
        }
        wait {
          for (i <- 0 until numberOfThreads) {
            parHashMap.foreach(i) { record =>
              val valuesAsKey = record(keys)
              val initFields = getInitFields(functions)
              hashMap.update(valuesAsKey, initFields) { currentFields =>
                execMerge(functions, valueSchema, currentFields, record) }
            }
          }
        }
        parallel {
          for (i <- 0 until numberOfThreads) {
            threadCallback(i)((callback: RecordCallback) =>
              hashMap.foreachInPartition(i, numberOfThreads) { callback(_) } )
          }
        }
      }

    // TODO: Do this in more sophisticate way
    case SortOp(child, keys) =>
      val parallelSection = execParOp(child)
      val result = new SortBuffer(getSchema(child), 1 << 16)
      (threadCallback: ThreadCallback) => {
        parallelSection { threadId: Rep[Int] => foreachRecord: DataLoop =>
          foreachRecord { record =>
            critical {
              result.add(record)
            }
          }
        }
        wait {
          result.sort(keys)
        }
        threadCallback(0)((callback: RecordCallback) => result foreach { callback(_) } )
      }

    case PrintOp(child) =>
      val schema = getSchema(child)
      printSchema(schema)
      val parallelSection = execParOp(child)
      (_: ThreadCallback) => parallelSection { _ => foreachRecord =>
        foreachRecord { record =>
          critical {
            printFields(record.fields)
          }
        }
      }
  }

  def fieldsHash(fields: Fields) = {
    val hash = (fields.foldLeft(unit(0L)) { (x, y) => x * 41L + y.hash() }).toInt
    if (hash >= 0) hash else 0-hash
  }

  def fieldsEqual(a: Fields, b: Fields) = {
    var flag: Rep[Boolean] = true
    (a, b).zipped.foreach { (a, b) =>
      flag = flag && (a isEquals b)
    }
    flag
  }

  class LB2HashMap(keySchema: Schema, valueSchema: Schema) {
    val size = (1 << 20)
    val keys = new ColumnarRecordBuffer(keySchema, size)
    val vals = new ColumnarRecordBuffer(valueSchema, size)
    val used = NewArray[Boolean](size)
    for (i <- 0 until size: Rep[Range]) {
      used(i) = false
    }
    val hashMap = NewArray[Int](size)
    var next = var_new(0)

    def update(keyFields: Fields, init: Fields)(updateFunction: Fields => Fields) = {
      // Use like this
      // hm.update(valuesAsKey, initFields){ currentFields => aggregate(currentFields, record) }
      // hm.foreach { record => do_something(record) }

      val index = lookup(keyFields)
      if (index == size - 1) {
        println("LB2HashMap table is full.") // TODO: Handle this case correctly
        exits(1)
      }
      if (used(index)) { // if the entry is empty
        vals(index) = updateFunction(vals(index))
      } else {
        hashMap(next) = index
        next += 1
        keys(index) = keyFields
        vals(index) = updateFunction(init)
        used(index) = true
      }
    }

    def lookup(keyFields: Fields): Rep[Int] = {
      var index = fieldsHash(keyFields) % size
      while (used(index) && !fieldsEqual(keys(index), keyFields)) {
        index += 1
      }
      index
    }

    def foreach(f: Record => Rep[Unit]) = {
      for (i <- 0 until next) {
        val index = hashMap(i)
        f(Record(keys(index) ++ vals(index), keySchema ++ valueSchema))
      }
    }

    def foreachInPartition(partitionNumber: Rep[Int], numberOfPartitions: Int)(f: Record => Rep[Unit]) = {
      val assignment = next / numberOfPartitions + 1
      val start = partitionNumber * assignment
      var end = (partitionNumber + 1) * assignment
      if (end > next)
        end = next
      for (i <- start until end) {
        val index = hashMap(i)
        f(Record(keys(index) ++ vals(index), keySchema ++ valueSchema))
      }
    }
  }

  class LB2HashMultiMap(keySchema: Schema, valueSchema: Schema) {
    val hashTableSize = (1 << 18)
    val bucketSize = (1 << 8)
    val keysBuffer = new ColumnarRecordBuffer(keySchema, hashTableSize)
    val valuesBuffer = new ColumnarRecordBuffer(valueSchema, hashTableSize*bucketSize)
    val bucketStatus = NewArray[Int](hashTableSize)
    for (i <- 0 until hashTableSize: Rep[Range]) {
      bucketStatus(i) = 0
    }

    def add(keyFields: Fields, record: Record) = {
      val bucketNumber = lookup(keyFields)
      if (bucketNumber == hashTableSize - 1) {
        println("LB2HashMultiMap table is full.") // TODO: Handle this case correctly
        exits(1)
      }
      if (bucketStatus(bucketNumber) == bucketSize - 1) {
        println("Bucket is full.") // TODO: Handle this case correctly
        exits(1)
      }
      val offset = bucketNumber * bucketSize + bucketStatus(bucketNumber)
      keysBuffer(bucketNumber) = keyFields
      valuesBuffer(offset) = record.fields
      bucketStatus(bucketNumber) = bucketStatus(bucketNumber) + 1
    }

    def lookup(keyFields: Fields): Rep[Int] = {
      var bucketNumber = fieldsHash(keyFields) % hashTableSize
      while (bucketStatus(bucketNumber) > 0 && !fieldsEqual(keysBuffer(bucketNumber), keyFields)) {
        bucketNumber = bucketNumber + 1
      }
      bucketNumber
    }

    def apply(keyFields: Fields) = new {
      // Create anonymous object to allow the following code
      // hashMap(keys) foreach { callback(record) }
      def foreach(f: Record => Rep[Unit]): Rep[Unit] = {
        val bucketNumber = lookup(keyFields)
        val numberOfRecords = bucketStatus(bucketNumber)
        val offset = bucketNumber * bucketSize
        for (i <- offset until (offset + numberOfRecords): Rep[Range]) {
          f(Record(valuesBuffer(i), valueSchema))
        }
        /*
         TODO: Why we cannot do this?
        for (i <- offset until (offset + numberOfRecords): Rep[Range]) yield {
          Record(valuesBuffer(i), valueSchema)
        }
        */
      }
    }
  }

  class LB2ParHashMap(numberOfThreads: Int, keySchema: Schema, valueSchema: Schema) {
    val partitionSize = (1 << 20)
    val size = partitionSize * numberOfThreads
    val keys = new ColumnarRecordBuffer(keySchema, size)
    val vals = new ColumnarRecordBuffer(valueSchema, size)
    val used = NewArray[Boolean](size)
    for (i <- 0 until size: Rep[Range]) {
      used(i) = false
    }
    val hashMap = NewArray[Int](size)
    val next = NewArray[Int](numberOfThreads)
    for (i <- 0 until numberOfThreads: Rep[Range]) {
      next(i) = i * partitionSize
    }

    def update(partitionNumber: Rep[Int])(keyFields: Fields, init: Fields)(updateFunction: Fields => Fields) = {
      // Use like this
      // hm.update(valuesAsKey, initFields){ currentFields => aggregate(currentFields, record) }
      // hm.foreach { record => do_something(record) }

      val index = lookup(partitionNumber)(keyFields)
      if (used(index)) { // if the entry is empty
        vals(index) = updateFunction(vals(index))
      } else {
        hashMap(next(partitionNumber)) = index
        next(partitionNumber) = next(partitionNumber) + 1
        keys(index) = keyFields
        vals(index) = updateFunction(init)
        used(index) = true
      }
    }

    def lookup(partitionNumber: Rep[Int])(keyFields: Fields): Rep[Int] = {
      val offset = partitionNumber * partitionSize
      var index = offset + (fieldsHash(keyFields) % partitionSize)
      while (used(index) && !fieldsEqual(keys(index), keyFields)) {
        index = index + 1
      }
      if (index - offset == partitionSize - 1) {
        println("Partition is full.") // TODO: Handle this case correctly
        exits(1)
      }
      index
    }

    def foreach(partitionNumber: Rep[Int])(f: Record => Rep[Unit]) = {
      val offset = partitionNumber * partitionSize
      for (i <- offset until next(partitionNumber)) {
        val index = hashMap(i)
        f(Record(keys(index) ++ vals(index), keySchema ++ valueSchema))
      }
    }
  }

  class SortBuffer(schema: Schema, size: Int) {
    val buffer = new ColumnarRecordBuffer(schema, size)
    val sortMap = NewArray[Int](size)
    var len = var_new(0)

    def add(record: Record) = {
      buffer(len) = record.fields
      sortMap(len) = len
      len += 1
    }

    def compare(a: Record, b: Record, keys: Seq[String]): Rep[Boolean] = {
      var i = var_new(0)
      val ltBuffer = NewArray[Boolean](keys.length)
      val eqBuffer = NewArray[Boolean](keys.length)
      keys foreach { key =>
        ltBuffer(i) = a(key) isLt b(key)
        eqBuffer(i) = a(key) isEquals b(key)
        i += 1
      }
      /* Do following comparison using loops with LMS
      keys.length match {
        case 1 => ltBuffer(0)
        case 2 => ltBuffer(0) || (eqBuffer(0) && ltBuffer(1))
        case 3 => ltBuffer(0) || (eqBuffer(0) && ltBuffer(1)) || (eqBuffer(0) && eqBuffer(1) && ltBuffer(2))
      }
       */
      var flag: Rep[Boolean] = false
      for (i <- 0 until keys.length: Range) {
        var eqFlag: Rep[Boolean] = true
        for (j <- 0 until i: Range) {
          eqFlag = eqFlag && eqBuffer(j)
        }
        flag = flag || (ltBuffer(i) && eqFlag)
      }
      flag
    }

    def sort(keys: Seq[String]): Rep[Unit] = {
      for (i <- 1 until len: Rep[Range]) {
        var j = i: Rep[Int]
        while (j > 0 && compare(Record(buffer(sortMap(j)), schema), Record(buffer(sortMap(j-1)), schema), keys)) {
          val tmp =  sortMap(j)
          sortMap(j) = sortMap(j-1)
          sortMap(j-1) = tmp
          j -= 1
        }
      }
    }

    def foreach(f: Record => Rep[Unit]) = {
      for (i <- 0 until len) {
        val index = sortMap(i)
        f(Record(buffer(index), schema))
      }
    }
  }

  abstract class ColumnarBuffer
  case class IntColumnarBuffer(data: Rep[Array[Int]]) extends ColumnarBuffer
  case class DoubleColumnarBuffer(data: Rep[Array[Double]]) extends ColumnarBuffer
  case class StringColumnarBuffer(data: Rep[Array[String]], len: Rep[Array[Int]]) extends ColumnarBuffer
  case class DateColumnarBuffer(year: Rep[Array[Int]], month: Rep[Array[Int]], day: Rep[Array[Int]]) extends ColumnarBuffer
  case class AverageColumnarBuffer(data: Rep[Array[Double]], count: Rep[Array[Int]]) extends ColumnarBuffer

  class ColumnarRecordBuffer(schema: Schema, size: Int) {
    val columns = schema.map {
      case IntAttribute(_) => IntColumnarBuffer(NewArray[Int](size))
      case DoubleAttribute(_) => DoubleColumnarBuffer(NewArray[Double](size))
      case StringAttribute(_) => StringColumnarBuffer(NewArray[String](size), NewArray[Int](size))
      case DateAttribute(_) => DateColumnarBuffer(NewArray[Int](size), NewArray[Int](size), NewArray[Int](size))
      case AverageAttribute(_) => AverageColumnarBuffer(NewArray[Double](size), NewArray[Int](size))
    }

    // TODO: What is this doing?
    //    var len = 0
    //    def +=(x: Fields) = {
    //      this(len) = x
    //      len += 1
    //    }
    def update(index: Rep[Int], fields: Fields) = (columns, fields).zipped.foreach {
      // For each pair of buffer and value, call update method of raw array buffer.
      // Note that the value is wrapped by type Field such as IntField(3)
      case (IntColumnarBuffer(arrayBuffer), IntField(value)) => arrayBuffer(index) = value
      case (DoubleColumnarBuffer(arrayBuffer), DoubleField(value)) => arrayBuffer(index) = value
      case (StringColumnarBuffer(stringArray, lengthArray), StringField(value, length)) =>
        stringArray(index) = value
        lengthArray(index) = length
      case (DateColumnarBuffer(yearArray, monthArray, dayArray), DateField(year, month, day)) =>
        yearArray(index) = year
        monthArray(index) = month
        dayArray(index) = day
      case (AverageColumnarBuffer(sumArray, countArray), AverageField(sum, count)) =>
        sumArray(index) = sum
        countArray(index) = count
    }

    def apply(index: Rep[Int]) = columns.map {
      case IntColumnarBuffer(arrayBuffer) => IntField(arrayBuffer(index))
      case DoubleColumnarBuffer(arrayBuffer) => DoubleField(arrayBuffer(index))
      case StringColumnarBuffer(stringArray, lengthArray) => StringField(stringArray(index), lengthArray(index))
      case DateColumnarBuffer(yearArray, monthArray, dayArray) => DateField(yearArray(index), monthArray(index), dayArray(index))
      case AverageColumnarBuffer(sumArray, countArray) => AverageField(sumArray(index), countArray(index))
    }
  }

}
