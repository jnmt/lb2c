package lb2c

import java.util.Calendar
import java.text.DateFormat

trait OpParser {
  type Schema = Vector[Attribute]

  abstract class Operator
  case class PrintOp(childOp: Operator) extends Operator
  case class ScanOp(tableName: String, schema: Schema, delimiter: Char) extends Operator
  case class ProjectOp(childOp: Operator, attributes: Seq[String]) extends Operator
  case class FilterOp(childOp: Operator, predicate: Seq[Predicate]) extends Operator
  case class NestedLoopJoinOp(leftChild: Operator, rightChild: Operator, leftAttr: String, rightAttr: String) extends Operator
  case class HashJoinOp(leftChild: Operator, rightChild: Operator, leftAttr: String, rightAttr: String) extends Operator
  case class AggregateOp(childOp: Operator, keys: Seq[String], functions: Seq[AggregateFunction]) extends Operator
  case class SortOp(childOp: Operator, attributes: Seq[String]) extends Operator
  case class CalculateOp(childOp: Operator, expressions: Seq[RootArithmeticOp]) extends Operator
  case class CaseWhenOp(childOp: Operator, predicates: Seq[Predicate], a: Term, b: Term, alias: String) extends Operator
  // SIMD
  case class FilterVOp(childOp: Operator, predicate: Seq[Predicate]) extends Operator

  abstract class ArithmeticOperator
  case class RootArithmeticOp(child: ArithmeticOperator, alias: String) extends ArithmeticOperator
  case class AddOp(leftChild: ArithmeticOperator, rightChild: ArithmeticOperator) extends ArithmeticOperator
  case class SubOp(leftChild: ArithmeticOperator, rightChild: ArithmeticOperator) extends ArithmeticOperator
  case class MultiplyOp(leftChild: ArithmeticOperator, rightChild: ArithmeticOperator) extends ArithmeticOperator
  case class DivideOp(leftChild: ArithmeticOperator, rightChild: ArithmeticOperator) extends ArithmeticOperator
  case class ParenthesizedOp(child: ArithmeticOperator) extends ArithmeticOperator
  case class AttributeOp(attribute: String) extends ArithmeticOperator
  case class ValueOp(v: Value) extends ArithmeticOperator

  abstract class AggregateFunction
  case class Count() extends AggregateFunction
  case class Max(attribute: String) extends AggregateFunction
  case class Min(attribute: String) extends AggregateFunction
  case class Sum(attribute: String) extends AggregateFunction
  case class Average(attribute: String) extends AggregateFunction

  abstract class Term
  abstract class Attribute extends Term { val name: String }
  case class IntAttribute(name: String) extends Attribute
  case class DoubleAttribute(name: String) extends Attribute
  case class StringAttribute(name: String) extends Attribute
  case class DateAttribute(name: String) extends Attribute
  case class AverageAttribute(name: String) extends Attribute
  case class AnyAttribute(name: String) extends Attribute

  case class Value(x: Any) extends Term

  abstract class Predicate
  case class Eq(a: Attribute, b: Value) extends Predicate
  case class Gte(a: Attribute, b: Value) extends Predicate
  case class Lte(a: Attribute, b: Value) extends Predicate
  case class Gt(a: Attribute, b: Value) extends Predicate
  case class Lt(a: Attribute, b: Value) extends Predicate
  case class Like(a: Attribute, b: Value) extends Predicate

  /*
  // some smart constructors
  def Scan(tableName: String): Scan = Scan(tableName, None, None)
  def Scan(tableName: String, schema: Option[Schema], delim: Option[Char]): Scan
   */

  def parseQuery(input: String) = Grammar.parseAll(input)

  import scala.util.parsing.combinator._
  object Grammar extends JavaTokenParsers { // JavaTokenParsers must be capsuled, or get some overriding error

    def query: Parser[Operator] = printOperator | relationalOperator ^^ {
      case op => op
    }

    def relationalOperator: Parser[Operator] = operatorExceptForProject | projectOperator ^^ {
      case op => op
    }

    def operatorExceptForProject: Parser[Operator] =
      scanOperator | filterOperator | joinOperator | aggregateOperator | sortOperator | calculateOperator | caseWhenOperator ^^ {
        case op => op
      }

    def printOperator: Parser[Operator] = "Print" ~> "(" ~> relationalOperator <~ ")" ^^ {
      case op => PrintOp(op)
    }

    def projectOperator: Parser[Operator] = "Project" ~> "(" ~> operatorExceptForProject ~ "," ~ attributeList <~ ")" ^^ {
      case relation ~ "," ~ attrList => ProjectOp(relation, attrList.toVector)
    }

    def calculateOperator: Parser[Operator] = "Calculate" ~> "(" ~> operatorExceptForProject ~ "," ~ attributeExpList <~ ")" ^^ {
      case relation ~ "," ~ attrExpList => CalculateOp(relation, attrExpList.toVector)
    }

    def caseWhenOperator: Parser[Operator] = "CaseWhen" ~> "(" ~> operatorExceptForProject ~ "," ~ predicates ~ "then" ~ attributeOrValue ~ "else" ~ attributeOrValue ~ "as" ~ ident <~ ")" ^^ {
      case relation ~ "," ~ predicates ~ "then" ~ a ~ "else" ~ b ~ "as" ~ alias => CaseWhenOp(relation, predicates, a, b, alias)
    }

    def scanOperator: Parser[Operator] = "Scan" ~> "(" ~> tableIdentifier ~ "," ~ attributeWithTypeList <~ ")" ^^ {
      case table ~ _ ~ attrList => ScanOp(table, attrList.toVector, '|')
    }

    def filterOperator: Parser[Operator] = filterScalarOperator | filterVectorOperator

    def filterScalarOperator: Parser[Operator] = "Filter" ~> "(" ~> operatorExceptForProject ~ "," ~ predicates <~ ")" ^^ {
      case relation ~ _ ~ predicates => FilterOp(relation, predicates)
    }

    def filterVectorOperator: Parser[Operator] = "FilterV" ~> "(" ~> operatorExceptForProject ~ "," ~ predicates <~ ")" ^^ {
      case relation ~ _ ~ predicates => FilterVOp(relation, predicates)
    }

    def joinOperator: Parser[Operator] = nestedLoopJoinOperator | hashJoinOperator

    def nestedLoopJoinOperator: Parser[Operator] = ("Join" | "NestedLoopJoin") ~>
      "(" ~> operatorExceptForProject ~ "," ~ operatorExceptForProject ~
      "," ~ attributeIdentifier ~ "," ~ attributeIdentifier <~ ")" ^^ {
      case leftOp ~ _ ~ rightOp ~ _ ~ leftAttr ~ _ ~ rightAttr => NestedLoopJoinOp(leftOp, rightOp, leftAttr, rightAttr)
    }

    def hashJoinOperator: Parser[Operator] = "HashJoin" ~>
      "(" ~> operatorExceptForProject ~ "," ~ operatorExceptForProject ~
      "," ~ attributeIdentifier ~ "," ~ attributeIdentifier <~ ")" ^^ {
        case leftOp ~ _ ~ rightOp ~ _ ~ leftAttr ~ _ ~ rightAttr => HashJoinOp(leftOp, rightOp, leftAttr, rightAttr)
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
        "max" ~> "(" ~> attributeIdentifier <~ ")" ^^ { attribute => Max(attribute) } |
        "min" ~> "(" ~> attributeIdentifier <~ ")" ^^ { attribute => Min(attribute) } |
        "sum" ~> "(" ~> attributeIdentifier <~ ")" ^^ { attribute => Sum(attribute) } |
        "avg" ~> "(" ~> attributeIdentifier <~ ")" ^^ { attribute => Average(attribute) }

    def predicates: Parser[Seq[Predicate]] = repsep(predicate, "and")

    def predicate: Parser[Predicate] =
      attribute ~ "=" ~ value ^^ { case a ~ _ ~ b => Eq(a, b) } |
        attribute ~ ">=" ~ value ^^ { case a ~ _ ~ b => Gte(a, b) } |
        attribute ~ "<=" ~ value ^^ { case a ~ _ ~ b => Lte(a, b) } |
        attribute ~ ">" ~ value ^^ { case a ~ _ ~ b => Gt(a, b) } |
        attribute ~ "<" ~ value ^^ { case a ~ _ ~ b => Lt(a, b) } |
        attribute ~ "like" ~ value ^^ { case a ~ _ ~ b => Like(a, b) }

    def attributeOrValue: Parser[Term] = attribute | value

    def attribute: Parser[Attribute] = attributeIdentifier ^^ { x => AnyAttribute(x) }

    def value: Parser[Value] = doubleValue | intValue | dateValue | strippedStringLiteral ^^ { s => Value(s) }

    def intValue: Parser[Value] = """[0-9]+""".r ^^ { s => Value(s.toInt) }

    def doubleValue: Parser[Value] = """[0-9]*\.[0-9]+""".r ^^ { s => Value(s.toDouble) }

    def dateValue: Parser[Value] = """\"\d{4}-\d{1,2}-\d{1,2}\"""".r ^^ {
      case s =>
        val calendar = Calendar.getInstance
        calendar.setTime(DateFormat.getDateInstance().parse(s drop 1 dropRight 1 replace("-", "/")))
        Value(calendar)
    }

    def strippedStringLiteral: Parser[String] = stringLiteral ^^ {
      _ drop 1 dropRight 1
    }

    def tableIdentifier: Parser[String] = strippedStringLiteral

    def attributeWithTypeList: Parser[Seq[Attribute]] = repsep(attributeWithType, ",")

    def attributeWithType: Parser[Attribute] = ident ~ attributeIdentifier ^^ {
      case "int" ~ name => IntAttribute(name)
      case "double" ~ name => DoubleAttribute(name)
      case "string" ~ name => StringAttribute(name)
      case "date" ~ name => DateAttribute(name)
    }

    def keyAttributes: Parser[Seq[String]] = "keys" ~> "(" ~> repsep(attributeIdentifier, ",") <~ ")"

    def attributeList: Parser[Seq[String]] = repsep(attributeIdentifier, ",")

    def attributeIdentifier: Parser[String] = ident

    def attributeExpList: Parser[Seq[RootArithmeticOp]] = repsep(attributeExpressionWithAlias, ",")

    def attributeExpressionWithAlias: Parser[RootArithmeticOp] = attributeExpression ~ "as" ~ ident ^^ {
      case root ~ _ ~ alias =>  RootArithmeticOp(root, alias)
    }

    def attributeExpression: Parser[ArithmeticOperator] = term ~ rep("+"~term | "-"~term) ^^ {
      case opr ~ terms => {
        var operand = opr
        terms.foreach {
          l => l match {
            case "+" ~ t => { operand = AddOp(operand, t) }
            case "-" ~ t => { operand = SubOp(operand, t) }
          }
        }
        operand
      }
    }

    def term: Parser[ArithmeticOperator] = factor ~ rep("*"~factor | "/"~factor) ^^ {
      case opr ~ factors => {
        var operand = opr
        factors.foreach {
          l => l match {
            case "*" ~ f => { operand = MultiplyOp(operand, f) }
            case "/" ~ f => { operand = DivideOp(operand, f) }
          }
        }
        operand
      }
    }

    def factor: Parser[ArithmeticOperator] = attributeOp | valueOp | parenthesizedOp

    def attributeOp: Parser[ArithmeticOperator] = attributeIdentifier ^^ { x => AttributeOp(x) }

    def valueOp: Parser[ArithmeticOperator] = value ^^ { x => ValueOp(x) }

    def parenthesizedOp: Parser[ArithmeticOperator] = "(" ~> attributeExpression <~ ")" ^^ { x => ParenthesizedOp(x) }

    def parseAll(input: String): Operator = parseAll(query, input) match {
      case Success(x, _) => x
      case x => throw new Exception(x.toString)
    }

  }

}
