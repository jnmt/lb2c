package lb2c

import scala.lms.common._
import scala.reflect.SourceContext

// TODO: jnmt: Understand the difference between Base and Exp
// TODO: jnmt: Understand technique of infix_toInt (See also .toInt in nextInt() method)

trait CLibraryBase extends Base with UncheckedOps { this: Dsl =>
  def open(name: Rep[String]): Rep[Int]
  def close(fd: Rep[Int]): Rep[Unit]
  def exits(ret: Rep[Int]): Rep[Unit]
  def filelen(fd: Rep[Int]): Rep[Int]
  def mmap[T:Typ](fd: Rep[Int], len: Rep[Int]): Rep[Array[T]]
  def stringFromCharArray(buf: Rep[Array[Char]], pos: Rep[Int], len: Rep[Int]): Rep[String]
  def prints(s: Rep[String]): Rep[Int]
  def infix_toInt(c: Rep[Char]): Rep[Int] = c.asInstanceOf[Rep[Int]]
}

trait CLibraryExp extends CLibraryBase with UncheckedOpsExp { this: DslExp =>
  def open(name: Rep[String]) = uncheckedPure[Int]("open(",name,",0)")
  def close(fd: Rep[Int]) = unchecked[Unit]("close(",fd,")")
  def exits(ret: Rep[Int]) = unchecked[Unit]("exit(",ret,")")
  def filelen(fd: Rep[Int]) = uncheckedPure[Int]("fsize(",fd,")") // FIXME: fresh name
  def mmap[T:Typ](fd: Rep[Int], len: Rep[Int]) = uncheckedPure[Array[T]]("mmap(0, ",len,", PROT_READ, MAP_FILE | MAP_SHARED, ",fd,", 0)")
  def stringFromCharArray(data: Rep[Array[Char]], pos: Rep[Int], len: Rep[Int]): Rep[String] = uncheckedPure[String](data," + ",pos)
  def prints(s: Rep[String]): Rep[Int] = unchecked[Int]("printll(",s,")")
}
