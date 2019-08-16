package lb2c

import lms.core.stub._
import lms.core.virtualize
import lms.macros.SourceContext

trait CGenPreamble { this: DslGenC =>
  registerHeader("<fcntl.h>", "<errno.h>", "<err.h>", "<sys/mman.h>", "<sys/stat.h>", "<unistd.h>")
  registerTopLevelFunction("preamble_tutorial") {
    emit("""#ifndef MAP_FILE
      #define MAP_FILE MAP_SHARED
      #endif
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
      long hash(char *str0, int len) {
        unsigned char* str = (unsigned char*)str0;
        unsigned long hash = 5381;
        int c;
        while ((c = *str++) && len--)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        return hash;
      }"""
    )
  }
}

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
          override val codegen = new DslGenC with CGenUncheckedOps with CGenPreamble {
            val IR: q.type = q
          }
          override def snippet(x: Rep[Int]): Rep[Unit] = execQuery(query)  // FIXME: Input x is unnecessary...
        }
        engine.eval(0)
      }
      case "interpreter" => QueryInterpreter.execQuery(query)
    }
  }

}
