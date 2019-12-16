
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
int32_t x87 = 0;
int32_t x84 = open("/Users/jun/src/tpch-dbgen/part.tbl",0);
int32_t x85 = fsize(x84);
int32_t x88 = x85;
char* x86 = (char*)mmap(0, x85, PROT_READ, MAP_FILE | MAP_SHARED, x84, 0);
for (;;) {
int32_t x89 = x87;
int32_t x90 = x88;
bool x91 = x89 < x90;
if (!x91) break;
int32_t x93 = x87;
int32_t x94 = 0;
for (;;) {
int32_t x95 = x87;
char x96 = x86[x95];
bool x97 = x96 != '|';
if (!x97) break;
int32_t x99 = x94;
int32_t x101 = x87;
int32_t x100 = x99 * 10;
char x102 = x86[x101];
char x103 = x102 - '0';
int32_t x104 = x100 + x103;
x94 = x104;
x87 += 1;
}
x87 += 1;
int32_t x110 = x94;
int32_t x111 = x87;
for (;;) {
int32_t x112 = x87;
char x113 = x86[x112];
bool x114 = x113 != '|';
if (!x114) break;
x87 += 1;
}
int32_t x119 = x87;
x87 += 1;
int32_t x123 = x87;
for (;;) {
int32_t x124 = x87;
char x125 = x86[x124];
bool x126 = x125 != '|';
if (!x126) break;
x87 += 1;
}
int32_t x131 = x87;
x87 += 1;
int32_t x135 = x87;
for (;;) {
int32_t x136 = x87;
char x137 = x86[x136];
bool x138 = x137 != '|';
if (!x138) break;
x87 += 1;
}
int32_t x143 = x87;
x87 += 1;
int32_t x147 = x87;
for (;;) {
int32_t x148 = x87;
char x149 = x86[x148];
bool x150 = x149 != '|';
if (!x150) break;
x87 += 1;
}
int32_t x155 = x87;
x87 += 1;
int32_t x159 = x87;
int32_t x160 = 0;
for (;;) {
int32_t x161 = x87;
char x162 = x86[x161];
bool x163 = x162 != '|';
if (!x163) break;
int32_t x165 = x160;
int32_t x167 = x87;
int32_t x166 = x165 * 10;
char x168 = x86[x167];
char x169 = x168 - '0';
int32_t x170 = x166 + x169;
x160 = x170;
x87 += 1;
}
x87 += 1;
int32_t x176 = x160;
int32_t x177 = x87;
for (;;) {
int32_t x178 = x87;
char x179 = x86[x178];
bool x180 = x179 != '|';
if (!x180) break;
x87 += 1;
}
int32_t x185 = x87;
x87 += 1;
int32_t x189 = x87;
double x190 = 0.0;
double x191 = 10.0;
for (;;) {
int32_t x192 = x87;
char x193 = x86[x192];
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
int32_t x201 = x87;
double x200 = x199 * 10.0;
char x202 = x86[x201];
char x203 = x202 - '0';
double x205 = (double)x203;
double x206 = x200 + x205;
x190 = x206;
x87 += 1;
}
int32_t x211 = x87;
char x212 = x86[x211];
bool x214 = x212 == '|';
if (x214) {
} else {
x87 += 1;
for (;;) {
int32_t x216 = x87;
char x217 = x86[x216];
bool x218 = x217 != '|';
if (!x218) break;
double x220 = x190;
int32_t x221 = x87;
double x224 = x191;
char x222 = x86[x221];
char x223 = x222 - '0';
double x226 = (double)x223;
double x227 = x226 / x224;
double x228 = x220 + x227;
x190 = x228;
double x230 = x224 * 10.0;
x191 = x230;
x87 += 1;
}
}
x87 += 1;
double x238 = x190;
int32_t x239 = x87;
for (;;) {
int32_t x240 = x87;
char x241 = x86[x240];
bool x242 = x241 != '\n';
if (!x242) break;
x87 += 1;
}
int32_t x247 = x87;
x87 += 1;
int32_t x251 = x18;
x2[x251] = x110;
char* x122 = x86 + x111;
x3[x251] = x122;
int32_t x120 = x119 - x111;
x4[x251] = x120;
char* x134 = x86 + x123;
x5[x251] = x134;
int32_t x132 = x131 - x123;
x6[x251] = x132;
char* x146 = x86 + x135;
x7[x251] = x146;
int32_t x144 = x143 - x135;
x8[x251] = x144;
char* x158 = x86 + x147;
x9[x251] = x158;
int32_t x156 = x155 - x147;
x10[x251] = x156;
x11[x251] = x176;
char* x188 = x86 + x177;
x12[x251] = x188;
int32_t x186 = x185 - x177;
x13[x251] = x186;
x14[x251] = x238;
char* x250 = x86 + x239;
x15[x251] = x250;
int32_t x248 = x247 - x239;
x16[x251] = x248;
x18 += 1;
}
close(x84);
int32_t x274 = 0;
int32_t x271 = open("/Users/jun/src/tpch-dbgen/lineitem.tbl",0);
int32_t x272 = fsize(x271);
int32_t x275 = x272;
char* x273 = (char*)mmap(0, x272, PROT_READ, MAP_FILE | MAP_SHARED, x271, 0);
for (;;) {
int32_t x276 = x274;
int32_t x277 = x275;
bool x278 = x276 < x277;
if (!x278) break;
int32_t x280 = x274;
int32_t x281 = 0;
for (;;) {
int32_t x282 = x274;
char x283 = x273[x282];
bool x284 = x283 != '|';
if (!x284) break;
int32_t x286 = x281;
int32_t x288 = x274;
int32_t x287 = x286 * 10;
char x289 = x273[x288];
char x290 = x289 - '0';
int32_t x291 = x287 + x290;
x281 = x291;
x274 += 1;
}
x274 += 1;
int32_t x297 = x281;
int32_t x298 = x274;
int32_t x299 = 0;
for (;;) {
int32_t x300 = x274;
char x301 = x273[x300];
bool x302 = x301 != '|';
if (!x302) break;
int32_t x304 = x299;
int32_t x306 = x274;
int32_t x305 = x304 * 10;
char x307 = x273[x306];
char x308 = x307 - '0';
int32_t x309 = x305 + x308;
x299 = x309;
x274 += 1;
}
x274 += 1;
int32_t x315 = x299;
int32_t x316 = x274;
int32_t x317 = 0;
for (;;) {
int32_t x318 = x274;
char x319 = x273[x318];
bool x320 = x319 != '|';
if (!x320) break;
int32_t x322 = x317;
int32_t x324 = x274;
int32_t x323 = x322 * 10;
char x325 = x273[x324];
char x326 = x325 - '0';
int32_t x327 = x323 + x326;
x317 = x327;
x274 += 1;
}
x274 += 1;
int32_t x333 = x317;
int32_t x334 = x274;
int32_t x335 = 0;
for (;;) {
int32_t x336 = x274;
char x337 = x273[x336];
bool x338 = x337 != '|';
if (!x338) break;
int32_t x340 = x335;
int32_t x342 = x274;
int32_t x341 = x340 * 10;
char x343 = x273[x342];
char x344 = x343 - '0';
int32_t x345 = x341 + x344;
x335 = x345;
x274 += 1;
}
x274 += 1;
int32_t x351 = x335;
int32_t x352 = x274;
double x353 = 0.0;
double x354 = 10.0;
for (;;) {
int32_t x355 = x274;
char x356 = x273[x355];
bool x358 = x356 == '.';
bool x360;
if (x358) {
x360 = false;
} else {
bool x359 = x356 != '|';
x360 = x359;
}
if (!x360) break;
double x362 = x353;
int32_t x364 = x274;
double x363 = x362 * 10.0;
char x365 = x273[x364];
char x366 = x365 - '0';
double x368 = (double)x366;
double x369 = x363 + x368;
x353 = x369;
x274 += 1;
}
int32_t x374 = x274;
char x375 = x273[x374];
bool x377 = x375 == '|';
if (x377) {
} else {
x274 += 1;
for (;;) {
int32_t x379 = x274;
char x380 = x273[x379];
bool x381 = x380 != '|';
if (!x381) break;
double x383 = x353;
int32_t x384 = x274;
double x387 = x354;
char x385 = x273[x384];
char x386 = x385 - '0';
double x389 = (double)x386;
double x390 = x389 / x387;
double x391 = x383 + x390;
x353 = x391;
double x393 = x387 * 10.0;
x354 = x393;
x274 += 1;
}
}
x274 += 1;
double x401 = x353;
int32_t x402 = x274;
double x403 = 0.0;
double x404 = 10.0;
for (;;) {
int32_t x405 = x274;
char x406 = x273[x405];
bool x408 = x406 == '.';
bool x410;
if (x408) {
x410 = false;
} else {
bool x409 = x406 != '|';
x410 = x409;
}
if (!x410) break;
double x412 = x403;
int32_t x414 = x274;
double x413 = x412 * 10.0;
char x415 = x273[x414];
char x416 = x415 - '0';
double x418 = (double)x416;
double x419 = x413 + x418;
x403 = x419;
x274 += 1;
}
int32_t x424 = x274;
char x425 = x273[x424];
bool x427 = x425 == '|';
if (x427) {
} else {
x274 += 1;
for (;;) {
int32_t x429 = x274;
char x430 = x273[x429];
bool x431 = x430 != '|';
if (!x431) break;
double x433 = x403;
int32_t x434 = x274;
double x437 = x404;
char x435 = x273[x434];
char x436 = x435 - '0';
double x439 = (double)x436;
double x440 = x439 / x437;
double x441 = x433 + x440;
x403 = x441;
double x443 = x437 * 10.0;
x404 = x443;
x274 += 1;
}
}
x274 += 1;
double x451 = x403;
int32_t x452 = x274;
double x453 = 0.0;
double x454 = 10.0;
for (;;) {
int32_t x455 = x274;
char x456 = x273[x455];
bool x458 = x456 == '.';
bool x460;
if (x458) {
x460 = false;
} else {
bool x459 = x456 != '|';
x460 = x459;
}
if (!x460) break;
double x462 = x453;
int32_t x464 = x274;
double x463 = x462 * 10.0;
char x465 = x273[x464];
char x466 = x465 - '0';
double x468 = (double)x466;
double x469 = x463 + x468;
x453 = x469;
x274 += 1;
}
int32_t x474 = x274;
char x475 = x273[x474];
bool x477 = x475 == '|';
if (x477) {
} else {
x274 += 1;
for (;;) {
int32_t x479 = x274;
char x480 = x273[x479];
bool x481 = x480 != '|';
if (!x481) break;
double x483 = x453;
int32_t x484 = x274;
double x487 = x454;
char x485 = x273[x484];
char x486 = x485 - '0';
double x489 = (double)x486;
double x490 = x489 / x487;
double x491 = x483 + x490;
x453 = x491;
double x493 = x487 * 10.0;
x454 = x493;
x274 += 1;
}
}
x274 += 1;
double x501 = x453;
int32_t x502 = x274;
double x503 = 0.0;
double x504 = 10.0;
for (;;) {
int32_t x505 = x274;
char x506 = x273[x505];
bool x508 = x506 == '.';
bool x510;
if (x508) {
x510 = false;
} else {
bool x509 = x506 != '|';
x510 = x509;
}
if (!x510) break;
double x512 = x503;
int32_t x514 = x274;
double x513 = x512 * 10.0;
char x515 = x273[x514];
char x516 = x515 - '0';
double x518 = (double)x516;
double x519 = x513 + x518;
x503 = x519;
x274 += 1;
}
int32_t x524 = x274;
char x525 = x273[x524];
bool x527 = x525 == '|';
if (x527) {
} else {
x274 += 1;
for (;;) {
int32_t x529 = x274;
char x530 = x273[x529];
bool x531 = x530 != '|';
if (!x531) break;
double x533 = x503;
int32_t x534 = x274;
double x537 = x504;
char x535 = x273[x534];
char x536 = x535 - '0';
double x539 = (double)x536;
double x540 = x539 / x537;
double x541 = x533 + x540;
x503 = x541;
double x543 = x537 * 10.0;
x504 = x543;
x274 += 1;
}
}
x274 += 1;
double x551 = x503;
int32_t x552 = x274;
for (;;) {
int32_t x553 = x274;
char x554 = x273[x553];
bool x555 = x554 != '|';
if (!x555) break;
x274 += 1;
}
int32_t x560 = x274;
x274 += 1;
int32_t x564 = x274;
for (;;) {
int32_t x565 = x274;
char x566 = x273[x565];
bool x567 = x566 != '|';
if (!x567) break;
x274 += 1;
}
int32_t x572 = x274;
x274 += 1;
int32_t x576 = x274;
int32_t x577 = 0;
int32_t x578 = 0;
int32_t x579 = 0;
for (;;) {
int32_t x580 = x274;
char x581 = x273[x580];
bool x582 = x581 != '-';
if (!x582) break;
int32_t x584 = x577;
int32_t x586 = x274;
int32_t x585 = x584 * 10;
char x587 = x273[x586];
char x588 = x587 - '0';
int32_t x589 = x585 + x588;
x577 = x589;
x274 += 1;
}
x274 += 1;
for (;;) {
int32_t x595 = x274;
char x596 = x273[x595];
bool x597 = x596 != '-';
if (!x597) break;
int32_t x599 = x578;
int32_t x601 = x274;
int32_t x600 = x599 * 10;
char x602 = x273[x601];
char x603 = x602 - '0';
int32_t x604 = x600 + x603;
x578 = x604;
x274 += 1;
}
x274 += 1;
for (;;) {
int32_t x610 = x274;
char x611 = x273[x610];
bool x612 = x611 != '|';
if (!x612) break;
int32_t x614 = x579;
int32_t x616 = x274;
int32_t x615 = x614 * 10;
char x617 = x273[x616];
char x618 = x617 - '0';
int32_t x619 = x615 + x618;
x579 = x619;
x274 += 1;
}
x274 += 1;
int32_t x625 = x577;
int32_t x626 = x578;
int32_t x627 = x579;
int32_t x628 = x274;
int32_t x629 = 0;
int32_t x630 = 0;
int32_t x631 = 0;
for (;;) {
int32_t x632 = x274;
char x633 = x273[x632];
bool x634 = x633 != '-';
if (!x634) break;
int32_t x636 = x629;
int32_t x638 = x274;
int32_t x637 = x636 * 10;
char x639 = x273[x638];
char x640 = x639 - '0';
int32_t x641 = x637 + x640;
x629 = x641;
x274 += 1;
}
x274 += 1;
for (;;) {
int32_t x647 = x274;
char x648 = x273[x647];
bool x649 = x648 != '-';
if (!x649) break;
int32_t x651 = x630;
int32_t x653 = x274;
int32_t x652 = x651 * 10;
char x654 = x273[x653];
char x655 = x654 - '0';
int32_t x656 = x652 + x655;
x630 = x656;
x274 += 1;
}
x274 += 1;
for (;;) {
int32_t x662 = x274;
char x663 = x273[x662];
bool x664 = x663 != '|';
if (!x664) break;
int32_t x666 = x631;
int32_t x668 = x274;
int32_t x667 = x666 * 10;
char x669 = x273[x668];
char x670 = x669 - '0';
int32_t x671 = x667 + x670;
x631 = x671;
x274 += 1;
}
x274 += 1;
int32_t x677 = x629;
int32_t x678 = x630;
int32_t x679 = x631;
int32_t x680 = x274;
int32_t x681 = 0;
int32_t x682 = 0;
int32_t x683 = 0;
for (;;) {
int32_t x684 = x274;
char x685 = x273[x684];
bool x686 = x685 != '-';
if (!x686) break;
int32_t x688 = x681;
int32_t x690 = x274;
int32_t x689 = x688 * 10;
char x691 = x273[x690];
char x692 = x691 - '0';
int32_t x693 = x689 + x692;
x681 = x693;
x274 += 1;
}
x274 += 1;
for (;;) {
int32_t x699 = x274;
char x700 = x273[x699];
bool x701 = x700 != '-';
if (!x701) break;
int32_t x703 = x682;
int32_t x705 = x274;
int32_t x704 = x703 * 10;
char x706 = x273[x705];
char x707 = x706 - '0';
int32_t x708 = x704 + x707;
x682 = x708;
x274 += 1;
}
x274 += 1;
for (;;) {
int32_t x714 = x274;
char x715 = x273[x714];
bool x716 = x715 != '|';
if (!x716) break;
int32_t x718 = x683;
int32_t x720 = x274;
int32_t x719 = x718 * 10;
char x721 = x273[x720];
char x722 = x721 - '0';
int32_t x723 = x719 + x722;
x683 = x723;
x274 += 1;
}
x274 += 1;
int32_t x729 = x681;
int32_t x730 = x682;
int32_t x731 = x683;
int32_t x732 = x274;
for (;;) {
int32_t x733 = x274;
char x734 = x273[x733];
bool x735 = x734 != '|';
if (!x735) break;
x274 += 1;
}
int32_t x740 = x274;
x274 += 1;
int32_t x744 = x274;
for (;;) {
int32_t x745 = x274;
char x746 = x273[x745];
bool x747 = x746 != '|';
if (!x747) break;
x274 += 1;
}
int32_t x752 = x274;
x274 += 1;
int32_t x756 = x274;
for (;;) {
int32_t x757 = x274;
char x758 = x273[x757];
bool x759 = x758 != '\n';
if (!x759) break;
x274 += 1;
}
int32_t x764 = x274;
x274 += 1;
int32_t x768 = x47;
x19[x768] = x297;
x20[x768] = x315;
x21[x768] = x333;
x22[x768] = x351;
x23[x768] = x401;
x24[x768] = x451;
x25[x768] = x501;
x26[x768] = x551;
char* x563 = x273 + x552;
x27[x768] = x563;
int32_t x561 = x560 - x552;
x28[x768] = x561;
char* x575 = x273 + x564;
x29[x768] = x575;
int32_t x573 = x572 - x564;
x30[x768] = x573;
x31[x768] = x625;
x32[x768] = x626;
x33[x768] = x627;
x34[x768] = x677;
x35[x768] = x678;
x36[x768] = x679;
x37[x768] = x729;
x38[x768] = x730;
x39[x768] = x731;
char* x743 = x273 + x732;
x40[x768] = x743;
int32_t x741 = x740 - x732;
x41[x768] = x741;
char* x755 = x273 + x744;
x42[x768] = x755;
int32_t x753 = x752 - x744;
x43[x768] = x753;
char* x767 = x273 + x756;
x44[x768] = x767;
int32_t x765 = x764 - x756;
x45[x768] = x765;
x47 += 1;
}
close(x271);
int32_t x839 = x49 - 1;
int32_t x846 = x61 - 1;
int32_t x955 = (int32_t)0L;
bool x956 = x955 >= 0;
int32_t x958;
if (x956) {
x958 = x955;
} else {
int32_t x957 = 0 - x955;
x958 = x957;
}
int32_t x959 = x958 % x49;
bool x963 = !true;
struct timeval begin, end;
begin = cur_time();
int32_t x800 = x18;
for(int x802=0; x802 < x800; x802++) {
int32_t x803 = x2[x802];
char* x804 = x3[x802];
int32_t x805 = x4[x802];
char* x806 = x5[x802];
int32_t x807 = x6[x802];
char* x808 = x7[x802];
int32_t x809 = x8[x802];
char* x810 = x9[x802];
int32_t x811 = x10[x802];
int32_t x812 = x11[x802];
char* x813 = x12[x802];
int32_t x814 = x13[x802];
double x815 = x14[x802];
char* x816 = x15[x802];
int32_t x817 = x16[x802];
int32_t x818 = (int32_t)x803;
bool x819 = x818 >= 0;
int32_t x821;
if (x819) {
x821 = x818;
} else {
int32_t x820 = 0 - x818;
x821 = x820;
}
int32_t x822 = x821 % x49;
int32_t x823 = x822;
for (;;) {
int32_t x824 = x823;
int32_t x825 = x79[x824];
bool x826 = x825 > 0;
bool x831;
if (x826) {
int32_t x827 = x62[x824];
bool x828 = x827 == x803;
bool x829 = !x828;
x831 = x829;
} else {
x831 = false;
}
if (!x831) break;
int32_t x833 = x823;
int32_t x834 = x833 + 1;
x823 = x834;
}
int32_t x838 = x823;
bool x840 = x838 == x839;
if (x840) {
printf("%s\n","LB2HashMultiMap table is full.");
exit(1);
} else {
}
int32_t x845 = x79[x838];
bool x847 = x845 == x846;
if (x847) {
printf("%s\n","Bucket is full.");
exit(1);
} else {
}
x62[x838] = x803;
int32_t x852 = x838 * x61;
int32_t x853 = x852 + x845;
x64[x853] = x803;
x65[x853] = x804;
x66[x853] = x805;
x67[x853] = x806;
x68[x853] = x807;
x69[x853] = x808;
x70[x853] = x809;
x71[x853] = x810;
x72[x853] = x811;
x73[x853] = x812;
x74[x853] = x813;
x75[x853] = x814;
x76[x853] = x815;
x77[x853] = x816;
x78[x853] = x817;
int32_t x870 = x845 + 1;
x79[x838] = x870;

}
int32_t x874 = x47;
for(int x876=0; x876 < x874; x876++) {
int32_t x877 = x19[x876];
int32_t x878 = x20[x876];
int32_t x879 = x21[x876];
int32_t x880 = x22[x876];
double x881 = x23[x876];
double x882 = x24[x876];
double x883 = x25[x876];
double x884 = x26[x876];
char* x885 = x27[x876];
int32_t x886 = x28[x876];
char* x887 = x29[x876];
int32_t x888 = x30[x876];
int32_t x889 = x31[x876];
int32_t x890 = x32[x876];
int32_t x891 = x33[x876];
int32_t x892 = x34[x876];
int32_t x893 = x35[x876];
int32_t x894 = x36[x876];
int32_t x895 = x37[x876];
int32_t x896 = x38[x876];
int32_t x897 = x39[x876];
char* x898 = x40[x876];
int32_t x899 = x41[x876];
char* x900 = x42[x876];
int32_t x901 = x43[x876];
char* x902 = x44[x876];
int32_t x903 = x45[x876];
int32_t x904 = x889 * 10000;
int32_t x905 = x890 * 100;
int32_t x906 = x904 + x905;
int32_t x907 = x906 + x891;
bool x908 = x907 >= 19950901;
bool x910;
if (x908) {
bool x909 = x907 < 19951001;
x910 = x909;
} else {
x910 = false;
}
if (x910) {
int32_t x911 = (int32_t)x878;
bool x912 = x911 >= 0;
int32_t x914;
if (x912) {
x914 = x911;
} else {
int32_t x913 = 0 - x911;
x914 = x913;
}
int32_t x915 = x914 % x49;
int32_t x916 = x915;
for (;;) {
int32_t x917 = x916;
int32_t x918 = x79[x917];
bool x919 = x918 > 0;
bool x924;
if (x919) {
int32_t x920 = x62[x917];
bool x921 = x920 == x878;
bool x922 = !x921;
x924 = x922;
} else {
x924 = false;
}
if (!x924) break;
int32_t x926 = x916;
int32_t x927 = x926 + 1;
x916 = x927;
}
int32_t x931 = x916;
int32_t x932 = x79[x931];
int32_t x933 = x931 * x61;
int32_t x934 = x933 + x932;
double x952 = 1.0 - x883;
double x953 = x882 * x952;
for(int x936=x933; x936 < x934; x936++) {
int32_t x937 = x64[x936];
char* x938 = x65[x936];
int32_t x939 = x66[x936];
char* x940 = x67[x936];
int32_t x941 = x68[x936];
char* x942 = x69[x936];
int32_t x943 = x70[x936];
char* x944 = x71[x936];
int32_t x945 = x72[x936];
int32_t x946 = x73[x936];
char* x947 = x74[x936];
int32_t x948 = x75[x936];
double x949 = x76[x936];
char* x950 = x77[x936];
int32_t x951 = x78[x936];
bool x954 = pattern_compare(x944,"PROMO%");
if (x954) {
int32_t x960 = x959;
for (;;) {
int32_t x961 = x960;
bool x962 = x52[x961];
bool x964;
if (x962) {
x964 = x963;
} else {
x964 = false;
}
if (!x964) break;
x960 += 1;
}
int32_t x969 = x960;
bool x970 = x969 == x839;
if (x970) {
printf("%s\n","LB2HashMap table is full.");
exit(1);
} else {
}
bool x975 = x52[x969];
if (x975) {
double x976 = x50[x969];
double x977 = x51[x969];
double x978 = x976 + x953;
x50[x969] = x978;
double x979 = x977 + x953;
x51[x969] = x979;
} else {
int32_t x983 = x60;
x58[x983] = x969;
x60 += 1;
x50[x969] = x953;
x51[x969] = x953;
x52[x969] = true;
}
} else {
int32_t x992 = x959;
for (;;) {
int32_t x993 = x992;
bool x994 = x52[x993];
bool x995;
if (x994) {
x995 = x963;
} else {
x995 = false;
}
if (!x995) break;
x992 += 1;
}
int32_t x1000 = x992;
bool x1001 = x1000 == x839;
if (x1001) {
printf("%s\n","LB2HashMap table is full.");
exit(1);
} else {
}
bool x1006 = x52[x1000];
if (x1006) {
double x1007 = x50[x1000];
double x1008 = x51[x1000];
x50[x1000] = x1007;
double x1009 = x1008 + x953;
x51[x1000] = x1009;
} else {
int32_t x1013 = x60;
x58[x1013] = x1000;
x60 += 1;
x50[x1000] = 0.0;
x51[x1000] = x953;
x52[x1000] = true;
}
}

}
} else {
}

}
int32_t x1029 = x60;
for(int x1031=0; x1031 < x1029; x1031++) {
int32_t x1032 = x58[x1031];
double x1033 = x50[x1032];
double x1034 = x51[x1032];
printf("%f",x1033);
printf(",");
printf("%f",x1034);
printf(",");
double x1035 = 100.0 * x1033;
double x1036 = x1035 / x1034;
printf("%f",x1036);
printf("%s\n","");

}
end = cur_time();
print_performance(begin, end);
}
/*****************************************
  End of C Generated Code                  
*******************************************/

