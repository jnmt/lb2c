package lb2c

import scala.util.parsing.combinator.JavaTokenParsers

trait OpParser extends JavaTokenParsers {
  type Schema = Vector[Attribute]
  type Values = Vector[Value]

  abstract class Operator
  case class PrintOp(childOp: Operator) extends Operator
  case class ScanOp(tableName: String, schema: Schema, delimiter: Char) extends Operator
  case class ProjectOp(childOp: Operator, attributes: Seq[String]) extends Operator
  case class FilterOp(childOp: Operator, predicate: Seq[Predicate]) extends Operator
  case class NestedLoopJoinOp(leftChild: Operator, rightChild: Operator, leftAttr: String, rightAttr: String) extends Operator
  case class HashJoinOp(leftChild: Operator, rightChild: Operator, leftAttr: String, rightAttr: String) extends Operator
  case class AggregateOp(childOp: Operator, keys: Seq[String], functions: Seq[AggregateFunction]) extends Operator
  case class SortOp(childOp: Operator, attributes: Seq[String]) extends Operator

  abstract class AggregateFunction
  case class Count() extends AggregateFunction
  case class Max(attribute: String) extends AggregateFunction
  case class Min(attribute: String) extends AggregateFunction
  case class Sum(attribute: String) extends AggregateFunction
  case class Average(attribute: String) extends AggregateFunction

  abstract class Predicate
  case class Eq(a: String, b: Value) extends Predicate
  case class Gte(a: String, b: Value) extends Predicate
  case class Lte(a: String, b: Value) extends Predicate
  case class Gt(a: String, b: Value) extends Predicate
  case class Lt(a: String, b: Value) extends Predicate

  abstract class Term
  abstract class Attribute extends Term { val name: String }
  abstract class Value extends Term { val value: Any }

  case class IntAttribute(name: String) extends Attribute
  case class DoubleAttribute(name: String) extends Attribute
  case class StringAttribute(name: String) extends Attribute

  case class IntValue(value: Int) extends Value
  case class DoubleValue(value: Double) extends Value
  case class StringValue(value: String) extends Value

  def Schema(schema: Seq[String]): Schema = schema.map(StringAttribute(_)).toVector // FIXME: This drops type info
  def Value(valueSeq: Seq[Value]): Values = valueSeq.toVector
  /*
  // some smart constructors
  def Scan(tableName: String): Scan = Scan(tableName, None, None)
  def Scan(tableName: String, schema: Option[Schema], delim: Option[Char]): Scan
   */

  def query: Parser[Operator] = printOperator | relationalOperator ^^ {
    case op => op
  }

  def relationalOperator: Parser[Operator] = operatorExceptForProject | projectOperator ^^ {
    case op => op
  }

  def operatorExceptForProject: Parser[Operator] =
    scanOperator | filterOperator | joinOperator | aggregateOperator | sortOperator ^^ {
      case op => op
    }

  def printOperator: Parser[Operator] = "Print" ~> "(" ~> relationalOperator <~ ")" ^^ {
    case op => PrintOp(op)
  }

  def projectOperator: Parser[Operator] = "Project" ~> "(" ~> operatorExceptForProject ~ "," ~ attributeList <~ ")" ^^ {
    case relation ~ "," ~ attrList => ProjectOp(relation, attrList.toVector)
  }

  def scanOperator: Parser[Operator] = "Scan" ~> "(" ~> tableIdentifier ~ "," ~ attributeWithTypeList <~ ")" ^^ {
    case table ~ _ ~ attrList => ScanOp(table, attrList.toVector, '|')
  }

  def filterOperator: Parser[Operator] = "Filter" ~> "(" ~> operatorExceptForProject ~ "," ~ predicates <~ ")" ^^ {
    case relation ~ _ ~ predicates => FilterOp(relation, predicates)
  }

  def joinOperator: Parser[Operator] = nestedLoopJoinOperator | hashJoinOperator

  def nestedLoopJoinOperator: Parser[Operator] = ("Join" | "NestedLoopJoin") ~>
    "(" ~> operatorExceptForProject ~ "," ~ operatorExceptForProject ~
    "," ~ attributeIdentifier ~ "," ~  attributeIdentifier <~ ")" ^^ {
      case leftOp ~ _ ~ rightOp ~ _ ~ leftAttr ~ _ ~ rightAttr => NestedLoopJoinOp(leftOp, rightOp, leftAttr, rightAttr)
    }

  def hashJoinOperator: Parser[Operator] =
    "HashJoin" ~> "(" ~> operatorExceptForProject ~ "," ~ operatorExceptForProject <~ ")" ^^ {
      case leftOp ~ _ ~ rightOp => HashJoinOp(leftOp, rightOp, "", "")
    }

  def aggregateOperator: Parser[Operator] =
    "Aggregate" ~> "(" ~> operatorExceptForProject ~ "," ~ keyAttributes ~ "," ~ aggregateFunctions <~ ")" ^^ {
      case relation ~ _ ~ attrList ~ _ ~ aggFunctions => AggregateOp(relation, attrList.toVector, aggFunctions)
    }

  def sortOperator: Parser[Operator] = "Sort" ~> "(" ~> operatorExceptForProject ~ "," ~ attributeList <~ ")" ^^ {
    case relation ~ "," ~ attrList => SortOp(relation, attrList)
  }

  def aggregateFunctions: Parser[Seq[AggregateFunction]] = repsep(aggregateFunction, ",")

  def aggregateFunction: Parser[AggregateFunction] =
    "count" ~> "(" ~> "*" <~ ")" ^^ { _ => Count() } |
      "max" ~> "(" ~> attributeIdentifier <~ ")" ^^ { case attribute => Max(attribute) } |
      "min" ~> "(" ~> attributeIdentifier <~ ")" ^^ { case attribute => Min(attribute) } |
      "sum" ~> "(" ~> attributeIdentifier <~ ")" ^^ { case attribute => Sum(attribute) } |
      "avg" ~> "(" ~> attributeIdentifier <~ ")" ^^ { case attribute => Average(attribute) }

  def predicates: Parser[Seq[Predicate]] = repsep(predicate, "and")

  def predicate: Parser[Predicate] =
    leftTerm ~ "="  ~ rightTerm ^^ { case a ~ _ ~ b => Eq(a, b)  } |
    leftTerm ~ ">=" ~ rightTerm ^^ { case a ~ _ ~ b => Gte(a, b) } |
    leftTerm ~ "<=" ~ rightTerm ^^ { case a ~ _ ~ b => Lte(a, b) } |
    leftTerm ~ ">"  ~ rightTerm ^^ { case a ~ _ ~ b => Gt(a, b)  } |
    leftTerm ~ "<"  ~ rightTerm ^^ { case a ~ _ ~ b => Lt(a, b)  }

  def leftTerm: Parser[String] = attributeIdentifier

  def rightTerm: Parser[Value] =
    strippedStringLiteral ^^ { case x => StringValue(x)    } |
    decimalNumber         ^^ { case x => IntValue(x.toInt) } |
    floatingPointNumber   ^^ { case x => DoubleValue(x.toDouble) }

  def strippedStringLiteral: Parser[String] = stringLiteral ^^ { _ drop 1 dropRight 1 }

  def tableIdentifier: Parser[String] = strippedStringLiteral

  def attributeWithTypeList: Parser[Seq[Attribute]] = repsep(attributeWithType, ",")

  def attributeWithType: Parser[Attribute] = ident ~ attributeIdentifier ^^ {
    case "int" ~ name => IntAttribute(name)
    case "double" ~ name => DoubleAttribute(name)
    case "string" ~ name => StringAttribute(name)
  }

  def keyAttributes: Parser[Seq[String]] = "keys" ~> "(" ~> repsep(attributeIdentifier, ",") <~ ")"

  def attributeList: Parser[Seq[String]] = repsep(attributeIdentifier, ",")

  def attributeIdentifier: Parser[String] = ident

  def apply(input: String): Either[String, Any] = parseAll(query, input) match {
    case Success(x, _)   => Right(x)
    case NoSuccess(_, _) => Left(s"Parse error")
  }

}
