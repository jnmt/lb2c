package lb2c

import scala.lms.common._
import scala.reflect.SourceContext

// should this be added to LMS?
trait UtilOps extends Base { this: Dsl =>
  def infix_HashCode[T:Typ](o: Rep[T])(implicit pos: SourceContext): Rep[Long]
  def infix_HashCode(o: Rep[String], len: Rep[Int])(implicit v: Overloaded1, pos: SourceContext): Rep[Long]
}
trait UtilOpsExp extends UtilOps with BaseExp { this: DslExp =>
  case class ObjHashCode[T:Typ](o: Rep[T])(implicit pos: SourceContext) extends Def[Long] { def m = typ[T] }
  case class StrSubHashCode(o: Rep[String], len: Rep[Int])(implicit pos: SourceContext) extends Def[Long]
  def infix_HashCode[T:Typ](o: Rep[T])(implicit pos: SourceContext) = ObjHashCode(o)
  def infix_HashCode(o: Rep[String], len: Rep[Int])(implicit v: Overloaded1, pos: SourceContext) = StrSubHashCode(o,len)

  override def mirror[A:Typ](e: Def[A], f: Transformer)(implicit pos: SourceContext): Exp[A] = (e match {
    case e@ObjHashCode(a) => infix_HashCode(f(a))(e.m,pos)
    case e@StrSubHashCode(o,len) => infix_HashCode(f(o),f(len))
    case _ => super.mirror(e,f)
  }).asInstanceOf[Exp[A]]
}
trait ScalaGenUtilOps extends ScalaGenBase {
  val IR: UtilOpsExp
  import IR._

  override def emitNode(sym: Sym[Any], rhs: Def[Any]) = rhs match {
    case ObjHashCode(o) => emitValDef(sym, src"$o.##")
    case _ => super.emitNode(sym, rhs)
  }
}
trait CGenUtilOps extends CGenBase {
  val IR: UtilOpsExp
  import IR._

  override def emitNode(sym: Sym[Any], rhs: Def[Any]) = rhs match {
    case StrSubHashCode(o,len) => emitValDef(sym, src"hash($o,$len)")
    case _ => super.emitNode(sym, rhs)
  }
}


trait Dsl extends PrimitiveOps with NumericOps with BooleanOps
  with LiftString with LiftPrimitives with LiftNumeric with LiftBoolean with IfThenElse with Equal with RangeOps
  with OrderingOps with MiscOps with ArrayOps with StringOps with SeqOps with Functions with While
  with StaticData with Variables with LiftVariables with ObjectOps with UtilOps with SIMDVectorOps {
  implicit def repStrToSeqOps(a: Rep[String]) = new SeqOpsCls(a.asInstanceOf[Rep[Seq[Char]]])
  override def infix_&&(lhs: Rep[Boolean], rhs: => Rep[Boolean])(implicit pos: scala.reflect.SourceContext): Rep[Boolean] =
    __ifThenElse(lhs, rhs, unit(false))
  def generate_comment(l: String): Rep[Unit]
  def comment[A:Typ](l: String, verbose: Boolean = true)(b: => Rep[A]): Rep[A]
  def single(b: => Rep[Unit]): Rep[Unit]
  def parallel(b: => Rep[Unit]): Rep[Unit]
  def parallel_for(b: => Rep[Unit]): Rep[Unit]
  def task(b: => Rep[Unit]): Rep[Unit]
  def task_wait(b: => Rep[Unit]): Rep[Unit]
  def critical(b: => Rep[Unit]): Rep[Unit]
  def barrier(b: => Rep[Unit]): Rep[Unit]
  def time(b: => Rep[Unit]): Rep[Unit]
}

trait DslExp extends Dsl with PrimitiveOpsExpOpt with NumericOpsExpOpt with BooleanOpsExp
  with IfThenElseExpOpt with EqualExpBridgeOpt with RangeOpsExp with OrderingOpsExp with MiscOpsExp
  with EffectExp with ArrayOpsExpOpt with StringOpsExp with SeqOpsExp with FunctionsRecursiveExp with WhileExp
  with StructExp
  with StaticDataExp with VariablesExpOpt with ObjectOpsExpOpt with UtilOpsExp with SIMDVectorExp {

  override def boolean_or(lhs: Exp[Boolean], rhs: Exp[Boolean])(implicit pos: SourceContext) : Exp[Boolean] = lhs match {
    case Const(false) => rhs
    case _ => super.boolean_or(lhs, rhs)
  }
  override def boolean_and(lhs: Exp[Boolean], rhs: Exp[Boolean])(implicit pos: SourceContext) : Exp[Boolean] = lhs match {
    case Const(true) => rhs
    case _ => super.boolean_and(lhs, rhs)
  }

  case class GenerateComment(l: String) extends Def[Unit]
  def generate_comment(l: String) = reflectEffect(GenerateComment(l))
  case class Comment[A:Typ](l: String, verbose: Boolean, b: Block[A]) extends Def[A]
  def comment[A:Typ](l: String, verbose: Boolean)(b: => Rep[A]): Rep[A] = {
    val br = reifyEffects(b)
    val be = summarizeEffects(br)
    reflectEffect[A](Comment(l, verbose, br), be)
  }

  case class Single(b: Block[Unit]) extends Def[Unit]
  def single(b: => Rep[Unit]): Rep[Unit] = {
    val br = reifyEffects(b)
    val be = summarizeEffects(br)
    reflectEffect[Unit](Single(br), be)
  }

  case class Parallel(b: Block[Unit]) extends Def[Unit]
  def parallel(b: => Rep[Unit]): Rep[Unit] = {
    val br = reifyEffects(b)
    val be = summarizeEffects(br)
    reflectEffect[Unit](Parallel(br), be)
  }

  case class ParallelFor(b: Block[Unit]) extends Def[Unit]
  def parallel_for(b: => Rep[Unit]): Rep[Unit] = {
    val br = reifyEffects(b)
    val be = summarizeEffects(br)
    reflectEffect[Unit](ParallelFor(br), be)
  }

  case class Task(b: Block[Unit]) extends Def[Unit]
  def task(b: => Rep[Unit]): Rep[Unit] = {
    val br = reifyEffects(b)
    val be = summarizeEffects(br)
    reflectEffect[Unit](Task(br), be)
  }

  case class TaskWait(b: Block[Unit]) extends Def[Unit]
  def task_wait(b: => Rep[Unit]): Rep[Unit] = {
    val br = reifyEffects(b)
    val be = summarizeEffects(br)
    reflectEffect[Unit](TaskWait(br), be)
  }

  case class Critical(b: Block[Unit]) extends Def[Unit]
  def critical(b: => Rep[Unit]): Rep[Unit] = {
    val br = reifyEffects(b)
    val be = summarizeEffects(br)
    reflectEffect[Unit](Critical(br), be)
  }

  case class Barrier(b: Block[Unit]) extends Def[Unit]
  def barrier(b: => Rep[Unit]): Rep[Unit] = {
    val br = reifyEffects(b)
    val be = summarizeEffects(br)
    reflectEffect[Unit](Barrier(br), be)
  }

  case class Time(b: Block[Unit]) extends Def[Unit]
  def time(b: => Rep[Unit]): Rep[Unit] = {
    val br = reifyEffects(b)
    val be = summarizeEffects(br)
    reflectEffect[Unit](Time(br), be)
  }

  override def boundSyms(e: Any): List[Sym[Any]] = e match {
    case Comment(_, _, b) => effectSyms(b)
    case Single(b) => effectSyms(b)
    case Parallel(b) => effectSyms(b)
    case ParallelFor(b) => effectSyms(b)
    case Task(b) => effectSyms(b)
    case TaskWait(b) => effectSyms(b)
    case Critical(b) => effectSyms(b)
    case Barrier(b) => effectSyms(b)
    case Time(b) => effectSyms(b)
    case _ => super.boundSyms(e)
  }

  override def array_apply[T:Typ](x: Exp[Array[T]], n: Exp[Int])(implicit pos: SourceContext): Exp[T] = (x,n) match {
    case (Def(StaticData(x:Array[T])), Const(n)) =>
      val y = x(n)
      if (y.isInstanceOf[Int]) unit(y) else staticData(y)
    case _ => super.array_apply(x,n)
  }

  // TODO: should this be in LMS?
  override def isPrimitiveType[T](m: Typ[T]) = (m == manifest[String]) || super.isPrimitiveType(m)
}
trait DslGen extends ScalaGenNumericOps
    with ScalaGenPrimitiveOps with ScalaGenBooleanOps with ScalaGenIfThenElse
    with ScalaGenEqual with ScalaGenRangeOps with ScalaGenOrderingOps
    with ScalaGenMiscOps with ScalaGenArrayOps with ScalaGenStringOps
    with ScalaGenSeqOps with ScalaGenFunctions with ScalaGenWhile
    with ScalaGenStaticData with ScalaGenVariables
    with ScalaGenObjectOps
    with ScalaGenUtilOps {
  val IR: DslExp

  import IR._

  override def quote(x: Exp[Any]) = x match {
    case Const('\n') if x.tp == typ[Char] => "'\\n'"
    case Const('\t') if x.tp == typ[Char] => "'\\t'"
    case Const(0)    if x.tp == typ[Char] => "'\\0'"
    case _ => super.quote(x)
  }
  override def emitNode(sym: Sym[Any], rhs: Def[Any]) = rhs match {
    case IfThenElse(c,Block(Const(true)),Block(Const(false))) =>
      emitValDef(sym, quote(c))
    case PrintF(f:String,xs) => 
      emitValDef(sym, src"printf(${Const(f)::xs})")
    case GenerateComment(s) =>
      stream.println("// "+s)
    case Comment(s, verbose, b) =>
      stream.println("val " + quote(sym) + " = {")
      stream.println("//#" + s)
      if (verbose) {
        stream.println("// generated code for " + s.replace('_', ' '))
      } else {
        stream.println("// generated code")
      }
      emitBlock(b)
      stream.println(quote(getBlockResult(b)))
      stream.println("//#" + s)
      stream.println("}")
    case _ => super.emitNode(sym, rhs)
  }
}
trait DslImpl extends DslExp { q =>
  val codegen = new DslGen {
    val IR: q.type = q
  }
}

trait CGenDataStruct extends CGenEffect {
  val IR: DslExp
  import IR._

  override def remap[A](m: Typ[A]) = m match {
    case ManifestTyp(s) if s <:< manifest[Record] => "struct " + structName(m)
    case _ => super.remap(m)
  }

  // TODO: Is this correct way? This is necessary to avoid adding '*' when matching FieldApply
  override def isPrimitiveType(tpe: String) : Boolean = true

  override def emitNode(sym: Sym[Any], rhs: Def[Any]) = rhs match {
    case Struct(tag, elems) =>
      val name = structName(sym.tp)
      registerStruct(name, elems)
      stream.println("struct " + name + " " + quote(sym)+ ";")
      elems.foreach( e => stream.println(quote(sym) + "." + e._1 + " = " + quote(e._2) + ";"))
    case FieldApply(struct, index) =>
      emitValDef(sym, quote(struct) + "." + index)
    case FieldUpdate(struct, index, rhs) =>
      emitValDef(sym, quote(struct) + "." + index + " = " + quote(rhs))
    case _ => super.emitNode(sym,rhs)
  }

  def structName[A](t: Typ[A]): String = {
    t match {
      // TODO: a little different LMS original
      case ManifestTyp(m) if (m <:< implicitly[Manifest[AnyRef]]) => "Anon" + math.abs(t.runtimeClass.##)
      case ManifestTyp(m) if (m <:< implicitly[Manifest[AnyVal]]) => m.toString
    }
  }

  override def emitDataStructures(ds: java.io.PrintWriter) {
    // Forward references to resolve dependencies
    val hm = new scala.collection.mutable.LinkedHashMap[String, Seq[(String, Typ[_])]]
    def hit(name: String, elements: Seq[(String, Typ[_])]): Unit = {
      elements foreach { element =>
        val elementName = structName(element._2)
        encounteredStructs.get(elementName).map(e => hit(elementName, e))
      }
      hm(name) = elements
    }
    encounteredStructs.foreach((hit _).tupled)

    //for ((name, elems) <- encounteredStructs) {
    for ((name, elems) <- hm) {
      ds.println("struct " + name + " {")
      for (e <- elems) ds.println(remap(e._2) + " " + e._1 + ";")
      ds.println("};")
    }
    super.emitDataStructures(ds)
  }
}

// TODO: currently part of this is specific to the query tests. generalize? move?
trait DslGenC extends CGenNumericOps
    with CGenPrimitiveOps with CGenBooleanOps with CGenIfThenElse
    with CGenEqual with CGenRangeOps with CGenOrderingOps
    with CGenMiscOps with CGenArrayOps with CGenStringOps
    with CGenSeqOps with CGenFunctions with CGenWhile
    with CGenStaticData with CGenVariables
    with CGenObjectOps
    with CGenSIMDOps
    with CGenDataStruct
    with CGenUtilOps {
  val IR: DslExp
  import IR._

  def getMemoryAllocString(count: String, memType: String): String = {
      "(" + memType + "*)malloc(" + count + " * sizeof(" + memType + "));"
  }
  override def remap[A](m: Typ[A]): String = {
    m match {
      case ArrayTyp(tp) => tp match {
        case ManifestTyp(s) if s <:< manifest[Char] => "char*"
        case ManifestTyp(s) if s <:< manifest[Record] => "struct " + structName(tp)
      }
      case _ => m.toString match {
        case "java.lang.String" => "char*"
        case "Array[Char]" => "char*"
        case "Char" => "char"
        case _ => super.remap(m)
      }
    }
  }

  override def format(s: Exp[Any]): String = {
    remap(s.tp) match {
      case "uint16_t" => "%c"
      case "bool" | "int8_t" | "int16_t" | "int32_t" => "%d"
      case "int64_t" => "%ld"
      case "float" | "double" => "%f"
      case "string" => "%s"
      case "char*" => "%s"
      case "char" => "%c"
      case "void" => "%c"
      case _ =>
        import scala.lms.internal.GenerationFailedException
        throw new GenerationFailedException("CGenMiscOps: cannot print type " + remap(s.tp))
    }
  }
  override def quoteRawString(s: Exp[Any]): String = {
    remap(s.tp) match {
      case "string" => quote(s) + ".c_str()"
      case _ => quote(s)
    }
  }
  // we treat string as a primitive type to prevent memory management on strings
  // strings are always stack allocated and freed automatically at the scope exit
  override def isPrimitiveType(tpe: String) : Boolean = {
    tpe match {
      case "char*" => true
      case "char" => true
      case _ => super.isPrimitiveType(tpe)
    }
  }

  override def quote(x: Exp[Any]) = x match {
    case Const(s: String) => "\""+s.replace("\"", "\\\"")+"\"" // TODO: more escapes?
    case Const('\n') if x.tp == typ[Char] => "'\\n'"
    case Const('\t') if x.tp == typ[Char] => "'\\t'"
    case Const(0)    if x.tp == typ[Char] => "'\\0'"
    case _ => super.quote(x)
  }
  override def emitNode(sym: Sym[Any], rhs: Def[Any]) = rhs match {
    case a@ArrayNew(n) =>
      val arrType = remap(a.m)
      stream.println(arrType + "* " + quote(sym) + " = " + getMemoryAllocString(quote(n), arrType))
    case ArrayApply(x,n) => emitValDef(sym, quote(x) + "[" + quote(n) + "]")
    case ArrayUpdate(x,n,y) => stream.println(quote(x) + "[" + quote(n) + "] = " + quote(y) + ";")
    case PrintLn(s) => stream.println("printf(\"" + format(s) + "\\n\"," + quoteRawString(s) + ");")
    case StringCharAt(s,i) => emitValDef(sym, "%s[%s]".format(quote(s), quote(i)))
    case Comment(s, verbose, b) =>
      stream.println("//#" + s)
      if (verbose) {
        stream.println("// generated code for " + s.replace('_', ' '))
      } else {
        stream.println("// generated code")
      }
      emitBlock(b)
      emitValDef(sym, quote(getBlockResult(b)))
      stream.println("//#" + s)
    case Single(b) =>
      stream.println("#pragma omp single")
      stream.println("{")
      emitBlock(b)
      stream.println("}")
    case Parallel(b) =>
      stream.println("#pragma omp parallel")
      stream.println("{")
      emitBlock(b)
      stream.println("}")
    case ParallelFor(b) =>
      stream.println("#pragma omp parallel for num_threads(NUM_THREADS)")
      emitBlock(b)
    case Task(b) =>
      stream.println("#pragma omp task default (shared)")
      stream.println("{")
      emitBlock(b)
      stream.println("}")
    case TaskWait(b) =>
      emitBlock(b)
      stream.println("#pragma omp taskwait")
    case Critical(b) =>
      stream.println("#pragma omp critical")
      stream.println("{")
      emitBlock(b)
      stream.println("}")
    case Barrier(b) =>
      stream.println("#pragma omp barrier")
      emitBlock(b)
    case Time(b) =>
      stream.println("struct timeval begin, end;")
      stream.println("begin = cur_time();")
      emitBlock(b)
      stream.println("end = cur_time();")
      stream.println("print_performance(begin, end);")
    case _ => super.emitNode(sym,rhs)
  }
  override def emitSource[A:Typ](args: List[Sym[_]], body: Block[A], functionName: String, out: java.io.PrintWriter) = {
    withStream(out) {
      stream.println("""
      #include <fcntl.h>
      #include <errno.h>
      #include <err.h>
      #include <immintrin.h>
      #include <omp.h>
      #include <sys/mman.h>
      #include <sys/stat.h>
      #include <sys/time.h>
      #include <stdbool.h>
      #include <stdio.h>
      #include <stdint.h>
      #include <string.h>
      #include <unistd.h>
      #include "snippet.h"
      #ifndef MAP_FILE
      #define MAP_FILE MAP_SHARED
      #endif
      #define MATCH 0
      #define NOMATCH 1
      #define NOWILDCARDMATCH 2
      #define CharRead(A) (*(A++))
      #define HASH_TABLE_SIZE (1<<22)
      #define BUCKET_SIZE (1<<8)
      #define NUM_THREADS 4
      int fsize(int fd) {
        struct stat stat;
        int res = fstat(fd,&stat);
        return stat.st_size;
      }
      int printll(char* s) {
        while (*s != '\n' && *s != ',' && *s != '|' && *s != '\t') {
          putchar(*s++);
        }
        return 0;
      }
      void print_performance(struct timeval begin, struct timeval end) {
        long diff = (end.tv_sec - begin.tv_sec) * 1000 * 1000
                  + (end.tv_usec - begin.tv_usec);
        if (diff > 1000) {
          printf("%ld.%ld ms\n", diff/1000, diff%1000);
        } else {
          printf("0.%ld ms\n", diff);
        }
      }
      struct timeval cur_time(void) {
        struct timeval t;
        gettimeofday(&t, NULL);
        return t;
      }
      int __pattern_compare(const char *s, const char *pattern) {
        char c;
        char c2;
        while ((c = CharRead(pattern)) != 0) {
          if (c == '%') {
            /* Skip over multiple "%" characters in the pattern. */
            while ((c = CharRead(pattern)) == '%')
              continue;
            if (c == 0) {
              return MATCH; /* "%" at the end of the pattern matches */
            }
            /* At this point variable c contains the first character of the
            ** pattern string past the "*".  Search in the input string for the
            ** first matching character and recursively continue the match from
            ** that point.
            */
            int match;
            char stop[4];
            stop[0] = c;
            stop[1] = '|';
            stop[2] = '\n';
            stop[3] = 0;
            while (1) {
              s += strcspn((const char *)s, stop);
              if (s[0] == '|' || s[0] == '\n' || s[0] == 0)
                break;
              s++;
              match = __pattern_compare(s, pattern);
              if (match != NOMATCH)
                return match;
            }
            return NOWILDCARDMATCH;
          }
          c2 = CharRead(s);
          if (c == c2)
            continue;
          return NOMATCH;
        }
        return (s[0] == '|' || s[0] == '\n' || s[0] == 0) ? MATCH : NOMATCH;
      }
      bool pattern_compare(const char *s, const char *pattern) {
        return __pattern_compare(s, pattern) == MATCH;
      }
      long hash(char *str0, int len)
      {
        unsigned char* str = (unsigned char*)str0;
        unsigned long hash = 5381;
        int c;

        while ((c = *str++) && len--)
          hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

        return hash;
      }
      //void Snippet(char*);
      void Snippet(int);
      int main(int argc, char *argv[])
      {
        /*
        if (argc != 2) {
          printf("usage: query <filename>\n");
          return 0;
        }
        */
        Snippet(0);
        return 0;
      }

      """)
    }
    super.emitSource[A](args, body, functionName, out)
    val ds = new java.io.PrintWriter("/tmp/snippet.h")
    emitDataStructures(ds)
    ds.flush
    ds.close
    Nil
  }
}


abstract class DslSnippet[A:Manifest,B:Manifest] extends Dsl {
  def snippet(x: Rep[A]): Rep[B]
}

abstract class DslDriver[A:Manifest,B:Manifest] extends DslSnippet[A,B] with DslImpl with CompileScala {
  lazy val f = compile(snippet)(manifestTyp[A],manifestTyp[B])
  def precompile: Unit = f
  def precompileSilently: Unit = utils.devnull(f)
  def eval(x: A): B = f(x)
  lazy val code: String = {
    val source = new java.io.StringWriter()
    codegen.emitSource(snippet, "Snippet", new java.io.PrintWriter(source))(manifestTyp[A],manifestTyp[B])
    source.toString
  }
}

abstract class DslDriverC[A:Manifest,B:Manifest] extends DslSnippet[A,B] with DslExp { q =>
  val codegen = new DslGenC {
    val IR: q.type = q
  }
  lazy val code: String = {
    implicit val mA = manifestTyp[A]
    implicit val mB = manifestTyp[B]
    val source = new java.io.StringWriter()
    codegen.emitSource(snippet, "Snippet", new java.io.PrintWriter(source))
    source.toString
  }
  def eval: Unit = { // TODO: jnmt: Clean up
    val out = new java.io.PrintWriter("/tmp/snippet.c")
    out.println(code)
    out.close
    //TODO: use precompile
    (new java.io.File("/tmp/snippet")).delete
    import scala.sys.process._
    (s"cc -std=c99 -O3 -Xpreprocessor -fopenmp -lomp /tmp/snippet.c -o /tmp/snippet":ProcessBuilder).lines.foreach(Console.println _)
    (s"/tmp/snippet":ProcessBuilder).lines.foreach(Console.println _)
  }
  def evalSIMD: Unit = { // TODO: jnmt: Clean up
    val out = new java.io.PrintWriter("/tmp/snippet.c")
    out.println(code)
    out.close
    //TODO: use precompile
    (new java.io.File("/tmp/snippet")).delete
    import scala.sys.process._
    (s"cc -std=c99 -O3 -Xpreprocessor -fopenmp -lomp -mavx512f -mavx512dq /tmp/snippet.c -o /tmp/snippet":ProcessBuilder).lines.foreach(Console.println _)
    (s"sde -skx -- /tmp/snippet":ProcessBuilder).lines.foreach(Console.println _) // Run snippet using emulator
  }
  /*
  def eval(a:A): Unit = { // TBD: should read result of type B?
    val out = new java.io.PrintWriter("/tmp/snippet.c")
    out.println(code)
    out.close
    //TODO: use precompile
    (new java.io.File("/tmp/snippet")).delete
    import scala.sys.process._
    (s"cc -std=c99 -O3 /tmp/snippet.c -o /tmp/snippet":ProcessBuilder).lines.foreach(Console.println _)
    (s"/tmp/snippet $a":ProcessBuilder).lines.foreach(Console.println _)
  }
  */
}
