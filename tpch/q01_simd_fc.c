
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
      int __pattern_compare(char *s, char *pattern) {
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
      bool pattern_compare(char *s, char *pattern) {
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

      
/*****************************************
  Emitting C Generated Code                  
*******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
void Snippet(int32_t  x1) {
int32_t* x2 = (int32_t*)malloc(268435456 * sizeof(int32_t));
int32_t* x3 = (int32_t*)malloc(268435456 * sizeof(int32_t));
int32_t* x4 = (int32_t*)malloc(268435456 * sizeof(int32_t));
int32_t* x5 = (int32_t*)malloc(268435456 * sizeof(int32_t));
double* x6 = (double*)malloc(268435456 * sizeof(double));
double* x7 = (double*)malloc(268435456 * sizeof(double));
double* x8 = (double*)malloc(268435456 * sizeof(double));
double* x9 = (double*)malloc(268435456 * sizeof(double));
char** x10 = (char**)malloc(268435456 * sizeof(char*));
int32_t* x11 = (int32_t*)malloc(268435456 * sizeof(int32_t));
char** x12 = (char**)malloc(268435456 * sizeof(char*));
int32_t* x13 = (int32_t*)malloc(268435456 * sizeof(int32_t));
int32_t* x14 = (int32_t*)malloc(268435456 * sizeof(int32_t));
int32_t* x15 = (int32_t*)malloc(268435456 * sizeof(int32_t));
int32_t* x16 = (int32_t*)malloc(268435456 * sizeof(int32_t));
int32_t* x17 = (int32_t*)malloc(268435456 * sizeof(int32_t));
int32_t* x18 = (int32_t*)malloc(268435456 * sizeof(int32_t));
int32_t* x19 = (int32_t*)malloc(268435456 * sizeof(int32_t));
int32_t* x20 = (int32_t*)malloc(268435456 * sizeof(int32_t));
int32_t* x21 = (int32_t*)malloc(268435456 * sizeof(int32_t));
int32_t* x22 = (int32_t*)malloc(268435456 * sizeof(int32_t));
char** x23 = (char**)malloc(268435456 * sizeof(char*));
int32_t* x24 = (int32_t*)malloc(268435456 * sizeof(int32_t));
char** x25 = (char**)malloc(268435456 * sizeof(char*));
int32_t* x26 = (int32_t*)malloc(268435456 * sizeof(int32_t));
char** x27 = (char**)malloc(268435456 * sizeof(char*));
int32_t* x28 = (int32_t*)malloc(268435456 * sizeof(int32_t));
int32_t x29 = 0;
int32_t x30 = 0;
printf("%s\n","l_returnflag,l_linestatus,sum_l_quantity,sum_l_extendedprice,sum_disc_price,sum_charge,avg_l_quantity,avg_l_extendedprice,avg_l_discount,count");
char** x32 = (char**)malloc(65536 * sizeof(char*));
int32_t* x33 = (int32_t*)malloc(65536 * sizeof(int32_t));
char** x34 = (char**)malloc(65536 * sizeof(char*));
int32_t* x35 = (int32_t*)malloc(65536 * sizeof(int32_t));
double* x36 = (double*)malloc(65536 * sizeof(double));
double* x37 = (double*)malloc(65536 * sizeof(double));
double* x38 = (double*)malloc(65536 * sizeof(double));
double* x39 = (double*)malloc(65536 * sizeof(double));
double* x40 = (double*)malloc(65536 * sizeof(double));
int32_t* x41 = (int32_t*)malloc(65536 * sizeof(int32_t));
double* x42 = (double*)malloc(65536 * sizeof(double));
int32_t* x43 = (int32_t*)malloc(65536 * sizeof(int32_t));
double* x44 = (double*)malloc(65536 * sizeof(double));
int32_t* x45 = (int32_t*)malloc(65536 * sizeof(int32_t));
int32_t* x46 = (int32_t*)malloc(65536 * sizeof(int32_t));
int32_t* x47 = (int32_t*)malloc(65536 * sizeof(int32_t));
int32_t x48 = 0;
int32_t x49 = 0;
int32_t* x50 = (int32_t*)malloc(256 * sizeof(int32_t));
int32_t* x51 = (int32_t*)malloc(256 * sizeof(int32_t));
int32_t x52 = HASH_TABLE_SIZE;
char** x53 = (char**)malloc(x52 * sizeof(char*));
int32_t* x54 = (int32_t*)malloc(x52 * sizeof(int32_t));
char** x55 = (char**)malloc(x52 * sizeof(char*));
int32_t* x56 = (int32_t*)malloc(x52 * sizeof(int32_t));
double* x57 = (double*)malloc(x52 * sizeof(double));
double* x58 = (double*)malloc(x52 * sizeof(double));
double* x59 = (double*)malloc(x52 * sizeof(double));
double* x60 = (double*)malloc(x52 * sizeof(double));
double* x61 = (double*)malloc(x52 * sizeof(double));
int32_t* x62 = (int32_t*)malloc(x52 * sizeof(int32_t));
double* x63 = (double*)malloc(x52 * sizeof(double));
int32_t* x64 = (int32_t*)malloc(x52 * sizeof(int32_t));
double* x65 = (double*)malloc(x52 * sizeof(double));
int32_t* x66 = (int32_t*)malloc(x52 * sizeof(int32_t));
int32_t* x67 = (int32_t*)malloc(x52 * sizeof(int32_t));
bool* x68 = (bool*)malloc(x52 * sizeof(bool));
for(int x70=0; x70 < x52; x70++) {
x68[x70] = false;

}
int32_t* x74 = (int32_t*)malloc(x52 * sizeof(int32_t));
int32_t x75 = 0;
int32_t x76 = 0;
int32_t* x77 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x78 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x79 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x80 = (int32_t*)malloc(16 * sizeof(int32_t));
double* x81 = (double*)malloc(16 * sizeof(double));
double* x82 = (double*)malloc(16 * sizeof(double));
double* x83 = (double*)malloc(16 * sizeof(double));
double* x84 = (double*)malloc(16 * sizeof(double));
char** x85 = (char**)malloc(16 * sizeof(char*));
int32_t* x86 = (int32_t*)malloc(16 * sizeof(int32_t));
char** x87 = (char**)malloc(16 * sizeof(char*));
int32_t* x88 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x89 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x90 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x91 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x92 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x93 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x94 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x95 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x96 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x97 = (int32_t*)malloc(16 * sizeof(int32_t));
char** x98 = (char**)malloc(16 * sizeof(char*));
int32_t* x99 = (int32_t*)malloc(16 * sizeof(int32_t));
char** x100 = (char**)malloc(16 * sizeof(char*));
int32_t* x101 = (int32_t*)malloc(16 * sizeof(int32_t));
char** x102 = (char**)malloc(16 * sizeof(char*));
int32_t* x103 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t x104 = 0;
int32_t x105 = 0;
double* x106 = (double*)malloc(16 * sizeof(double));
double* x107 = (double*)malloc(16 * sizeof(double));
int32_t x108 = 0;
int32_t x109 = 0;
int32_t* x110 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x111 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x112 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x113 = (int32_t*)malloc(16 * sizeof(int32_t));
double* x114 = (double*)malloc(16 * sizeof(double));
double* x115 = (double*)malloc(16 * sizeof(double));
double* x116 = (double*)malloc(16 * sizeof(double));
double* x117 = (double*)malloc(16 * sizeof(double));
char** x118 = (char**)malloc(16 * sizeof(char*));
int32_t* x119 = (int32_t*)malloc(16 * sizeof(int32_t));
char** x120 = (char**)malloc(16 * sizeof(char*));
int32_t* x121 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x122 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x123 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x124 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x125 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x126 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x127 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x128 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x129 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x130 = (int32_t*)malloc(16 * sizeof(int32_t));
char** x131 = (char**)malloc(16 * sizeof(char*));
int32_t* x132 = (int32_t*)malloc(16 * sizeof(int32_t));
char** x133 = (char**)malloc(16 * sizeof(char*));
int32_t* x134 = (int32_t*)malloc(16 * sizeof(int32_t));
char** x135 = (char**)malloc(16 * sizeof(char*));
int32_t* x136 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t x137 = 0;
int32_t x138 = 0;
int32_t* x140 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t x144 = 0;
int32_t x141 = open("/home/jun/tpch-dbgen/sf1/lineitem.tbl",0);
int32_t x142 = fsize(x141);
int32_t x145 = x142;
char* x143 = (char*)mmap(0, x142, PROT_READ, MAP_FILE | MAP_SHARED, x141, 0);
for (;;) {
int32_t x146 = x144;
int32_t x147 = x145;
bool x148 = x146 < x147;
if (!x148) break;
int32_t x150 = x144;
int32_t x151 = 0;
for (;;) {
int32_t x152 = x144;
char x153 = x143[x152];
bool x154 = x153 != '|';
if (!x154) break;
int32_t x156 = x151;
int32_t x158 = x144;
int32_t x157 = x156 * 10;
char x159 = x143[x158];
char x160 = x159 - '0';
int32_t x161 = x157 + x160;
x151 = x161;
x144 += 1;
}
x144 += 1;
int32_t x167 = x151;
int32_t x168 = x144;
int32_t x169 = 0;
for (;;) {
int32_t x170 = x144;
char x171 = x143[x170];
bool x172 = x171 != '|';
if (!x172) break;
int32_t x174 = x169;
int32_t x176 = x144;
int32_t x175 = x174 * 10;
char x177 = x143[x176];
char x178 = x177 - '0';
int32_t x179 = x175 + x178;
x169 = x179;
x144 += 1;
}
x144 += 1;
int32_t x185 = x169;
int32_t x186 = x144;
int32_t x187 = 0;
for (;;) {
int32_t x188 = x144;
char x189 = x143[x188];
bool x190 = x189 != '|';
if (!x190) break;
int32_t x192 = x187;
int32_t x194 = x144;
int32_t x193 = x192 * 10;
char x195 = x143[x194];
char x196 = x195 - '0';
int32_t x197 = x193 + x196;
x187 = x197;
x144 += 1;
}
x144 += 1;
int32_t x203 = x187;
int32_t x204 = x144;
int32_t x205 = 0;
for (;;) {
int32_t x206 = x144;
char x207 = x143[x206];
bool x208 = x207 != '|';
if (!x208) break;
int32_t x210 = x205;
int32_t x212 = x144;
int32_t x211 = x210 * 10;
char x213 = x143[x212];
char x214 = x213 - '0';
int32_t x215 = x211 + x214;
x205 = x215;
x144 += 1;
}
x144 += 1;
int32_t x221 = x205;
int32_t x222 = x144;
double x223 = 0.0;
double x224 = 10.0;
for (;;) {
int32_t x225 = x144;
char x226 = x143[x225];
bool x228 = x226 == '.';
bool x230;
if (x228) {
x230 = false;
} else {
bool x229 = x226 != '|';
x230 = x229;
}
if (!x230) break;
double x232 = x223;
int32_t x234 = x144;
double x233 = x232 * 10.0;
char x235 = x143[x234];
char x236 = x235 - '0';
double x238 = (double)x236;
double x239 = x233 + x238;
x223 = x239;
x144 += 1;
}
int32_t x244 = x144;
char x245 = x143[x244];
bool x247 = x245 == '|';
if (x247) {
} else {
x144 += 1;
for (;;) {
int32_t x249 = x144;
char x250 = x143[x249];
bool x251 = x250 != '|';
if (!x251) break;
double x253 = x223;
int32_t x254 = x144;
double x257 = x224;
char x255 = x143[x254];
char x256 = x255 - '0';
double x259 = (double)x256;
double x260 = x259 / x257;
double x261 = x253 + x260;
x223 = x261;
double x263 = x257 * 10.0;
x224 = x263;
x144 += 1;
}
}
x144 += 1;
double x271 = x223;
int32_t x272 = x144;
double x273 = 0.0;
double x274 = 10.0;
for (;;) {
int32_t x275 = x144;
char x276 = x143[x275];
bool x278 = x276 == '.';
bool x280;
if (x278) {
x280 = false;
} else {
bool x279 = x276 != '|';
x280 = x279;
}
if (!x280) break;
double x282 = x273;
int32_t x284 = x144;
double x283 = x282 * 10.0;
char x285 = x143[x284];
char x286 = x285 - '0';
double x288 = (double)x286;
double x289 = x283 + x288;
x273 = x289;
x144 += 1;
}
int32_t x294 = x144;
char x295 = x143[x294];
bool x297 = x295 == '|';
if (x297) {
} else {
x144 += 1;
for (;;) {
int32_t x299 = x144;
char x300 = x143[x299];
bool x301 = x300 != '|';
if (!x301) break;
double x303 = x273;
int32_t x304 = x144;
double x307 = x274;
char x305 = x143[x304];
char x306 = x305 - '0';
double x309 = (double)x306;
double x310 = x309 / x307;
double x311 = x303 + x310;
x273 = x311;
double x313 = x307 * 10.0;
x274 = x313;
x144 += 1;
}
}
x144 += 1;
double x321 = x273;
int32_t x322 = x144;
double x323 = 0.0;
double x324 = 10.0;
for (;;) {
int32_t x325 = x144;
char x326 = x143[x325];
bool x328 = x326 == '.';
bool x330;
if (x328) {
x330 = false;
} else {
bool x329 = x326 != '|';
x330 = x329;
}
if (!x330) break;
double x332 = x323;
int32_t x334 = x144;
double x333 = x332 * 10.0;
char x335 = x143[x334];
char x336 = x335 - '0';
double x338 = (double)x336;
double x339 = x333 + x338;
x323 = x339;
x144 += 1;
}
int32_t x344 = x144;
char x345 = x143[x344];
bool x347 = x345 == '|';
if (x347) {
} else {
x144 += 1;
for (;;) {
int32_t x349 = x144;
char x350 = x143[x349];
bool x351 = x350 != '|';
if (!x351) break;
double x353 = x323;
int32_t x354 = x144;
double x357 = x324;
char x355 = x143[x354];
char x356 = x355 - '0';
double x359 = (double)x356;
double x360 = x359 / x357;
double x361 = x353 + x360;
x323 = x361;
double x363 = x357 * 10.0;
x324 = x363;
x144 += 1;
}
}
x144 += 1;
double x371 = x323;
int32_t x372 = x144;
double x373 = 0.0;
double x374 = 10.0;
for (;;) {
int32_t x375 = x144;
char x376 = x143[x375];
bool x378 = x376 == '.';
bool x380;
if (x378) {
x380 = false;
} else {
bool x379 = x376 != '|';
x380 = x379;
}
if (!x380) break;
double x382 = x373;
int32_t x384 = x144;
double x383 = x382 * 10.0;
char x385 = x143[x384];
char x386 = x385 - '0';
double x388 = (double)x386;
double x389 = x383 + x388;
x373 = x389;
x144 += 1;
}
int32_t x394 = x144;
char x395 = x143[x394];
bool x397 = x395 == '|';
if (x397) {
} else {
x144 += 1;
for (;;) {
int32_t x399 = x144;
char x400 = x143[x399];
bool x401 = x400 != '|';
if (!x401) break;
double x403 = x373;
int32_t x404 = x144;
double x407 = x374;
char x405 = x143[x404];
char x406 = x405 - '0';
double x409 = (double)x406;
double x410 = x409 / x407;
double x411 = x403 + x410;
x373 = x411;
double x413 = x407 * 10.0;
x374 = x413;
x144 += 1;
}
}
x144 += 1;
double x421 = x373;
int32_t x422 = x144;
for (;;) {
int32_t x423 = x144;
char x424 = x143[x423];
bool x425 = x424 != '|';
if (!x425) break;
x144 += 1;
}
int32_t x430 = x144;
x144 += 1;
int32_t x434 = x144;
for (;;) {
int32_t x435 = x144;
char x436 = x143[x435];
bool x437 = x436 != '|';
if (!x437) break;
x144 += 1;
}
int32_t x442 = x144;
x144 += 1;
int32_t x446 = x144;
int32_t x447 = 0;
int32_t x448 = 0;
int32_t x449 = 0;
for (;;) {
int32_t x450 = x144;
char x451 = x143[x450];
bool x452 = x451 != '-';
if (!x452) break;
int32_t x454 = x447;
int32_t x456 = x144;
int32_t x455 = x454 * 10;
char x457 = x143[x456];
char x458 = x457 - '0';
int32_t x459 = x455 + x458;
x447 = x459;
x144 += 1;
}
x144 += 1;
for (;;) {
int32_t x465 = x144;
char x466 = x143[x465];
bool x467 = x466 != '-';
if (!x467) break;
int32_t x469 = x448;
int32_t x471 = x144;
int32_t x470 = x469 * 10;
char x472 = x143[x471];
char x473 = x472 - '0';
int32_t x474 = x470 + x473;
x448 = x474;
x144 += 1;
}
x144 += 1;
for (;;) {
int32_t x480 = x144;
char x481 = x143[x480];
bool x482 = x481 != '|';
if (!x482) break;
int32_t x484 = x449;
int32_t x486 = x144;
int32_t x485 = x484 * 10;
char x487 = x143[x486];
char x488 = x487 - '0';
int32_t x489 = x485 + x488;
x449 = x489;
x144 += 1;
}
x144 += 1;
int32_t x495 = x447;
int32_t x496 = x448;
int32_t x497 = x449;
int32_t x498 = x144;
int32_t x499 = 0;
int32_t x500 = 0;
int32_t x501 = 0;
for (;;) {
int32_t x502 = x144;
char x503 = x143[x502];
bool x504 = x503 != '-';
if (!x504) break;
int32_t x506 = x499;
int32_t x508 = x144;
int32_t x507 = x506 * 10;
char x509 = x143[x508];
char x510 = x509 - '0';
int32_t x511 = x507 + x510;
x499 = x511;
x144 += 1;
}
x144 += 1;
for (;;) {
int32_t x517 = x144;
char x518 = x143[x517];
bool x519 = x518 != '-';
if (!x519) break;
int32_t x521 = x500;
int32_t x523 = x144;
int32_t x522 = x521 * 10;
char x524 = x143[x523];
char x525 = x524 - '0';
int32_t x526 = x522 + x525;
x500 = x526;
x144 += 1;
}
x144 += 1;
for (;;) {
int32_t x532 = x144;
char x533 = x143[x532];
bool x534 = x533 != '|';
if (!x534) break;
int32_t x536 = x501;
int32_t x538 = x144;
int32_t x537 = x536 * 10;
char x539 = x143[x538];
char x540 = x539 - '0';
int32_t x541 = x537 + x540;
x501 = x541;
x144 += 1;
}
x144 += 1;
int32_t x547 = x499;
int32_t x548 = x500;
int32_t x549 = x501;
int32_t x550 = x144;
int32_t x551 = 0;
int32_t x552 = 0;
int32_t x553 = 0;
for (;;) {
int32_t x554 = x144;
char x555 = x143[x554];
bool x556 = x555 != '-';
if (!x556) break;
int32_t x558 = x551;
int32_t x560 = x144;
int32_t x559 = x558 * 10;
char x561 = x143[x560];
char x562 = x561 - '0';
int32_t x563 = x559 + x562;
x551 = x563;
x144 += 1;
}
x144 += 1;
for (;;) {
int32_t x569 = x144;
char x570 = x143[x569];
bool x571 = x570 != '-';
if (!x571) break;
int32_t x573 = x552;
int32_t x575 = x144;
int32_t x574 = x573 * 10;
char x576 = x143[x575];
char x577 = x576 - '0';
int32_t x578 = x574 + x577;
x552 = x578;
x144 += 1;
}
x144 += 1;
for (;;) {
int32_t x584 = x144;
char x585 = x143[x584];
bool x586 = x585 != '|';
if (!x586) break;
int32_t x588 = x553;
int32_t x590 = x144;
int32_t x589 = x588 * 10;
char x591 = x143[x590];
char x592 = x591 - '0';
int32_t x593 = x589 + x592;
x553 = x593;
x144 += 1;
}
x144 += 1;
int32_t x599 = x551;
int32_t x600 = x552;
int32_t x601 = x553;
int32_t x602 = x144;
for (;;) {
int32_t x603 = x144;
char x604 = x143[x603];
bool x605 = x604 != '|';
if (!x605) break;
x144 += 1;
}
int32_t x610 = x144;
x144 += 1;
int32_t x614 = x144;
for (;;) {
int32_t x615 = x144;
char x616 = x143[x615];
bool x617 = x616 != '|';
if (!x617) break;
x144 += 1;
}
int32_t x622 = x144;
x144 += 1;
int32_t x626 = x144;
for (;;) {
int32_t x627 = x144;
char x628 = x143[x627];
bool x629 = x628 != '\n';
if (!x629) break;
x144 += 1;
}
int32_t x634 = x144;
x144 += 1;
int32_t x638 = x30;
x2[x638] = x167;
x3[x638] = x185;
x4[x638] = x203;
x5[x638] = x221;
x6[x638] = x271;
x7[x638] = x321;
x8[x638] = x371;
x9[x638] = x421;
char* x433 = x143 + x422;
x10[x638] = x433;
int32_t x431 = x430 - x422;
x11[x638] = x431;
char* x445 = x143 + x434;
x12[x638] = x445;
int32_t x443 = x442 - x434;
x13[x638] = x443;
x14[x638] = x495;
x15[x638] = x496;
x16[x638] = x497;
x17[x638] = x547;
x18[x638] = x548;
x19[x638] = x549;
x20[x638] = x599;
x21[x638] = x600;
x22[x638] = x601;
char* x613 = x143 + x602;
x23[x638] = x613;
int32_t x611 = x610 - x602;
x24[x638] = x611;
char* x625 = x143 + x614;
x25[x638] = x625;
int32_t x623 = x622 - x614;
x26[x638] = x623;
char* x637 = x143 + x626;
x27[x638] = x637;
int32_t x635 = x634 - x626;
x28[x638] = x635;
x30 += 1;
}
close(x141);
__m512i x733 = _mm512_set1_epi32(10000);
__m512i x736 = _mm512_set1_epi32(100);
__m512i x741 = _mm512_set1_epi32(1998);
__m512i x742 = _mm512_mullo_epi32(x741,x733);
__m512i x743 = _mm512_set1_epi32(9);
__m512i x744 = _mm512_mullo_epi32(x743,x736);
__m512i x745 = _mm512_add_epi32(x742,x744);
__m512i x746 = _mm512_set1_epi32(2);
__m512i x747 = _mm512_add_epi32(x745,x746);
__mmask16 x731 = 65535;
__m512i x139 = _mm512_set_epi32(15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0);
__m512i x815 = _mm512_set1_epi32(1);
__m256i x818 = _mm512_extracti32x8_epi32(x815,0);
__m512d x819 = _mm512_cvtepi32_pd(x818);
__m256i x820 = _mm512_extracti32x8_epi32(x815,1);
__m512d x821 = _mm512_cvtepi32_pd(x820);
__mmask8 x826 = _mm512_kand(x731, 0x00ff);
__mmask8 x828 = _mm512_kand(x731>>8, 0x00ff);
int32_t x928 = x52 - 1;
struct timeval begin, end;
begin = cur_time();
int32_t x670 = x30;
for(int x672=0; x672 < x670; x672++) {
int32_t x673 = x2[x672];
int32_t x674 = x3[x672];
int32_t x675 = x4[x672];
int32_t x676 = x5[x672];
double x677 = x6[x672];
double x678 = x7[x672];
double x679 = x8[x672];
double x680 = x9[x672];
char* x681 = x10[x672];
int32_t x682 = x11[x672];
char* x683 = x12[x672];
int32_t x684 = x13[x672];
int32_t x685 = x14[x672];
int32_t x686 = x15[x672];
int32_t x687 = x16[x672];
int32_t x688 = x17[x672];
int32_t x689 = x18[x672];
int32_t x690 = x19[x672];
int32_t x691 = x20[x672];
int32_t x692 = x21[x672];
int32_t x693 = x22[x672];
char* x694 = x23[x672];
int32_t x695 = x24[x672];
char* x696 = x25[x672];
int32_t x697 = x26[x672];
char* x698 = x27[x672];
int32_t x699 = x28[x672];
int32_t x700 = x138;
x110[x700] = x673;
x111[x700] = x674;
x112[x700] = x675;
x113[x700] = x676;
x114[x700] = x677;
x115[x700] = x678;
x116[x700] = x679;
x117[x700] = x680;
x118[x700] = x681;
x119[x700] = x682;
x120[x700] = x683;
x121[x700] = x684;
x122[x700] = x685;
x123[x700] = x686;
x124[x700] = x687;
x125[x700] = x688;
x126[x700] = x689;
x127[x700] = x690;
x128[x700] = x691;
x129[x700] = x692;
x130[x700] = x693;
x131[x700] = x694;
x132[x700] = x695;
x133[x700] = x696;
x134[x700] = x697;
x135[x700] = x698;
x136[x700] = x699;
x138 += 1;
int32_t x729 = x138;
bool x730 = x729 == 16;
if (x730) {
__m512i x732 = _mm512_loadu_si512(x122);
__m512i x734 = _mm512_mullo_epi32(x732,x733);
__m512i x735 = _mm512_loadu_si512(x123);
__m512i x737 = _mm512_mullo_epi32(x735,x736);
__m512i x738 = _mm512_add_epi32(x734,x737);
__m512i x739 = _mm512_loadu_si512(x124);
__m512i x740 = _mm512_add_epi32(x738,x739);
__mmask16 x748 = _mm512_cmple_epi32_mask(x740,x747);
__mmask16 x749 = _mm512_kand(x731,x748);
_mm512_mask_compressstoreu_epi32(x140,x749,x139);
int32_t x751 = _mm_popcnt_u32(x749);
for(int x753=0; x753 < x751; x753++) {
int32_t x754 = x140[x753];
int32_t x755 = x110[x754];
int32_t x756 = x111[x754];
int32_t x757 = x112[x754];
int32_t x758 = x113[x754];
double x759 = x114[x754];
double x760 = x115[x754];
double x761 = x116[x754];
double x762 = x117[x754];
char* x763 = x118[x754];
int32_t x764 = x119[x754];
char* x765 = x120[x754];
int32_t x766 = x121[x754];
int32_t x767 = x122[x754];
int32_t x768 = x123[x754];
int32_t x769 = x124[x754];
int32_t x770 = x125[x754];
int32_t x771 = x126[x754];
int32_t x772 = x127[x754];
int32_t x773 = x128[x754];
int32_t x774 = x129[x754];
int32_t x775 = x130[x754];
char* x776 = x131[x754];
int32_t x777 = x132[x754];
char* x778 = x133[x754];
int32_t x779 = x134[x754];
char* x780 = x135[x754];
int32_t x781 = x136[x754];
int32_t x782 = x105;
x77[x782] = x755;
x78[x782] = x756;
x79[x782] = x757;
x80[x782] = x758;
x81[x782] = x759;
x82[x782] = x760;
x83[x782] = x761;
x84[x782] = x762;
x85[x782] = x763;
x86[x782] = x764;
x87[x782] = x765;
x88[x782] = x766;
x89[x782] = x767;
x90[x782] = x768;
x91[x782] = x769;
x92[x782] = x770;
x93[x782] = x771;
x94[x782] = x772;
x95[x782] = x773;
x96[x782] = x774;
x97[x782] = x775;
x98[x782] = x776;
x99[x782] = x777;
x100[x782] = x778;
x101[x782] = x779;
x102[x782] = x780;
x103[x782] = x781;
x105 += 1;
int32_t x811 = x105;
bool x812 = x811 == 16;
if (x812) {
__m512d x813 = _mm512_loadu_pd(x82);
__m512d x814 = _mm512_loadu_pd(x82+8);
__m512d x816 = _mm512_loadu_pd(x83);
__m512d x817 = _mm512_loadu_pd(x83+8);
__m512d x822 = _mm512_sub_pd(x819,x816);
__m512d x823 = _mm512_sub_pd(x821,x817);
__m512d x824 = _mm512_mul_pd(x813,x822);
__m512d x825 = _mm512_mul_pd(x814,x823);
_mm512_mask_storeu_pd(x106,x826,x824);
_mm512_mask_storeu_pd(x106+8,x828,x825);
__m512d x830 = _mm512_loadu_pd(x84);
__m512d x831 = _mm512_loadu_pd(x84+8);
__m512d x832 = _mm512_add_pd(x819,x830);
__m512d x833 = _mm512_add_pd(x821,x831);
__m512d x834 = _mm512_mul_pd(x824,x832);
__m512d x835 = _mm512_mul_pd(x825,x833);
_mm512_mask_storeu_pd(x107,x826,x834);
_mm512_mask_storeu_pd(x107+8,x828,x835);
for(int x839=0; x839 < 16; x839++) {
int32_t x840 = x77[x839];
int32_t x841 = x78[x839];
int32_t x842 = x79[x839];
int32_t x843 = x80[x839];
double x844 = x81[x839];
double x845 = x82[x839];
double x846 = x83[x839];
double x847 = x84[x839];
char* x848 = x85[x839];
int32_t x849 = x86[x839];
char* x850 = x87[x839];
int32_t x851 = x88[x839];
int32_t x852 = x89[x839];
int32_t x853 = x90[x839];
int32_t x854 = x91[x839];
int32_t x855 = x92[x839];
int32_t x856 = x93[x839];
int32_t x857 = x94[x839];
int32_t x858 = x95[x839];
int32_t x859 = x96[x839];
int32_t x860 = x97[x839];
char* x861 = x98[x839];
int32_t x862 = x99[x839];
char* x863 = x100[x839];
int32_t x864 = x101[x839];
char* x865 = x102[x839];
int32_t x866 = x103[x839];
double x867 = x106[x839];
double x868 = x107[x839];
int64_t x869 = hash(x848,x849);
int64_t x870 = x869 * 41L;
int64_t x871 = hash(x850,x851);
int64_t x872 = x870 + x871;
int32_t x873 = (int32_t)x872;
bool x874 = x873 >= 0;
int32_t x876;
if (x874) {
x876 = x873;
} else {
int32_t x875 = 0 - x873;
x876 = x875;
}
int32_t x877 = x876 % x52;
int32_t x878 = x877;
for (;;) {
int32_t x879 = x878;
bool x880 = x68[x879];
bool x922;
if (x880) {
char* x881 = x53[x879];
int32_t x882 = x54[x879];
char* x883 = x55[x879];
int32_t x884 = x56[x879];
bool x886 = x882 == x849;
bool x901;
if (x886) {
int32_t x887 = 0;
for (;;) {
int32_t x888 = x887;
bool x889 = x888 < x882;
bool x893;
if (x889) {
char x890 = x881[x888];
char x891 = x848[x888];
bool x892 = x890 == x891;
x893 = x892;
} else {
x893 = false;
}
if (!x893) break;
x887 += 1;
}
int32_t x898 = x887;
bool x899 = x898 == x882;
x901 = x899;
} else {
x901 = false;
}
bool x919;
if (x901) {
bool x903 = x884 == x851;
bool x918;
if (x903) {
int32_t x904 = 0;
for (;;) {
int32_t x905 = x904;
bool x906 = x905 < x884;
bool x910;
if (x906) {
char x907 = x883[x905];
char x908 = x850[x905];
bool x909 = x907 == x908;
x910 = x909;
} else {
x910 = false;
}
if (!x910) break;
x904 += 1;
}
int32_t x915 = x904;
bool x916 = x915 == x884;
x918 = x916;
} else {
x918 = false;
}
x919 = x918;
} else {
x919 = false;
}
bool x920 = !x919;
x922 = x920;
} else {
x922 = false;
}
if (!x922) break;
x878 += 1;
}
int32_t x927 = x878;
bool x929 = x927 == x928;
if (x929) {
printf("%s\n","LB2HashMap table is full.");
exit(1);
} else {
}
bool x934 = x68[x927];
if (x934) {
double x935 = x57[x927];
double x936 = x58[x927];
double x937 = x59[x927];
double x938 = x60[x927];
double x939 = x61[x927];
int32_t x940 = x62[x927];
double x941 = x63[x927];
int32_t x942 = x64[x927];
double x943 = x65[x927];
int32_t x944 = x66[x927];
int32_t x945 = x67[x927];
double x946 = x935 + x844;
x57[x927] = x946;
double x947 = x936 + x845;
x58[x927] = x947;
double x948 = x937 + x867;
x59[x927] = x948;
double x949 = x938 + x868;
x60[x927] = x949;
double x950 = x939 + x844;
x61[x927] = x950;
int32_t x951 = x940 + 1;
x62[x927] = x951;
double x952 = x941 + x845;
x63[x927] = x952;
int32_t x953 = x942 + 1;
x64[x927] = x953;
double x954 = x943 + x846;
x65[x927] = x954;
int32_t x955 = x944 + 1;
x66[x927] = x955;
int32_t x956 = x945 + 1;
x67[x927] = x956;
} else {
int32_t x969 = x76;
x74[x969] = x927;
x76 += 1;
x53[x927] = x848;
x54[x927] = x849;
x55[x927] = x850;
x56[x927] = x851;
x57[x927] = x844;
x58[x927] = x845;
x59[x927] = x867;
x60[x927] = x868;
x61[x927] = x844;
x62[x927] = 1;
x63[x927] = x845;
x64[x927] = 1;
x65[x927] = x846;
x66[x927] = 1;
x67[x927] = 1;
x68[x927] = true;
}

}
x105 = 0;
} else {
}

}
x138 = 0;
} else {
}

}
int32_t x1002 = x138;
for(int x1004=0; x1004 < x1002; x1004++) {
int32_t x1005 = x110[x1004];
int32_t x1006 = x111[x1004];
int32_t x1007 = x112[x1004];
int32_t x1008 = x113[x1004];
double x1009 = x114[x1004];
double x1010 = x115[x1004];
double x1011 = x116[x1004];
double x1012 = x117[x1004];
char* x1013 = x118[x1004];
int32_t x1014 = x119[x1004];
char* x1015 = x120[x1004];
int32_t x1016 = x121[x1004];
int32_t x1017 = x122[x1004];
int32_t x1018 = x123[x1004];
int32_t x1019 = x124[x1004];
int32_t x1020 = x125[x1004];
int32_t x1021 = x126[x1004];
int32_t x1022 = x127[x1004];
int32_t x1023 = x128[x1004];
int32_t x1024 = x129[x1004];
int32_t x1025 = x130[x1004];
char* x1026 = x131[x1004];
int32_t x1027 = x132[x1004];
char* x1028 = x133[x1004];
int32_t x1029 = x134[x1004];
char* x1030 = x135[x1004];
int32_t x1031 = x136[x1004];
int32_t x1032 = x1017 * 10000;
int32_t x1033 = x1018 * 100;
int32_t x1034 = x1032 + x1033;
int32_t x1035 = x1034 + x1019;
bool x1036 = x1035 <= 19980902;
if (x1036) {
int32_t x1037 = x105;
x77[x1037] = x1005;
x78[x1037] = x1006;
x79[x1037] = x1007;
x80[x1037] = x1008;
x81[x1037] = x1009;
x82[x1037] = x1010;
x83[x1037] = x1011;
x84[x1037] = x1012;
x85[x1037] = x1013;
x86[x1037] = x1014;
x87[x1037] = x1015;
x88[x1037] = x1016;
x89[x1037] = x1017;
x90[x1037] = x1018;
x91[x1037] = x1019;
x92[x1037] = x1020;
x93[x1037] = x1021;
x94[x1037] = x1022;
x95[x1037] = x1023;
x96[x1037] = x1024;
x97[x1037] = x1025;
x98[x1037] = x1026;
x99[x1037] = x1027;
x100[x1037] = x1028;
x101[x1037] = x1029;
x102[x1037] = x1030;
x103[x1037] = x1031;
x105 += 1;
int32_t x1066 = x105;
bool x1067 = x1066 == 16;
if (x1067) {
__m512d x1068 = _mm512_loadu_pd(x82);
__m512d x1069 = _mm512_loadu_pd(x82+8);
__m512d x1070 = _mm512_loadu_pd(x83);
__m512d x1071 = _mm512_loadu_pd(x83+8);
__m512d x1072 = _mm512_sub_pd(x819,x1070);
__m512d x1073 = _mm512_sub_pd(x821,x1071);
__m512d x1074 = _mm512_mul_pd(x1068,x1072);
__m512d x1075 = _mm512_mul_pd(x1069,x1073);
_mm512_mask_storeu_pd(x106,x826,x1074);
_mm512_mask_storeu_pd(x106+8,x828,x1075);
__m512d x1078 = _mm512_loadu_pd(x84);
__m512d x1079 = _mm512_loadu_pd(x84+8);
__m512d x1080 = _mm512_add_pd(x819,x1078);
__m512d x1081 = _mm512_add_pd(x821,x1079);
__m512d x1082 = _mm512_mul_pd(x1074,x1080);
__m512d x1083 = _mm512_mul_pd(x1075,x1081);
_mm512_mask_storeu_pd(x107,x826,x1082);
_mm512_mask_storeu_pd(x107+8,x828,x1083);
for(int x1086=0; x1086 < 16; x1086++) {
int32_t x1087 = x77[x1086];
int32_t x1088 = x78[x1086];
int32_t x1089 = x79[x1086];
int32_t x1090 = x80[x1086];
double x1091 = x81[x1086];
double x1092 = x82[x1086];
double x1093 = x83[x1086];
double x1094 = x84[x1086];
char* x1095 = x85[x1086];
int32_t x1096 = x86[x1086];
char* x1097 = x87[x1086];
int32_t x1098 = x88[x1086];
int32_t x1099 = x89[x1086];
int32_t x1100 = x90[x1086];
int32_t x1101 = x91[x1086];
int32_t x1102 = x92[x1086];
int32_t x1103 = x93[x1086];
int32_t x1104 = x94[x1086];
int32_t x1105 = x95[x1086];
int32_t x1106 = x96[x1086];
int32_t x1107 = x97[x1086];
char* x1108 = x98[x1086];
int32_t x1109 = x99[x1086];
char* x1110 = x100[x1086];
int32_t x1111 = x101[x1086];
char* x1112 = x102[x1086];
int32_t x1113 = x103[x1086];
double x1114 = x106[x1086];
double x1115 = x107[x1086];
int64_t x1116 = hash(x1095,x1096);
int64_t x1117 = x1116 * 41L;
int64_t x1118 = hash(x1097,x1098);
int64_t x1119 = x1117 + x1118;
int32_t x1120 = (int32_t)x1119;
bool x1121 = x1120 >= 0;
int32_t x1123;
if (x1121) {
x1123 = x1120;
} else {
int32_t x1122 = 0 - x1120;
x1123 = x1122;
}
int32_t x1124 = x1123 % x52;
int32_t x1125 = x1124;
for (;;) {
int32_t x1126 = x1125;
bool x1127 = x68[x1126];
bool x1169;
if (x1127) {
char* x1128 = x53[x1126];
int32_t x1129 = x54[x1126];
char* x1130 = x55[x1126];
int32_t x1131 = x56[x1126];
bool x1133 = x1129 == x1096;
bool x1148;
if (x1133) {
int32_t x1134 = 0;
for (;;) {
int32_t x1135 = x1134;
bool x1136 = x1135 < x1129;
bool x1140;
if (x1136) {
char x1137 = x1128[x1135];
char x1138 = x1095[x1135];
bool x1139 = x1137 == x1138;
x1140 = x1139;
} else {
x1140 = false;
}
if (!x1140) break;
x1134 += 1;
}
int32_t x1145 = x1134;
bool x1146 = x1145 == x1129;
x1148 = x1146;
} else {
x1148 = false;
}
bool x1166;
if (x1148) {
bool x1150 = x1131 == x1098;
bool x1165;
if (x1150) {
int32_t x1151 = 0;
for (;;) {
int32_t x1152 = x1151;
bool x1153 = x1152 < x1131;
bool x1157;
if (x1153) {
char x1154 = x1130[x1152];
char x1155 = x1097[x1152];
bool x1156 = x1154 == x1155;
x1157 = x1156;
} else {
x1157 = false;
}
if (!x1157) break;
x1151 += 1;
}
int32_t x1162 = x1151;
bool x1163 = x1162 == x1131;
x1165 = x1163;
} else {
x1165 = false;
}
x1166 = x1165;
} else {
x1166 = false;
}
bool x1167 = !x1166;
x1169 = x1167;
} else {
x1169 = false;
}
if (!x1169) break;
x1125 += 1;
}
int32_t x1174 = x1125;
bool x1175 = x1174 == x928;
if (x1175) {
printf("%s\n","LB2HashMap table is full.");
exit(1);
} else {
}
bool x1180 = x68[x1174];
if (x1180) {
double x1181 = x57[x1174];
double x1182 = x58[x1174];
double x1183 = x59[x1174];
double x1184 = x60[x1174];
double x1185 = x61[x1174];
int32_t x1186 = x62[x1174];
double x1187 = x63[x1174];
int32_t x1188 = x64[x1174];
double x1189 = x65[x1174];
int32_t x1190 = x66[x1174];
int32_t x1191 = x67[x1174];
double x1192 = x1181 + x1091;
x57[x1174] = x1192;
double x1193 = x1182 + x1092;
x58[x1174] = x1193;
double x1194 = x1183 + x1114;
x59[x1174] = x1194;
double x1195 = x1184 + x1115;
x60[x1174] = x1195;
double x1196 = x1185 + x1091;
x61[x1174] = x1196;
int32_t x1197 = x1186 + 1;
x62[x1174] = x1197;
double x1198 = x1187 + x1092;
x63[x1174] = x1198;
int32_t x1199 = x1188 + 1;
x64[x1174] = x1199;
double x1200 = x1189 + x1093;
x65[x1174] = x1200;
int32_t x1201 = x1190 + 1;
x66[x1174] = x1201;
int32_t x1202 = x1191 + 1;
x67[x1174] = x1202;
} else {
int32_t x1215 = x76;
x74[x1215] = x1174;
x76 += 1;
x53[x1174] = x1095;
x54[x1174] = x1096;
x55[x1174] = x1097;
x56[x1174] = x1098;
x57[x1174] = x1091;
x58[x1174] = x1092;
x59[x1174] = x1114;
x60[x1174] = x1115;
x61[x1174] = x1091;
x62[x1174] = 1;
x63[x1174] = x1092;
x64[x1174] = 1;
x65[x1174] = x1093;
x66[x1174] = 1;
x67[x1174] = 1;
x68[x1174] = true;
}

}
x105 = 0;
} else {
}
} else {
}

}
int32_t x1245 = x105;
for(int x1247=0; x1247 < x1245; x1247++) {
int32_t x1248 = x77[x1247];
int32_t x1249 = x78[x1247];
int32_t x1250 = x79[x1247];
int32_t x1251 = x80[x1247];
double x1252 = x81[x1247];
double x1253 = x82[x1247];
double x1254 = x83[x1247];
double x1255 = x84[x1247];
char* x1256 = x85[x1247];
int32_t x1257 = x86[x1247];
char* x1258 = x87[x1247];
int32_t x1259 = x88[x1247];
int32_t x1260 = x89[x1247];
int32_t x1261 = x90[x1247];
int32_t x1262 = x91[x1247];
int32_t x1263 = x92[x1247];
int32_t x1264 = x93[x1247];
int32_t x1265 = x94[x1247];
int32_t x1266 = x95[x1247];
int32_t x1267 = x96[x1247];
int32_t x1268 = x97[x1247];
char* x1269 = x98[x1247];
int32_t x1270 = x99[x1247];
char* x1271 = x100[x1247];
int32_t x1272 = x101[x1247];
char* x1273 = x102[x1247];
int32_t x1274 = x103[x1247];
int64_t x1279 = hash(x1256,x1257);
int64_t x1280 = x1279 * 41L;
int64_t x1281 = hash(x1258,x1259);
int64_t x1282 = x1280 + x1281;
int32_t x1283 = (int32_t)x1282;
bool x1284 = x1283 >= 0;
int32_t x1286;
if (x1284) {
x1286 = x1283;
} else {
int32_t x1285 = 0 - x1283;
x1286 = x1285;
}
int32_t x1287 = x1286 % x52;
int32_t x1288 = x1287;
for (;;) {
int32_t x1289 = x1288;
bool x1290 = x68[x1289];
bool x1332;
if (x1290) {
char* x1291 = x53[x1289];
int32_t x1292 = x54[x1289];
char* x1293 = x55[x1289];
int32_t x1294 = x56[x1289];
bool x1296 = x1292 == x1257;
bool x1311;
if (x1296) {
int32_t x1297 = 0;
for (;;) {
int32_t x1298 = x1297;
bool x1299 = x1298 < x1292;
bool x1303;
if (x1299) {
char x1300 = x1291[x1298];
char x1301 = x1256[x1298];
bool x1302 = x1300 == x1301;
x1303 = x1302;
} else {
x1303 = false;
}
if (!x1303) break;
x1297 += 1;
}
int32_t x1308 = x1297;
bool x1309 = x1308 == x1292;
x1311 = x1309;
} else {
x1311 = false;
}
bool x1329;
if (x1311) {
bool x1313 = x1294 == x1259;
bool x1328;
if (x1313) {
int32_t x1314 = 0;
for (;;) {
int32_t x1315 = x1314;
bool x1316 = x1315 < x1294;
bool x1320;
if (x1316) {
char x1317 = x1293[x1315];
char x1318 = x1258[x1315];
bool x1319 = x1317 == x1318;
x1320 = x1319;
} else {
x1320 = false;
}
if (!x1320) break;
x1314 += 1;
}
int32_t x1325 = x1314;
bool x1326 = x1325 == x1294;
x1328 = x1326;
} else {
x1328 = false;
}
x1329 = x1328;
} else {
x1329 = false;
}
bool x1330 = !x1329;
x1332 = x1330;
} else {
x1332 = false;
}
if (!x1332) break;
x1288 += 1;
}
int32_t x1337 = x1288;
bool x1338 = x1337 == x928;
if (x1338) {
printf("%s\n","LB2HashMap table is full.");
exit(1);
} else {
}
bool x1343 = x68[x1337];
if (x1343) {
double x1344 = x57[x1337];
double x1345 = x58[x1337];
double x1346 = x59[x1337];
double x1347 = x60[x1337];
double x1348 = x61[x1337];
int32_t x1349 = x62[x1337];
double x1350 = x63[x1337];
int32_t x1351 = x64[x1337];
double x1352 = x65[x1337];
int32_t x1353 = x66[x1337];
int32_t x1354 = x67[x1337];
double x1355 = x1344 + x1252;
x57[x1337] = x1355;
double x1356 = x1345 + x1253;
x58[x1337] = x1356;
double x1275 = 1.0 - x1254;
double x1276 = x1253 * x1275;
double x1357 = x1346 + x1276;
x59[x1337] = x1357;
double x1277 = 1.0 + x1255;
double x1278 = x1276 * x1277;
double x1358 = x1347 + x1278;
x60[x1337] = x1358;
double x1359 = x1348 + x1252;
x61[x1337] = x1359;
int32_t x1360 = x1349 + 1;
x62[x1337] = x1360;
double x1361 = x1350 + x1253;
x63[x1337] = x1361;
int32_t x1362 = x1351 + 1;
x64[x1337] = x1362;
double x1363 = x1352 + x1254;
x65[x1337] = x1363;
int32_t x1364 = x1353 + 1;
x66[x1337] = x1364;
int32_t x1365 = x1354 + 1;
x67[x1337] = x1365;
} else {
int32_t x1378 = x76;
x74[x1378] = x1337;
x76 += 1;
x53[x1337] = x1256;
x54[x1337] = x1257;
x55[x1337] = x1258;
x56[x1337] = x1259;
x57[x1337] = x1252;
x58[x1337] = x1253;
double x1275 = 1.0 - x1254;
double x1276 = x1253 * x1275;
x59[x1337] = x1276;
double x1277 = 1.0 + x1255;
double x1278 = x1276 * x1277;
x60[x1337] = x1278;
x61[x1337] = x1252;
x62[x1337] = 1;
x63[x1337] = x1253;
x64[x1337] = 1;
x65[x1337] = x1254;
x66[x1337] = 1;
x67[x1337] = 1;
x68[x1337] = true;
}

}
int32_t x1401 = x76;
for(int x1403=0; x1403 < x1401; x1403++) {
int32_t x1404 = x74[x1403];
char* x1405 = x53[x1404];
int32_t x1406 = x54[x1404];
char* x1407 = x55[x1404];
int32_t x1408 = x56[x1404];
double x1409 = x57[x1404];
double x1410 = x58[x1404];
double x1411 = x59[x1404];
double x1412 = x60[x1404];
double x1413 = x61[x1404];
int32_t x1414 = x62[x1404];
double x1415 = x63[x1404];
int32_t x1416 = x64[x1404];
double x1417 = x65[x1404];
int32_t x1418 = x66[x1404];
int32_t x1419 = x67[x1404];
int32_t x1420 = x49;
x32[x1420] = x1405;
x33[x1420] = x1406;
x34[x1420] = x1407;
x35[x1420] = x1408;
x36[x1420] = x1409;
x37[x1420] = x1410;
x38[x1420] = x1411;
x39[x1420] = x1412;
x40[x1420] = x1413;
x41[x1420] = x1414;
x42[x1420] = x1415;
x43[x1420] = x1416;
x44[x1420] = x1417;
x45[x1420] = x1418;
x46[x1420] = x1419;
x47[x1420] = x1420;
x49 += 1;

}
x50[0] = 0;
int32_t x1441 = x49;
int32_t x1442 = x1441 - 1;
x51[0] = x1442;
int32_t x1444 = 1;
int32_t x1445 = 1;
for (;;) {
int32_t x1446 = x1445;
bool x1447 = x1446 > 0;
if (!x1447) break;
int32_t x1449 = x1445;
int32_t x1450 = x1449 - 1;
x1445 = x1450;
int32_t x1452 = x50[x1450];
int32_t x1453 = x51[x1450];
int32_t x1454 = x1452;
int32_t x1455 = x1453;
int32_t x1459 = x47[x1452];
char* x1460 = x32[x1459];
int32_t x1461 = x33[x1459];
char* x1462 = x34[x1459];
int32_t x1463 = x35[x1459];
double x1464 = x36[x1459];
double x1465 = x37[x1459];
double x1466 = x38[x1459];
double x1467 = x39[x1459];
double x1468 = x40[x1459];
int32_t x1469 = x41[x1459];
double x1470 = x42[x1459];
int32_t x1471 = x43[x1459];
double x1472 = x44[x1459];
int32_t x1473 = x45[x1459];
int32_t x1474 = x46[x1459];
int32_t x1475 = x47[x1453];
char* x1476 = x32[x1475];
int32_t x1477 = x33[x1475];
char* x1478 = x34[x1475];
int32_t x1479 = x35[x1475];
double x1480 = x36[x1475];
double x1481 = x37[x1475];
double x1482 = x38[x1475];
double x1483 = x39[x1475];
double x1484 = x40[x1475];
int32_t x1485 = x41[x1475];
double x1486 = x42[x1475];
int32_t x1487 = x43[x1475];
double x1488 = x44[x1475];
int32_t x1489 = x45[x1475];
int32_t x1490 = x46[x1475];
int32_t x1491 = 0;
int32_t x1492 = 0;
bool* x1493 = (bool*)malloc(2 * sizeof(bool));
bool* x1494 = (bool*)malloc(2 * sizeof(bool));
int32_t x1495 = 0;
for (;;) {
int32_t x1496 = x1495;
bool x1497 = x1496 < x1461;
bool x1499;
if (x1497) {
bool x1498 = x1496 < x1477;
x1499 = x1498;
} else {
x1499 = false;
}
bool x1503;
if (x1499) {
char x1500 = x1460[x1496];
char x1501 = x1476[x1496];
bool x1502 = x1500 == x1501;
x1503 = x1502;
} else {
x1503 = false;
}
if (!x1503) break;
x1495 += 1;
}
int32_t x1508 = x1495;
char x1509 = x1460[x1508];
char x1510 = x1476[x1508];
bool x1511 = x1509 < x1510;
x1493[0] = x1511;
bool x1514 = x1461 == x1477;
bool x1529;
if (x1514) {
int32_t x1515 = 0;
for (;;) {
int32_t x1516 = x1515;
bool x1517 = x1516 < x1461;
bool x1521;
if (x1517) {
char x1518 = x1460[x1516];
char x1519 = x1476[x1516];
bool x1520 = x1518 == x1519;
x1521 = x1520;
} else {
x1521 = false;
}
if (!x1521) break;
x1515 += 1;
}
int32_t x1526 = x1515;
bool x1527 = x1526 == x1461;
x1529 = x1527;
} else {
x1529 = false;
}
x1494[0] = x1529;
x1492 += 1;
int32_t x1532 = x1492;
int32_t x1533 = 0;
for (;;) {
int32_t x1534 = x1533;
bool x1535 = x1534 < x1463;
bool x1537;
if (x1535) {
bool x1536 = x1534 < x1479;
x1537 = x1536;
} else {
x1537 = false;
}
bool x1541;
if (x1537) {
char x1538 = x1462[x1534];
char x1539 = x1478[x1534];
bool x1540 = x1538 == x1539;
x1541 = x1540;
} else {
x1541 = false;
}
if (!x1541) break;
x1533 += 1;
}
int32_t x1546 = x1533;
char x1547 = x1462[x1546];
char x1548 = x1478[x1546];
bool x1549 = x1547 < x1548;
x1493[x1532] = x1549;
bool x1552 = x1463 == x1479;
bool x1567;
if (x1552) {
int32_t x1553 = 0;
for (;;) {
int32_t x1554 = x1553;
bool x1555 = x1554 < x1463;
bool x1559;
if (x1555) {
char x1556 = x1462[x1554];
char x1557 = x1478[x1554];
bool x1558 = x1556 == x1557;
x1559 = x1558;
} else {
x1559 = false;
}
if (!x1559) break;
x1553 += 1;
}
int32_t x1564 = x1553;
bool x1565 = x1564 == x1463;
x1567 = x1565;
} else {
x1567 = false;
}
x1494[x1532] = x1567;
x1492 += 1;
bool x1570 = x1493[0];
bool x1572 = x1494[0];
bool x1573 = x1493[1];
bool x1571;
if (x1570) {
x1571 = true;
} else {
x1571 = false;
}
bool x1574;
if (x1573) {
x1574 = x1572;
} else {
x1574 = false;
}
bool x1575 = x1571 || x1574;
int32_t x1456 = x1453 - x1452;
int32_t x1457 = x1456 / 2;
int32_t x1458 = x1452 + x1457;
int32_t x1956;
if (x1575) {
int32_t x1576 = x47[x1458];
char* x1577 = x32[x1576];
int32_t x1578 = x33[x1576];
char* x1579 = x34[x1576];
int32_t x1580 = x35[x1576];
double x1581 = x36[x1576];
double x1582 = x37[x1576];
double x1583 = x38[x1576];
double x1584 = x39[x1576];
double x1585 = x40[x1576];
int32_t x1586 = x41[x1576];
double x1587 = x42[x1576];
int32_t x1588 = x43[x1576];
double x1589 = x44[x1576];
int32_t x1590 = x45[x1576];
int32_t x1591 = x46[x1576];
int32_t x1592 = 0;
int32_t x1593 = 0;
bool* x1594 = (bool*)malloc(2 * sizeof(bool));
bool* x1595 = (bool*)malloc(2 * sizeof(bool));
int32_t x1596 = 0;
for (;;) {
int32_t x1597 = x1596;
bool x1598 = x1597 < x1477;
bool x1600;
if (x1598) {
bool x1599 = x1597 < x1578;
x1600 = x1599;
} else {
x1600 = false;
}
bool x1604;
if (x1600) {
char x1601 = x1476[x1597];
char x1602 = x1577[x1597];
bool x1603 = x1601 == x1602;
x1604 = x1603;
} else {
x1604 = false;
}
if (!x1604) break;
x1596 += 1;
}
int32_t x1609 = x1596;
char x1610 = x1476[x1609];
char x1611 = x1577[x1609];
bool x1612 = x1610 < x1611;
x1594[0] = x1612;
bool x1615 = x1477 == x1578;
bool x1630;
if (x1615) {
int32_t x1616 = 0;
for (;;) {
int32_t x1617 = x1616;
bool x1618 = x1617 < x1477;
bool x1622;
if (x1618) {
char x1619 = x1476[x1617];
char x1620 = x1577[x1617];
bool x1621 = x1619 == x1620;
x1622 = x1621;
} else {
x1622 = false;
}
if (!x1622) break;
x1616 += 1;
}
int32_t x1627 = x1616;
bool x1628 = x1627 == x1477;
x1630 = x1628;
} else {
x1630 = false;
}
x1595[0] = x1630;
x1593 += 1;
int32_t x1633 = x1593;
int32_t x1634 = 0;
for (;;) {
int32_t x1635 = x1634;
bool x1636 = x1635 < x1479;
bool x1638;
if (x1636) {
bool x1637 = x1635 < x1580;
x1638 = x1637;
} else {
x1638 = false;
}
bool x1642;
if (x1638) {
char x1639 = x1478[x1635];
char x1640 = x1579[x1635];
bool x1641 = x1639 == x1640;
x1642 = x1641;
} else {
x1642 = false;
}
if (!x1642) break;
x1634 += 1;
}
int32_t x1647 = x1634;
char x1648 = x1478[x1647];
char x1649 = x1579[x1647];
bool x1650 = x1648 < x1649;
x1594[x1633] = x1650;
bool x1653 = x1479 == x1580;
bool x1668;
if (x1653) {
int32_t x1654 = 0;
for (;;) {
int32_t x1655 = x1654;
bool x1656 = x1655 < x1479;
bool x1660;
if (x1656) {
char x1657 = x1478[x1655];
char x1658 = x1579[x1655];
bool x1659 = x1657 == x1658;
x1660 = x1659;
} else {
x1660 = false;
}
if (!x1660) break;
x1654 += 1;
}
int32_t x1665 = x1654;
bool x1666 = x1665 == x1479;
x1668 = x1666;
} else {
x1668 = false;
}
x1595[x1633] = x1668;
x1593 += 1;
bool x1671 = x1594[0];
bool x1673 = x1595[0];
bool x1674 = x1594[1];
bool x1672;
if (x1671) {
x1672 = true;
} else {
x1672 = false;
}
bool x1675;
if (x1674) {
x1675 = x1673;
} else {
x1675 = false;
}
bool x1676 = x1672 || x1675;
int32_t x1764;
if (x1676) {
x1764 = x1453;
} else {
int32_t x1677 = 0;
int32_t x1678 = 0;
bool* x1679 = (bool*)malloc(2 * sizeof(bool));
bool* x1680 = (bool*)malloc(2 * sizeof(bool));
int32_t x1681 = 0;
for (;;) {
int32_t x1682 = x1681;
bool x1683 = x1682 < x1578;
bool x1685;
if (x1683) {
bool x1684 = x1682 < x1461;
x1685 = x1684;
} else {
x1685 = false;
}
bool x1689;
if (x1685) {
char x1686 = x1577[x1682];
char x1687 = x1460[x1682];
bool x1688 = x1686 == x1687;
x1689 = x1688;
} else {
x1689 = false;
}
if (!x1689) break;
x1681 += 1;
}
int32_t x1694 = x1681;
char x1695 = x1577[x1694];
char x1696 = x1460[x1694];
bool x1697 = x1695 < x1696;
x1679[0] = x1697;
bool x1700 = x1578 == x1461;
bool x1715;
if (x1700) {
int32_t x1701 = 0;
for (;;) {
int32_t x1702 = x1701;
bool x1703 = x1702 < x1578;
bool x1707;
if (x1703) {
char x1704 = x1577[x1702];
char x1705 = x1460[x1702];
bool x1706 = x1704 == x1705;
x1707 = x1706;
} else {
x1707 = false;
}
if (!x1707) break;
x1701 += 1;
}
int32_t x1712 = x1701;
bool x1713 = x1712 == x1578;
x1715 = x1713;
} else {
x1715 = false;
}
x1680[0] = x1715;
x1678 += 1;
int32_t x1718 = x1678;
int32_t x1719 = 0;
for (;;) {
int32_t x1720 = x1719;
bool x1721 = x1720 < x1580;
bool x1723;
if (x1721) {
bool x1722 = x1720 < x1463;
x1723 = x1722;
} else {
x1723 = false;
}
bool x1727;
if (x1723) {
char x1724 = x1579[x1720];
char x1725 = x1462[x1720];
bool x1726 = x1724 == x1725;
x1727 = x1726;
} else {
x1727 = false;
}
if (!x1727) break;
x1719 += 1;
}
int32_t x1732 = x1719;
char x1733 = x1579[x1732];
char x1734 = x1462[x1732];
bool x1735 = x1733 < x1734;
x1679[x1718] = x1735;
bool x1738 = x1580 == x1463;
bool x1753;
if (x1738) {
int32_t x1739 = 0;
for (;;) {
int32_t x1740 = x1739;
bool x1741 = x1740 < x1580;
bool x1745;
if (x1741) {
char x1742 = x1579[x1740];
char x1743 = x1462[x1740];
bool x1744 = x1742 == x1743;
x1745 = x1744;
} else {
x1745 = false;
}
if (!x1745) break;
x1739 += 1;
}
int32_t x1750 = x1739;
bool x1751 = x1750 == x1580;
x1753 = x1751;
} else {
x1753 = false;
}
x1680[x1718] = x1753;
x1678 += 1;
bool x1756 = x1679[0];
bool x1758 = x1680[0];
bool x1759 = x1679[1];
bool x1757;
if (x1756) {
x1757 = true;
} else {
x1757 = false;
}
bool x1760;
if (x1759) {
x1760 = x1758;
} else {
x1760 = false;
}
bool x1761 = x1757 || x1760;
int32_t x1762;
if (x1761) {
x1762 = x1452;
} else {
x1762 = x1458;
}
x1764 = x1762;
}
x1956 = x1764;
} else {
int32_t x1766 = x47[x1458];
char* x1767 = x32[x1766];
int32_t x1768 = x33[x1766];
char* x1769 = x34[x1766];
int32_t x1770 = x35[x1766];
double x1771 = x36[x1766];
double x1772 = x37[x1766];
double x1773 = x38[x1766];
double x1774 = x39[x1766];
double x1775 = x40[x1766];
int32_t x1776 = x41[x1766];
double x1777 = x42[x1766];
int32_t x1778 = x43[x1766];
double x1779 = x44[x1766];
int32_t x1780 = x45[x1766];
int32_t x1781 = x46[x1766];
int32_t x1782 = 0;
int32_t x1783 = 0;
bool* x1784 = (bool*)malloc(2 * sizeof(bool));
bool* x1785 = (bool*)malloc(2 * sizeof(bool));
int32_t x1786 = 0;
for (;;) {
int32_t x1787 = x1786;
bool x1788 = x1787 < x1461;
bool x1790;
if (x1788) {
bool x1789 = x1787 < x1768;
x1790 = x1789;
} else {
x1790 = false;
}
bool x1794;
if (x1790) {
char x1791 = x1460[x1787];
char x1792 = x1767[x1787];
bool x1793 = x1791 == x1792;
x1794 = x1793;
} else {
x1794 = false;
}
if (!x1794) break;
x1786 += 1;
}
int32_t x1799 = x1786;
char x1800 = x1460[x1799];
char x1801 = x1767[x1799];
bool x1802 = x1800 < x1801;
x1784[0] = x1802;
bool x1805 = x1461 == x1768;
bool x1820;
if (x1805) {
int32_t x1806 = 0;
for (;;) {
int32_t x1807 = x1806;
bool x1808 = x1807 < x1461;
bool x1812;
if (x1808) {
char x1809 = x1460[x1807];
char x1810 = x1767[x1807];
bool x1811 = x1809 == x1810;
x1812 = x1811;
} else {
x1812 = false;
}
if (!x1812) break;
x1806 += 1;
}
int32_t x1817 = x1806;
bool x1818 = x1817 == x1461;
x1820 = x1818;
} else {
x1820 = false;
}
x1785[0] = x1820;
x1783 += 1;
int32_t x1823 = x1783;
int32_t x1824 = 0;
for (;;) {
int32_t x1825 = x1824;
bool x1826 = x1825 < x1463;
bool x1828;
if (x1826) {
bool x1827 = x1825 < x1770;
x1828 = x1827;
} else {
x1828 = false;
}
bool x1832;
if (x1828) {
char x1829 = x1462[x1825];
char x1830 = x1769[x1825];
bool x1831 = x1829 == x1830;
x1832 = x1831;
} else {
x1832 = false;
}
if (!x1832) break;
x1824 += 1;
}
int32_t x1837 = x1824;
char x1838 = x1462[x1837];
char x1839 = x1769[x1837];
bool x1840 = x1838 < x1839;
x1784[x1823] = x1840;
bool x1843 = x1463 == x1770;
bool x1858;
if (x1843) {
int32_t x1844 = 0;
for (;;) {
int32_t x1845 = x1844;
bool x1846 = x1845 < x1463;
bool x1850;
if (x1846) {
char x1847 = x1462[x1845];
char x1848 = x1769[x1845];
bool x1849 = x1847 == x1848;
x1850 = x1849;
} else {
x1850 = false;
}
if (!x1850) break;
x1844 += 1;
}
int32_t x1855 = x1844;
bool x1856 = x1855 == x1463;
x1858 = x1856;
} else {
x1858 = false;
}
x1785[x1823] = x1858;
x1783 += 1;
bool x1861 = x1784[0];
bool x1863 = x1785[0];
bool x1864 = x1784[1];
bool x1862;
if (x1861) {
x1862 = true;
} else {
x1862 = false;
}
bool x1865;
if (x1864) {
x1865 = x1863;
} else {
x1865 = false;
}
bool x1866 = x1862 || x1865;
int32_t x1954;
if (x1866) {
x1954 = x1452;
} else {
int32_t x1867 = 0;
int32_t x1868 = 0;
bool* x1869 = (bool*)malloc(2 * sizeof(bool));
bool* x1870 = (bool*)malloc(2 * sizeof(bool));
int32_t x1871 = 0;
for (;;) {
int32_t x1872 = x1871;
bool x1873 = x1872 < x1768;
bool x1875;
if (x1873) {
bool x1874 = x1872 < x1477;
x1875 = x1874;
} else {
x1875 = false;
}
bool x1879;
if (x1875) {
char x1876 = x1767[x1872];
char x1877 = x1476[x1872];
bool x1878 = x1876 == x1877;
x1879 = x1878;
} else {
x1879 = false;
}
if (!x1879) break;
x1871 += 1;
}
int32_t x1884 = x1871;
char x1885 = x1767[x1884];
char x1886 = x1476[x1884];
bool x1887 = x1885 < x1886;
x1869[0] = x1887;
bool x1890 = x1768 == x1477;
bool x1905;
if (x1890) {
int32_t x1891 = 0;
for (;;) {
int32_t x1892 = x1891;
bool x1893 = x1892 < x1768;
bool x1897;
if (x1893) {
char x1894 = x1767[x1892];
char x1895 = x1476[x1892];
bool x1896 = x1894 == x1895;
x1897 = x1896;
} else {
x1897 = false;
}
if (!x1897) break;
x1891 += 1;
}
int32_t x1902 = x1891;
bool x1903 = x1902 == x1768;
x1905 = x1903;
} else {
x1905 = false;
}
x1870[0] = x1905;
x1868 += 1;
int32_t x1908 = x1868;
int32_t x1909 = 0;
for (;;) {
int32_t x1910 = x1909;
bool x1911 = x1910 < x1770;
bool x1913;
if (x1911) {
bool x1912 = x1910 < x1479;
x1913 = x1912;
} else {
x1913 = false;
}
bool x1917;
if (x1913) {
char x1914 = x1769[x1910];
char x1915 = x1478[x1910];
bool x1916 = x1914 == x1915;
x1917 = x1916;
} else {
x1917 = false;
}
if (!x1917) break;
x1909 += 1;
}
int32_t x1922 = x1909;
char x1923 = x1769[x1922];
char x1924 = x1478[x1922];
bool x1925 = x1923 < x1924;
x1869[x1908] = x1925;
bool x1928 = x1770 == x1479;
bool x1943;
if (x1928) {
int32_t x1929 = 0;
for (;;) {
int32_t x1930 = x1929;
bool x1931 = x1930 < x1770;
bool x1935;
if (x1931) {
char x1932 = x1769[x1930];
char x1933 = x1478[x1930];
bool x1934 = x1932 == x1933;
x1935 = x1934;
} else {
x1935 = false;
}
if (!x1935) break;
x1929 += 1;
}
int32_t x1940 = x1929;
bool x1941 = x1940 == x1770;
x1943 = x1941;
} else {
x1943 = false;
}
x1870[x1908] = x1943;
x1868 += 1;
bool x1946 = x1869[0];
bool x1948 = x1870[0];
bool x1949 = x1869[1];
bool x1947;
if (x1946) {
x1947 = true;
} else {
x1947 = false;
}
bool x1950;
if (x1949) {
x1950 = x1948;
} else {
x1950 = false;
}
bool x1951 = x1947 || x1950;
int32_t x1952;
if (x1951) {
x1952 = x1453;
} else {
x1952 = x1458;
}
x1954 = x1952;
}
x1956 = x1954;
}
int32_t x1957 = x47[x1956];
for (;;) {
int32_t x1958 = x1454;
int32_t x1959 = x1455;
bool x1960 = x1958 <= x1959;
if (!x1960) break;
for (;;) {
int32_t x1962 = x1454;
int32_t x1963 = x47[x1962];
char* x1964 = x32[x1963];
int32_t x1965 = x33[x1963];
char* x1966 = x34[x1963];
int32_t x1967 = x35[x1963];
double x1968 = x36[x1963];
double x1969 = x37[x1963];
double x1970 = x38[x1963];
double x1971 = x39[x1963];
double x1972 = x40[x1963];
int32_t x1973 = x41[x1963];
double x1974 = x42[x1963];
int32_t x1975 = x43[x1963];
double x1976 = x44[x1963];
int32_t x1977 = x45[x1963];
int32_t x1978 = x46[x1963];
char* x1979 = x32[x1957];
int32_t x1980 = x33[x1957];
char* x1981 = x34[x1957];
int32_t x1982 = x35[x1957];
double x1983 = x36[x1957];
double x1984 = x37[x1957];
double x1985 = x38[x1957];
double x1986 = x39[x1957];
double x1987 = x40[x1957];
int32_t x1988 = x41[x1957];
double x1989 = x42[x1957];
int32_t x1990 = x43[x1957];
double x1991 = x44[x1957];
int32_t x1992 = x45[x1957];
int32_t x1993 = x46[x1957];
int32_t x1994 = 0;
int32_t x1995 = 0;
bool* x1996 = (bool*)malloc(2 * sizeof(bool));
bool* x1997 = (bool*)malloc(2 * sizeof(bool));
int32_t x1998 = 0;
for (;;) {
int32_t x1999 = x1998;
bool x2000 = x1999 < x1965;
bool x2002;
if (x2000) {
bool x2001 = x1999 < x1980;
x2002 = x2001;
} else {
x2002 = false;
}
bool x2006;
if (x2002) {
char x2003 = x1964[x1999];
char x2004 = x1979[x1999];
bool x2005 = x2003 == x2004;
x2006 = x2005;
} else {
x2006 = false;
}
if (!x2006) break;
x1998 += 1;
}
int32_t x2011 = x1998;
char x2012 = x1964[x2011];
char x2013 = x1979[x2011];
bool x2014 = x2012 < x2013;
x1996[0] = x2014;
bool x2017 = x1965 == x1980;
bool x2032;
if (x2017) {
int32_t x2018 = 0;
for (;;) {
int32_t x2019 = x2018;
bool x2020 = x2019 < x1965;
bool x2024;
if (x2020) {
char x2021 = x1964[x2019];
char x2022 = x1979[x2019];
bool x2023 = x2021 == x2022;
x2024 = x2023;
} else {
x2024 = false;
}
if (!x2024) break;
x2018 += 1;
}
int32_t x2029 = x2018;
bool x2030 = x2029 == x1965;
x2032 = x2030;
} else {
x2032 = false;
}
x1997[0] = x2032;
x1995 += 1;
int32_t x2035 = x1995;
int32_t x2036 = 0;
for (;;) {
int32_t x2037 = x2036;
bool x2038 = x2037 < x1967;
bool x2040;
if (x2038) {
bool x2039 = x2037 < x1982;
x2040 = x2039;
} else {
x2040 = false;
}
bool x2044;
if (x2040) {
char x2041 = x1966[x2037];
char x2042 = x1981[x2037];
bool x2043 = x2041 == x2042;
x2044 = x2043;
} else {
x2044 = false;
}
if (!x2044) break;
x2036 += 1;
}
int32_t x2049 = x2036;
char x2050 = x1966[x2049];
char x2051 = x1981[x2049];
bool x2052 = x2050 < x2051;
x1996[x2035] = x2052;
bool x2055 = x1967 == x1982;
bool x2070;
if (x2055) {
int32_t x2056 = 0;
for (;;) {
int32_t x2057 = x2056;
bool x2058 = x2057 < x1967;
bool x2062;
if (x2058) {
char x2059 = x1966[x2057];
char x2060 = x1981[x2057];
bool x2061 = x2059 == x2060;
x2062 = x2061;
} else {
x2062 = false;
}
if (!x2062) break;
x2056 += 1;
}
int32_t x2067 = x2056;
bool x2068 = x2067 == x1967;
x2070 = x2068;
} else {
x2070 = false;
}
x1997[x2035] = x2070;
x1995 += 1;
bool x2073 = x1996[0];
bool x2075 = x1997[0];
bool x2076 = x1996[1];
bool x2074;
if (x2073) {
x2074 = true;
} else {
x2074 = false;
}
bool x2077;
if (x2076) {
x2077 = x2075;
} else {
x2077 = false;
}
bool x2078 = x2074 || x2077;
if (!x2078) break;
int32_t x2080 = x1454;
int32_t x2081 = x2080 + 1;
x1454 = x2081;
}
for (;;) {
char* x2085 = x32[x1957];
int32_t x2086 = x33[x1957];
char* x2087 = x34[x1957];
int32_t x2088 = x35[x1957];
double x2089 = x36[x1957];
double x2090 = x37[x1957];
double x2091 = x38[x1957];
double x2092 = x39[x1957];
double x2093 = x40[x1957];
int32_t x2094 = x41[x1957];
double x2095 = x42[x1957];
int32_t x2096 = x43[x1957];
double x2097 = x44[x1957];
int32_t x2098 = x45[x1957];
int32_t x2099 = x46[x1957];
int32_t x2100 = x1455;
int32_t x2101 = x47[x2100];
char* x2102 = x32[x2101];
int32_t x2103 = x33[x2101];
char* x2104 = x34[x2101];
int32_t x2105 = x35[x2101];
double x2106 = x36[x2101];
double x2107 = x37[x2101];
double x2108 = x38[x2101];
double x2109 = x39[x2101];
double x2110 = x40[x2101];
int32_t x2111 = x41[x2101];
double x2112 = x42[x2101];
int32_t x2113 = x43[x2101];
double x2114 = x44[x2101];
int32_t x2115 = x45[x2101];
int32_t x2116 = x46[x2101];
int32_t x2117 = 0;
int32_t x2118 = 0;
bool* x2119 = (bool*)malloc(2 * sizeof(bool));
bool* x2120 = (bool*)malloc(2 * sizeof(bool));
int32_t x2121 = 0;
for (;;) {
int32_t x2122 = x2121;
bool x2123 = x2122 < x2086;
bool x2125;
if (x2123) {
bool x2124 = x2122 < x2103;
x2125 = x2124;
} else {
x2125 = false;
}
bool x2129;
if (x2125) {
char x2126 = x2085[x2122];
char x2127 = x2102[x2122];
bool x2128 = x2126 == x2127;
x2129 = x2128;
} else {
x2129 = false;
}
if (!x2129) break;
x2121 += 1;
}
int32_t x2134 = x2121;
char x2135 = x2085[x2134];
char x2136 = x2102[x2134];
bool x2137 = x2135 < x2136;
x2119[0] = x2137;
bool x2140 = x2086 == x2103;
bool x2155;
if (x2140) {
int32_t x2141 = 0;
for (;;) {
int32_t x2142 = x2141;
bool x2143 = x2142 < x2086;
bool x2147;
if (x2143) {
char x2144 = x2085[x2142];
char x2145 = x2102[x2142];
bool x2146 = x2144 == x2145;
x2147 = x2146;
} else {
x2147 = false;
}
if (!x2147) break;
x2141 += 1;
}
int32_t x2152 = x2141;
bool x2153 = x2152 == x2086;
x2155 = x2153;
} else {
x2155 = false;
}
x2120[0] = x2155;
x2118 += 1;
int32_t x2158 = x2118;
int32_t x2159 = 0;
for (;;) {
int32_t x2160 = x2159;
bool x2161 = x2160 < x2088;
bool x2163;
if (x2161) {
bool x2162 = x2160 < x2105;
x2163 = x2162;
} else {
x2163 = false;
}
bool x2167;
if (x2163) {
char x2164 = x2087[x2160];
char x2165 = x2104[x2160];
bool x2166 = x2164 == x2165;
x2167 = x2166;
} else {
x2167 = false;
}
if (!x2167) break;
x2159 += 1;
}
int32_t x2172 = x2159;
char x2173 = x2087[x2172];
char x2174 = x2104[x2172];
bool x2175 = x2173 < x2174;
x2119[x2158] = x2175;
bool x2178 = x2088 == x2105;
bool x2193;
if (x2178) {
int32_t x2179 = 0;
for (;;) {
int32_t x2180 = x2179;
bool x2181 = x2180 < x2088;
bool x2185;
if (x2181) {
char x2182 = x2087[x2180];
char x2183 = x2104[x2180];
bool x2184 = x2182 == x2183;
x2185 = x2184;
} else {
x2185 = false;
}
if (!x2185) break;
x2179 += 1;
}
int32_t x2190 = x2179;
bool x2191 = x2190 == x2088;
x2193 = x2191;
} else {
x2193 = false;
}
x2120[x2158] = x2193;
x2118 += 1;
bool x2196 = x2119[0];
bool x2198 = x2120[0];
bool x2199 = x2119[1];
bool x2197;
if (x2196) {
x2197 = true;
} else {
x2197 = false;
}
bool x2200;
if (x2199) {
x2200 = x2198;
} else {
x2200 = false;
}
bool x2201 = x2197 || x2200;
if (!x2201) break;
int32_t x2203 = x1455;
int32_t x2204 = x2203 - 1;
x1455 = x2204;
}
int32_t x2208 = x1454;
int32_t x2209 = x1455;
bool x2210 = x2208 <= x2209;
if (x2210) {
int32_t x2211 = x47[x2208];
int32_t x2212 = x47[x2209];
x47[x2208] = x2212;
x47[x2209] = x2211;
int32_t x2215 = x2208 + 1;
x1454 = x2215;
int32_t x2217 = x2209 - 1;
x1455 = x2217;
} else {
}
}
int32_t x2223 = x1455;
bool x2224 = x1452 < x2223;
if (x2224) {
x50[x1450] = x1452;
x51[x1450] = x2223;
int32_t x2227 = x1450 + 1;
x1445 = x2227;
} else {
}
int32_t x2231 = x1454;
bool x2232 = x2231 < x1453;
if (x2232) {
int32_t x2233 = x1445;
x50[x2233] = x2231;
x51[x2233] = x1453;
int32_t x2236 = x2233 + 1;
x1445 = x2236;
} else {
}
}
for(int x2243=0; x2243 < x1441; x2243++) {
int32_t x2244 = x47[x2243];
char* x2245 = x32[x2244];
int32_t x2246 = x33[x2244];
char* x2247 = x34[x2244];
int32_t x2248 = x35[x2244];
double x2249 = x36[x2244];
double x2250 = x37[x2244];
double x2251 = x38[x2244];
double x2252 = x39[x2244];
double x2253 = x40[x2244];
int32_t x2254 = x41[x2244];
double x2255 = x42[x2244];
int32_t x2256 = x43[x2244];
double x2257 = x44[x2244];
int32_t x2258 = x45[x2244];
int32_t x2259 = x46[x2244];
int32_t x2260 = printll(x2245);
printf(",");
int32_t x2262 = printll(x2247);
printf(",");
printf("%f",x2249);
printf(",");
printf("%f",x2250);
printf(",");
printf("%f",x2251);
printf(",");
printf("%f",x2252);
printf(",");
double x2273 = (double)x2254;
double x2274 = x2253 / x2273;
printf("%f",x2274);
printf(",");
double x2278 = (double)x2256;
double x2279 = x2255 / x2278;
printf("%f",x2279);
printf(",");
double x2283 = (double)x2258;
double x2284 = x2257 / x2283;
printf("%f",x2284);
printf(",");
printf("%d",x2259);
printf("%s\n","");

}
end = cur_time();
print_performance(begin, end);
}
/*****************************************
  End of C Generated Code                  
*******************************************/

