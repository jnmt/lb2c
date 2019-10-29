package lb2c

import scala.lms.common._
import scala.reflect.SourceContext

trait SIMDVectorOps extends Base with UncheckedOps { this: Dsl =>
  class __m512i
  class __mmask16

  implicit def __m512iTyp: Typ[__m512i]
  implicit def __mmask16Typ: Typ[__mmask16]
  implicit def toRep512i(x: __m512i) = unit(x)
  implicit def toRepMask16(x: __mmask16) = unit(x)

  def _mm512_set_epi32(e15: Rep[Int], e14: Rep[Int], e13: Rep[Int], e12: Rep[Int],
                       e11: Rep[Int], e10: Rep[Int], e9: Rep[Int], e8: Rep[Int],
                       e7: Rep[Int], e6: Rep[Int], e5: Rep[Int], e4: Rep[Int],
                       e3: Rep[Int], e2: Rep[Int], e1: Rep[Int], e0: Rep[Int]): Rep[__m512i]

  def _mm512_loadu_si512(array: Rep[Array[Int]]): Rep[__m512i]

  def _mm512_mask_compressstoreu_epi32(array: Rep[Array[Int]], bitmask: Rep[__mmask16], v: Rep[__m512i]): Rep[Unit]

  def _mm512_set1_epi32(x: Rep[Int]): Rep[__m512i]

  def _mm_popcnt_u32(bitmask: Rep[__mmask16]): Rep[Int]

  def _mm512_cmpeq_epi32_mask(vx: Rep[__m512i], vy: Rep[__m512i]): Rep[__mmask16]
  def _mm512_cmpge_epi32_mask(vx: Rep[__m512i], vy: Rep[__m512i]): Rep[__mmask16]
  def _mm512_cmpgt_epi32_mask(vx: Rep[__m512i], vy: Rep[__m512i]): Rep[__mmask16]
  def _mm512_cmple_epi32_mask(vx: Rep[__m512i], vy: Rep[__m512i]): Rep[__mmask16]
  def _mm512_cmplt_epi32_mask(vx: Rep[__m512i], vy: Rep[__m512i]): Rep[__mmask16]
}

trait SIMDVectorExp extends SIMDVectorOps with UncheckedOpsExp { this: DslExp =>
  implicit def __m512iTyp: Typ[__m512i] = manifestTyp
  implicit def __mmask16Typ: Typ[__mmask16] = manifestTyp

  def _mm512_set_epi32(e15: Rep[Int], e14: Rep[Int], e13: Rep[Int], e12: Rep[Int],
                       e11: Rep[Int], e10: Rep[Int], e9: Rep[Int], e8: Rep[Int],
                       e7: Rep[Int], e6: Rep[Int], e5: Rep[Int], e4: Rep[Int],
                       e3: Rep[Int], e2: Rep[Int], e1: Rep[Int], e0: Rep[Int]): Rep[__m512i] = {
    uncheckedPure[__m512i]("_mm512_set_epi32(", e15, ",", e14, ",", e13, ",", e12, ",", e11, ",", e10, ",", e9, ",", e8, ",",
      e7, ",", e6, ",", e5, ",", e4, ",", e3, ",", e2, ",", e1, ",", e0, ")")
  }

  def _mm512_loadu_si512(array: Rep[Array[Int]]): Rep[__m512i] = uncheckedPure[__m512i]("_mm512_loadu_si512(", array, ")")

  def _mm512_mask_compressstoreu_epi32(array: Rep[Array[Int]], bitmask: Rep[__mmask16], v: Rep[__m512i]): Rep[Unit] = {
    uncheckedPure[Unit]("_mm512_mask_compressstoreu_epi32(", array, ",", bitmask, ",", v, ")")
  }

  def _mm512_set1_epi32(x: Rep[Int]): Rep[__m512i] = uncheckedPure[__m512i]("_mm512_set1_epi32(", x, ")")

  def _mm_popcnt_u32(bitmask: Rep[__mmask16]): Rep[Int] = uncheckedPure[Int]("_mm_popcnt_u32(", bitmask, ")")

  def _mm512_cmpeq_epi32_mask(vx: Rep[__m512i], vy: Rep[__m512i]): Rep[__mmask16] = uncheckedPure[__mmask16]("_mm512_cmpeq_epi32_mask(", vx, ",", vy, ")")
  def _mm512_cmpge_epi32_mask(vx: Rep[__m512i], vy: Rep[__m512i]): Rep[__mmask16] = uncheckedPure[__mmask16]("_mm512_cmpge_epi32_mask(", vx, ",", vy, ")")
  def _mm512_cmpgt_epi32_mask(vx: Rep[__m512i], vy: Rep[__m512i]): Rep[__mmask16] = uncheckedPure[__mmask16]("_mm512_cmpgt_epi32_mask(", vx, ",", vy, ")")
  def _mm512_cmple_epi32_mask(vx: Rep[__m512i], vy: Rep[__m512i]): Rep[__mmask16] = uncheckedPure[__mmask16]("_mm512_cmple_epi32_mask(", vx, ",", vy, ")")
  def _mm512_cmplt_epi32_mask(vx: Rep[__m512i], vy: Rep[__m512i]): Rep[__mmask16] = uncheckedPure[__mmask16]("_mm512_cmplt_epi32_mask(", vx, ",", vy, ")")
}

trait CGenSIMDOps extends CGenEffect {
  val IR: DslExp
  import IR._

  override def remap[A](m: Typ[A]): String = {
    // To make this match the type string like: lb2c.Run$$anon$1@26eea7e.type#lb2c.SIMDVectorOps$_m512i
    // TODO: Should not use _m512i as anonymous?
    val is512i = ".*__m512i$".r
    val isMask16 = ".*__mmask16$".r
    m.toString match {
      case is512i() => "__m512i"
      case isMask16() => "__mmask16"
      case _ => super.remap(m)
    }
  }

  override def isPrimitiveType(tpe: String) : Boolean = {
    // Use __m512 as primitive type not as object (pointer)
    // To make this match the type string like: lb2c.Run$$anon$1@26eea7e.type#lb2c.SIMDVectorOps$_m512i
    // TODO: Should not use _m512i as anonymous?
    val is512i = ".*__m512i$".r
    val isMask16 = ".*__mmask16$".r
    tpe match {
      case is512i() => true
      case isMask16() => true
      case _ => super.isPrimitiveType(tpe)
    }
  }
}