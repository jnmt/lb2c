
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

      
/*****************************************
  Emitting C Generated Code                  
*******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
void Snippet(int32_t  x1) {
int32_t* x2 = (int32_t*)malloc(268435456 * sizeof(int32_t));
char** x3 = (char**)malloc(268435456 * sizeof(char*));
int32_t* x4 = (int32_t*)malloc(268435456 * sizeof(int32_t));
char** x5 = (char**)malloc(268435456 * sizeof(char*));
int32_t* x6 = (int32_t*)malloc(268435456 * sizeof(int32_t));
char** x7 = (char**)malloc(268435456 * sizeof(char*));
int32_t* x8 = (int32_t*)malloc(268435456 * sizeof(int32_t));
char** x9 = (char**)malloc(268435456 * sizeof(char*));
int32_t* x10 = (int32_t*)malloc(268435456 * sizeof(int32_t));
int32_t* x11 = (int32_t*)malloc(268435456 * sizeof(int32_t));
char** x12 = (char**)malloc(268435456 * sizeof(char*));
int32_t* x13 = (int32_t*)malloc(268435456 * sizeof(int32_t));
double* x14 = (double*)malloc(268435456 * sizeof(double));
char** x15 = (char**)malloc(268435456 * sizeof(char*));
int32_t* x16 = (int32_t*)malloc(268435456 * sizeof(int32_t));
int32_t x17 = 0;
int32_t x18 = 0;
int32_t* x19 = (int32_t*)malloc(268435456 * sizeof(int32_t));
int32_t* x20 = (int32_t*)malloc(268435456 * sizeof(int32_t));
int32_t* x21 = (int32_t*)malloc(268435456 * sizeof(int32_t));
int32_t* x22 = (int32_t*)malloc(268435456 * sizeof(int32_t));
double* x23 = (double*)malloc(268435456 * sizeof(double));
double* x24 = (double*)malloc(268435456 * sizeof(double));
double* x25 = (double*)malloc(268435456 * sizeof(double));
double* x26 = (double*)malloc(268435456 * sizeof(double));
char** x27 = (char**)malloc(268435456 * sizeof(char*));
int32_t* x28 = (int32_t*)malloc(268435456 * sizeof(int32_t));
char** x29 = (char**)malloc(268435456 * sizeof(char*));
int32_t* x30 = (int32_t*)malloc(268435456 * sizeof(int32_t));
int32_t* x31 = (int32_t*)malloc(268435456 * sizeof(int32_t));
int32_t* x32 = (int32_t*)malloc(268435456 * sizeof(int32_t));
int32_t* x33 = (int32_t*)malloc(268435456 * sizeof(int32_t));
int32_t* x34 = (int32_t*)malloc(268435456 * sizeof(int32_t));
int32_t* x35 = (int32_t*)malloc(268435456 * sizeof(int32_t));
int32_t* x36 = (int32_t*)malloc(268435456 * sizeof(int32_t));
int32_t* x37 = (int32_t*)malloc(268435456 * sizeof(int32_t));
int32_t* x38 = (int32_t*)malloc(268435456 * sizeof(int32_t));
int32_t* x39 = (int32_t*)malloc(268435456 * sizeof(int32_t));
char** x40 = (char**)malloc(268435456 * sizeof(char*));
int32_t* x41 = (int32_t*)malloc(268435456 * sizeof(int32_t));
char** x42 = (char**)malloc(268435456 * sizeof(char*));
int32_t* x43 = (int32_t*)malloc(268435456 * sizeof(int32_t));
char** x44 = (char**)malloc(268435456 * sizeof(char*));
int32_t* x45 = (int32_t*)malloc(268435456 * sizeof(int32_t));
int32_t x46 = 0;
int32_t x47 = 0;
printf("%s\n","sum_cw,sum_x,promo_revenue");
int32_t x49 = HASH_TABLE_SIZE;
double* x50 = (double*)malloc(x49 * sizeof(double));
double* x51 = (double*)malloc(x49 * sizeof(double));
bool* x52 = (bool*)malloc(x49 * sizeof(bool));
for(int x54=0; x54 < x49; x54++) {
x52[x54] = false;

}
int32_t* x58 = (int32_t*)malloc(x49 * sizeof(int32_t));
int32_t x59 = 0;
int32_t x60 = 0;
int32_t* x62 = (int32_t*)malloc(x49 * sizeof(int32_t));
int32_t x61 = BUCKET_SIZE;
int32_t x63 = x49 * x61;
int32_t* x64 = (int32_t*)malloc(x63 * sizeof(int32_t));
char** x65 = (char**)malloc(x63 * sizeof(char*));
int32_t* x66 = (int32_t*)malloc(x63 * sizeof(int32_t));
char** x67 = (char**)malloc(x63 * sizeof(char*));
int32_t* x68 = (int32_t*)malloc(x63 * sizeof(int32_t));
char** x69 = (char**)malloc(x63 * sizeof(char*));
int32_t* x70 = (int32_t*)malloc(x63 * sizeof(int32_t));
char** x71 = (char**)malloc(x63 * sizeof(char*));
int32_t* x72 = (int32_t*)malloc(x63 * sizeof(int32_t));
int32_t* x73 = (int32_t*)malloc(x63 * sizeof(int32_t));
char** x74 = (char**)malloc(x63 * sizeof(char*));
int32_t* x75 = (int32_t*)malloc(x63 * sizeof(int32_t));
double* x76 = (double*)malloc(x63 * sizeof(double));
char** x77 = (char**)malloc(x63 * sizeof(char*));
int32_t* x78 = (int32_t*)malloc(x63 * sizeof(int32_t));
int32_t* x79 = (int32_t*)malloc(x49 * sizeof(int32_t));
for(int x80=0; x80 < x49; x80++) {
x79[x80] = 0;

}
int32_t* x84 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x85 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x86 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x87 = (int32_t*)malloc(16 * sizeof(int32_t));
double* x88 = (double*)malloc(16 * sizeof(double));
double* x89 = (double*)malloc(16 * sizeof(double));
double* x90 = (double*)malloc(16 * sizeof(double));
double* x91 = (double*)malloc(16 * sizeof(double));
char** x92 = (char**)malloc(16 * sizeof(char*));
int32_t* x93 = (int32_t*)malloc(16 * sizeof(int32_t));
char** x94 = (char**)malloc(16 * sizeof(char*));
int32_t* x95 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x96 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x97 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x98 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x99 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x100 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x101 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x102 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x103 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x104 = (int32_t*)malloc(16 * sizeof(int32_t));
char** x105 = (char**)malloc(16 * sizeof(char*));
int32_t* x106 = (int32_t*)malloc(16 * sizeof(int32_t));
char** x107 = (char**)malloc(16 * sizeof(char*));
int32_t* x108 = (int32_t*)malloc(16 * sizeof(int32_t));
char** x109 = (char**)malloc(16 * sizeof(char*));
int32_t* x110 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t x111 = 0;
int32_t x112 = 0;
int32_t* x114 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t x118 = 0;
int32_t x115 = open("/Users/jun/src/tpch-dbgen/part.tbl",0);
int32_t x116 = fsize(x115);
int32_t x119 = x116;
char* x117 = (char*)mmap(0, x116, PROT_READ, MAP_FILE | MAP_SHARED, x115, 0);
for (;;) {
int32_t x120 = x118;
int32_t x121 = x119;
bool x122 = x120 < x121;
if (!x122) break;
int32_t x124 = x118;
int32_t x125 = 0;
for (;;) {
int32_t x126 = x118;
char x127 = x117[x126];
bool x128 = x127 != '|';
if (!x128) break;
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
if (!x145) break;
x118 += 1;
}
int32_t x150 = x118;
x118 += 1;
int32_t x154 = x118;
for (;;) {
int32_t x155 = x118;
char x156 = x117[x155];
bool x157 = x156 != '|';
if (!x157) break;
x118 += 1;
}
int32_t x162 = x118;
x118 += 1;
int32_t x166 = x118;
for (;;) {
int32_t x167 = x118;
char x168 = x117[x167];
bool x169 = x168 != '|';
if (!x169) break;
x118 += 1;
}
int32_t x174 = x118;
x118 += 1;
int32_t x178 = x118;
for (;;) {
int32_t x179 = x118;
char x180 = x117[x179];
bool x181 = x180 != '|';
if (!x181) break;
x118 += 1;
}
int32_t x186 = x118;
x118 += 1;
int32_t x190 = x118;
int32_t x191 = 0;
for (;;) {
int32_t x192 = x118;
char x193 = x117[x192];
bool x194 = x193 != '|';
if (!x194) break;
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
if (!x211) break;
x118 += 1;
}
int32_t x216 = x118;
x118 += 1;
int32_t x220 = x118;
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
if (!x228) break;
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
if (!x249) break;
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
if (!x273) break;
x118 += 1;
}
int32_t x278 = x118;
x118 += 1;
int32_t x282 = x18;
x2[x282] = x141;
char* x153 = x117 + x142;
x3[x282] = x153;
int32_t x151 = x150 - x142;
x4[x282] = x151;
char* x165 = x117 + x154;
x5[x282] = x165;
int32_t x163 = x162 - x154;
x6[x282] = x163;
char* x177 = x117 + x166;
x7[x282] = x177;
int32_t x175 = x174 - x166;
x8[x282] = x175;
char* x189 = x117 + x178;
x9[x282] = x189;
int32_t x187 = x186 - x178;
x10[x282] = x187;
x11[x282] = x207;
char* x219 = x117 + x208;
x12[x282] = x219;
int32_t x217 = x216 - x208;
x13[x282] = x217;
x14[x282] = x269;
char* x281 = x117 + x270;
x15[x282] = x281;
int32_t x279 = x278 - x270;
x16[x282] = x279;
x18 += 1;
}
close(x115);
int32_t x305 = 0;
int32_t x302 = open("/Users/jun/src/tpch-dbgen/lineitem.tbl",0);
int32_t x303 = fsize(x302);
int32_t x306 = x303;
char* x304 = (char*)mmap(0, x303, PROT_READ, MAP_FILE | MAP_SHARED, x302, 0);
for (;;) {
int32_t x307 = x305;
int32_t x308 = x306;
bool x309 = x307 < x308;
if (!x309) break;
int32_t x311 = x305;
int32_t x312 = 0;
for (;;) {
int32_t x313 = x305;
char x314 = x304[x313];
bool x315 = x314 != '|';
if (!x315) break;
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
int32_t x329 = x305;
int32_t x330 = 0;
for (;;) {
int32_t x331 = x305;
char x332 = x304[x331];
bool x333 = x332 != '|';
if (!x333) break;
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
int32_t x347 = x305;
int32_t x348 = 0;
for (;;) {
int32_t x349 = x305;
char x350 = x304[x349];
bool x351 = x350 != '|';
if (!x351) break;
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
int32_t x365 = x305;
int32_t x366 = 0;
for (;;) {
int32_t x367 = x305;
char x368 = x304[x367];
bool x369 = x368 != '|';
if (!x369) break;
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
int32_t x383 = x305;
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
if (!x391) break;
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
if (!x412) break;
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
int32_t x433 = x305;
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
if (!x441) break;
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
if (!x462) break;
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
int32_t x483 = x305;
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
if (!x491) break;
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
if (!x512) break;
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
int32_t x533 = x305;
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
if (!x541) break;
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
if (!x562) break;
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
if (!x586) break;
x305 += 1;
}
int32_t x591 = x305;
x305 += 1;
int32_t x595 = x305;
for (;;) {
int32_t x596 = x305;
char x597 = x304[x596];
bool x598 = x597 != '|';
if (!x598) break;
x305 += 1;
}
int32_t x603 = x305;
x305 += 1;
int32_t x607 = x305;
int32_t x608 = 0;
int32_t x609 = 0;
int32_t x610 = 0;
for (;;) {
int32_t x611 = x305;
char x612 = x304[x611];
bool x613 = x612 != '-';
if (!x613) break;
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
if (!x628) break;
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
if (!x643) break;
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
int32_t x659 = x305;
int32_t x660 = 0;
int32_t x661 = 0;
int32_t x662 = 0;
for (;;) {
int32_t x663 = x305;
char x664 = x304[x663];
bool x665 = x664 != '-';
if (!x665) break;
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
if (!x680) break;
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
if (!x695) break;
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
int32_t x711 = x305;
int32_t x712 = 0;
int32_t x713 = 0;
int32_t x714 = 0;
for (;;) {
int32_t x715 = x305;
char x716 = x304[x715];
bool x717 = x716 != '-';
if (!x717) break;
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
if (!x732) break;
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
if (!x747) break;
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
if (!x766) break;
x305 += 1;
}
int32_t x771 = x305;
x305 += 1;
int32_t x775 = x305;
for (;;) {
int32_t x776 = x305;
char x777 = x304[x776];
bool x778 = x777 != '|';
if (!x778) break;
x305 += 1;
}
int32_t x783 = x305;
x305 += 1;
int32_t x787 = x305;
for (;;) {
int32_t x788 = x305;
char x789 = x304[x788];
bool x790 = x789 != '\n';
if (!x790) break;
x305 += 1;
}
int32_t x795 = x305;
x305 += 1;
int32_t x799 = x47;
x19[x799] = x328;
x20[x799] = x346;
x21[x799] = x364;
x22[x799] = x382;
x23[x799] = x432;
x24[x799] = x482;
x25[x799] = x532;
x26[x799] = x582;
char* x594 = x304 + x583;
x27[x799] = x594;
int32_t x592 = x591 - x583;
x28[x799] = x592;
char* x606 = x304 + x595;
x29[x799] = x606;
int32_t x604 = x603 - x595;
x30[x799] = x604;
x31[x799] = x656;
x32[x799] = x657;
x33[x799] = x658;
x34[x799] = x708;
x35[x799] = x709;
x36[x799] = x710;
x37[x799] = x760;
x38[x799] = x761;
x39[x799] = x762;
char* x774 = x304 + x763;
x40[x799] = x774;
int32_t x772 = x771 - x763;
x41[x799] = x772;
char* x786 = x304 + x775;
x42[x799] = x786;
int32_t x784 = x783 - x775;
x43[x799] = x784;
char* x798 = x304 + x787;
x44[x799] = x798;
int32_t x796 = x795 - x787;
x45[x799] = x796;
x47 += 1;
}
close(x302);
int32_t x870 = x49 - 1;
int32_t x877 = x61 - 1;
__m512i x968 = _mm512_set1_epi32(10000);
__m512i x971 = _mm512_set1_epi32(100);
__m512i x976 = _mm512_set1_epi32(1995);
__m512i x977 = _mm512_mullo_epi32(x976,x968);
__m512i x978 = _mm512_set1_epi32(9);
__m512i x979 = _mm512_mullo_epi32(x978,x971);
__m512i x980 = _mm512_add_epi32(x977,x979);
__m512i x981 = _mm512_set1_epi32(1);
__m512i x982 = _mm512_add_epi32(x980,x981);
__mmask16 x966 = 65535;
__m512i x985 = _mm512_set1_epi32(10);
__m512i x986 = _mm512_mullo_epi32(x985,x971);
__m512i x987 = _mm512_add_epi32(x977,x986);
__m512i x988 = _mm512_add_epi32(x987,x981);
__m512i x113 = _mm512_set_epi32(15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0);
int32_t x1067 = (int32_t)0L;
bool x1068 = x1067 >= 0;
int32_t x1070;
if (x1068) {
x1070 = x1067;
} else {
int32_t x1069 = 0 - x1067;
x1070 = x1069;
}
int32_t x1071 = x1070 % x49;
bool x1075 = !true;
struct timeval begin, end;
begin = cur_time();
int32_t x831 = x18;
for(int x833=0; x833 < x831; x833++) {
int32_t x834 = x2[x833];
char* x835 = x3[x833];
int32_t x836 = x4[x833];
char* x837 = x5[x833];
int32_t x838 = x6[x833];
char* x839 = x7[x833];
int32_t x840 = x8[x833];
char* x841 = x9[x833];
int32_t x842 = x10[x833];
int32_t x843 = x11[x833];
char* x844 = x12[x833];
int32_t x845 = x13[x833];
double x846 = x14[x833];
char* x847 = x15[x833];
int32_t x848 = x16[x833];
int32_t x849 = (int32_t)x834;
bool x850 = x849 >= 0;
int32_t x852;
if (x850) {
x852 = x849;
} else {
int32_t x851 = 0 - x849;
x852 = x851;
}
int32_t x853 = x852 % x49;
int32_t x854 = x853;
for (;;) {
int32_t x855 = x854;
int32_t x856 = x79[x855];
bool x857 = x856 > 0;
bool x862;
if (x857) {
int32_t x858 = x62[x855];
bool x859 = x858 == x834;
bool x860 = !x859;
x862 = x860;
} else {
x862 = false;
}
if (!x862) break;
int32_t x864 = x854;
int32_t x865 = x864 + 1;
x854 = x865;
}
int32_t x869 = x854;
bool x871 = x869 == x870;
if (x871) {
printf("%s\n","LB2HashMultiMap table is full.");
exit(1);
} else {
}
int32_t x876 = x79[x869];
bool x878 = x876 == x877;
if (x878) {
printf("%s\n","Bucket is full.");
exit(1);
} else {
}
x62[x869] = x834;
int32_t x883 = x869 * x61;
int32_t x884 = x883 + x876;
x64[x884] = x834;
x65[x884] = x835;
x66[x884] = x836;
x67[x884] = x837;
x68[x884] = x838;
x69[x884] = x839;
x70[x884] = x840;
x71[x884] = x841;
x72[x884] = x842;
x73[x884] = x843;
x74[x884] = x844;
x75[x884] = x845;
x76[x884] = x846;
x77[x884] = x847;
x78[x884] = x848;
int32_t x901 = x876 + 1;
x79[x869] = x901;

}
int32_t x905 = x47;
for(int x907=0; x907 < x905; x907++) {
int32_t x908 = x19[x907];
int32_t x909 = x20[x907];
int32_t x910 = x21[x907];
int32_t x911 = x22[x907];
double x912 = x23[x907];
double x913 = x24[x907];
double x914 = x25[x907];
double x915 = x26[x907];
char* x916 = x27[x907];
int32_t x917 = x28[x907];
char* x918 = x29[x907];
int32_t x919 = x30[x907];
int32_t x920 = x31[x907];
int32_t x921 = x32[x907];
int32_t x922 = x33[x907];
int32_t x923 = x34[x907];
int32_t x924 = x35[x907];
int32_t x925 = x36[x907];
int32_t x926 = x37[x907];
int32_t x927 = x38[x907];
int32_t x928 = x39[x907];
char* x929 = x40[x907];
int32_t x930 = x41[x907];
char* x931 = x42[x907];
int32_t x932 = x43[x907];
char* x933 = x44[x907];
int32_t x934 = x45[x907];
int32_t x935 = x112;
x84[x935] = x908;
x85[x935] = x909;
x86[x935] = x910;
x87[x935] = x911;
x88[x935] = x912;
x89[x935] = x913;
x90[x935] = x914;
x91[x935] = x915;
x92[x935] = x916;
x93[x935] = x917;
x94[x935] = x918;
x95[x935] = x919;
x96[x935] = x920;
x97[x935] = x921;
x98[x935] = x922;
x99[x935] = x923;
x100[x935] = x924;
x101[x935] = x925;
x102[x935] = x926;
x103[x935] = x927;
x104[x935] = x928;
x105[x935] = x929;
x106[x935] = x930;
x107[x935] = x931;
x108[x935] = x932;
x109[x935] = x933;
x110[x935] = x934;
x112 += 1;
int32_t x964 = x112;
bool x965 = x964 == 16;
if (x965) {
__m512i x967 = _mm512_loadu_si512(x96);
__m512i x969 = _mm512_mullo_epi32(x967,x968);
__m512i x970 = _mm512_loadu_si512(x97);
__m512i x972 = _mm512_mullo_epi32(x970,x971);
__m512i x973 = _mm512_add_epi32(x969,x972);
__m512i x974 = _mm512_loadu_si512(x98);
__m512i x975 = _mm512_add_epi32(x973,x974);
__mmask16 x983 = _mm512_cmpge_epi32_mask(x975,x982);
__mmask16 x984 = _mm512_kand(x966,x983);
__mmask16 x989 = _mm512_cmplt_epi32_mask(x975,x988);
__mmask16 x990 = _mm512_kand(x984,x989);
_mm512_mask_compressstoreu_epi32(x114,x990,x113);
int32_t x992 = _mm_popcnt_u32(x990);
for(int x994=0; x994 < x992; x994++) {
int32_t x995 = x114[x994];
int32_t x996 = x84[x995];
int32_t x997 = x85[x995];
int32_t x998 = x86[x995];
int32_t x999 = x87[x995];
double x1000 = x88[x995];
double x1001 = x89[x995];
double x1002 = x90[x995];
double x1003 = x91[x995];
char* x1004 = x92[x995];
int32_t x1005 = x93[x995];
char* x1006 = x94[x995];
int32_t x1007 = x95[x995];
int32_t x1008 = x96[x995];
int32_t x1009 = x97[x995];
int32_t x1010 = x98[x995];
int32_t x1011 = x99[x995];
int32_t x1012 = x100[x995];
int32_t x1013 = x101[x995];
int32_t x1014 = x102[x995];
int32_t x1015 = x103[x995];
int32_t x1016 = x104[x995];
char* x1017 = x105[x995];
int32_t x1018 = x106[x995];
char* x1019 = x107[x995];
int32_t x1020 = x108[x995];
char* x1021 = x109[x995];
int32_t x1022 = x110[x995];
int32_t x1023 = (int32_t)x997;
bool x1024 = x1023 >= 0;
int32_t x1026;
if (x1024) {
x1026 = x1023;
} else {
int32_t x1025 = 0 - x1023;
x1026 = x1025;
}
int32_t x1027 = x1026 % x49;
int32_t x1028 = x1027;
for (;;) {
int32_t x1029 = x1028;
int32_t x1030 = x79[x1029];
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
if (!x1036) break;
int32_t x1038 = x1028;
int32_t x1039 = x1038 + 1;
x1028 = x1039;
}
int32_t x1043 = x1028;
int32_t x1044 = x79[x1043];
int32_t x1045 = x1043 * x61;
int32_t x1046 = x1045 + x1044;
double x1064 = 1.0 - x1002;
double x1065 = x1001 * x1064;
for(int x1048=x1045; x1048 < x1046; x1048++) {
int32_t x1049 = x64[x1048];
char* x1050 = x65[x1048];
int32_t x1051 = x66[x1048];
char* x1052 = x67[x1048];
int32_t x1053 = x68[x1048];
char* x1054 = x69[x1048];
int32_t x1055 = x70[x1048];
char* x1056 = x71[x1048];
int32_t x1057 = x72[x1048];
int32_t x1058 = x73[x1048];
char* x1059 = x74[x1048];
int32_t x1060 = x75[x1048];
double x1061 = x76[x1048];
char* x1062 = x77[x1048];
int32_t x1063 = x78[x1048];
bool x1066 = pattern_compare(x1056,"PROMO%");
if (x1066) {
int32_t x1072 = x1071;
for (;;) {
int32_t x1073 = x1072;
bool x1074 = x52[x1073];
bool x1076;
if (x1074) {
x1076 = x1075;
} else {
x1076 = false;
}
if (!x1076) break;
x1072 += 1;
}
int32_t x1081 = x1072;
bool x1082 = x1081 == x870;
if (x1082) {
printf("%s\n","LB2HashMap table is full.");
exit(1);
} else {
}
bool x1087 = x52[x1081];
if (x1087) {
double x1088 = x50[x1081];
double x1089 = x51[x1081];
double x1090 = x1088 + x1065;
x50[x1081] = x1090;
double x1091 = x1089 + x1065;
x51[x1081] = x1091;
} else {
int32_t x1095 = x60;
x58[x1095] = x1081;
x60 += 1;
x50[x1081] = x1065;
x51[x1081] = x1065;
x52[x1081] = true;
}
} else {
int32_t x1104 = x1071;
for (;;) {
int32_t x1105 = x1104;
bool x1106 = x52[x1105];
bool x1107;
if (x1106) {
x1107 = x1075;
} else {
x1107 = false;
}
if (!x1107) break;
x1104 += 1;
}
int32_t x1112 = x1104;
bool x1113 = x1112 == x870;
if (x1113) {
printf("%s\n","LB2HashMap table is full.");
exit(1);
} else {
}
bool x1118 = x52[x1112];
if (x1118) {
double x1119 = x50[x1112];
double x1120 = x51[x1112];
x50[x1112] = x1119;
double x1121 = x1120 + x1065;
x51[x1112] = x1121;
} else {
int32_t x1125 = x60;
x58[x1125] = x1112;
x60 += 1;
x50[x1112] = 0.0;
x51[x1112] = x1065;
x52[x1112] = true;
}
}

}

}
x112 = 0;
} else {
}

}
int32_t x1144 = x112;
for(int x1146=0; x1146 < x1144; x1146++) {
int32_t x1147 = x84[x1146];
int32_t x1148 = x85[x1146];
int32_t x1149 = x86[x1146];
int32_t x1150 = x87[x1146];
double x1151 = x88[x1146];
double x1152 = x89[x1146];
double x1153 = x90[x1146];
double x1154 = x91[x1146];
char* x1155 = x92[x1146];
int32_t x1156 = x93[x1146];
char* x1157 = x94[x1146];
int32_t x1158 = x95[x1146];
int32_t x1159 = x96[x1146];
int32_t x1160 = x97[x1146];
int32_t x1161 = x98[x1146];
int32_t x1162 = x99[x1146];
int32_t x1163 = x100[x1146];
int32_t x1164 = x101[x1146];
int32_t x1165 = x102[x1146];
int32_t x1166 = x103[x1146];
int32_t x1167 = x104[x1146];
char* x1168 = x105[x1146];
int32_t x1169 = x106[x1146];
char* x1170 = x107[x1146];
int32_t x1171 = x108[x1146];
char* x1172 = x109[x1146];
int32_t x1173 = x110[x1146];
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
int32_t x1185 = x1184 % x49;
int32_t x1186 = x1185;
for (;;) {
int32_t x1187 = x1186;
int32_t x1188 = x79[x1187];
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
if (!x1194) break;
int32_t x1196 = x1186;
int32_t x1197 = x1196 + 1;
x1186 = x1197;
}
int32_t x1201 = x1186;
int32_t x1202 = x79[x1201];
int32_t x1203 = x1201 * x61;
int32_t x1204 = x1203 + x1202;
double x1222 = 1.0 - x1153;
double x1223 = x1152 * x1222;
for(int x1206=x1203; x1206 < x1204; x1206++) {
int32_t x1207 = x64[x1206];
char* x1208 = x65[x1206];
int32_t x1209 = x66[x1206];
char* x1210 = x67[x1206];
int32_t x1211 = x68[x1206];
char* x1212 = x69[x1206];
int32_t x1213 = x70[x1206];
char* x1214 = x71[x1206];
int32_t x1215 = x72[x1206];
int32_t x1216 = x73[x1206];
char* x1217 = x74[x1206];
int32_t x1218 = x75[x1206];
double x1219 = x76[x1206];
char* x1220 = x77[x1206];
int32_t x1221 = x78[x1206];
bool x1224 = pattern_compare(x1214,"PROMO%");
if (x1224) {
int32_t x1225 = x1071;
for (;;) {
int32_t x1226 = x1225;
bool x1227 = x52[x1226];
bool x1228;
if (x1227) {
x1228 = x1075;
} else {
x1228 = false;
}
if (!x1228) break;
x1225 += 1;
}
int32_t x1233 = x1225;
bool x1234 = x1233 == x870;
if (x1234) {
printf("%s\n","LB2HashMap table is full.");
exit(1);
} else {
}
bool x1239 = x52[x1233];
if (x1239) {
double x1240 = x50[x1233];
double x1241 = x51[x1233];
double x1242 = x1240 + x1223;
x50[x1233] = x1242;
double x1243 = x1241 + x1223;
x51[x1233] = x1243;
} else {
int32_t x1247 = x60;
x58[x1247] = x1233;
x60 += 1;
x50[x1233] = x1223;
x51[x1233] = x1223;
x52[x1233] = true;
}
} else {
int32_t x1256 = x1071;
for (;;) {
int32_t x1257 = x1256;
bool x1258 = x52[x1257];
bool x1259;
if (x1258) {
x1259 = x1075;
} else {
x1259 = false;
}
if (!x1259) break;
x1256 += 1;
}
int32_t x1264 = x1256;
bool x1265 = x1264 == x870;
if (x1265) {
printf("%s\n","LB2HashMap table is full.");
exit(1);
} else {
}
bool x1270 = x52[x1264];
if (x1270) {
double x1271 = x50[x1264];
double x1272 = x51[x1264];
x50[x1264] = x1271;
double x1273 = x1272 + x1223;
x51[x1264] = x1273;
} else {
int32_t x1277 = x60;
x58[x1277] = x1264;
x60 += 1;
x50[x1264] = 0.0;
x51[x1264] = x1223;
x52[x1264] = true;
}
}

}
} else {
}

}
int32_t x1293 = x60;
for(int x1295=0; x1295 < x1293; x1295++) {
int32_t x1296 = x58[x1295];
double x1297 = x50[x1296];
double x1298 = x51[x1296];
printf("%f",x1297);
printf(",");
printf("%f",x1298);
printf(",");
double x1299 = 100.0 * x1297;
double x1300 = x1299 / x1298;
printf("%f",x1300);
printf("%s\n","");

}
end = cur_time();
print_performance(begin, end);
}
/*****************************************
  End of C Generated Code                  
*******************************************/

