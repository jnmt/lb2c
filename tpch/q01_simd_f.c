
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
int32_t* x107 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t x111 = 0;
int32_t x108 = open("/Users/jun/src/tpch-dbgen/lineitem.tbl",0);
int32_t x109 = fsize(x108);
int32_t x112 = x109;
char* x110 = (char*)mmap(0, x109, PROT_READ, MAP_FILE | MAP_SHARED, x108, 0);
for (;;) {
int32_t x113 = x111;
int32_t x114 = x112;
bool x115 = x113 < x114;
if (!x115) break;
int32_t x117 = x111;
int32_t x118 = 0;
for (;;) {
int32_t x119 = x111;
char x120 = x110[x119];
bool x121 = x120 != '|';
if (!x121) break;
int32_t x123 = x118;
int32_t x125 = x111;
int32_t x124 = x123 * 10;
char x126 = x110[x125];
char x127 = x126 - '0';
int32_t x128 = x124 + x127;
x118 = x128;
x111 += 1;
}
x111 += 1;
int32_t x134 = x118;
int32_t x135 = x111;
int32_t x136 = 0;
for (;;) {
int32_t x137 = x111;
char x138 = x110[x137];
bool x139 = x138 != '|';
if (!x139) break;
int32_t x141 = x136;
int32_t x143 = x111;
int32_t x142 = x141 * 10;
char x144 = x110[x143];
char x145 = x144 - '0';
int32_t x146 = x142 + x145;
x136 = x146;
x111 += 1;
}
x111 += 1;
int32_t x152 = x136;
int32_t x153 = x111;
int32_t x154 = 0;
for (;;) {
int32_t x155 = x111;
char x156 = x110[x155];
bool x157 = x156 != '|';
if (!x157) break;
int32_t x159 = x154;
int32_t x161 = x111;
int32_t x160 = x159 * 10;
char x162 = x110[x161];
char x163 = x162 - '0';
int32_t x164 = x160 + x163;
x154 = x164;
x111 += 1;
}
x111 += 1;
int32_t x170 = x154;
int32_t x171 = x111;
int32_t x172 = 0;
for (;;) {
int32_t x173 = x111;
char x174 = x110[x173];
bool x175 = x174 != '|';
if (!x175) break;
int32_t x177 = x172;
int32_t x179 = x111;
int32_t x178 = x177 * 10;
char x180 = x110[x179];
char x181 = x180 - '0';
int32_t x182 = x178 + x181;
x172 = x182;
x111 += 1;
}
x111 += 1;
int32_t x188 = x172;
int32_t x189 = x111;
double x190 = 0.0;
double x191 = 10.0;
for (;;) {
int32_t x192 = x111;
char x193 = x110[x192];
bool x195 = x193 == '.';
bool x197;
if (x195) {
x197 = false;
} else {
bool x196 = x193 != '|';
x197 = x196;
}
if (!x197) break;
double x199 = x190;
int32_t x201 = x111;
double x200 = x199 * 10.0;
char x202 = x110[x201];
char x203 = x202 - '0';
double x205 = (double)x203;
double x206 = x200 + x205;
x190 = x206;
x111 += 1;
}
int32_t x211 = x111;
char x212 = x110[x211];
bool x214 = x212 == '|';
if (x214) {
} else {
x111 += 1;
for (;;) {
int32_t x216 = x111;
char x217 = x110[x216];
bool x218 = x217 != '|';
if (!x218) break;
double x220 = x190;
int32_t x221 = x111;
double x224 = x191;
char x222 = x110[x221];
char x223 = x222 - '0';
double x226 = (double)x223;
double x227 = x226 / x224;
double x228 = x220 + x227;
x190 = x228;
double x230 = x224 * 10.0;
x191 = x230;
x111 += 1;
}
}
x111 += 1;
double x238 = x190;
int32_t x239 = x111;
double x240 = 0.0;
double x241 = 10.0;
for (;;) {
int32_t x242 = x111;
char x243 = x110[x242];
bool x245 = x243 == '.';
bool x247;
if (x245) {
x247 = false;
} else {
bool x246 = x243 != '|';
x247 = x246;
}
if (!x247) break;
double x249 = x240;
int32_t x251 = x111;
double x250 = x249 * 10.0;
char x252 = x110[x251];
char x253 = x252 - '0';
double x255 = (double)x253;
double x256 = x250 + x255;
x240 = x256;
x111 += 1;
}
int32_t x261 = x111;
char x262 = x110[x261];
bool x264 = x262 == '|';
if (x264) {
} else {
x111 += 1;
for (;;) {
int32_t x266 = x111;
char x267 = x110[x266];
bool x268 = x267 != '|';
if (!x268) break;
double x270 = x240;
int32_t x271 = x111;
double x274 = x241;
char x272 = x110[x271];
char x273 = x272 - '0';
double x276 = (double)x273;
double x277 = x276 / x274;
double x278 = x270 + x277;
x240 = x278;
double x280 = x274 * 10.0;
x241 = x280;
x111 += 1;
}
}
x111 += 1;
double x288 = x240;
int32_t x289 = x111;
double x290 = 0.0;
double x291 = 10.0;
for (;;) {
int32_t x292 = x111;
char x293 = x110[x292];
bool x295 = x293 == '.';
bool x297;
if (x295) {
x297 = false;
} else {
bool x296 = x293 != '|';
x297 = x296;
}
if (!x297) break;
double x299 = x290;
int32_t x301 = x111;
double x300 = x299 * 10.0;
char x302 = x110[x301];
char x303 = x302 - '0';
double x305 = (double)x303;
double x306 = x300 + x305;
x290 = x306;
x111 += 1;
}
int32_t x311 = x111;
char x312 = x110[x311];
bool x314 = x312 == '|';
if (x314) {
} else {
x111 += 1;
for (;;) {
int32_t x316 = x111;
char x317 = x110[x316];
bool x318 = x317 != '|';
if (!x318) break;
double x320 = x290;
int32_t x321 = x111;
double x324 = x291;
char x322 = x110[x321];
char x323 = x322 - '0';
double x326 = (double)x323;
double x327 = x326 / x324;
double x328 = x320 + x327;
x290 = x328;
double x330 = x324 * 10.0;
x291 = x330;
x111 += 1;
}
}
x111 += 1;
double x338 = x290;
int32_t x339 = x111;
double x340 = 0.0;
double x341 = 10.0;
for (;;) {
int32_t x342 = x111;
char x343 = x110[x342];
bool x345 = x343 == '.';
bool x347;
if (x345) {
x347 = false;
} else {
bool x346 = x343 != '|';
x347 = x346;
}
if (!x347) break;
double x349 = x340;
int32_t x351 = x111;
double x350 = x349 * 10.0;
char x352 = x110[x351];
char x353 = x352 - '0';
double x355 = (double)x353;
double x356 = x350 + x355;
x340 = x356;
x111 += 1;
}
int32_t x361 = x111;
char x362 = x110[x361];
bool x364 = x362 == '|';
if (x364) {
} else {
x111 += 1;
for (;;) {
int32_t x366 = x111;
char x367 = x110[x366];
bool x368 = x367 != '|';
if (!x368) break;
double x370 = x340;
int32_t x371 = x111;
double x374 = x341;
char x372 = x110[x371];
char x373 = x372 - '0';
double x376 = (double)x373;
double x377 = x376 / x374;
double x378 = x370 + x377;
x340 = x378;
double x380 = x374 * 10.0;
x341 = x380;
x111 += 1;
}
}
x111 += 1;
double x388 = x340;
int32_t x389 = x111;
for (;;) {
int32_t x390 = x111;
char x391 = x110[x390];
bool x392 = x391 != '|';
if (!x392) break;
x111 += 1;
}
int32_t x397 = x111;
x111 += 1;
int32_t x401 = x111;
for (;;) {
int32_t x402 = x111;
char x403 = x110[x402];
bool x404 = x403 != '|';
if (!x404) break;
x111 += 1;
}
int32_t x409 = x111;
x111 += 1;
int32_t x413 = x111;
int32_t x414 = 0;
int32_t x415 = 0;
int32_t x416 = 0;
for (;;) {
int32_t x417 = x111;
char x418 = x110[x417];
bool x419 = x418 != '-';
if (!x419) break;
int32_t x421 = x414;
int32_t x423 = x111;
int32_t x422 = x421 * 10;
char x424 = x110[x423];
char x425 = x424 - '0';
int32_t x426 = x422 + x425;
x414 = x426;
x111 += 1;
}
x111 += 1;
for (;;) {
int32_t x432 = x111;
char x433 = x110[x432];
bool x434 = x433 != '-';
if (!x434) break;
int32_t x436 = x415;
int32_t x438 = x111;
int32_t x437 = x436 * 10;
char x439 = x110[x438];
char x440 = x439 - '0';
int32_t x441 = x437 + x440;
x415 = x441;
x111 += 1;
}
x111 += 1;
for (;;) {
int32_t x447 = x111;
char x448 = x110[x447];
bool x449 = x448 != '|';
if (!x449) break;
int32_t x451 = x416;
int32_t x453 = x111;
int32_t x452 = x451 * 10;
char x454 = x110[x453];
char x455 = x454 - '0';
int32_t x456 = x452 + x455;
x416 = x456;
x111 += 1;
}
x111 += 1;
int32_t x462 = x414;
int32_t x463 = x415;
int32_t x464 = x416;
int32_t x465 = x111;
int32_t x466 = 0;
int32_t x467 = 0;
int32_t x468 = 0;
for (;;) {
int32_t x469 = x111;
char x470 = x110[x469];
bool x471 = x470 != '-';
if (!x471) break;
int32_t x473 = x466;
int32_t x475 = x111;
int32_t x474 = x473 * 10;
char x476 = x110[x475];
char x477 = x476 - '0';
int32_t x478 = x474 + x477;
x466 = x478;
x111 += 1;
}
x111 += 1;
for (;;) {
int32_t x484 = x111;
char x485 = x110[x484];
bool x486 = x485 != '-';
if (!x486) break;
int32_t x488 = x467;
int32_t x490 = x111;
int32_t x489 = x488 * 10;
char x491 = x110[x490];
char x492 = x491 - '0';
int32_t x493 = x489 + x492;
x467 = x493;
x111 += 1;
}
x111 += 1;
for (;;) {
int32_t x499 = x111;
char x500 = x110[x499];
bool x501 = x500 != '|';
if (!x501) break;
int32_t x503 = x468;
int32_t x505 = x111;
int32_t x504 = x503 * 10;
char x506 = x110[x505];
char x507 = x506 - '0';
int32_t x508 = x504 + x507;
x468 = x508;
x111 += 1;
}
x111 += 1;
int32_t x514 = x466;
int32_t x515 = x467;
int32_t x516 = x468;
int32_t x517 = x111;
int32_t x518 = 0;
int32_t x519 = 0;
int32_t x520 = 0;
for (;;) {
int32_t x521 = x111;
char x522 = x110[x521];
bool x523 = x522 != '-';
if (!x523) break;
int32_t x525 = x518;
int32_t x527 = x111;
int32_t x526 = x525 * 10;
char x528 = x110[x527];
char x529 = x528 - '0';
int32_t x530 = x526 + x529;
x518 = x530;
x111 += 1;
}
x111 += 1;
for (;;) {
int32_t x536 = x111;
char x537 = x110[x536];
bool x538 = x537 != '-';
if (!x538) break;
int32_t x540 = x519;
int32_t x542 = x111;
int32_t x541 = x540 * 10;
char x543 = x110[x542];
char x544 = x543 - '0';
int32_t x545 = x541 + x544;
x519 = x545;
x111 += 1;
}
x111 += 1;
for (;;) {
int32_t x551 = x111;
char x552 = x110[x551];
bool x553 = x552 != '|';
if (!x553) break;
int32_t x555 = x520;
int32_t x557 = x111;
int32_t x556 = x555 * 10;
char x558 = x110[x557];
char x559 = x558 - '0';
int32_t x560 = x556 + x559;
x520 = x560;
x111 += 1;
}
x111 += 1;
int32_t x566 = x518;
int32_t x567 = x519;
int32_t x568 = x520;
int32_t x569 = x111;
for (;;) {
int32_t x570 = x111;
char x571 = x110[x570];
bool x572 = x571 != '|';
if (!x572) break;
x111 += 1;
}
int32_t x577 = x111;
x111 += 1;
int32_t x581 = x111;
for (;;) {
int32_t x582 = x111;
char x583 = x110[x582];
bool x584 = x583 != '|';
if (!x584) break;
x111 += 1;
}
int32_t x589 = x111;
x111 += 1;
int32_t x593 = x111;
for (;;) {
int32_t x594 = x111;
char x595 = x110[x594];
bool x596 = x595 != '\n';
if (!x596) break;
x111 += 1;
}
int32_t x601 = x111;
x111 += 1;
int32_t x605 = x30;
x2[x605] = x134;
x3[x605] = x152;
x4[x605] = x170;
x5[x605] = x188;
x6[x605] = x238;
x7[x605] = x288;
x8[x605] = x338;
x9[x605] = x388;
char* x400 = x110 + x389;
x10[x605] = x400;
int32_t x398 = x397 - x389;
x11[x605] = x398;
char* x412 = x110 + x401;
x12[x605] = x412;
int32_t x410 = x409 - x401;
x13[x605] = x410;
x14[x605] = x462;
x15[x605] = x463;
x16[x605] = x464;
x17[x605] = x514;
x18[x605] = x515;
x19[x605] = x516;
x20[x605] = x566;
x21[x605] = x567;
x22[x605] = x568;
char* x580 = x110 + x569;
x23[x605] = x580;
int32_t x578 = x577 - x569;
x24[x605] = x578;
char* x592 = x110 + x581;
x25[x605] = x592;
int32_t x590 = x589 - x581;
x26[x605] = x590;
char* x604 = x110 + x593;
x27[x605] = x604;
int32_t x602 = x601 - x593;
x28[x605] = x602;
x30 += 1;
}
close(x108);
__m512i x700 = _mm512_set1_epi32(10000);
__m512i x703 = _mm512_set1_epi32(100);
__m512i x708 = _mm512_set1_epi32(1998);
__m512i x709 = _mm512_mullo_epi32(x708,x700);
__m512i x710 = _mm512_set1_epi32(9);
__m512i x711 = _mm512_mullo_epi32(x710,x703);
__m512i x712 = _mm512_add_epi32(x709,x711);
__m512i x713 = _mm512_set1_epi32(2);
__m512i x714 = _mm512_add_epi32(x712,x713);
__mmask16 x698 = 65535;
__m512i x106 = _mm512_set_epi32(15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0);
int32_t x812 = x52 - 1;
struct timeval begin, end;
begin = cur_time();
int32_t x637 = x30;
for(int x639=0; x639 < x637; x639++) {
int32_t x640 = x2[x639];
int32_t x641 = x3[x639];
int32_t x642 = x4[x639];
int32_t x643 = x5[x639];
double x644 = x6[x639];
double x645 = x7[x639];
double x646 = x8[x639];
double x647 = x9[x639];
char* x648 = x10[x639];
int32_t x649 = x11[x639];
char* x650 = x12[x639];
int32_t x651 = x13[x639];
int32_t x652 = x14[x639];
int32_t x653 = x15[x639];
int32_t x654 = x16[x639];
int32_t x655 = x17[x639];
int32_t x656 = x18[x639];
int32_t x657 = x19[x639];
int32_t x658 = x20[x639];
int32_t x659 = x21[x639];
int32_t x660 = x22[x639];
char* x661 = x23[x639];
int32_t x662 = x24[x639];
char* x663 = x25[x639];
int32_t x664 = x26[x639];
char* x665 = x27[x639];
int32_t x666 = x28[x639];
int32_t x667 = x105;
x77[x667] = x640;
x78[x667] = x641;
x79[x667] = x642;
x80[x667] = x643;
x81[x667] = x644;
x82[x667] = x645;
x83[x667] = x646;
x84[x667] = x647;
x85[x667] = x648;
x86[x667] = x649;
x87[x667] = x650;
x88[x667] = x651;
x89[x667] = x652;
x90[x667] = x653;
x91[x667] = x654;
x92[x667] = x655;
x93[x667] = x656;
x94[x667] = x657;
x95[x667] = x658;
x96[x667] = x659;
x97[x667] = x660;
x98[x667] = x661;
x99[x667] = x662;
x100[x667] = x663;
x101[x667] = x664;
x102[x667] = x665;
x103[x667] = x666;
x105 += 1;
int32_t x696 = x105;
bool x697 = x696 == 16;
if (x697) {
__m512i x699 = _mm512_loadu_si512(x89);
__m512i x701 = _mm512_mullo_epi32(x699,x700);
__m512i x702 = _mm512_loadu_si512(x90);
__m512i x704 = _mm512_mullo_epi32(x702,x703);
__m512i x705 = _mm512_add_epi32(x701,x704);
__m512i x706 = _mm512_loadu_si512(x91);
__m512i x707 = _mm512_add_epi32(x705,x706);
__mmask16 x715 = _mm512_cmple_epi32_mask(x707,x714);
__mmask16 x716 = _mm512_kand(x698,x715);
_mm512_mask_compressstoreu_epi32(x107,x716,x106);
int32_t x718 = _mm_popcnt_u32(x716);
for(int x720=0; x720 < x718; x720++) {
int32_t x721 = x107[x720];
int32_t x722 = x77[x721];
int32_t x723 = x78[x721];
int32_t x724 = x79[x721];
int32_t x725 = x80[x721];
double x726 = x81[x721];
double x727 = x82[x721];
double x728 = x83[x721];
double x729 = x84[x721];
char* x730 = x85[x721];
int32_t x731 = x86[x721];
char* x732 = x87[x721];
int32_t x733 = x88[x721];
int32_t x734 = x89[x721];
int32_t x735 = x90[x721];
int32_t x736 = x91[x721];
int32_t x737 = x92[x721];
int32_t x738 = x93[x721];
int32_t x739 = x94[x721];
int32_t x740 = x95[x721];
int32_t x741 = x96[x721];
int32_t x742 = x97[x721];
char* x743 = x98[x721];
int32_t x744 = x99[x721];
char* x745 = x100[x721];
int32_t x746 = x101[x721];
char* x747 = x102[x721];
int32_t x748 = x103[x721];
int64_t x753 = hash(x730,x731);
int64_t x754 = x753 * 41L;
int64_t x755 = hash(x732,x733);
int64_t x756 = x754 + x755;
int32_t x757 = (int32_t)x756;
bool x758 = x757 >= 0;
int32_t x760;
if (x758) {
x760 = x757;
} else {
int32_t x759 = 0 - x757;
x760 = x759;
}
int32_t x761 = x760 % x52;
int32_t x762 = x761;
for (;;) {
int32_t x763 = x762;
bool x764 = x68[x763];
bool x806;
if (x764) {
char* x765 = x53[x763];
int32_t x766 = x54[x763];
char* x767 = x55[x763];
int32_t x768 = x56[x763];
bool x770 = x766 == x731;
bool x785;
if (x770) {
int32_t x771 = 0;
for (;;) {
int32_t x772 = x771;
bool x773 = x772 < x766;
bool x777;
if (x773) {
char x774 = x765[x772];
char x775 = x730[x772];
bool x776 = x774 == x775;
x777 = x776;
} else {
x777 = false;
}
if (!x777) break;
x771 += 1;
}
int32_t x782 = x771;
bool x783 = x782 == x766;
x785 = x783;
} else {
x785 = false;
}
bool x803;
if (x785) {
bool x787 = x768 == x733;
bool x802;
if (x787) {
int32_t x788 = 0;
for (;;) {
int32_t x789 = x788;
bool x790 = x789 < x768;
bool x794;
if (x790) {
char x791 = x767[x789];
char x792 = x732[x789];
bool x793 = x791 == x792;
x794 = x793;
} else {
x794 = false;
}
if (!x794) break;
x788 += 1;
}
int32_t x799 = x788;
bool x800 = x799 == x768;
x802 = x800;
} else {
x802 = false;
}
x803 = x802;
} else {
x803 = false;
}
bool x804 = !x803;
x806 = x804;
} else {
x806 = false;
}
if (!x806) break;
x762 += 1;
}
int32_t x811 = x762;
bool x813 = x811 == x812;
if (x813) {
printf("%s\n","LB2HashMap table is full.");
exit(1);
} else {
}
bool x818 = x68[x811];
if (x818) {
double x819 = x57[x811];
double x820 = x58[x811];
double x821 = x59[x811];
double x822 = x60[x811];
double x823 = x61[x811];
int32_t x824 = x62[x811];
double x825 = x63[x811];
int32_t x826 = x64[x811];
double x827 = x65[x811];
int32_t x828 = x66[x811];
int32_t x829 = x67[x811];
double x830 = x819 + x726;
x57[x811] = x830;
double x831 = x820 + x727;
x58[x811] = x831;
double x749 = 1.0 - x728;
double x750 = x727 * x749;
double x832 = x821 + x750;
x59[x811] = x832;
double x751 = 1.0 + x729;
double x752 = x750 * x751;
double x833 = x822 + x752;
x60[x811] = x833;
double x834 = x823 + x726;
x61[x811] = x834;
int32_t x835 = x824 + 1;
x62[x811] = x835;
double x836 = x825 + x727;
x63[x811] = x836;
int32_t x837 = x826 + 1;
x64[x811] = x837;
double x838 = x827 + x728;
x65[x811] = x838;
int32_t x839 = x828 + 1;
x66[x811] = x839;
int32_t x840 = x829 + 1;
x67[x811] = x840;
} else {
int32_t x853 = x76;
x74[x853] = x811;
x76 += 1;
x53[x811] = x730;
x54[x811] = x731;
x55[x811] = x732;
x56[x811] = x733;
x57[x811] = x726;
x58[x811] = x727;
double x749 = 1.0 - x728;
double x750 = x727 * x749;
x59[x811] = x750;
double x751 = 1.0 + x729;
double x752 = x750 * x751;
x60[x811] = x752;
x61[x811] = x726;
x62[x811] = 1;
x63[x811] = x727;
x64[x811] = 1;
x65[x811] = x728;
x66[x811] = 1;
x67[x811] = 1;
x68[x811] = true;
}

}
x105 = 0;
} else {
}

}
int32_t x881 = x105;
for(int x883=0; x883 < x881; x883++) {
int32_t x884 = x77[x883];
int32_t x885 = x78[x883];
int32_t x886 = x79[x883];
int32_t x887 = x80[x883];
double x888 = x81[x883];
double x889 = x82[x883];
double x890 = x83[x883];
double x891 = x84[x883];
char* x892 = x85[x883];
int32_t x893 = x86[x883];
char* x894 = x87[x883];
int32_t x895 = x88[x883];
int32_t x896 = x89[x883];
int32_t x897 = x90[x883];
int32_t x898 = x91[x883];
int32_t x899 = x92[x883];
int32_t x900 = x93[x883];
int32_t x901 = x94[x883];
int32_t x902 = x95[x883];
int32_t x903 = x96[x883];
int32_t x904 = x97[x883];
char* x905 = x98[x883];
int32_t x906 = x99[x883];
char* x907 = x100[x883];
int32_t x908 = x101[x883];
char* x909 = x102[x883];
int32_t x910 = x103[x883];
int32_t x911 = x896 * 10000;
int32_t x912 = x897 * 100;
int32_t x913 = x911 + x912;
int32_t x914 = x913 + x898;
bool x915 = x914 <= 19980902;
if (x915) {
int64_t x920 = hash(x892,x893);
int64_t x921 = x920 * 41L;
int64_t x922 = hash(x894,x895);
int64_t x923 = x921 + x922;
int32_t x924 = (int32_t)x923;
bool x925 = x924 >= 0;
int32_t x927;
if (x925) {
x927 = x924;
} else {
int32_t x926 = 0 - x924;
x927 = x926;
}
int32_t x928 = x927 % x52;
int32_t x929 = x928;
for (;;) {
int32_t x930 = x929;
bool x931 = x68[x930];
bool x973;
if (x931) {
char* x932 = x53[x930];
int32_t x933 = x54[x930];
char* x934 = x55[x930];
int32_t x935 = x56[x930];
bool x937 = x933 == x893;
bool x952;
if (x937) {
int32_t x938 = 0;
for (;;) {
int32_t x939 = x938;
bool x940 = x939 < x933;
bool x944;
if (x940) {
char x941 = x932[x939];
char x942 = x892[x939];
bool x943 = x941 == x942;
x944 = x943;
} else {
x944 = false;
}
if (!x944) break;
x938 += 1;
}
int32_t x949 = x938;
bool x950 = x949 == x933;
x952 = x950;
} else {
x952 = false;
}
bool x970;
if (x952) {
bool x954 = x935 == x895;
bool x969;
if (x954) {
int32_t x955 = 0;
for (;;) {
int32_t x956 = x955;
bool x957 = x956 < x935;
bool x961;
if (x957) {
char x958 = x934[x956];
char x959 = x894[x956];
bool x960 = x958 == x959;
x961 = x960;
} else {
x961 = false;
}
if (!x961) break;
x955 += 1;
}
int32_t x966 = x955;
bool x967 = x966 == x935;
x969 = x967;
} else {
x969 = false;
}
x970 = x969;
} else {
x970 = false;
}
bool x971 = !x970;
x973 = x971;
} else {
x973 = false;
}
if (!x973) break;
x929 += 1;
}
int32_t x978 = x929;
bool x979 = x978 == x812;
if (x979) {
printf("%s\n","LB2HashMap table is full.");
exit(1);
} else {
}
bool x984 = x68[x978];
if (x984) {
double x985 = x57[x978];
double x986 = x58[x978];
double x987 = x59[x978];
double x988 = x60[x978];
double x989 = x61[x978];
int32_t x990 = x62[x978];
double x991 = x63[x978];
int32_t x992 = x64[x978];
double x993 = x65[x978];
int32_t x994 = x66[x978];
int32_t x995 = x67[x978];
double x996 = x985 + x888;
x57[x978] = x996;
double x997 = x986 + x889;
x58[x978] = x997;
double x916 = 1.0 - x890;
double x917 = x889 * x916;
double x998 = x987 + x917;
x59[x978] = x998;
double x918 = 1.0 + x891;
double x919 = x917 * x918;
double x999 = x988 + x919;
x60[x978] = x999;
double x1000 = x989 + x888;
x61[x978] = x1000;
int32_t x1001 = x990 + 1;
x62[x978] = x1001;
double x1002 = x991 + x889;
x63[x978] = x1002;
int32_t x1003 = x992 + 1;
x64[x978] = x1003;
double x1004 = x993 + x890;
x65[x978] = x1004;
int32_t x1005 = x994 + 1;
x66[x978] = x1005;
int32_t x1006 = x995 + 1;
x67[x978] = x1006;
} else {
int32_t x1019 = x76;
x74[x1019] = x978;
x76 += 1;
x53[x978] = x892;
x54[x978] = x893;
x55[x978] = x894;
x56[x978] = x895;
x57[x978] = x888;
x58[x978] = x889;
double x916 = 1.0 - x890;
double x917 = x889 * x916;
x59[x978] = x917;
double x918 = 1.0 + x891;
double x919 = x917 * x918;
x60[x978] = x919;
x61[x978] = x888;
x62[x978] = 1;
x63[x978] = x889;
x64[x978] = 1;
x65[x978] = x890;
x66[x978] = 1;
x67[x978] = 1;
x68[x978] = true;
}
} else {
}

}
int32_t x1044 = x76;
for(int x1046=0; x1046 < x1044; x1046++) {
int32_t x1047 = x74[x1046];
char* x1048 = x53[x1047];
int32_t x1049 = x54[x1047];
char* x1050 = x55[x1047];
int32_t x1051 = x56[x1047];
double x1052 = x57[x1047];
double x1053 = x58[x1047];
double x1054 = x59[x1047];
double x1055 = x60[x1047];
double x1056 = x61[x1047];
int32_t x1057 = x62[x1047];
double x1058 = x63[x1047];
int32_t x1059 = x64[x1047];
double x1060 = x65[x1047];
int32_t x1061 = x66[x1047];
int32_t x1062 = x67[x1047];
int32_t x1063 = x49;
x32[x1063] = x1048;
x33[x1063] = x1049;
x34[x1063] = x1050;
x35[x1063] = x1051;
x36[x1063] = x1052;
x37[x1063] = x1053;
x38[x1063] = x1054;
x39[x1063] = x1055;
x40[x1063] = x1056;
x41[x1063] = x1057;
x42[x1063] = x1058;
x43[x1063] = x1059;
x44[x1063] = x1060;
x45[x1063] = x1061;
x46[x1063] = x1062;
x47[x1063] = x1063;
x49 += 1;

}
x50[0] = 0;
int32_t x1084 = x49;
int32_t x1085 = x1084 - 1;
x51[0] = x1085;
int32_t x1087 = 1;
int32_t x1088 = 1;
for (;;) {
int32_t x1089 = x1088;
bool x1090 = x1089 > 0;
if (!x1090) break;
int32_t x1092 = x1088;
int32_t x1093 = x1092 - 1;
x1088 = x1093;
int32_t x1095 = x50[x1093];
int32_t x1096 = x51[x1093];
int32_t x1097 = x1095;
int32_t x1098 = x1096;
int32_t x1102 = x47[x1095];
char* x1103 = x32[x1102];
int32_t x1104 = x33[x1102];
char* x1105 = x34[x1102];
int32_t x1106 = x35[x1102];
double x1107 = x36[x1102];
double x1108 = x37[x1102];
double x1109 = x38[x1102];
double x1110 = x39[x1102];
double x1111 = x40[x1102];
int32_t x1112 = x41[x1102];
double x1113 = x42[x1102];
int32_t x1114 = x43[x1102];
double x1115 = x44[x1102];
int32_t x1116 = x45[x1102];
int32_t x1117 = x46[x1102];
int32_t x1118 = x47[x1096];
char* x1119 = x32[x1118];
int32_t x1120 = x33[x1118];
char* x1121 = x34[x1118];
int32_t x1122 = x35[x1118];
double x1123 = x36[x1118];
double x1124 = x37[x1118];
double x1125 = x38[x1118];
double x1126 = x39[x1118];
double x1127 = x40[x1118];
int32_t x1128 = x41[x1118];
double x1129 = x42[x1118];
int32_t x1130 = x43[x1118];
double x1131 = x44[x1118];
int32_t x1132 = x45[x1118];
int32_t x1133 = x46[x1118];
int32_t x1134 = 0;
int32_t x1135 = 0;
bool* x1136 = (bool*)malloc(2 * sizeof(bool));
bool* x1137 = (bool*)malloc(2 * sizeof(bool));
int32_t x1138 = 0;
for (;;) {
int32_t x1139 = x1138;
bool x1140 = x1139 < x1104;
bool x1142;
if (x1140) {
bool x1141 = x1139 < x1120;
x1142 = x1141;
} else {
x1142 = false;
}
bool x1146;
if (x1142) {
char x1143 = x1103[x1139];
char x1144 = x1119[x1139];
bool x1145 = x1143 == x1144;
x1146 = x1145;
} else {
x1146 = false;
}
if (!x1146) break;
x1138 += 1;
}
int32_t x1151 = x1138;
char x1152 = x1103[x1151];
char x1153 = x1119[x1151];
bool x1154 = x1152 < x1153;
x1136[0] = x1154;
bool x1157 = x1104 == x1120;
bool x1172;
if (x1157) {
int32_t x1158 = 0;
for (;;) {
int32_t x1159 = x1158;
bool x1160 = x1159 < x1104;
bool x1164;
if (x1160) {
char x1161 = x1103[x1159];
char x1162 = x1119[x1159];
bool x1163 = x1161 == x1162;
x1164 = x1163;
} else {
x1164 = false;
}
if (!x1164) break;
x1158 += 1;
}
int32_t x1169 = x1158;
bool x1170 = x1169 == x1104;
x1172 = x1170;
} else {
x1172 = false;
}
x1137[0] = x1172;
x1135 += 1;
int32_t x1175 = x1135;
int32_t x1176 = 0;
for (;;) {
int32_t x1177 = x1176;
bool x1178 = x1177 < x1106;
bool x1180;
if (x1178) {
bool x1179 = x1177 < x1122;
x1180 = x1179;
} else {
x1180 = false;
}
bool x1184;
if (x1180) {
char x1181 = x1105[x1177];
char x1182 = x1121[x1177];
bool x1183 = x1181 == x1182;
x1184 = x1183;
} else {
x1184 = false;
}
if (!x1184) break;
x1176 += 1;
}
int32_t x1189 = x1176;
char x1190 = x1105[x1189];
char x1191 = x1121[x1189];
bool x1192 = x1190 < x1191;
x1136[x1175] = x1192;
bool x1195 = x1106 == x1122;
bool x1210;
if (x1195) {
int32_t x1196 = 0;
for (;;) {
int32_t x1197 = x1196;
bool x1198 = x1197 < x1106;
bool x1202;
if (x1198) {
char x1199 = x1105[x1197];
char x1200 = x1121[x1197];
bool x1201 = x1199 == x1200;
x1202 = x1201;
} else {
x1202 = false;
}
if (!x1202) break;
x1196 += 1;
}
int32_t x1207 = x1196;
bool x1208 = x1207 == x1106;
x1210 = x1208;
} else {
x1210 = false;
}
x1137[x1175] = x1210;
x1135 += 1;
bool x1213 = x1136[0];
bool x1215 = x1137[0];
bool x1216 = x1136[1];
bool x1214;
if (x1213) {
x1214 = true;
} else {
x1214 = false;
}
bool x1217;
if (x1216) {
x1217 = x1215;
} else {
x1217 = false;
}
bool x1218 = x1214 || x1217;
int32_t x1099 = x1096 - x1095;
int32_t x1100 = x1099 / 2;
int32_t x1101 = x1095 + x1100;
int32_t x1599;
if (x1218) {
int32_t x1219 = x47[x1101];
char* x1220 = x32[x1219];
int32_t x1221 = x33[x1219];
char* x1222 = x34[x1219];
int32_t x1223 = x35[x1219];
double x1224 = x36[x1219];
double x1225 = x37[x1219];
double x1226 = x38[x1219];
double x1227 = x39[x1219];
double x1228 = x40[x1219];
int32_t x1229 = x41[x1219];
double x1230 = x42[x1219];
int32_t x1231 = x43[x1219];
double x1232 = x44[x1219];
int32_t x1233 = x45[x1219];
int32_t x1234 = x46[x1219];
int32_t x1235 = 0;
int32_t x1236 = 0;
bool* x1237 = (bool*)malloc(2 * sizeof(bool));
bool* x1238 = (bool*)malloc(2 * sizeof(bool));
int32_t x1239 = 0;
for (;;) {
int32_t x1240 = x1239;
bool x1241 = x1240 < x1120;
bool x1243;
if (x1241) {
bool x1242 = x1240 < x1221;
x1243 = x1242;
} else {
x1243 = false;
}
bool x1247;
if (x1243) {
char x1244 = x1119[x1240];
char x1245 = x1220[x1240];
bool x1246 = x1244 == x1245;
x1247 = x1246;
} else {
x1247 = false;
}
if (!x1247) break;
x1239 += 1;
}
int32_t x1252 = x1239;
char x1253 = x1119[x1252];
char x1254 = x1220[x1252];
bool x1255 = x1253 < x1254;
x1237[0] = x1255;
bool x1258 = x1120 == x1221;
bool x1273;
if (x1258) {
int32_t x1259 = 0;
for (;;) {
int32_t x1260 = x1259;
bool x1261 = x1260 < x1120;
bool x1265;
if (x1261) {
char x1262 = x1119[x1260];
char x1263 = x1220[x1260];
bool x1264 = x1262 == x1263;
x1265 = x1264;
} else {
x1265 = false;
}
if (!x1265) break;
x1259 += 1;
}
int32_t x1270 = x1259;
bool x1271 = x1270 == x1120;
x1273 = x1271;
} else {
x1273 = false;
}
x1238[0] = x1273;
x1236 += 1;
int32_t x1276 = x1236;
int32_t x1277 = 0;
for (;;) {
int32_t x1278 = x1277;
bool x1279 = x1278 < x1122;
bool x1281;
if (x1279) {
bool x1280 = x1278 < x1223;
x1281 = x1280;
} else {
x1281 = false;
}
bool x1285;
if (x1281) {
char x1282 = x1121[x1278];
char x1283 = x1222[x1278];
bool x1284 = x1282 == x1283;
x1285 = x1284;
} else {
x1285 = false;
}
if (!x1285) break;
x1277 += 1;
}
int32_t x1290 = x1277;
char x1291 = x1121[x1290];
char x1292 = x1222[x1290];
bool x1293 = x1291 < x1292;
x1237[x1276] = x1293;
bool x1296 = x1122 == x1223;
bool x1311;
if (x1296) {
int32_t x1297 = 0;
for (;;) {
int32_t x1298 = x1297;
bool x1299 = x1298 < x1122;
bool x1303;
if (x1299) {
char x1300 = x1121[x1298];
char x1301 = x1222[x1298];
bool x1302 = x1300 == x1301;
x1303 = x1302;
} else {
x1303 = false;
}
if (!x1303) break;
x1297 += 1;
}
int32_t x1308 = x1297;
bool x1309 = x1308 == x1122;
x1311 = x1309;
} else {
x1311 = false;
}
x1238[x1276] = x1311;
x1236 += 1;
bool x1314 = x1237[0];
bool x1316 = x1238[0];
bool x1317 = x1237[1];
bool x1315;
if (x1314) {
x1315 = true;
} else {
x1315 = false;
}
bool x1318;
if (x1317) {
x1318 = x1316;
} else {
x1318 = false;
}
bool x1319 = x1315 || x1318;
int32_t x1407;
if (x1319) {
x1407 = x1096;
} else {
int32_t x1320 = 0;
int32_t x1321 = 0;
bool* x1322 = (bool*)malloc(2 * sizeof(bool));
bool* x1323 = (bool*)malloc(2 * sizeof(bool));
int32_t x1324 = 0;
for (;;) {
int32_t x1325 = x1324;
bool x1326 = x1325 < x1221;
bool x1328;
if (x1326) {
bool x1327 = x1325 < x1104;
x1328 = x1327;
} else {
x1328 = false;
}
bool x1332;
if (x1328) {
char x1329 = x1220[x1325];
char x1330 = x1103[x1325];
bool x1331 = x1329 == x1330;
x1332 = x1331;
} else {
x1332 = false;
}
if (!x1332) break;
x1324 += 1;
}
int32_t x1337 = x1324;
char x1338 = x1220[x1337];
char x1339 = x1103[x1337];
bool x1340 = x1338 < x1339;
x1322[0] = x1340;
bool x1343 = x1221 == x1104;
bool x1358;
if (x1343) {
int32_t x1344 = 0;
for (;;) {
int32_t x1345 = x1344;
bool x1346 = x1345 < x1221;
bool x1350;
if (x1346) {
char x1347 = x1220[x1345];
char x1348 = x1103[x1345];
bool x1349 = x1347 == x1348;
x1350 = x1349;
} else {
x1350 = false;
}
if (!x1350) break;
x1344 += 1;
}
int32_t x1355 = x1344;
bool x1356 = x1355 == x1221;
x1358 = x1356;
} else {
x1358 = false;
}
x1323[0] = x1358;
x1321 += 1;
int32_t x1361 = x1321;
int32_t x1362 = 0;
for (;;) {
int32_t x1363 = x1362;
bool x1364 = x1363 < x1223;
bool x1366;
if (x1364) {
bool x1365 = x1363 < x1106;
x1366 = x1365;
} else {
x1366 = false;
}
bool x1370;
if (x1366) {
char x1367 = x1222[x1363];
char x1368 = x1105[x1363];
bool x1369 = x1367 == x1368;
x1370 = x1369;
} else {
x1370 = false;
}
if (!x1370) break;
x1362 += 1;
}
int32_t x1375 = x1362;
char x1376 = x1222[x1375];
char x1377 = x1105[x1375];
bool x1378 = x1376 < x1377;
x1322[x1361] = x1378;
bool x1381 = x1223 == x1106;
bool x1396;
if (x1381) {
int32_t x1382 = 0;
for (;;) {
int32_t x1383 = x1382;
bool x1384 = x1383 < x1223;
bool x1388;
if (x1384) {
char x1385 = x1222[x1383];
char x1386 = x1105[x1383];
bool x1387 = x1385 == x1386;
x1388 = x1387;
} else {
x1388 = false;
}
if (!x1388) break;
x1382 += 1;
}
int32_t x1393 = x1382;
bool x1394 = x1393 == x1223;
x1396 = x1394;
} else {
x1396 = false;
}
x1323[x1361] = x1396;
x1321 += 1;
bool x1399 = x1322[0];
bool x1401 = x1323[0];
bool x1402 = x1322[1];
bool x1400;
if (x1399) {
x1400 = true;
} else {
x1400 = false;
}
bool x1403;
if (x1402) {
x1403 = x1401;
} else {
x1403 = false;
}
bool x1404 = x1400 || x1403;
int32_t x1405;
if (x1404) {
x1405 = x1095;
} else {
x1405 = x1101;
}
x1407 = x1405;
}
x1599 = x1407;
} else {
int32_t x1409 = x47[x1101];
char* x1410 = x32[x1409];
int32_t x1411 = x33[x1409];
char* x1412 = x34[x1409];
int32_t x1413 = x35[x1409];
double x1414 = x36[x1409];
double x1415 = x37[x1409];
double x1416 = x38[x1409];
double x1417 = x39[x1409];
double x1418 = x40[x1409];
int32_t x1419 = x41[x1409];
double x1420 = x42[x1409];
int32_t x1421 = x43[x1409];
double x1422 = x44[x1409];
int32_t x1423 = x45[x1409];
int32_t x1424 = x46[x1409];
int32_t x1425 = 0;
int32_t x1426 = 0;
bool* x1427 = (bool*)malloc(2 * sizeof(bool));
bool* x1428 = (bool*)malloc(2 * sizeof(bool));
int32_t x1429 = 0;
for (;;) {
int32_t x1430 = x1429;
bool x1431 = x1430 < x1104;
bool x1433;
if (x1431) {
bool x1432 = x1430 < x1411;
x1433 = x1432;
} else {
x1433 = false;
}
bool x1437;
if (x1433) {
char x1434 = x1103[x1430];
char x1435 = x1410[x1430];
bool x1436 = x1434 == x1435;
x1437 = x1436;
} else {
x1437 = false;
}
if (!x1437) break;
x1429 += 1;
}
int32_t x1442 = x1429;
char x1443 = x1103[x1442];
char x1444 = x1410[x1442];
bool x1445 = x1443 < x1444;
x1427[0] = x1445;
bool x1448 = x1104 == x1411;
bool x1463;
if (x1448) {
int32_t x1449 = 0;
for (;;) {
int32_t x1450 = x1449;
bool x1451 = x1450 < x1104;
bool x1455;
if (x1451) {
char x1452 = x1103[x1450];
char x1453 = x1410[x1450];
bool x1454 = x1452 == x1453;
x1455 = x1454;
} else {
x1455 = false;
}
if (!x1455) break;
x1449 += 1;
}
int32_t x1460 = x1449;
bool x1461 = x1460 == x1104;
x1463 = x1461;
} else {
x1463 = false;
}
x1428[0] = x1463;
x1426 += 1;
int32_t x1466 = x1426;
int32_t x1467 = 0;
for (;;) {
int32_t x1468 = x1467;
bool x1469 = x1468 < x1106;
bool x1471;
if (x1469) {
bool x1470 = x1468 < x1413;
x1471 = x1470;
} else {
x1471 = false;
}
bool x1475;
if (x1471) {
char x1472 = x1105[x1468];
char x1473 = x1412[x1468];
bool x1474 = x1472 == x1473;
x1475 = x1474;
} else {
x1475 = false;
}
if (!x1475) break;
x1467 += 1;
}
int32_t x1480 = x1467;
char x1481 = x1105[x1480];
char x1482 = x1412[x1480];
bool x1483 = x1481 < x1482;
x1427[x1466] = x1483;
bool x1486 = x1106 == x1413;
bool x1501;
if (x1486) {
int32_t x1487 = 0;
for (;;) {
int32_t x1488 = x1487;
bool x1489 = x1488 < x1106;
bool x1493;
if (x1489) {
char x1490 = x1105[x1488];
char x1491 = x1412[x1488];
bool x1492 = x1490 == x1491;
x1493 = x1492;
} else {
x1493 = false;
}
if (!x1493) break;
x1487 += 1;
}
int32_t x1498 = x1487;
bool x1499 = x1498 == x1106;
x1501 = x1499;
} else {
x1501 = false;
}
x1428[x1466] = x1501;
x1426 += 1;
bool x1504 = x1427[0];
bool x1506 = x1428[0];
bool x1507 = x1427[1];
bool x1505;
if (x1504) {
x1505 = true;
} else {
x1505 = false;
}
bool x1508;
if (x1507) {
x1508 = x1506;
} else {
x1508 = false;
}
bool x1509 = x1505 || x1508;
int32_t x1597;
if (x1509) {
x1597 = x1095;
} else {
int32_t x1510 = 0;
int32_t x1511 = 0;
bool* x1512 = (bool*)malloc(2 * sizeof(bool));
bool* x1513 = (bool*)malloc(2 * sizeof(bool));
int32_t x1514 = 0;
for (;;) {
int32_t x1515 = x1514;
bool x1516 = x1515 < x1411;
bool x1518;
if (x1516) {
bool x1517 = x1515 < x1120;
x1518 = x1517;
} else {
x1518 = false;
}
bool x1522;
if (x1518) {
char x1519 = x1410[x1515];
char x1520 = x1119[x1515];
bool x1521 = x1519 == x1520;
x1522 = x1521;
} else {
x1522 = false;
}
if (!x1522) break;
x1514 += 1;
}
int32_t x1527 = x1514;
char x1528 = x1410[x1527];
char x1529 = x1119[x1527];
bool x1530 = x1528 < x1529;
x1512[0] = x1530;
bool x1533 = x1411 == x1120;
bool x1548;
if (x1533) {
int32_t x1534 = 0;
for (;;) {
int32_t x1535 = x1534;
bool x1536 = x1535 < x1411;
bool x1540;
if (x1536) {
char x1537 = x1410[x1535];
char x1538 = x1119[x1535];
bool x1539 = x1537 == x1538;
x1540 = x1539;
} else {
x1540 = false;
}
if (!x1540) break;
x1534 += 1;
}
int32_t x1545 = x1534;
bool x1546 = x1545 == x1411;
x1548 = x1546;
} else {
x1548 = false;
}
x1513[0] = x1548;
x1511 += 1;
int32_t x1551 = x1511;
int32_t x1552 = 0;
for (;;) {
int32_t x1553 = x1552;
bool x1554 = x1553 < x1413;
bool x1556;
if (x1554) {
bool x1555 = x1553 < x1122;
x1556 = x1555;
} else {
x1556 = false;
}
bool x1560;
if (x1556) {
char x1557 = x1412[x1553];
char x1558 = x1121[x1553];
bool x1559 = x1557 == x1558;
x1560 = x1559;
} else {
x1560 = false;
}
if (!x1560) break;
x1552 += 1;
}
int32_t x1565 = x1552;
char x1566 = x1412[x1565];
char x1567 = x1121[x1565];
bool x1568 = x1566 < x1567;
x1512[x1551] = x1568;
bool x1571 = x1413 == x1122;
bool x1586;
if (x1571) {
int32_t x1572 = 0;
for (;;) {
int32_t x1573 = x1572;
bool x1574 = x1573 < x1413;
bool x1578;
if (x1574) {
char x1575 = x1412[x1573];
char x1576 = x1121[x1573];
bool x1577 = x1575 == x1576;
x1578 = x1577;
} else {
x1578 = false;
}
if (!x1578) break;
x1572 += 1;
}
int32_t x1583 = x1572;
bool x1584 = x1583 == x1413;
x1586 = x1584;
} else {
x1586 = false;
}
x1513[x1551] = x1586;
x1511 += 1;
bool x1589 = x1512[0];
bool x1591 = x1513[0];
bool x1592 = x1512[1];
bool x1590;
if (x1589) {
x1590 = true;
} else {
x1590 = false;
}
bool x1593;
if (x1592) {
x1593 = x1591;
} else {
x1593 = false;
}
bool x1594 = x1590 || x1593;
int32_t x1595;
if (x1594) {
x1595 = x1096;
} else {
x1595 = x1101;
}
x1597 = x1595;
}
x1599 = x1597;
}
int32_t x1600 = x47[x1599];
for (;;) {
int32_t x1601 = x1097;
int32_t x1602 = x1098;
bool x1603 = x1601 <= x1602;
if (!x1603) break;
for (;;) {
int32_t x1605 = x1097;
int32_t x1606 = x47[x1605];
char* x1607 = x32[x1606];
int32_t x1608 = x33[x1606];
char* x1609 = x34[x1606];
int32_t x1610 = x35[x1606];
double x1611 = x36[x1606];
double x1612 = x37[x1606];
double x1613 = x38[x1606];
double x1614 = x39[x1606];
double x1615 = x40[x1606];
int32_t x1616 = x41[x1606];
double x1617 = x42[x1606];
int32_t x1618 = x43[x1606];
double x1619 = x44[x1606];
int32_t x1620 = x45[x1606];
int32_t x1621 = x46[x1606];
char* x1622 = x32[x1600];
int32_t x1623 = x33[x1600];
char* x1624 = x34[x1600];
int32_t x1625 = x35[x1600];
double x1626 = x36[x1600];
double x1627 = x37[x1600];
double x1628 = x38[x1600];
double x1629 = x39[x1600];
double x1630 = x40[x1600];
int32_t x1631 = x41[x1600];
double x1632 = x42[x1600];
int32_t x1633 = x43[x1600];
double x1634 = x44[x1600];
int32_t x1635 = x45[x1600];
int32_t x1636 = x46[x1600];
int32_t x1637 = 0;
int32_t x1638 = 0;
bool* x1639 = (bool*)malloc(2 * sizeof(bool));
bool* x1640 = (bool*)malloc(2 * sizeof(bool));
int32_t x1641 = 0;
for (;;) {
int32_t x1642 = x1641;
bool x1643 = x1642 < x1608;
bool x1645;
if (x1643) {
bool x1644 = x1642 < x1623;
x1645 = x1644;
} else {
x1645 = false;
}
bool x1649;
if (x1645) {
char x1646 = x1607[x1642];
char x1647 = x1622[x1642];
bool x1648 = x1646 == x1647;
x1649 = x1648;
} else {
x1649 = false;
}
if (!x1649) break;
x1641 += 1;
}
int32_t x1654 = x1641;
char x1655 = x1607[x1654];
char x1656 = x1622[x1654];
bool x1657 = x1655 < x1656;
x1639[0] = x1657;
bool x1660 = x1608 == x1623;
bool x1675;
if (x1660) {
int32_t x1661 = 0;
for (;;) {
int32_t x1662 = x1661;
bool x1663 = x1662 < x1608;
bool x1667;
if (x1663) {
char x1664 = x1607[x1662];
char x1665 = x1622[x1662];
bool x1666 = x1664 == x1665;
x1667 = x1666;
} else {
x1667 = false;
}
if (!x1667) break;
x1661 += 1;
}
int32_t x1672 = x1661;
bool x1673 = x1672 == x1608;
x1675 = x1673;
} else {
x1675 = false;
}
x1640[0] = x1675;
x1638 += 1;
int32_t x1678 = x1638;
int32_t x1679 = 0;
for (;;) {
int32_t x1680 = x1679;
bool x1681 = x1680 < x1610;
bool x1683;
if (x1681) {
bool x1682 = x1680 < x1625;
x1683 = x1682;
} else {
x1683 = false;
}
bool x1687;
if (x1683) {
char x1684 = x1609[x1680];
char x1685 = x1624[x1680];
bool x1686 = x1684 == x1685;
x1687 = x1686;
} else {
x1687 = false;
}
if (!x1687) break;
x1679 += 1;
}
int32_t x1692 = x1679;
char x1693 = x1609[x1692];
char x1694 = x1624[x1692];
bool x1695 = x1693 < x1694;
x1639[x1678] = x1695;
bool x1698 = x1610 == x1625;
bool x1713;
if (x1698) {
int32_t x1699 = 0;
for (;;) {
int32_t x1700 = x1699;
bool x1701 = x1700 < x1610;
bool x1705;
if (x1701) {
char x1702 = x1609[x1700];
char x1703 = x1624[x1700];
bool x1704 = x1702 == x1703;
x1705 = x1704;
} else {
x1705 = false;
}
if (!x1705) break;
x1699 += 1;
}
int32_t x1710 = x1699;
bool x1711 = x1710 == x1610;
x1713 = x1711;
} else {
x1713 = false;
}
x1640[x1678] = x1713;
x1638 += 1;
bool x1716 = x1639[0];
bool x1718 = x1640[0];
bool x1719 = x1639[1];
bool x1717;
if (x1716) {
x1717 = true;
} else {
x1717 = false;
}
bool x1720;
if (x1719) {
x1720 = x1718;
} else {
x1720 = false;
}
bool x1721 = x1717 || x1720;
if (!x1721) break;
int32_t x1723 = x1097;
int32_t x1724 = x1723 + 1;
x1097 = x1724;
}
for (;;) {
char* x1728 = x32[x1600];
int32_t x1729 = x33[x1600];
char* x1730 = x34[x1600];
int32_t x1731 = x35[x1600];
double x1732 = x36[x1600];
double x1733 = x37[x1600];
double x1734 = x38[x1600];
double x1735 = x39[x1600];
double x1736 = x40[x1600];
int32_t x1737 = x41[x1600];
double x1738 = x42[x1600];
int32_t x1739 = x43[x1600];
double x1740 = x44[x1600];
int32_t x1741 = x45[x1600];
int32_t x1742 = x46[x1600];
int32_t x1743 = x1098;
int32_t x1744 = x47[x1743];
char* x1745 = x32[x1744];
int32_t x1746 = x33[x1744];
char* x1747 = x34[x1744];
int32_t x1748 = x35[x1744];
double x1749 = x36[x1744];
double x1750 = x37[x1744];
double x1751 = x38[x1744];
double x1752 = x39[x1744];
double x1753 = x40[x1744];
int32_t x1754 = x41[x1744];
double x1755 = x42[x1744];
int32_t x1756 = x43[x1744];
double x1757 = x44[x1744];
int32_t x1758 = x45[x1744];
int32_t x1759 = x46[x1744];
int32_t x1760 = 0;
int32_t x1761 = 0;
bool* x1762 = (bool*)malloc(2 * sizeof(bool));
bool* x1763 = (bool*)malloc(2 * sizeof(bool));
int32_t x1764 = 0;
for (;;) {
int32_t x1765 = x1764;
bool x1766 = x1765 < x1729;
bool x1768;
if (x1766) {
bool x1767 = x1765 < x1746;
x1768 = x1767;
} else {
x1768 = false;
}
bool x1772;
if (x1768) {
char x1769 = x1728[x1765];
char x1770 = x1745[x1765];
bool x1771 = x1769 == x1770;
x1772 = x1771;
} else {
x1772 = false;
}
if (!x1772) break;
x1764 += 1;
}
int32_t x1777 = x1764;
char x1778 = x1728[x1777];
char x1779 = x1745[x1777];
bool x1780 = x1778 < x1779;
x1762[0] = x1780;
bool x1783 = x1729 == x1746;
bool x1798;
if (x1783) {
int32_t x1784 = 0;
for (;;) {
int32_t x1785 = x1784;
bool x1786 = x1785 < x1729;
bool x1790;
if (x1786) {
char x1787 = x1728[x1785];
char x1788 = x1745[x1785];
bool x1789 = x1787 == x1788;
x1790 = x1789;
} else {
x1790 = false;
}
if (!x1790) break;
x1784 += 1;
}
int32_t x1795 = x1784;
bool x1796 = x1795 == x1729;
x1798 = x1796;
} else {
x1798 = false;
}
x1763[0] = x1798;
x1761 += 1;
int32_t x1801 = x1761;
int32_t x1802 = 0;
for (;;) {
int32_t x1803 = x1802;
bool x1804 = x1803 < x1731;
bool x1806;
if (x1804) {
bool x1805 = x1803 < x1748;
x1806 = x1805;
} else {
x1806 = false;
}
bool x1810;
if (x1806) {
char x1807 = x1730[x1803];
char x1808 = x1747[x1803];
bool x1809 = x1807 == x1808;
x1810 = x1809;
} else {
x1810 = false;
}
if (!x1810) break;
x1802 += 1;
}
int32_t x1815 = x1802;
char x1816 = x1730[x1815];
char x1817 = x1747[x1815];
bool x1818 = x1816 < x1817;
x1762[x1801] = x1818;
bool x1821 = x1731 == x1748;
bool x1836;
if (x1821) {
int32_t x1822 = 0;
for (;;) {
int32_t x1823 = x1822;
bool x1824 = x1823 < x1731;
bool x1828;
if (x1824) {
char x1825 = x1730[x1823];
char x1826 = x1747[x1823];
bool x1827 = x1825 == x1826;
x1828 = x1827;
} else {
x1828 = false;
}
if (!x1828) break;
x1822 += 1;
}
int32_t x1833 = x1822;
bool x1834 = x1833 == x1731;
x1836 = x1834;
} else {
x1836 = false;
}
x1763[x1801] = x1836;
x1761 += 1;
bool x1839 = x1762[0];
bool x1841 = x1763[0];
bool x1842 = x1762[1];
bool x1840;
if (x1839) {
x1840 = true;
} else {
x1840 = false;
}
bool x1843;
if (x1842) {
x1843 = x1841;
} else {
x1843 = false;
}
bool x1844 = x1840 || x1843;
if (!x1844) break;
int32_t x1846 = x1098;
int32_t x1847 = x1846 - 1;
x1098 = x1847;
}
int32_t x1851 = x1097;
int32_t x1852 = x1098;
bool x1853 = x1851 <= x1852;
if (x1853) {
int32_t x1854 = x47[x1851];
int32_t x1855 = x47[x1852];
x47[x1851] = x1855;
x47[x1852] = x1854;
int32_t x1858 = x1851 + 1;
x1097 = x1858;
int32_t x1860 = x1852 - 1;
x1098 = x1860;
} else {
}
}
int32_t x1866 = x1098;
bool x1867 = x1095 < x1866;
if (x1867) {
x50[x1093] = x1095;
x51[x1093] = x1866;
int32_t x1870 = x1093 + 1;
x1088 = x1870;
} else {
}
int32_t x1874 = x1097;
bool x1875 = x1874 < x1096;
if (x1875) {
int32_t x1876 = x1088;
x50[x1876] = x1874;
x51[x1876] = x1096;
int32_t x1879 = x1876 + 1;
x1088 = x1879;
} else {
}
}
for(int x1886=0; x1886 < x1084; x1886++) {
int32_t x1887 = x47[x1886];
char* x1888 = x32[x1887];
int32_t x1889 = x33[x1887];
char* x1890 = x34[x1887];
int32_t x1891 = x35[x1887];
double x1892 = x36[x1887];
double x1893 = x37[x1887];
double x1894 = x38[x1887];
double x1895 = x39[x1887];
double x1896 = x40[x1887];
int32_t x1897 = x41[x1887];
double x1898 = x42[x1887];
int32_t x1899 = x43[x1887];
double x1900 = x44[x1887];
int32_t x1901 = x45[x1887];
int32_t x1902 = x46[x1887];
int32_t x1903 = printll(x1888);
printf(",");
int32_t x1905 = printll(x1890);
printf(",");
printf("%f",x1892);
printf(",");
printf("%f",x1893);
printf(",");
printf("%f",x1894);
printf(",");
printf("%f",x1895);
printf(",");
double x1916 = (double)x1897;
double x1917 = x1896 / x1916;
printf("%f",x1917);
printf(",");
double x1921 = (double)x1899;
double x1922 = x1898 / x1921;
printf("%f",x1922);
printf(",");
double x1926 = (double)x1901;
double x1927 = x1900 / x1926;
printf("%f",x1927);
printf(",");
printf("%d",x1902);
printf("%s\n","");

}
end = cur_time();
print_performance(begin, end);
}
/*****************************************
  End of C Generated Code                  
*******************************************/

