package lb2c

import scala.lms.common._

object Run {

  def main(args: Array[String]) {
    var engineType: String = ""
    var query: String = ""

    args.length match {
      case 1 => { engineType = "interpreter"; query = args(0) }
      case 2 => { engineType = args(0); query = args(1) }
      case _ => { println("Specify engine type and query"); return }
    }

    engineType match {
      case "compiler" => {
        val engine = new DslDriverC[Int, Unit] with QueryCompiler with CLibraryExp { q =>
          override val codegen = new DslGenC with CGenUncheckedOps {
            val IR: q.type = q
          }
          override def snippet(x: Rep[Int]): Rep[Unit] = execQuery(query)  // FIXME: Input x is unnecessary...
        }
        engine.eval
      }
      case "interpreter" => QueryInterpreter.execQuery(query)
    }
  }

}
