
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <immintrin.h>
#include <omp.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
#ifndef MAP_FILE
#define MAP_FILE MAP_SHARED
#endif
#define MATCH 0
#define NOMATCH 1
#define NOWILDCARDMATCH 2
#define CharRead(A) (*(A++))
#define HASH_TABLE_SIZE (1 << 22)
#define BUCKET_SIZE (1 << 8)
#define NUM_THREADS 4
#define BUFFER_SIZE 16
int fsize(int fd) {
  struct stat stat;
  fstat(fd, &stat);
  return stat.st_size;
}
int printll(char *s) {
  while (*s != '\n' && *s != ',' && *s != '|' && *s != '\t') {
    putchar(*s++);
  }
  return 0;
}
void print_performance(struct timeval begin, struct timeval end) {
  long diff =
      (end.tv_sec - begin.tv_sec) * 1000 * 1000 + (end.tv_usec - begin.tv_usec);
  if (diff > 1000) {
    printf("%ld.%ld ms\n", diff / 1000, diff % 1000);
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
long hash(char *str0, int len) {
  unsigned char *str = (unsigned char *)str0;
  unsigned long hash = 5381;
  int c;

  while ((c = *str++) && len--)
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash;
}
// void Snippet(char*);
void Snippet(int);
int main(int argc, char *argv[]) {
  /*
  if (argc != 2) {
    printf("usage: query <filename>\n");
    return 0;
  }
  */
  Snippet(0);
  return 0;
}

/*****************************************
  Emitting C Generated Code
*******************************************/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void Snippet(int32_t x1) {
  // For Part Table On-Memory Data Store
  int32_t *p_partkey = (int32_t *)malloc(268435456 * sizeof(int32_t));
  char **p_name = (char **)malloc(268435456 * sizeof(char *));
  int32_t *p_name_len = (int32_t *)malloc(268435456 * sizeof(int32_t));
  char **p_mfgr = (char **)malloc(268435456 * sizeof(char *));
  int32_t *p_mfgr_len = (int32_t *)malloc(268435456 * sizeof(int32_t));
  char **p_brand = (char **)malloc(268435456 * sizeof(char *));
  int32_t *p_brand_len = (int32_t *)malloc(268435456 * sizeof(int32_t));
  char **p_type = (char **)malloc(268435456 * sizeof(char *));
  int32_t *p_type_len = (int32_t *)malloc(268435456 * sizeof(int32_t));
  int32_t *p_size = (int32_t *)malloc(268435456 * sizeof(int32_t));
  char **p_container = (char **)malloc(268435456 * sizeof(char *));
  int32_t *p_container_len = (int32_t *)malloc(268435456 * sizeof(int32_t));
  double *p_retailprice = (double *)malloc(268435456 * sizeof(double));
  char **p_comment = (char **)malloc(268435456 * sizeof(char *));
  int32_t *p_comment_len = (int32_t *)malloc(268435456 * sizeof(int32_t));
  int32_t numPartTuples = 0;

  // For LineItem Table On-Memory Data Store
  int32_t *l_orderkey = (int32_t *)malloc(268435456 * sizeof(int32_t));
  int32_t *l_partkey = (int32_t *)malloc(268435456 * sizeof(int32_t));
  int32_t *l_suppkey = (int32_t *)malloc(268435456 * sizeof(int32_t));
  int32_t *l_linenumber = (int32_t *)malloc(268435456 * sizeof(int32_t));
  double *l_quantity = (double *)malloc(268435456 * sizeof(double));
  double *l_extendedprice = (double *)malloc(268435456 * sizeof(double));
  double *l_discount = (double *)malloc(268435456 * sizeof(double));
  double *l_tax = (double *)malloc(268435456 * sizeof(double));
  char **l_returnflag = (char **)malloc(268435456 * sizeof(char *));
  int32_t *l_returnflag_len = (int32_t *)malloc(268435456 * sizeof(int32_t));
  char **l_linestatus = (char **)malloc(268435456 * sizeof(char *));
  int32_t *l_linestatus_len = (int32_t *)malloc(268435456 * sizeof(int32_t));
  int32_t *l_shipdate_y = (int32_t *)malloc(268435456 * sizeof(int32_t));
  int32_t *l_shipdate_m = (int32_t *)malloc(268435456 * sizeof(int32_t));
  int32_t *l_shipdate_d = (int32_t *)malloc(268435456 * sizeof(int32_t));
  int32_t *l_commitdate_y = (int32_t *)malloc(268435456 * sizeof(int32_t));
  int32_t *l_commitdate_m = (int32_t *)malloc(268435456 * sizeof(int32_t));
  int32_t *l_commitdate_d = (int32_t *)malloc(268435456 * sizeof(int32_t));
  int32_t *l_receiptdate_y = (int32_t *)malloc(268435456 * sizeof(int32_t));
  int32_t *l_receiptdate_m = (int32_t *)malloc(268435456 * sizeof(int32_t));
  int32_t *l_receiptdate_d = (int32_t *)malloc(268435456 * sizeof(int32_t));
  char **l_shipinstruct = (char **)malloc(268435456 * sizeof(char *));
  int32_t *l_shipinstruct_len = (int32_t *)malloc(268435456 * sizeof(int32_t));
  char **l_shipmode = (char **)malloc(268435456 * sizeof(char *));
  int32_t *l_shipmode_len = (int32_t *)malloc(268435456 * sizeof(int32_t));
  char **l_comment = (char **)malloc(268435456 * sizeof(char *));
  int32_t *l_comment_len = (int32_t *)malloc(268435456 * sizeof(int32_t));
  int32_t numLineItemTuples = 0;

  printf("%s\n", "sum_cw,sum_x,promo_revenue");
  double *agg_ht_sum1 = (double *)malloc(HASH_TABLE_SIZE * sizeof(double));
  double *agg_ht_sum2 = (double *)malloc(HASH_TABLE_SIZE * sizeof(double));
  bool *agg_ht_entry_used = (bool *)malloc(HASH_TABLE_SIZE * sizeof(bool));
  for (int x54 = 0; x54 < HASH_TABLE_SIZE; x54++) {
    agg_ht_entry_used[x54] = false;
  }
  int32_t *agg_htable = (int32_t *)malloc(HASH_TABLE_SIZE * sizeof(int32_t));
  int32_t num_agg_ht_entries = 0;
  int32_t *x62 = (int32_t *)malloc(HASH_TABLE_SIZE * sizeof(int32_t));
  int32_t x63 = HASH_TABLE_SIZE * BUCKET_SIZE;
  int32_t *ht_p_partkey = (int32_t *)malloc(x63 * sizeof(int32_t));
  char **ht_p_name = (char **)malloc(x63 * sizeof(char *));
  int32_t *ht_p_name_len = (int32_t *)malloc(x63 * sizeof(int32_t));
  char **ht_p_mfgr = (char **)malloc(x63 * sizeof(char *));
  int32_t *ht_p_mfgr_len = (int32_t *)malloc(x63 * sizeof(int32_t));
  char **ht_p_brand = (char **)malloc(x63 * sizeof(char *));
  int32_t *ht_p_brand_len = (int32_t *)malloc(x63 * sizeof(int32_t));
  char **ht_p_type = (char **)malloc(x63 * sizeof(char *));
  int32_t *ht_p_type_len = (int32_t *)malloc(x63 * sizeof(int32_t));
  int32_t *ht_p_size = (int32_t *)malloc(x63 * sizeof(int32_t));
  char **ht_p_container = (char **)malloc(x63 * sizeof(char *));
  int32_t *ht_p_container_len = (int32_t *)malloc(x63 * sizeof(int32_t));
  double *ht_p_retailprice = (double *)malloc(x63 * sizeof(double));
  char **ht_p_comment = (char **)malloc(x63 * sizeof(char *));
  int32_t *ht_p_comment_len = (int32_t *)malloc(x63 * sizeof(int32_t));
  int32_t *bucket_status = (int32_t *)malloc(HASH_TABLE_SIZE * sizeof(int32_t));
  for (int x80 = 0; x80 < HASH_TABLE_SIZE; x80++) {
    bucket_status[x80] = 0;
  }

  // For LineItem Table Buffer x84-x110
  int32_t *buf_l_orderkey = (int32_t *)malloc(16 * sizeof(int32_t));
  int32_t *buf_l_partkey = (int32_t *)malloc(16 * sizeof(int32_t));
  int32_t *buf_l_suppkey = (int32_t *)malloc(16 * sizeof(int32_t));
  int32_t *buf_l_linenumber = (int32_t *)malloc(16 * sizeof(int32_t));
  double *buf_l_quantity = (double *)malloc(16 * sizeof(double));
  double *buf_l_extendedprice = (double *)malloc(16 * sizeof(double));
  double *buf_l_discount = (double *)malloc(16 * sizeof(double));
  double *buf_l_tax = (double *)malloc(16 * sizeof(double));
  char **buf_l_returnflag = (char **)malloc(16 * sizeof(char *));
  int32_t *buf_l_returnflag_len = (int32_t *)malloc(16 * sizeof(int32_t));
  char **buf_l_linestatus = (char **)malloc(16 * sizeof(char *));
  int32_t *buf_l_linestatus_len = (int32_t *)malloc(16 * sizeof(int32_t));
  int32_t *buf_l_shipdate_y = (int32_t *)malloc(16 * sizeof(int32_t));
  int32_t *buf_l_shipdate_m = (int32_t *)malloc(16 * sizeof(int32_t));
  int32_t *buf_l_shipdate_d = (int32_t *)malloc(16 * sizeof(int32_t));
  int32_t *buf_l_commitdate_y = (int32_t *)malloc(16 * sizeof(int32_t));
  int32_t *buf_l_commitdate_m = (int32_t *)malloc(16 * sizeof(int32_t));
  int32_t *buf_l_commitdate_d = (int32_t *)malloc(16 * sizeof(int32_t));
  int32_t *buf_l_receiptdate_y = (int32_t *)malloc(16 * sizeof(int32_t));
  int32_t *buf_l_receiptdate_m = (int32_t *)malloc(16 * sizeof(int32_t));
  int32_t *buf_l_receiptdate_d = (int32_t *)malloc(16 * sizeof(int32_t));
  char **buf_l_shipinstruct = (char **)malloc(16 * sizeof(char *));
  int32_t *buf_l_shipinstruct_len = (int32_t *)malloc(16 * sizeof(int32_t));
  char **buf_l_shipmode = (char **)malloc(16 * sizeof(char *));
  int32_t *buf_l_shipmode_len = (int32_t *)malloc(16 * sizeof(int32_t));
  char **buf_l_comment = (char **)malloc(16 * sizeof(char *));
  int32_t *buf_l_comment_len = (int32_t *)malloc(16 * sizeof(int32_t));
  int32_t index = 0;

  int32_t *indexBuffer = (int32_t *)malloc(16 * sizeof(int32_t));
  int32_t x118 = 0;
  int32_t x115 = open("/Users/jun/src/tpch-dbgen/part.tbl", 0);
  int32_t x116 = fsize(x115);
  int32_t x119 = x116;
  char *x117 = (char *)mmap(0, x116, PROT_READ, MAP_FILE | MAP_SHARED, x115, 0);
  for (;;) {
    int32_t x120 = x118;
    int32_t x121 = x119;
    bool x122 = x120 < x121;
    if (!x122)
      break;
    int32_t x125 = 0;
    for (;;) {
      int32_t x126 = x118;
      char x127 = x117[x126];
      bool x128 = x127 != '|';
      if (!x128)
        break;
      int32_t x130 = x125;
      int32_t x132 = x118;
      int32_t x131 = x130 * 10;
      char x133 = x117[x132];
      char x134 = x133 - '0';
      int32_t x135 = x131 + x134;
      x125 = x135;
      x118 += 1;
    }
    x118 += 1;
    int32_t x141 = x125;
    int32_t x142 = x118;
    for (;;) {
      int32_t x143 = x118;
      char x144 = x117[x143];
      bool x145 = x144 != '|';
      if (!x145)
        break;
      x118 += 1;
    }
    int32_t x150 = x118;
    x118 += 1;
    int32_t x154 = x118;
    for (;;) {
      int32_t x155 = x118;
      char x156 = x117[x155];
      bool x157 = x156 != '|';
      if (!x157)
        break;
      x118 += 1;
    }
    int32_t x162 = x118;
    x118 += 1;
    int32_t x166 = x118;
    for (;;) {
      int32_t x167 = x118;
      char x168 = x117[x167];
      bool x169 = x168 != '|';
      if (!x169)
        break;
      x118 += 1;
    }
    int32_t x174 = x118;
    x118 += 1;
    int32_t x178 = x118;
    for (;;) {
      int32_t x179 = x118;
      char x180 = x117[x179];
      bool x181 = x180 != '|';
      if (!x181)
        break;
      x118 += 1;
    }
    int32_t x186 = x118;
    x118 += 1;
    int32_t x191 = 0;
    for (;;) {
      int32_t x192 = x118;
      char x193 = x117[x192];
      bool x194 = x193 != '|';
      if (!x194)
        break;
      int32_t x196 = x191;
      int32_t x198 = x118;
      int32_t x197 = x196 * 10;
      char x199 = x117[x198];
      char x200 = x199 - '0';
      int32_t x201 = x197 + x200;
      x191 = x201;
      x118 += 1;
    }
    x118 += 1;
    int32_t x207 = x191;
    int32_t x208 = x118;
    for (;;) {
      int32_t x209 = x118;
      char x210 = x117[x209];
      bool x211 = x210 != '|';
      if (!x211)
        break;
      x118 += 1;
    }
    int32_t x216 = x118;
    x118 += 1;
    double x221 = 0.0;
    double x222 = 10.0;
    for (;;) {
      int32_t x223 = x118;
      char x224 = x117[x223];
      bool x226 = x224 == '.';
      bool x228;
      if (x226) {
        x228 = false;
      } else {
        bool x227 = x224 != '|';
        x228 = x227;
      }
      if (!x228)
        break;
      double x230 = x221;
      int32_t x232 = x118;
      double x231 = x230 * 10.0;
      char x233 = x117[x232];
      char x234 = x233 - '0';
      double x236 = (double)x234;
      double x237 = x231 + x236;
      x221 = x237;
      x118 += 1;
    }
    int32_t x242 = x118;
    char x243 = x117[x242];
    bool x245 = x243 == '|';
    if (x245) {
    } else {
      x118 += 1;
      for (;;) {
        int32_t x247 = x118;
        char x248 = x117[x247];
        bool x249 = x248 != '|';
        if (!x249)
          break;
        double x251 = x221;
        int32_t x252 = x118;
        double x255 = x222;
        char x253 = x117[x252];
        char x254 = x253 - '0';
        double x257 = (double)x254;
        double x258 = x257 / x255;
        double x259 = x251 + x258;
        x221 = x259;
        double x261 = x255 * 10.0;
        x222 = x261;
        x118 += 1;
      }
    }
    x118 += 1;
    double x269 = x221;
    int32_t x270 = x118;
    for (;;) {
      int32_t x271 = x118;
      char x272 = x117[x271];
      bool x273 = x272 != '\n';
      if (!x273)
        break;
      x118 += 1;
    }
    int32_t x278 = x118;
    x118 += 1;
    p_partkey[numPartTuples] = x141;
    p_name[numPartTuples] = x117 + x142;
    p_name_len[numPartTuples] = x150 - x142;
    p_mfgr[numPartTuples] = x117 + x154;
    p_mfgr_len[numPartTuples] = x162 - x154;
    p_brand[numPartTuples] = x117 + x166;
    p_brand_len[numPartTuples] = x174 - x166;
    p_type[numPartTuples] = x117 + x178;
    p_type_len[numPartTuples] = x186 - x178;
    p_size[numPartTuples] = x207;
    p_container[numPartTuples] = x117 + x208;
    p_container_len[numPartTuples] = x216 - x208;
    p_retailprice[numPartTuples] = x269;
    p_comment[numPartTuples] = x117 + x270;
    p_comment_len[numPartTuples] = x278 - x270;
    numPartTuples += 1;
  }
  close(x115);
  int32_t x305 = 0;
  int32_t x302 = open("/Users/jun/src/tpch-dbgen/lineitem.tbl", 0);
  int32_t x303 = fsize(x302);
  int32_t x306 = x303;
  char *x304 = (char *)mmap(0, x303, PROT_READ, MAP_FILE | MAP_SHARED, x302, 0);
  for (;;) {
    int32_t x307 = x305;
    int32_t x308 = x306;
    bool x309 = x307 < x308;
    if (!x309)
      break;
    int32_t x312 = 0;
    for (;;) {
      int32_t x313 = x305;
      char x314 = x304[x313];
      bool x315 = x314 != '|';
      if (!x315)
        break;
      int32_t x317 = x312;
      int32_t x319 = x305;
      int32_t x318 = x317 * 10;
      char x320 = x304[x319];
      char x321 = x320 - '0';
      int32_t x322 = x318 + x321;
      x312 = x322;
      x305 += 1;
    }
    x305 += 1;
    int32_t x328 = x312;
    int32_t x330 = 0;
    for (;;) {
      int32_t x331 = x305;
      char x332 = x304[x331];
      bool x333 = x332 != '|';
      if (!x333)
        break;
      int32_t x335 = x330;
      int32_t x337 = x305;
      int32_t x336 = x335 * 10;
      char x338 = x304[x337];
      char x339 = x338 - '0';
      int32_t x340 = x336 + x339;
      x330 = x340;
      x305 += 1;
    }
    x305 += 1;
    int32_t x346 = x330;
    int32_t x348 = 0;
    for (;;) {
      int32_t x349 = x305;
      char x350 = x304[x349];
      bool x351 = x350 != '|';
      if (!x351)
        break;
      int32_t x353 = x348;
      int32_t x355 = x305;
      int32_t x354 = x353 * 10;
      char x356 = x304[x355];
      char x357 = x356 - '0';
      int32_t x358 = x354 + x357;
      x348 = x358;
      x305 += 1;
    }
    x305 += 1;
    int32_t x364 = x348;
    int32_t x366 = 0;
    for (;;) {
      int32_t x367 = x305;
      char x368 = x304[x367];
      bool x369 = x368 != '|';
      if (!x369)
        break;
      int32_t x371 = x366;
      int32_t x373 = x305;
      int32_t x372 = x371 * 10;
      char x374 = x304[x373];
      char x375 = x374 - '0';
      int32_t x376 = x372 + x375;
      x366 = x376;
      x305 += 1;
    }
    x305 += 1;
    int32_t x382 = x366;
    double x384 = 0.0;
    double x385 = 10.0;
    for (;;) {
      int32_t x386 = x305;
      char x387 = x304[x386];
      bool x389 = x387 == '.';
      bool x391;
      if (x389) {
        x391 = false;
      } else {
        bool x390 = x387 != '|';
        x391 = x390;
      }
      if (!x391)
        break;
      double x393 = x384;
      int32_t x395 = x305;
      double x394 = x393 * 10.0;
      char x396 = x304[x395];
      char x397 = x396 - '0';
      double x399 = (double)x397;
      double x400 = x394 + x399;
      x384 = x400;
      x305 += 1;
    }
    int32_t x405 = x305;
    char x406 = x304[x405];
    bool x408 = x406 == '|';
    if (x408) {
    } else {
      x305 += 1;
      for (;;) {
        int32_t x410 = x305;
        char x411 = x304[x410];
        bool x412 = x411 != '|';
        if (!x412)
          break;
        double x414 = x384;
        int32_t x415 = x305;
        double x418 = x385;
        char x416 = x304[x415];
        char x417 = x416 - '0';
        double x420 = (double)x417;
        double x421 = x420 / x418;
        double x422 = x414 + x421;
        x384 = x422;
        double x424 = x418 * 10.0;
        x385 = x424;
        x305 += 1;
      }
    }
    x305 += 1;
    double x432 = x384;
    double x434 = 0.0;
    double x435 = 10.0;
    for (;;) {
      int32_t x436 = x305;
      char x437 = x304[x436];
      bool x439 = x437 == '.';
      bool x441;
      if (x439) {
        x441 = false;
      } else {
        bool x440 = x437 != '|';
        x441 = x440;
      }
      if (!x441)
        break;
      double x443 = x434;
      int32_t x445 = x305;
      double x444 = x443 * 10.0;
      char x446 = x304[x445];
      char x447 = x446 - '0';
      double x449 = (double)x447;
      double x450 = x444 + x449;
      x434 = x450;
      x305 += 1;
    }
    int32_t x455 = x305;
    char x456 = x304[x455];
    bool x458 = x456 == '|';
    if (x458) {
    } else {
      x305 += 1;
      for (;;) {
        int32_t x460 = x305;
        char x461 = x304[x460];
        bool x462 = x461 != '|';
        if (!x462)
          break;
        double x464 = x434;
        int32_t x465 = x305;
        double x468 = x435;
        char x466 = x304[x465];
        char x467 = x466 - '0';
        double x470 = (double)x467;
        double x471 = x470 / x468;
        double x472 = x464 + x471;
        x434 = x472;
        double x474 = x468 * 10.0;
        x435 = x474;
        x305 += 1;
      }
    }
    x305 += 1;
    double x482 = x434;
    double x484 = 0.0;
    double x485 = 10.0;
    for (;;) {
      int32_t x486 = x305;
      char x487 = x304[x486];
      bool x489 = x487 == '.';
      bool x491;
      if (x489) {
        x491 = false;
      } else {
        bool x490 = x487 != '|';
        x491 = x490;
      }
      if (!x491)
        break;
      double x493 = x484;
      int32_t x495 = x305;
      double x494 = x493 * 10.0;
      char x496 = x304[x495];
      char x497 = x496 - '0';
      double x499 = (double)x497;
      double x500 = x494 + x499;
      x484 = x500;
      x305 += 1;
    }
    int32_t x505 = x305;
    char x506 = x304[x505];
    bool x508 = x506 == '|';
    if (x508) {
    } else {
      x305 += 1;
      for (;;) {
        int32_t x510 = x305;
        char x511 = x304[x510];
        bool x512 = x511 != '|';
        if (!x512)
          break;
        double x514 = x484;
        int32_t x515 = x305;
        double x518 = x485;
        char x516 = x304[x515];
        char x517 = x516 - '0';
        double x520 = (double)x517;
        double x521 = x520 / x518;
        double x522 = x514 + x521;
        x484 = x522;
        double x524 = x518 * 10.0;
        x485 = x524;
        x305 += 1;
      }
    }
    x305 += 1;
    double x532 = x484;
    double x534 = 0.0;
    double x535 = 10.0;
    for (;;) {
      int32_t x536 = x305;
      char x537 = x304[x536];
      bool x539 = x537 == '.';
      bool x541;
      if (x539) {
        x541 = false;
      } else {
        bool x540 = x537 != '|';
        x541 = x540;
      }
      if (!x541)
        break;
      double x543 = x534;
      int32_t x545 = x305;
      double x544 = x543 * 10.0;
      char x546 = x304[x545];
      char x547 = x546 - '0';
      double x549 = (double)x547;
      double x550 = x544 + x549;
      x534 = x550;
      x305 += 1;
    }
    int32_t x555 = x305;
    char x556 = x304[x555];
    bool x558 = x556 == '|';
    if (x558) {
    } else {
      x305 += 1;
      for (;;) {
        int32_t x560 = x305;
        char x561 = x304[x560];
        bool x562 = x561 != '|';
        if (!x562)
          break;
        double x564 = x534;
        int32_t x565 = x305;
        double x568 = x535;
        char x566 = x304[x565];
        char x567 = x566 - '0';
        double x570 = (double)x567;
        double x571 = x570 / x568;
        double x572 = x564 + x571;
        x534 = x572;
        double x574 = x568 * 10.0;
        x535 = x574;
        x305 += 1;
      }
    }
    x305 += 1;
    double x582 = x534;
    int32_t x583 = x305;
    for (;;) {
      int32_t x584 = x305;
      char x585 = x304[x584];
      bool x586 = x585 != '|';
      if (!x586)
        break;
      x305 += 1;
    }
    int32_t x591 = x305;
    x305 += 1;
    int32_t x595 = x305;
    for (;;) {
      int32_t x596 = x305;
      char x597 = x304[x596];
      bool x598 = x597 != '|';
      if (!x598)
        break;
      x305 += 1;
    }
    int32_t x603 = x305;
    x305 += 1;
    int32_t x608 = 0;
    int32_t x609 = 0;
    int32_t x610 = 0;
    for (;;) {
      int32_t x611 = x305;
      char x612 = x304[x611];
      bool x613 = x612 != '-';
      if (!x613)
        break;
      int32_t x615 = x608;
      int32_t x617 = x305;
      int32_t x616 = x615 * 10;
      char x618 = x304[x617];
      char x619 = x618 - '0';
      int32_t x620 = x616 + x619;
      x608 = x620;
      x305 += 1;
    }
    x305 += 1;
    for (;;) {
      int32_t x626 = x305;
      char x627 = x304[x626];
      bool x628 = x627 != '-';
      if (!x628)
        break;
      int32_t x630 = x609;
      int32_t x632 = x305;
      int32_t x631 = x630 * 10;
      char x633 = x304[x632];
      char x634 = x633 - '0';
      int32_t x635 = x631 + x634;
      x609 = x635;
      x305 += 1;
    }
    x305 += 1;
    for (;;) {
      int32_t x641 = x305;
      char x642 = x304[x641];
      bool x643 = x642 != '|';
      if (!x643)
        break;
      int32_t x645 = x610;
      int32_t x647 = x305;
      int32_t x646 = x645 * 10;
      char x648 = x304[x647];
      char x649 = x648 - '0';
      int32_t x650 = x646 + x649;
      x610 = x650;
      x305 += 1;
    }
    x305 += 1;
    int32_t x656 = x608;
    int32_t x657 = x609;
    int32_t x658 = x610;
    int32_t x660 = 0;
    int32_t x661 = 0;
    int32_t x662 = 0;
    for (;;) {
      int32_t x663 = x305;
      char x664 = x304[x663];
      bool x665 = x664 != '-';
      if (!x665)
        break;
      int32_t x667 = x660;
      int32_t x669 = x305;
      int32_t x668 = x667 * 10;
      char x670 = x304[x669];
      char x671 = x670 - '0';
      int32_t x672 = x668 + x671;
      x660 = x672;
      x305 += 1;
    }
    x305 += 1;
    for (;;) {
      int32_t x678 = x305;
      char x679 = x304[x678];
      bool x680 = x679 != '-';
      if (!x680)
        break;
      int32_t x682 = x661;
      int32_t x684 = x305;
      int32_t x683 = x682 * 10;
      char x685 = x304[x684];
      char x686 = x685 - '0';
      int32_t x687 = x683 + x686;
      x661 = x687;
      x305 += 1;
    }
    x305 += 1;
    for (;;) {
      int32_t x693 = x305;
      char x694 = x304[x693];
      bool x695 = x694 != '|';
      if (!x695)
        break;
      int32_t x697 = x662;
      int32_t x699 = x305;
      int32_t x698 = x697 * 10;
      char x700 = x304[x699];
      char x701 = x700 - '0';
      int32_t x702 = x698 + x701;
      x662 = x702;
      x305 += 1;
    }
    x305 += 1;
    int32_t x708 = x660;
    int32_t x709 = x661;
    int32_t x710 = x662;
    int32_t x712 = 0;
    int32_t x713 = 0;
    int32_t x714 = 0;
    for (;;) {
      int32_t x715 = x305;
      char x716 = x304[x715];
      bool x717 = x716 != '-';
      if (!x717)
        break;
      int32_t x719 = x712;
      int32_t x721 = x305;
      int32_t x720 = x719 * 10;
      char x722 = x304[x721];
      char x723 = x722 - '0';
      int32_t x724 = x720 + x723;
      x712 = x724;
      x305 += 1;
    }
    x305 += 1;
    for (;;) {
      int32_t x730 = x305;
      char x731 = x304[x730];
      bool x732 = x731 != '-';
      if (!x732)
        break;
      int32_t x734 = x713;
      int32_t x736 = x305;
      int32_t x735 = x734 * 10;
      char x737 = x304[x736];
      char x738 = x737 - '0';
      int32_t x739 = x735 + x738;
      x713 = x739;
      x305 += 1;
    }
    x305 += 1;
    for (;;) {
      int32_t x745 = x305;
      char x746 = x304[x745];
      bool x747 = x746 != '|';
      if (!x747)
        break;
      int32_t x749 = x714;
      int32_t x751 = x305;
      int32_t x750 = x749 * 10;
      char x752 = x304[x751];
      char x753 = x752 - '0';
      int32_t x754 = x750 + x753;
      x714 = x754;
      x305 += 1;
    }
    x305 += 1;
    int32_t x760 = x712;
    int32_t x761 = x713;
    int32_t x762 = x714;
    int32_t x763 = x305;
    for (;;) {
      int32_t x764 = x305;
      char x765 = x304[x764];
      bool x766 = x765 != '|';
      if (!x766)
        break;
      x305 += 1;
    }
    int32_t x771 = x305;
    x305 += 1;
    int32_t x775 = x305;
    for (;;) {
      int32_t x776 = x305;
      char x777 = x304[x776];
      bool x778 = x777 != '|';
      if (!x778)
        break;
      x305 += 1;
    }
    int32_t x783 = x305;
    x305 += 1;
    int32_t x787 = x305;
    for (;;) {
      int32_t x788 = x305;
      char x789 = x304[x788];
      bool x790 = x789 != '\n';
      if (!x790)
        break;
      x305 += 1;
    }
    int32_t x795 = x305;
    x305 += 1;
    l_orderkey[numLineItemTuples] = x328;
    l_partkey[numLineItemTuples] = x346;
    l_suppkey[numLineItemTuples] = x364;
    l_linenumber[numLineItemTuples] = x382;
    l_quantity[numLineItemTuples] = x432;
    l_extendedprice[numLineItemTuples] = x482;
    l_discount[numLineItemTuples] = x532;
    l_tax[numLineItemTuples] = x582;
    l_returnflag[numLineItemTuples] = x304 + x583;
    l_returnflag_len[numLineItemTuples] = x591 - x583;
    l_linestatus[numLineItemTuples] = x304 + x595;
    l_linestatus_len[numLineItemTuples] = x603 - x595;
    l_shipdate_y[numLineItemTuples] = x656;
    l_shipdate_m[numLineItemTuples] = x657;
    l_shipdate_d[numLineItemTuples] = x658;
    l_commitdate_y[numLineItemTuples] = x708;
    l_commitdate_m[numLineItemTuples] = x709;
    l_commitdate_d[numLineItemTuples] = x710;
    l_receiptdate_y[numLineItemTuples] = x760;
    l_receiptdate_m[numLineItemTuples] = x761;
    l_receiptdate_d[numLineItemTuples] = x762;
    l_shipinstruct[numLineItemTuples] = x304 + x763;
    l_shipinstruct_len[numLineItemTuples] = x771 - x763;
    l_shipmode[numLineItemTuples] = x304 + x775;
    l_shipmode_len[numLineItemTuples] = x783 - x775;
    l_comment[numLineItemTuples] = x304 + x787;
    l_comment_len[numLineItemTuples] = x795 - x787;
    numLineItemTuples += 1;
  }
  close(x302);

  // Start Query Processing
  int32_t x870 = HASH_TABLE_SIZE - 1;
  int32_t x877 = BUCKET_SIZE - 1;
  __m512i x968 = _mm512_set1_epi32(10000);
  __m512i x971 = _mm512_set1_epi32(100);
  __m512i x976 = _mm512_set1_epi32(1995);
  __m512i x977 = _mm512_mullo_epi32(x976, x968);
  __m512i x978 = _mm512_set1_epi32(9);
  __m512i x979 = _mm512_mullo_epi32(x978, x971);
  __m512i x980 = _mm512_add_epi32(x977, x979);
  __m512i x981 = _mm512_set1_epi32(1);
  __m512i x982 = _mm512_add_epi32(x980, x981);
  __mmask16 x966 = 65535;
  __m512i x985 = _mm512_set1_epi32(10);
  __m512i x986 = _mm512_mullo_epi32(x985, x971);
  __m512i x987 = _mm512_add_epi32(x977, x986);
  __m512i x988 = _mm512_add_epi32(x987, x981);
  __m512i indexVec =
      _mm512_set_epi32(15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);
  int32_t x1067 = (int32_t)0L;
  bool x1068 = x1067 >= 0;
  int32_t x1070;
  if (x1068) {
    x1070 = x1067;
  } else {
    int32_t x1069 = 0 - x1067;
    x1070 = x1069;
  }
  int32_t x1071 = x1070 % HASH_TABLE_SIZE;
  bool x1075 = !true;
  struct timeval begin, end;
  begin = cur_time();
  for (int i = 0; i < numPartTuples; i++) {
    int32_t x849 = (int32_t)p_partkey[i];
    bool x850 = x849 >= 0;
    int32_t x852;
    if (x850) {
      x852 = x849;
    } else {
      int32_t x851 = 0 - x849;
      x852 = x851;
    }
    int32_t x853 = x852 % HASH_TABLE_SIZE;
    int32_t x854 = x853;
    for (;;) {
      int32_t x855 = x854;
      int32_t x856 = bucket_status[x855];
      bool x857 = x856 > 0;
      bool x862;
      if (x857) {
        int32_t x858 = x62[x855];
        bool x859 = x858 == p_partkey[i];
        bool x860 = !x859;
        x862 = x860;
      } else {
        x862 = false;
      }
      if (!x862)
        break;
      int32_t x864 = x854;
      int32_t x865 = x864 + 1;
      x854 = x865;
    }
    int32_t x869 = x854;
    bool x871 = x869 == x870;
    if (x871) {
      printf("%s\n", "LB2HashMultiMap table is full.");
      exit(1);
    } else {
    }
    int32_t x876 = bucket_status[x869];
    bool x878 = x876 == x877;
    if (x878) {
      printf("%s\n", "Bucket is full.");
      exit(1);
    } else {
    }
    x62[x869] = p_partkey[i];
    int32_t x884 = x869 * BUCKET_SIZE + x876;
    ht_p_partkey[x884] = p_partkey[i];
    ht_p_name[x884] = p_name[i];
    ht_p_name_len[x884] = p_name_len[i];
    ht_p_mfgr[x884] = p_mfgr[i];
    ht_p_mfgr_len[x884] = p_mfgr_len[i];
    ht_p_brand[x884] = p_brand[i];
    ht_p_brand_len[x884] = p_brand_len[i];
    ht_p_type[x884] = p_type[i];
    ht_p_type_len[x884] = p_type_len[i];
    ht_p_size[x884] = p_size[i];
    ht_p_container[x884] = p_container[i];
    ht_p_container_len[x884] = p_container_len[i];
    ht_p_retailprice[x884] = p_retailprice[i];
    ht_p_comment[x884] = p_comment[i];
    ht_p_comment_len[x884] = p_comment_len[i];
    int32_t x901 = x876 + 1;
    bucket_status[x869] = x901;
  }
  for (int j = 0; j < numLineItemTuples; j++) {
    buf_l_orderkey[index] = l_orderkey[j];
    buf_l_partkey[index] = l_partkey[j];
    buf_l_suppkey[index] = l_suppkey[j];
    buf_l_linenumber[index] = l_linenumber[j];
    buf_l_quantity[index] = l_quantity[j];
    buf_l_extendedprice[index] = l_extendedprice[j];
    buf_l_discount[index] = l_discount[j];
    buf_l_tax[index] = l_tax[j];
    buf_l_returnflag[index] = l_returnflag[j];
    buf_l_returnflag_len[index] = l_returnflag_len[j];
    buf_l_linestatus[index] = l_linestatus[j];
    buf_l_linestatus_len[index] = l_linestatus_len[j];
    buf_l_shipdate_y[index] = l_shipdate_y[j];
    buf_l_shipdate_m[index] = l_shipdate_m[j];
    buf_l_shipdate_d[index] = l_shipdate_d[j];
    buf_l_commitdate_y[index] = l_commitdate_y[j];
    buf_l_commitdate_m[index] = l_commitdate_m[j];
    buf_l_commitdate_d[index] = l_commitdate_d[j];
    buf_l_receiptdate_y[index] = l_receiptdate_y[j];
    buf_l_receiptdate_m[index] = l_receiptdate_m[j];
    buf_l_receiptdate_d[index] = l_receiptdate_d[j];
    buf_l_shipinstruct[index] = l_shipinstruct[j];
    buf_l_shipinstruct_len[index] = l_shipinstruct_len[j];
    buf_l_shipmode[index] = l_shipmode[j];
    buf_l_shipmode_len[index] = l_shipmode_len[j];
    buf_l_comment[index] = l_comment[j];
    buf_l_comment_len[index] = l_comment_len[j];
    index += 1;
    if (index == BUFFER_SIZE) {
      __m512i x967 = _mm512_loadu_si512(buf_l_shipdate_y);
      __m512i x969 = _mm512_mullo_epi32(x967, x968);
      __m512i x970 = _mm512_loadu_si512(buf_l_shipdate_m);
      __m512i x972 = _mm512_mullo_epi32(x970, x971);
      __m512i x973 = _mm512_add_epi32(x969, x972);
      __m512i x974 = _mm512_loadu_si512(buf_l_shipdate_d);
      __m512i x975 = _mm512_add_epi32(x973, x974);
      __mmask16 x983 = _mm512_cmpge_epi32_mask(x975, x982);
      __mmask16 x984 = _mm512_kand(x966, x983);
      __mmask16 x989 = _mm512_cmplt_epi32_mask(x975, x988);
      __mmask16 x990 = _mm512_kand(x984, x989);
      _mm512_mask_compressstoreu_epi32(indexBuffer, x990, indexVec);
      int32_t x992 = _mm_popcnt_u32(x990);
      for (int x994 = 0; x994 < x992; x994++) {
        int32_t x995 = indexBuffer[x994];
        int32_t x997 = buf_l_partkey[x995];
        double x1001 = buf_l_extendedprice[x995];
        double x1002 = buf_l_discount[x995];
        int32_t x1023 = (int32_t)x997;
        bool x1024 = x1023 >= 0;
        int32_t x1026;
        if (x1024) {
          x1026 = x1023;
        } else {
          int32_t x1025 = 0 - x1023;
          x1026 = x1025;
        }
        int32_t x1027 = x1026 % HASH_TABLE_SIZE;
        int32_t x1028 = x1027;
        for (;;) {
          int32_t x1029 = x1028;
          int32_t x1030 = bucket_status[x1029];
          bool x1031 = x1030 > 0;
          bool x1036;
          if (x1031) {
            int32_t x1032 = x62[x1029];
            bool x1033 = x1032 == x997;
            bool x1034 = !x1033;
            x1036 = x1034;
          } else {
            x1036 = false;
          }
          if (!x1036)
            break;
          int32_t x1038 = x1028;
          int32_t x1039 = x1038 + 1;
          x1028 = x1039;
        }
        int32_t x1043 = x1028;
        int32_t x1044 = bucket_status[x1043];
        int32_t x1045 = x1043 * BUCKET_SIZE;
        int32_t x1046 = x1045 + x1044;
        double x1064 = 1.0 - x1002;
        double x1065 = x1001 * x1064;
        for (int x1048 = x1045; x1048 < x1046; x1048++) {
          bool x1066 = pattern_compare(ht_p_type[x1048], "PROMO%");
          if (x1066) {
            int32_t x1072 = x1071;
            for (;;) {
              int32_t x1073 = x1072;
              bool x1074 = agg_ht_entry_used[x1073];
              bool x1076;
              if (x1074) {
                x1076 = x1075;
              } else {
                x1076 = false;
              }
              if (!x1076)
                break;
              x1072 += 1;
            }
            int32_t x1081 = x1072;
            bool x1082 = x1081 == x870;
            if (x1082) {
              printf("%s\n", "LB2HashMap table is full.");
              exit(1);
            } else {
            }
            bool x1087 = agg_ht_entry_used[x1081];
            if (x1087) {
              double x1088 = agg_ht_sum1[x1081];
              double x1089 = agg_ht_sum2[x1081];
              double x1090 = x1088 + x1065;
              agg_ht_sum1[x1081] = x1090;
              double x1091 = x1089 + x1065;
              agg_ht_sum2[x1081] = x1091;
            } else {
              int32_t x1095 = num_agg_ht_entries;
              agg_htable[x1095] = x1081;
              num_agg_ht_entries += 1;
              agg_ht_sum1[x1081] = x1065;
              agg_ht_sum2[x1081] = x1065;
              agg_ht_entry_used[x1081] = true;
            }
          } else {
            int32_t x1104 = x1071;
            for (;;) {
              int32_t x1105 = x1104;
              bool x1106 = agg_ht_entry_used[x1105];
              bool x1107;
              if (x1106) {
                x1107 = x1075;
              } else {
                x1107 = false;
              }
              if (!x1107)
                break;
              x1104 += 1;
            }
            int32_t x1112 = x1104;
            bool x1113 = x1112 == x870;
            if (x1113) {
              printf("%s\n", "LB2HashMap table is full.");
              exit(1);
            } else {
            }
            bool x1118 = agg_ht_entry_used[x1112];
            if (x1118) {
              double x1119 = agg_ht_sum1[x1112];
              double x1120 = agg_ht_sum2[x1112];
              agg_ht_sum1[x1112] = x1119;
              double x1121 = x1120 + x1065;
              agg_ht_sum2[x1112] = x1121;
            } else {
              int32_t x1125 = num_agg_ht_entries;
              agg_htable[x1125] = x1112;
              num_agg_ht_entries += 1;
              agg_ht_sum1[x1112] = 0.0;
              agg_ht_sum2[x1112] = x1065;
              agg_ht_entry_used[x1112] = true;
            }
          }
        }
      }
      index = 0;
    } else {
    }
  }
  int32_t x1144 = index;
  for (int x1146 = 0; x1146 < x1144; x1146++) {
    int32_t x1148 = buf_l_partkey[x1146];
    double x1152 = buf_l_extendedprice[x1146];
    double x1153 = buf_l_discount[x1146];
    int32_t x1159 = buf_l_shipdate_y[x1146];
    int32_t x1160 = buf_l_shipdate_m[x1146];
    int32_t x1161 = buf_l_shipdate_d[x1146];
    int32_t x1174 = x1159 * 10000;
    int32_t x1175 = x1160 * 100;
    int32_t x1176 = x1174 + x1175;
    int32_t x1177 = x1176 + x1161;
    bool x1178 = x1177 >= 19950901;
    bool x1180;
    if (x1178) {
      bool x1179 = x1177 < 19951001;
      x1180 = x1179;
    } else {
      x1180 = false;
    }
    if (x1180) {
      int32_t x1181 = (int32_t)x1148;
      bool x1182 = x1181 >= 0;
      int32_t x1184;
      if (x1182) {
        x1184 = x1181;
      } else {
        int32_t x1183 = 0 - x1181;
        x1184 = x1183;
      }
      int32_t x1185 = x1184 % HASH_TABLE_SIZE;
      int32_t x1186 = x1185;
      for (;;) {
        int32_t x1187 = x1186;
        int32_t x1188 = bucket_status[x1187];
        bool x1189 = x1188 > 0;
        bool x1194;
        if (x1189) {
          int32_t x1190 = x62[x1187];
          bool x1191 = x1190 == x1148;
          bool x1192 = !x1191;
          x1194 = x1192;
        } else {
          x1194 = false;
        }
        if (!x1194)
          break;
        int32_t x1196 = x1186;
        int32_t x1197 = x1196 + 1;
        x1186 = x1197;
      }
      int32_t x1201 = x1186;
      int32_t x1202 = bucket_status[x1201];
      int32_t x1203 = x1201 * BUCKET_SIZE;
      int32_t x1204 = x1203 + x1202;
      double x1222 = 1.0 - x1153;
      double x1223 = x1152 * x1222;
      for (int x1206 = x1203; x1206 < x1204; x1206++) {
        bool x1224 = pattern_compare(ht_p_type[x1206], "PROMO%");
        if (x1224) {
          int32_t x1225 = x1071;
          for (;;) {
            int32_t x1226 = x1225;
            bool x1227 = agg_ht_entry_used[x1226];
            bool x1228;
            if (x1227) {
              x1228 = x1075;
            } else {
              x1228 = false;
            }
            if (!x1228)
              break;
            x1225 += 1;
          }
          int32_t x1233 = x1225;
          bool x1234 = x1233 == x870;
          if (x1234) {
            printf("%s\n", "LB2HashMap table is full.");
            exit(1);
          } else {
          }
          bool x1239 = agg_ht_entry_used[x1233];
          if (x1239) {
            double x1240 = agg_ht_sum1[x1233];
            double x1241 = agg_ht_sum2[x1233];
            double x1242 = x1240 + x1223;
            agg_ht_sum1[x1233] = x1242;
            double x1243 = x1241 + x1223;
            agg_ht_sum2[x1233] = x1243;
          } else {
            int32_t x1247 = num_agg_ht_entries;
            agg_htable[x1247] = x1233;
            num_agg_ht_entries += 1;
            agg_ht_sum1[x1233] = x1223;
            agg_ht_sum2[x1233] = x1223;
            agg_ht_entry_used[x1233] = true;
          }
        } else {
          int32_t x1256 = x1071;
          for (;;) {
            int32_t x1257 = x1256;
            bool x1258 = agg_ht_entry_used[x1257];
            bool x1259;
            if (x1258) {
              x1259 = x1075;
            } else {
              x1259 = false;
            }
            if (!x1259)
              break;
            x1256 += 1;
          }
          int32_t x1264 = x1256;
          bool x1265 = x1264 == x870;
          if (x1265) {
            printf("%s\n", "LB2HashMap table is full.");
            exit(1);
          } else {
          }
          bool x1270 = agg_ht_entry_used[x1264];
          if (x1270) {
            double x1271 = agg_ht_sum1[x1264];
            double x1272 = agg_ht_sum2[x1264];
            agg_ht_sum1[x1264] = x1271;
            double x1273 = x1272 + x1223;
            agg_ht_sum2[x1264] = x1273;
          } else {
            int32_t x1277 = num_agg_ht_entries;
            agg_htable[x1277] = x1264;
            num_agg_ht_entries += 1;
            agg_ht_sum1[x1264] = 0.0;
            agg_ht_sum2[x1264] = x1223;
            agg_ht_entry_used[x1264] = true;
          }
        }
      }
    } else {
    }
  }
  for (int agg_ht_index = 0; agg_ht_index < num_agg_ht_entries;
       agg_ht_index++) {
    double x1297 = agg_ht_sum1[agg_htable[agg_ht_index]];
    double x1298 = agg_ht_sum2[agg_htable[agg_ht_index]];
    printf("%f", x1297);
    printf(",");
    printf("%f", x1298);
    printf(",");
    double x1299 = 100.0 * x1297;
    double x1300 = x1299 / x1298;
    printf("%f", x1300);
    printf("%s\n", "");
  }
  end = cur_time();
  print_performance(begin, end);
}
/*****************************************
  End of C Generated Code
*******************************************/
