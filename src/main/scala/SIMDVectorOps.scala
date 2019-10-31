package lb2c

import scala.lms.common._
import scala.reflect.SourceContext

trait SIMDVectorOps extends Base with UncheckedOps { this: Dsl =>
  class __m512i
  class __m512d
  class __mmask8
  class __mmask16

  implicit def __m512iTyp: Typ[__m512i]
  implicit def __m512dTyp: Typ[__m512d]
  implicit def __mmask8Typ: Typ[__mmask8]
  implicit def __mmask16Typ: Typ[__mmask16]
  implicit def toRep512i(x: __m512i) = unit(x)
  implicit def toRep512d(x: __m512d) = unit(x)
  implicit def toRepMask8(x: __mmask8) = unit(x)
  implicit def toRepMask16(x: __mmask16) = unit(x)

  def _mm512_set_epi32(e15: Rep[Int], e14: Rep[Int], e13: Rep[Int], e12: Rep[Int],
                       e11: Rep[Int], e10: Rep[Int], e9: Rep[Int], e8: Rep[Int],
                       e7: Rep[Int], e6: Rep[Int], e5: Rep[Int], e4: Rep[Int],
                       e3: Rep[Int], e2: Rep[Int], e1: Rep[Int], e0: Rep[Int]): Rep[__m512i]
  def _mm512_set_pd(e7: Rep[Double], e6: Rep[Double], e5: Rep[Double], e4: Rep[Double],
                    e3: Rep[Double], e2: Rep[Double], e1: Rep[Double], e0: Rep[Double]): Rep[__m512d]


  def _mm512_loadu_si512(array: Rep[Array[Int]]): Rep[__m512i]
  def _mm512_loadu_pd(array: Rep[Array[Double]]): Rep[__m512d]
  def _mm512_loadu_pd(array: Rep[Array[Double]], offset: Int): Rep[__m512d]

  def _mm512_mask_storeu_epi32(array: Rep[Array[Int]], bitmask: Rep[__mmask16], v: Rep[__m512i]): Rep[Unit]
  def _mm512_mask_storeu_pd(array: Rep[Array[Double]], bitmask: Rep[__mmask8], v: Rep[__m512d]): Rep[Unit]

  def _mm512_mask_compressstoreu_epi32(array: Rep[Array[Int]], bitmask: Rep[__mmask16], v: Rep[__m512i]): Rep[Unit]
  def _mm512_mask_compressstoreu_pd(array: Rep[Array[Double]], bitmask: Rep[__mmask8], v: Rep[__m512d]): Rep[Unit]

  def _mm512_set1_epi32(x: Rep[Int]): Rep[__m512i]
  def _mm512_set1_pd(x: Rep[Double]): Rep[__m512d]

  def _mm_popcnt8(bitmask: Rep[__mmask8]): Rep[Int]
  def _mm_popcnt16(bitmask: Rep[__mmask16]): Rep[Int]

  def _mm512_add_epi32(vx: Rep[__m512i], vy: Rep[__m512i]): Rep[__m512i]
  def _mm512_sub_epi32(vx: Rep[__m512i], vy: Rep[__m512i]): Rep[__m512i]
  def _mm512_mullo_epi32(vx: Rep[__m512i], vy: Rep[__m512i]): Rep[__m512i]

  def _mm512_add_pd(vx: Rep[__m512d], vy: Rep[__m512d]): Rep[__m512d]
  def _mm512_sub_pd(vx: Rep[__m512d], vy: Rep[__m512d]): Rep[__m512d]
  def _mm512_mul_pd(vx: Rep[__m512d], vy: Rep[__m512d]): Rep[__m512d]

  def _mm512_cmpeq_epi32_mask(vx: Rep[__m512i], vy: Rep[__m512i]): Rep[__mmask16]
  def _mm512_cmpge_epi32_mask(vx: Rep[__m512i], vy: Rep[__m512i]): Rep[__mmask16]
  def _mm512_cmpgt_epi32_mask(vx: Rep[__m512i], vy: Rep[__m512i]): Rep[__mmask16]
  def _mm512_cmple_epi32_mask(vx: Rep[__m512i], vy: Rep[__m512i]): Rep[__mmask16]
  def _mm512_cmplt_epi32_mask(vx: Rep[__m512i], vy: Rep[__m512i]): Rep[__mmask16]

  def _mm512_cmpeq_pd_mask(vx: Rep[__m512d], vy: Rep[__m512d]): Rep[__mmask8]
  def _mm512_cmpge_pd_mask(vx: Rep[__m512d], vy: Rep[__m512d]): Rep[__mmask8]
  def _mm512_cmpgt_pd_mask(vx: Rep[__m512d], vy: Rep[__m512d]): Rep[__mmask8]
  def _mm512_cmple_pd_mask(vx: Rep[__m512d], vy: Rep[__m512d]): Rep[__mmask8]
  def _mm512_cmplt_pd_mask(vx: Rep[__m512d], vy: Rep[__m512d]): Rep[__mmask8]

  def _mm512_kand8(x: Rep[__mmask8], y: Rep[__mmask8]): Rep[__mmask8]
  def _mm512_kor8(x: Rep[__mmask8], y: Rep[__mmask8]): Rep[__mmask8]

  def _mm512_kand16(x: Rep[__mmask16], y: Rep[__mmask16]): Rep[__mmask16]
  def _mm512_kor16(x: Rep[__mmask16], y: Rep[__mmask16]): Rep[__mmask16]

  case class Vec16i(reg: Rep[__m512i]) {
    def add(x: Vec16i): Vec16i = Vec16i(_mm512_add_epi32(reg, x.reg))
    def sub(x: Vec16i): Vec16i = Vec16i(_mm512_sub_epi32(reg, x.reg))
    def mullo(x: Vec16i): Vec16i = Vec16i(_mm512_mullo_epi32(reg, x.reg))
    def isEq(x: Vec16i): Mask16 = Mask16(_mm512_cmpeq_epi32_mask(reg, x.reg))
    def isGe(x: Vec16i): Mask16 = Mask16(_mm512_cmpge_epi32_mask(reg, x.reg))
    def isGt(x: Vec16i): Mask16 = Mask16(_mm512_cmpgt_epi32_mask(reg, x.reg))
    def isLe(x: Vec16i): Mask16 = Mask16(_mm512_cmple_epi32_mask(reg, x.reg))
    def isLt(x: Vec16i): Mask16 = Mask16(_mm512_cmplt_epi32_mask(reg, x.reg))
    def toBuffer(buffer: Rep[Array[Int]], mask: Mask16) = _mm512_mask_storeu_epi32(buffer, mask.reg, reg)
    def toBufferPacked(buffer: Rep[Array[Int]], mask: Mask16) = _mm512_mask_compressstoreu_epi32(buffer, mask.reg, reg)
  }
  def Vec16i(x: Rep[Int]): Vec16i = Vec16i(_mm512_set1_epi32(x))
  def Vec16i(e15: Rep[Int], e14: Rep[Int], e13: Rep[Int], e12: Rep[Int],
             e11: Rep[Int], e10: Rep[Int], e9: Rep[Int], e8: Rep[Int],
             e7: Rep[Int], e6: Rep[Int], e5: Rep[Int], e4: Rep[Int],
             e3: Rep[Int], e2: Rep[Int], e1: Rep[Int], e0: Rep[Int]): Vec16i =
    Vec16i(_mm512_set_epi32(e15, e14, e13, e12, e11, e10, e9, e8, e7, e6, e5, e4, e3, e2, e1, e0))
  def Vec16iFromArray(array: Rep[Array[Int]]): Vec16i = Vec16i(_mm512_loadu_si512(array))

  case class Vec8d(reg: Rep[__m512d]) {
    def add(x: Vec8d): Vec8d = Vec8d(_mm512_add_pd(reg, x.reg))
    def sub(x: Vec8d): Vec8d = Vec8d(_mm512_sub_pd(reg, x.reg))
    def mul(x: Vec8d): Vec8d = Vec8d(_mm512_mul_pd(reg, x.reg))
    def isEq(x: Vec8d): Mask8 = Mask8(_mm512_cmpeq_pd_mask(reg, x.reg))
    def isGe(x: Vec8d): Mask8 = Mask8(_mm512_cmpge_pd_mask(reg, x.reg))
    def isGt(x: Vec8d): Mask8 = Mask8(_mm512_cmpgt_pd_mask(reg, x.reg))
    def isLe(x: Vec8d): Mask8 = Mask8(_mm512_cmple_pd_mask(reg, x.reg))
    def isLt(x: Vec8d): Mask8 = Mask8(_mm512_cmplt_pd_mask(reg, x.reg))
    def toBuffer(buffer: Rep[Array[Double]], mask: Mask8) = _mm512_mask_storeu_pd(buffer, mask.reg, reg)
    def toBufferPacked(buffer: Rep[Array[Double]], mask: Mask8) = _mm512_mask_compressstoreu_pd(buffer, mask.reg, reg)
  }
  def Vec8d(x: Rep[Double]): Vec8d = Vec8d(_mm512_set1_pd(x))
  def Vec8d(e7: Rep[Double], e6: Rep[Double], e5: Rep[Double], e4: Rep[Double],
            e3: Rep[Double], e2: Rep[Double], e1: Rep[Double], e0: Rep[Double]): Vec8d = Vec8d(_mm512_set_pd(e7, e6, e5, e4, e3, e2, e1, e0))
  def Vec8dFromArray(array: Rep[Array[Double]]): Vec8d = Vec8d(_mm512_loadu_pd(array))
  def Vec8dFromArray(array: Rep[Array[Double]], offset: Int): Vec8d = Vec8d(_mm512_loadu_pd(array, offset))

  case class Mask8(reg: Rep[__mmask8]) {
    def and(x: Mask8): Mask8 = Mask8(_mm512_kand8(reg, x.reg))
    def or(x: Mask8): Mask8 = Mask8(_mm512_kor8(reg, x.reg))
    def popcount: Rep[Int] = _mm_popcnt8(reg)
  }

  case class Mask16(reg: Rep[__mmask16]) {
    def and(x: Mask16): Mask16 = Mask16(_mm512_kand16(reg, x.reg))
    def or(x: Mask16): Mask16 = Mask16(_mm512_kor16(reg, x.reg))
    def popcount: Rep[Int] = _mm_popcnt16(reg)
  }
  def Mask16(low: Mask8, high: Mask8): Mask16 = Mask16(_mm512_concat_mask8(low.reg, high.reg))
  def Mask16FromInt(x: Rep[Int]): Mask16 = Mask16(_mm512_set_mask16(x))
  def _mm512_concat_mask8(low: Rep[__mmask8], high: Rep[__mmask8]): Rep[__mmask16]
  def _mm512_set_mask16(x: Rep[Int]): Rep[__mmask16]
}

trait SIMDVectorExp extends SIMDVectorOps with UncheckedOpsExp { this: DslExp =>
  implicit def __m512iTyp: Typ[__m512i] = manifestTyp
  implicit def __m512dTyp: Typ[__m512d] = manifestTyp
  implicit def __mmask8Typ: Typ[__mmask8] = manifestTyp
  implicit def __mmask16Typ: Typ[__mmask16] = manifestTyp

  def _mm512_set_epi32(e15: Rep[Int], e14: Rep[Int], e13: Rep[Int], e12: Rep[Int],
                       e11: Rep[Int], e10: Rep[Int], e9: Rep[Int], e8: Rep[Int],
                       e7: Rep[Int], e6: Rep[Int], e5: Rep[Int], e4: Rep[Int],
                       e3: Rep[Int], e2: Rep[Int], e1: Rep[Int], e0: Rep[Int]): Rep[__m512i] = {
    uncheckedPure[__m512i]("_mm512_set_epi32(", e15, ",", e14, ",", e13, ",", e12, ",", e11, ",", e10, ",", e9, ",", e8, ",",
      e7, ",", e6, ",", e5, ",", e4, ",", e3, ",", e2, ",", e1, ",", e0, ")")
  }
  def _mm512_set_pd(e7: Rep[Double], e6: Rep[Double], e5: Rep[Double], e4: Rep[Double],
                    e3: Rep[Double], e2: Rep[Double], e1: Rep[Double], e0: Rep[Double]): Rep[__m512d] = {
    uncheckedPure[__m512d]("_mm512_set_pd(", e7, ",", e6, ",", e5, ",", e4, ",", e3, ",", e2, ",", e1, ",", e0, ")")
  }

  def _mm512_loadu_si512(array: Rep[Array[Int]]): Rep[__m512i] = uncheckedPure[__m512i]("_mm512_loadu_si512(", array, ")")
  def _mm512_loadu_pd(array: Rep[Array[Double]]): Rep[__m512d] = uncheckedPure[__m512d]("_mm512_loadu_pd(", array, ")")
  def _mm512_loadu_pd(array: Rep[Array[Double]], offset: Int): Rep[__m512d] = uncheckedPure[__m512d]("_mm512_loadu_pd(", array, "+", offset, ")")

  def _mm512_mask_storeu_epi32(array: Rep[Array[Int]], bitmask: Rep[__mmask16], v: Rep[__m512i]): Rep[Unit] = {
    uncheckedPure[Unit]("_mm512_mask_storeu_epi32(", array, ",", bitmask, ",", v, ")")
  }
  def _mm512_mask_storeu_pd(array: Rep[Array[Double]], bitmask: Rep[__mmask8], v: Rep[__m512d]): Rep[Unit] = {
    uncheckedPure[Unit]("_mm512_mask_storeu_pd(", array, ",", bitmask, ",", v, ")")
  }

  def _mm512_mask_compressstoreu_epi32(array: Rep[Array[Int]], bitmask: Rep[__mmask16], v: Rep[__m512i]): Rep[Unit] = {
    uncheckedPure[Unit]("_mm512_mask_compressstoreu_epi32(", array, ",", bitmask, ",", v, ")")
  }
  def _mm512_mask_compressstoreu_pd(array: Rep[Array[Double]], bitmask: Rep[__mmask8], v: Rep[__m512d]): Rep[Unit] = {
    uncheckedPure[Unit]("_mm512_mask_compressstoreu_pd(", array, ",", bitmask, ",", v, ")")
  }

  def _mm512_set1_epi32(x: Rep[Int]): Rep[__m512i] = uncheckedPure[__m512i]("_mm512_set1_epi32(", x, ")")
  def _mm512_set1_pd(x: Rep[Double]): Rep[__m512d] = uncheckedPure[__m512d]("_mm512_set1_pd(", x, ")")

  def _mm_popcnt8(bitmask: Rep[__mmask8]): Rep[Int] = uncheckedPure[Int]("_mm_popcnt_u32(", bitmask, ")")
  def _mm_popcnt16(bitmask: Rep[__mmask16]): Rep[Int] = uncheckedPure[Int]("_mm_popcnt_u32(", bitmask, ")")

  def _mm512_add_epi32(vx: Rep[__m512i], vy: Rep[__m512i]): Rep[__m512i] = uncheckedPure[__m512i]("_mm512_add_epi32(", vx, ",", vy, ")")
  def _mm512_sub_epi32(vx: Rep[__m512i], vy: Rep[__m512i]): Rep[__m512i] = uncheckedPure[__m512i]("_mm512_sub_epi32(", vx, ",", vy, ")")
  def _mm512_mullo_epi32(vx: Rep[__m512i], vy: Rep[__m512i]): Rep[__m512i] = uncheckedPure[__m512i]("_mm512_mullo_epi32(", vx, ",", vy, ")")

  def _mm512_add_pd(vx: Rep[__m512d], vy: Rep[__m512d]): Rep[__m512d] = uncheckedPure[__m512d]("_mm512_add_pd(", vx, ",", vy, ")")
  def _mm512_sub_pd(vx: Rep[__m512d], vy: Rep[__m512d]): Rep[__m512d] = uncheckedPure[__m512d]("_mm512_sub_pd(", vx, ",", vy, ")")
  def _mm512_mul_pd(vx: Rep[__m512d], vy: Rep[__m512d]): Rep[__m512d] = uncheckedPure[__m512d]("_mm512_mul_pd(", vx, ",", vy, ")")

  def _mm512_cmpeq_epi32_mask(vx: Rep[__m512i], vy: Rep[__m512i]): Rep[__mmask16] = uncheckedPure[__mmask16]("_mm512_cmpeq_epi32_mask(", vx, ",", vy, ")")
  def _mm512_cmpge_epi32_mask(vx: Rep[__m512i], vy: Rep[__m512i]): Rep[__mmask16] = uncheckedPure[__mmask16]("_mm512_cmpge_epi32_mask(", vx, ",", vy, ")")
  def _mm512_cmpgt_epi32_mask(vx: Rep[__m512i], vy: Rep[__m512i]): Rep[__mmask16] = uncheckedPure[__mmask16]("_mm512_cmpgt_epi32_mask(", vx, ",", vy, ")")
  def _mm512_cmple_epi32_mask(vx: Rep[__m512i], vy: Rep[__m512i]): Rep[__mmask16] = uncheckedPure[__mmask16]("_mm512_cmple_epi32_mask(", vx, ",", vy, ")")
  def _mm512_cmplt_epi32_mask(vx: Rep[__m512i], vy: Rep[__m512i]): Rep[__mmask16] = uncheckedPure[__mmask16]("_mm512_cmplt_epi32_mask(", vx, ",", vy, ")")

  def _mm512_cmpeq_pd_mask(vx: Rep[__m512d], vy: Rep[__m512d]): Rep[__mmask8] = uncheckedPure[__mmask8]("_mm512_cmpeq_pd_mask(", vx, ",", vy, ")")
  def _mm512_cmpge_pd_mask(vx: Rep[__m512d], vy: Rep[__m512d]): Rep[__mmask8] = uncheckedPure[__mmask8]("_mm512_cmp_pd_mask(", vx, ",", vy, ",_MM_CMPINT_GE)")
  def _mm512_cmpgt_pd_mask(vx: Rep[__m512d], vy: Rep[__m512d]): Rep[__mmask8] = uncheckedPure[__mmask8]("_mm512_cmp_pd_mask(", vx, ",", vy, ",_MM_CMPINT_GT)")
  def _mm512_cmple_pd_mask(vx: Rep[__m512d], vy: Rep[__m512d]): Rep[__mmask8] = uncheckedPure[__mmask8]("_mm512_cmp_pd_mask(", vx, ",", vy, ",_MM_CMPINT_LE)")
  def _mm512_cmplt_pd_mask(vx: Rep[__m512d], vy: Rep[__m512d]): Rep[__mmask8] = uncheckedPure[__mmask8]("_mm512_cmp_pd_mask(", vx, ",", vy, ",_MM_CMPINT_LT)")

  def _mm512_kand8(x: Rep[__mmask8], y: Rep[__mmask8]): Rep[__mmask8] = uncheckedPure[__mmask8]("_mm512_kand(", x, ",", y, ")")
  def _mm512_kor8(x: Rep[__mmask8], y: Rep[__mmask8]): Rep[__mmask8] = uncheckedPure[__mmask8]("_mm512_kor(", x, ",", y, ")")

  def _mm512_kand16(x: Rep[__mmask16], y: Rep[__mmask16]): Rep[__mmask16] = uncheckedPure[__mmask16]("_mm512_kand(", x, ",", y, ")")
  def _mm512_kor16(x: Rep[__mmask16], y: Rep[__mmask16]): Rep[__mmask16] = uncheckedPure[__mmask16]("_mm512_kor(", x, ",", y, ")")

  def _mm512_set_mask16(x: Rep[Int]): Rep[__mmask16] = uncheckedPure[__mmask16](x)
  def _mm512_concat_mask8(low: Rep[__mmask8], high: Rep[__mmask8]): Rep[__mmask16] = uncheckedPure[__mmask16]("_mm512_kor(", low, ",", high, "<<8)")
}

trait CGenSIMDOps extends CGenEffect {
  val IR: DslExp
  import IR._

  override def remap[A](m: Typ[A]): String = {
    // To make this match the type string like: lb2c.Run$$anon$1@26eea7e.type#lb2c.SIMDVectorOps$_m512i
    // TODO: Should not use _m512i as anonymous?
    val is512i = ".*__m512i$".r
    val is512d = ".*__m512d$".r
    val isMask8 = ".*__mmask8$".r
    val isMask16 = ".*__mmask16$".r
    m.toString match {
      case is512i() => "__m512i"
      case is512d() => "__m512i"
      case isMask8() => "__mmask8"
      case isMask16() => "__mmask16"
      case _ => super.remap(m)
    }
  }

  override def isPrimitiveType(tpe: String) : Boolean = {
    // Use __m512 as primitive type not as object (pointer)
    // To make this match the type string like: lb2c.Run$$anon$1@26eea7e.type#lb2c.SIMDVectorOps$_m512i
    // TODO: Should not use _m512i as anonymous?
    val is512i = ".*__m512i$".r
    val is512d = ".*__m512d$".r
    val isMask8 = ".*__mmask8$".r
    val isMask16 = ".*__mmask16$".r
    tpe match {
      case is512i() => true
      case is512d() => true
      case isMask8() => true
      case isMask16() => true
      case _ => super.isPrimitiveType(tpe)
    }
  }
}