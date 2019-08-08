package lb2c

import scala.lms.common._

object Run {

  def main(args: Array[String]) {

    /*
    val snippet = new DslDriverC[Int,Int] {
      def snippet(x: Rep[Int]) = {

        def compute(b: Rep[Boolean]): Rep[Int] = {
          // the if is deferred to the second stage
          if (b) 1 else x
        }
        compute(x==1)
      }
    }
    println(snippet.code)

     */
    println(args(0))
    QueryInterpreter.execQuery(args(0))
    //args.map(_.toInt).map(snippet.eval)
  }

}
