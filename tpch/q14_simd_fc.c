
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
int32_t* x61 = (int32_t*)malloc(16 * sizeof(int32_t));
char** x62 = (char**)malloc(16 * sizeof(char*));
int32_t* x63 = (int32_t*)malloc(16 * sizeof(int32_t));
char** x64 = (char**)malloc(16 * sizeof(char*));
int32_t* x65 = (int32_t*)malloc(16 * sizeof(int32_t));
char** x66 = (char**)malloc(16 * sizeof(char*));
int32_t* x67 = (int32_t*)malloc(16 * sizeof(int32_t));
char** x68 = (char**)malloc(16 * sizeof(char*));
int32_t* x69 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x70 = (int32_t*)malloc(16 * sizeof(int32_t));
char** x71 = (char**)malloc(16 * sizeof(char*));
int32_t* x72 = (int32_t*)malloc(16 * sizeof(int32_t));
double* x73 = (double*)malloc(16 * sizeof(double));
char** x74 = (char**)malloc(16 * sizeof(char*));
int32_t* x75 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x76 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x77 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x78 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x79 = (int32_t*)malloc(16 * sizeof(int32_t));
double* x80 = (double*)malloc(16 * sizeof(double));
double* x81 = (double*)malloc(16 * sizeof(double));
double* x82 = (double*)malloc(16 * sizeof(double));
double* x83 = (double*)malloc(16 * sizeof(double));
char** x84 = (char**)malloc(16 * sizeof(char*));
int32_t* x85 = (int32_t*)malloc(16 * sizeof(int32_t));
char** x86 = (char**)malloc(16 * sizeof(char*));
int32_t* x87 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x88 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x89 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x90 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x91 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x92 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x93 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x94 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x95 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x96 = (int32_t*)malloc(16 * sizeof(int32_t));
char** x97 = (char**)malloc(16 * sizeof(char*));
int32_t* x98 = (int32_t*)malloc(16 * sizeof(int32_t));
char** x99 = (char**)malloc(16 * sizeof(char*));
int32_t* x100 = (int32_t*)malloc(16 * sizeof(int32_t));
char** x101 = (char**)malloc(16 * sizeof(char*));
int32_t* x102 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t x103 = 0;
int32_t x104 = 0;
double* x105 = (double*)malloc(16 * sizeof(double));
int32_t x106 = 0;
int32_t x107 = 0;
int32_t* x109 = (int32_t*)malloc(x49 * sizeof(int32_t));
int32_t x108 = BUCKET_SIZE;
int32_t x110 = x49 * x108;
int32_t* x111 = (int32_t*)malloc(x110 * sizeof(int32_t));
char** x112 = (char**)malloc(x110 * sizeof(char*));
int32_t* x113 = (int32_t*)malloc(x110 * sizeof(int32_t));
char** x114 = (char**)malloc(x110 * sizeof(char*));
int32_t* x115 = (int32_t*)malloc(x110 * sizeof(int32_t));
char** x116 = (char**)malloc(x110 * sizeof(char*));
int32_t* x117 = (int32_t*)malloc(x110 * sizeof(int32_t));
char** x118 = (char**)malloc(x110 * sizeof(char*));
int32_t* x119 = (int32_t*)malloc(x110 * sizeof(int32_t));
int32_t* x120 = (int32_t*)malloc(x110 * sizeof(int32_t));
char** x121 = (char**)malloc(x110 * sizeof(char*));
int32_t* x122 = (int32_t*)malloc(x110 * sizeof(int32_t));
double* x123 = (double*)malloc(x110 * sizeof(double));
char** x124 = (char**)malloc(x110 * sizeof(char*));
int32_t* x125 = (int32_t*)malloc(x110 * sizeof(int32_t));
int32_t* x126 = (int32_t*)malloc(x49 * sizeof(int32_t));
for(int x127=0; x127 < x49; x127++) {
x126[x127] = 0;

}
int32_t* x131 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x132 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x133 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x134 = (int32_t*)malloc(16 * sizeof(int32_t));
double* x135 = (double*)malloc(16 * sizeof(double));
double* x136 = (double*)malloc(16 * sizeof(double));
double* x137 = (double*)malloc(16 * sizeof(double));
double* x138 = (double*)malloc(16 * sizeof(double));
char** x139 = (char**)malloc(16 * sizeof(char*));
int32_t* x140 = (int32_t*)malloc(16 * sizeof(int32_t));
char** x141 = (char**)malloc(16 * sizeof(char*));
int32_t* x142 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x143 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x144 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x145 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x146 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x147 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x148 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x149 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x150 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t* x151 = (int32_t*)malloc(16 * sizeof(int32_t));
char** x152 = (char**)malloc(16 * sizeof(char*));
int32_t* x153 = (int32_t*)malloc(16 * sizeof(int32_t));
char** x154 = (char**)malloc(16 * sizeof(char*));
int32_t* x155 = (int32_t*)malloc(16 * sizeof(int32_t));
char** x156 = (char**)malloc(16 * sizeof(char*));
int32_t* x157 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t x158 = 0;
int32_t x159 = 0;
int32_t* x161 = (int32_t*)malloc(16 * sizeof(int32_t));
int32_t x165 = 0;
int32_t x162 = open("/home/jun/tpch-dbgen/sf1/part.tbl",0);
int32_t x163 = fsize(x162);
int32_t x166 = x163;
char* x164 = (char*)mmap(0, x163, PROT_READ, MAP_FILE | MAP_SHARED, x162, 0);
for (;;) {
int32_t x167 = x165;
int32_t x168 = x166;
bool x169 = x167 < x168;
if (!x169) break;
int32_t x171 = x165;
int32_t x172 = 0;
for (;;) {
int32_t x173 = x165;
char x174 = x164[x173];
bool x175 = x174 != '|';
if (!x175) break;
int32_t x177 = x172;
int32_t x179 = x165;
int32_t x178 = x177 * 10;
char x180 = x164[x179];
char x181 = x180 - '0';
int32_t x182 = x178 + x181;
x172 = x182;
x165 += 1;
}
x165 += 1;
int32_t x188 = x172;
int32_t x189 = x165;
for (;;) {
int32_t x190 = x165;
char x191 = x164[x190];
bool x192 = x191 != '|';
if (!x192) break;
x165 += 1;
}
int32_t x197 = x165;
x165 += 1;
int32_t x201 = x165;
for (;;) {
int32_t x202 = x165;
char x203 = x164[x202];
bool x204 = x203 != '|';
if (!x204) break;
x165 += 1;
}
int32_t x209 = x165;
x165 += 1;
int32_t x213 = x165;
for (;;) {
int32_t x214 = x165;
char x215 = x164[x214];
bool x216 = x215 != '|';
if (!x216) break;
x165 += 1;
}
int32_t x221 = x165;
x165 += 1;
int32_t x225 = x165;
for (;;) {
int32_t x226 = x165;
char x227 = x164[x226];
bool x228 = x227 != '|';
if (!x228) break;
x165 += 1;
}
int32_t x233 = x165;
x165 += 1;
int32_t x237 = x165;
int32_t x238 = 0;
for (;;) {
int32_t x239 = x165;
char x240 = x164[x239];
bool x241 = x240 != '|';
if (!x241) break;
int32_t x243 = x238;
int32_t x245 = x165;
int32_t x244 = x243 * 10;
char x246 = x164[x245];
char x247 = x246 - '0';
int32_t x248 = x244 + x247;
x238 = x248;
x165 += 1;
}
x165 += 1;
int32_t x254 = x238;
int32_t x255 = x165;
for (;;) {
int32_t x256 = x165;
char x257 = x164[x256];
bool x258 = x257 != '|';
if (!x258) break;
x165 += 1;
}
int32_t x263 = x165;
x165 += 1;
int32_t x267 = x165;
double x268 = 0.0;
double x269 = 10.0;
for (;;) {
int32_t x270 = x165;
char x271 = x164[x270];
bool x273 = x271 == '.';
bool x275;
if (x273) {
x275 = false;
} else {
bool x274 = x271 != '|';
x275 = x274;
}
if (!x275) break;
double x277 = x268;
int32_t x279 = x165;
double x278 = x277 * 10.0;
char x280 = x164[x279];
char x281 = x280 - '0';
double x283 = (double)x281;
double x284 = x278 + x283;
x268 = x284;
x165 += 1;
}
int32_t x289 = x165;
char x290 = x164[x289];
bool x292 = x290 == '|';
if (x292) {
} else {
x165 += 1;
for (;;) {
int32_t x294 = x165;
char x295 = x164[x294];
bool x296 = x295 != '|';
if (!x296) break;
double x298 = x268;
int32_t x299 = x165;
double x302 = x269;
char x300 = x164[x299];
char x301 = x300 - '0';
double x304 = (double)x301;
double x305 = x304 / x302;
double x306 = x298 + x305;
x268 = x306;
double x308 = x302 * 10.0;
x269 = x308;
x165 += 1;
}
}
x165 += 1;
double x316 = x268;
int32_t x317 = x165;
for (;;) {
int32_t x318 = x165;
char x319 = x164[x318];
bool x320 = x319 != '\n';
if (!x320) break;
x165 += 1;
}
int32_t x325 = x165;
x165 += 1;
int32_t x329 = x18;
x2[x329] = x188;
char* x200 = x164 + x189;
x3[x329] = x200;
int32_t x198 = x197 - x189;
x4[x329] = x198;
char* x212 = x164 + x201;
x5[x329] = x212;
int32_t x210 = x209 - x201;
x6[x329] = x210;
char* x224 = x164 + x213;
x7[x329] = x224;
int32_t x222 = x221 - x213;
x8[x329] = x222;
char* x236 = x164 + x225;
x9[x329] = x236;
int32_t x234 = x233 - x225;
x10[x329] = x234;
x11[x329] = x254;
char* x266 = x164 + x255;
x12[x329] = x266;
int32_t x264 = x263 - x255;
x13[x329] = x264;
x14[x329] = x316;
char* x328 = x164 + x317;
x15[x329] = x328;
int32_t x326 = x325 - x317;
x16[x329] = x326;
x18 += 1;
}
close(x162);
int32_t x352 = 0;
int32_t x349 = open("/home/jun/tpch-dbgen/sf1/lineitem.tbl",0);
int32_t x350 = fsize(x349);
int32_t x353 = x350;
char* x351 = (char*)mmap(0, x350, PROT_READ, MAP_FILE | MAP_SHARED, x349, 0);
for (;;) {
int32_t x354 = x352;
int32_t x355 = x353;
bool x356 = x354 < x355;
if (!x356) break;
int32_t x358 = x352;
int32_t x359 = 0;
for (;;) {
int32_t x360 = x352;
char x361 = x351[x360];
bool x362 = x361 != '|';
if (!x362) break;
int32_t x364 = x359;
int32_t x366 = x352;
int32_t x365 = x364 * 10;
char x367 = x351[x366];
char x368 = x367 - '0';
int32_t x369 = x365 + x368;
x359 = x369;
x352 += 1;
}
x352 += 1;
int32_t x375 = x359;
int32_t x376 = x352;
int32_t x377 = 0;
for (;;) {
int32_t x378 = x352;
char x379 = x351[x378];
bool x380 = x379 != '|';
if (!x380) break;
int32_t x382 = x377;
int32_t x384 = x352;
int32_t x383 = x382 * 10;
char x385 = x351[x384];
char x386 = x385 - '0';
int32_t x387 = x383 + x386;
x377 = x387;
x352 += 1;
}
x352 += 1;
int32_t x393 = x377;
int32_t x394 = x352;
int32_t x395 = 0;
for (;;) {
int32_t x396 = x352;
char x397 = x351[x396];
bool x398 = x397 != '|';
if (!x398) break;
int32_t x400 = x395;
int32_t x402 = x352;
int32_t x401 = x400 * 10;
char x403 = x351[x402];
char x404 = x403 - '0';
int32_t x405 = x401 + x404;
x395 = x405;
x352 += 1;
}
x352 += 1;
int32_t x411 = x395;
int32_t x412 = x352;
int32_t x413 = 0;
for (;;) {
int32_t x414 = x352;
char x415 = x351[x414];
bool x416 = x415 != '|';
if (!x416) break;
int32_t x418 = x413;
int32_t x420 = x352;
int32_t x419 = x418 * 10;
char x421 = x351[x420];
char x422 = x421 - '0';
int32_t x423 = x419 + x422;
x413 = x423;
x352 += 1;
}
x352 += 1;
int32_t x429 = x413;
int32_t x430 = x352;
double x431 = 0.0;
double x432 = 10.0;
for (;;) {
int32_t x433 = x352;
char x434 = x351[x433];
bool x436 = x434 == '.';
bool x438;
if (x436) {
x438 = false;
} else {
bool x437 = x434 != '|';
x438 = x437;
}
if (!x438) break;
double x440 = x431;
int32_t x442 = x352;
double x441 = x440 * 10.0;
char x443 = x351[x442];
char x444 = x443 - '0';
double x446 = (double)x444;
double x447 = x441 + x446;
x431 = x447;
x352 += 1;
}
int32_t x452 = x352;
char x453 = x351[x452];
bool x455 = x453 == '|';
if (x455) {
} else {
x352 += 1;
for (;;) {
int32_t x457 = x352;
char x458 = x351[x457];
bool x459 = x458 != '|';
if (!x459) break;
double x461 = x431;
int32_t x462 = x352;
double x465 = x432;
char x463 = x351[x462];
char x464 = x463 - '0';
double x467 = (double)x464;
double x468 = x467 / x465;
double x469 = x461 + x468;
x431 = x469;
double x471 = x465 * 10.0;
x432 = x471;
x352 += 1;
}
}
x352 += 1;
double x479 = x431;
int32_t x480 = x352;
double x481 = 0.0;
double x482 = 10.0;
for (;;) {
int32_t x483 = x352;
char x484 = x351[x483];
bool x486 = x484 == '.';
bool x488;
if (x486) {
x488 = false;
} else {
bool x487 = x484 != '|';
x488 = x487;
}
if (!x488) break;
double x490 = x481;
int32_t x492 = x352;
double x491 = x490 * 10.0;
char x493 = x351[x492];
char x494 = x493 - '0';
double x496 = (double)x494;
double x497 = x491 + x496;
x481 = x497;
x352 += 1;
}
int32_t x502 = x352;
char x503 = x351[x502];
bool x505 = x503 == '|';
if (x505) {
} else {
x352 += 1;
for (;;) {
int32_t x507 = x352;
char x508 = x351[x507];
bool x509 = x508 != '|';
if (!x509) break;
double x511 = x481;
int32_t x512 = x352;
double x515 = x482;
char x513 = x351[x512];
char x514 = x513 - '0';
double x517 = (double)x514;
double x518 = x517 / x515;
double x519 = x511 + x518;
x481 = x519;
double x521 = x515 * 10.0;
x482 = x521;
x352 += 1;
}
}
x352 += 1;
double x529 = x481;
int32_t x530 = x352;
double x531 = 0.0;
double x532 = 10.0;
for (;;) {
int32_t x533 = x352;
char x534 = x351[x533];
bool x536 = x534 == '.';
bool x538;
if (x536) {
x538 = false;
} else {
bool x537 = x534 != '|';
x538 = x537;
}
if (!x538) break;
double x540 = x531;
int32_t x542 = x352;
double x541 = x540 * 10.0;
char x543 = x351[x542];
char x544 = x543 - '0';
double x546 = (double)x544;
double x547 = x541 + x546;
x531 = x547;
x352 += 1;
}
int32_t x552 = x352;
char x553 = x351[x552];
bool x555 = x553 == '|';
if (x555) {
} else {
x352 += 1;
for (;;) {
int32_t x557 = x352;
char x558 = x351[x557];
bool x559 = x558 != '|';
if (!x559) break;
double x561 = x531;
int32_t x562 = x352;
double x565 = x532;
char x563 = x351[x562];
char x564 = x563 - '0';
double x567 = (double)x564;
double x568 = x567 / x565;
double x569 = x561 + x568;
x531 = x569;
double x571 = x565 * 10.0;
x532 = x571;
x352 += 1;
}
}
x352 += 1;
double x579 = x531;
int32_t x580 = x352;
double x581 = 0.0;
double x582 = 10.0;
for (;;) {
int32_t x583 = x352;
char x584 = x351[x583];
bool x586 = x584 == '.';
bool x588;
if (x586) {
x588 = false;
} else {
bool x587 = x584 != '|';
x588 = x587;
}
if (!x588) break;
double x590 = x581;
int32_t x592 = x352;
double x591 = x590 * 10.0;
char x593 = x351[x592];
char x594 = x593 - '0';
double x596 = (double)x594;
double x597 = x591 + x596;
x581 = x597;
x352 += 1;
}
int32_t x602 = x352;
char x603 = x351[x602];
bool x605 = x603 == '|';
if (x605) {
} else {
x352 += 1;
for (;;) {
int32_t x607 = x352;
char x608 = x351[x607];
bool x609 = x608 != '|';
if (!x609) break;
double x611 = x581;
int32_t x612 = x352;
double x615 = x582;
char x613 = x351[x612];
char x614 = x613 - '0';
double x617 = (double)x614;
double x618 = x617 / x615;
double x619 = x611 + x618;
x581 = x619;
double x621 = x615 * 10.0;
x582 = x621;
x352 += 1;
}
}
x352 += 1;
double x629 = x581;
int32_t x630 = x352;
for (;;) {
int32_t x631 = x352;
char x632 = x351[x631];
bool x633 = x632 != '|';
if (!x633) break;
x352 += 1;
}
int32_t x638 = x352;
x352 += 1;
int32_t x642 = x352;
for (;;) {
int32_t x643 = x352;
char x644 = x351[x643];
bool x645 = x644 != '|';
if (!x645) break;
x352 += 1;
}
int32_t x650 = x352;
x352 += 1;
int32_t x654 = x352;
int32_t x655 = 0;
int32_t x656 = 0;
int32_t x657 = 0;
for (;;) {
int32_t x658 = x352;
char x659 = x351[x658];
bool x660 = x659 != '-';
if (!x660) break;
int32_t x662 = x655;
int32_t x664 = x352;
int32_t x663 = x662 * 10;
char x665 = x351[x664];
char x666 = x665 - '0';
int32_t x667 = x663 + x666;
x655 = x667;
x352 += 1;
}
x352 += 1;
for (;;) {
int32_t x673 = x352;
char x674 = x351[x673];
bool x675 = x674 != '-';
if (!x675) break;
int32_t x677 = x656;
int32_t x679 = x352;
int32_t x678 = x677 * 10;
char x680 = x351[x679];
char x681 = x680 - '0';
int32_t x682 = x678 + x681;
x656 = x682;
x352 += 1;
}
x352 += 1;
for (;;) {
int32_t x688 = x352;
char x689 = x351[x688];
bool x690 = x689 != '|';
if (!x690) break;
int32_t x692 = x657;
int32_t x694 = x352;
int32_t x693 = x692 * 10;
char x695 = x351[x694];
char x696 = x695 - '0';
int32_t x697 = x693 + x696;
x657 = x697;
x352 += 1;
}
x352 += 1;
int32_t x703 = x655;
int32_t x704 = x656;
int32_t x705 = x657;
int32_t x706 = x352;
int32_t x707 = 0;
int32_t x708 = 0;
int32_t x709 = 0;
for (;;) {
int32_t x710 = x352;
char x711 = x351[x710];
bool x712 = x711 != '-';
if (!x712) break;
int32_t x714 = x707;
int32_t x716 = x352;
int32_t x715 = x714 * 10;
char x717 = x351[x716];
char x718 = x717 - '0';
int32_t x719 = x715 + x718;
x707 = x719;
x352 += 1;
}
x352 += 1;
for (;;) {
int32_t x725 = x352;
char x726 = x351[x725];
bool x727 = x726 != '-';
if (!x727) break;
int32_t x729 = x708;
int32_t x731 = x352;
int32_t x730 = x729 * 10;
char x732 = x351[x731];
char x733 = x732 - '0';
int32_t x734 = x730 + x733;
x708 = x734;
x352 += 1;
}
x352 += 1;
for (;;) {
int32_t x740 = x352;
char x741 = x351[x740];
bool x742 = x741 != '|';
if (!x742) break;
int32_t x744 = x709;
int32_t x746 = x352;
int32_t x745 = x744 * 10;
char x747 = x351[x746];
char x748 = x747 - '0';
int32_t x749 = x745 + x748;
x709 = x749;
x352 += 1;
}
x352 += 1;
int32_t x755 = x707;
int32_t x756 = x708;
int32_t x757 = x709;
int32_t x758 = x352;
int32_t x759 = 0;
int32_t x760 = 0;
int32_t x761 = 0;
for (;;) {
int32_t x762 = x352;
char x763 = x351[x762];
bool x764 = x763 != '-';
if (!x764) break;
int32_t x766 = x759;
int32_t x768 = x352;
int32_t x767 = x766 * 10;
char x769 = x351[x768];
char x770 = x769 - '0';
int32_t x771 = x767 + x770;
x759 = x771;
x352 += 1;
}
x352 += 1;
for (;;) {
int32_t x777 = x352;
char x778 = x351[x777];
bool x779 = x778 != '-';
if (!x779) break;
int32_t x781 = x760;
int32_t x783 = x352;
int32_t x782 = x781 * 10;
char x784 = x351[x783];
char x785 = x784 - '0';
int32_t x786 = x782 + x785;
x760 = x786;
x352 += 1;
}
x352 += 1;
for (;;) {
int32_t x792 = x352;
char x793 = x351[x792];
bool x794 = x793 != '|';
if (!x794) break;
int32_t x796 = x761;
int32_t x798 = x352;
int32_t x797 = x796 * 10;
char x799 = x351[x798];
char x800 = x799 - '0';
int32_t x801 = x797 + x800;
x761 = x801;
x352 += 1;
}
x352 += 1;
int32_t x807 = x759;
int32_t x808 = x760;
int32_t x809 = x761;
int32_t x810 = x352;
for (;;) {
int32_t x811 = x352;
char x812 = x351[x811];
bool x813 = x812 != '|';
if (!x813) break;
x352 += 1;
}
int32_t x818 = x352;
x352 += 1;
int32_t x822 = x352;
for (;;) {
int32_t x823 = x352;
char x824 = x351[x823];
bool x825 = x824 != '|';
if (!x825) break;
x352 += 1;
}
int32_t x830 = x352;
x352 += 1;
int32_t x834 = x352;
for (;;) {
int32_t x835 = x352;
char x836 = x351[x835];
bool x837 = x836 != '\n';
if (!x837) break;
x352 += 1;
}
int32_t x842 = x352;
x352 += 1;
int32_t x846 = x47;
x19[x846] = x375;
x20[x846] = x393;
x21[x846] = x411;
x22[x846] = x429;
x23[x846] = x479;
x24[x846] = x529;
x25[x846] = x579;
x26[x846] = x629;
char* x641 = x351 + x630;
x27[x846] = x641;
int32_t x639 = x638 - x630;
x28[x846] = x639;
char* x653 = x351 + x642;
x29[x846] = x653;
int32_t x651 = x650 - x642;
x30[x846] = x651;
x31[x846] = x703;
x32[x846] = x704;
x33[x846] = x705;
x34[x846] = x755;
x35[x846] = x756;
x36[x846] = x757;
x37[x846] = x807;
x38[x846] = x808;
x39[x846] = x809;
char* x821 = x351 + x810;
x40[x846] = x821;
int32_t x819 = x818 - x810;
x41[x846] = x819;
char* x833 = x351 + x822;
x42[x846] = x833;
int32_t x831 = x830 - x822;
x43[x846] = x831;
char* x845 = x351 + x834;
x44[x846] = x845;
int32_t x843 = x842 - x834;
x45[x846] = x843;
x47 += 1;
}
close(x349);
int32_t x917 = x49 - 1;
int32_t x924 = x108 - 1;
__m512i x1015 = _mm512_set1_epi32(10000);
__m512i x1018 = _mm512_set1_epi32(100);
__m512i x1023 = _mm512_set1_epi32(1995);
__m512i x1024 = _mm512_mullo_epi32(x1023,x1015);
__m512i x1025 = _mm512_set1_epi32(9);
__m512i x1026 = _mm512_mullo_epi32(x1025,x1018);
__m512i x1027 = _mm512_add_epi32(x1024,x1026);
__m512i x1028 = _mm512_set1_epi32(1);
__m512i x1029 = _mm512_add_epi32(x1027,x1028);
__mmask16 x1013 = 65535;
__m512i x1032 = _mm512_set1_epi32(10);
__m512i x1033 = _mm512_mullo_epi32(x1032,x1018);
__m512i x1034 = _mm512_add_epi32(x1024,x1033);
__m512i x1035 = _mm512_add_epi32(x1034,x1028);
__m512i x160 = _mm512_set_epi32(15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0);
__m256i x1161 = _mm512_extracti32x8_epi32(x1028,0);
__m512d x1162 = _mm512_cvtepi32_pd(x1161);
__m256i x1163 = _mm512_extracti32x8_epi32(x1028,1);
__m512d x1164 = _mm512_cvtepi32_pd(x1163);
__mmask8 x1169 = _mm512_kand(x1013, 0x00ff);
__mmask8 x1171 = _mm512_kand(x1013>>8, 0x00ff);
int32_t x1219 = (int32_t)0L;
bool x1220 = x1219 >= 0;
int32_t x1222;
if (x1220) {
x1222 = x1219;
} else {
int32_t x1221 = 0 - x1219;
x1222 = x1221;
}
int32_t x1223 = x1222 % x49;
bool x1227 = !true;
struct timeval begin, end;
begin = cur_time();
int32_t x878 = x18;
for(int x880=0; x880 < x878; x880++) {
int32_t x881 = x2[x880];
char* x882 = x3[x880];
int32_t x883 = x4[x880];
char* x884 = x5[x880];
int32_t x885 = x6[x880];
char* x886 = x7[x880];
int32_t x887 = x8[x880];
char* x888 = x9[x880];
int32_t x889 = x10[x880];
int32_t x890 = x11[x880];
char* x891 = x12[x880];
int32_t x892 = x13[x880];
double x893 = x14[x880];
char* x894 = x15[x880];
int32_t x895 = x16[x880];
int32_t x896 = (int32_t)x881;
bool x897 = x896 >= 0;
int32_t x899;
if (x897) {
x899 = x896;
} else {
int32_t x898 = 0 - x896;
x899 = x898;
}
int32_t x900 = x899 % x49;
int32_t x901 = x900;
for (;;) {
int32_t x902 = x901;
int32_t x903 = x126[x902];
bool x904 = x903 > 0;
bool x909;
if (x904) {
int32_t x905 = x109[x902];
bool x906 = x905 == x881;
bool x907 = !x906;
x909 = x907;
} else {
x909 = false;
}
if (!x909) break;
int32_t x911 = x901;
int32_t x912 = x911 + 1;
x901 = x912;
}
int32_t x916 = x901;
bool x918 = x916 == x917;
if (x918) {
printf("%s\n","LB2HashMultiMap table is full.");
exit(1);
} else {
}
int32_t x923 = x126[x916];
bool x925 = x923 == x924;
if (x925) {
printf("%s\n","Bucket is full.");
exit(1);
} else {
}
x109[x916] = x881;
int32_t x930 = x916 * x108;
int32_t x931 = x930 + x923;
x111[x931] = x881;
x112[x931] = x882;
x113[x931] = x883;
x114[x931] = x884;
x115[x931] = x885;
x116[x931] = x886;
x117[x931] = x887;
x118[x931] = x888;
x119[x931] = x889;
x120[x931] = x890;
x121[x931] = x891;
x122[x931] = x892;
x123[x931] = x893;
x124[x931] = x894;
x125[x931] = x895;
int32_t x948 = x923 + 1;
x126[x916] = x948;

}
int32_t x952 = x47;
for(int x954=0; x954 < x952; x954++) {
int32_t x955 = x19[x954];
int32_t x956 = x20[x954];
int32_t x957 = x21[x954];
int32_t x958 = x22[x954];
double x959 = x23[x954];
double x960 = x24[x954];
double x961 = x25[x954];
double x962 = x26[x954];
char* x963 = x27[x954];
int32_t x964 = x28[x954];
char* x965 = x29[x954];
int32_t x966 = x30[x954];
int32_t x967 = x31[x954];
int32_t x968 = x32[x954];
int32_t x969 = x33[x954];
int32_t x970 = x34[x954];
int32_t x971 = x35[x954];
int32_t x972 = x36[x954];
int32_t x973 = x37[x954];
int32_t x974 = x38[x954];
int32_t x975 = x39[x954];
char* x976 = x40[x954];
int32_t x977 = x41[x954];
char* x978 = x42[x954];
int32_t x979 = x43[x954];
char* x980 = x44[x954];
int32_t x981 = x45[x954];
int32_t x982 = x159;
x131[x982] = x955;
x132[x982] = x956;
x133[x982] = x957;
x134[x982] = x958;
x135[x982] = x959;
x136[x982] = x960;
x137[x982] = x961;
x138[x982] = x962;
x139[x982] = x963;
x140[x982] = x964;
x141[x982] = x965;
x142[x982] = x966;
x143[x982] = x967;
x144[x982] = x968;
x145[x982] = x969;
x146[x982] = x970;
x147[x982] = x971;
x148[x982] = x972;
x149[x982] = x973;
x150[x982] = x974;
x151[x982] = x975;
x152[x982] = x976;
x153[x982] = x977;
x154[x982] = x978;
x155[x982] = x979;
x156[x982] = x980;
x157[x982] = x981;
x159 += 1;
int32_t x1011 = x159;
bool x1012 = x1011 == 16;
if (x1012) {
__m512i x1014 = _mm512_loadu_si512(x143);
__m512i x1016 = _mm512_mullo_epi32(x1014,x1015);
__m512i x1017 = _mm512_loadu_si512(x144);
__m512i x1019 = _mm512_mullo_epi32(x1017,x1018);
__m512i x1020 = _mm512_add_epi32(x1016,x1019);
__m512i x1021 = _mm512_loadu_si512(x145);
__m512i x1022 = _mm512_add_epi32(x1020,x1021);
__mmask16 x1030 = _mm512_cmpge_epi32_mask(x1022,x1029);
__mmask16 x1031 = _mm512_kand(x1013,x1030);
__mmask16 x1036 = _mm512_cmplt_epi32_mask(x1022,x1035);
__mmask16 x1037 = _mm512_kand(x1031,x1036);
_mm512_mask_compressstoreu_epi32(x161,x1037,x160);
int32_t x1039 = _mm_popcnt_u32(x1037);
for(int x1041=0; x1041 < x1039; x1041++) {
int32_t x1042 = x161[x1041];
int32_t x1043 = x131[x1042];
int32_t x1044 = x132[x1042];
int32_t x1045 = x133[x1042];
int32_t x1046 = x134[x1042];
double x1047 = x135[x1042];
double x1048 = x136[x1042];
double x1049 = x137[x1042];
double x1050 = x138[x1042];
char* x1051 = x139[x1042];
int32_t x1052 = x140[x1042];
char* x1053 = x141[x1042];
int32_t x1054 = x142[x1042];
int32_t x1055 = x143[x1042];
int32_t x1056 = x144[x1042];
int32_t x1057 = x145[x1042];
int32_t x1058 = x146[x1042];
int32_t x1059 = x147[x1042];
int32_t x1060 = x148[x1042];
int32_t x1061 = x149[x1042];
int32_t x1062 = x150[x1042];
int32_t x1063 = x151[x1042];
char* x1064 = x152[x1042];
int32_t x1065 = x153[x1042];
char* x1066 = x154[x1042];
int32_t x1067 = x155[x1042];
char* x1068 = x156[x1042];
int32_t x1069 = x157[x1042];
int32_t x1070 = (int32_t)x1044;
bool x1071 = x1070 >= 0;
int32_t x1073;
if (x1071) {
x1073 = x1070;
} else {
int32_t x1072 = 0 - x1070;
x1073 = x1072;
}
int32_t x1074 = x1073 % x49;
int32_t x1075 = x1074;
for (;;) {
int32_t x1076 = x1075;
int32_t x1077 = x126[x1076];
bool x1078 = x1077 > 0;
bool x1083;
if (x1078) {
int32_t x1079 = x109[x1076];
bool x1080 = x1079 == x1044;
bool x1081 = !x1080;
x1083 = x1081;
} else {
x1083 = false;
}
if (!x1083) break;
int32_t x1085 = x1075;
int32_t x1086 = x1085 + 1;
x1075 = x1086;
}
int32_t x1090 = x1075;
int32_t x1091 = x126[x1090];
int32_t x1092 = x1090 * x108;
int32_t x1093 = x1092 + x1091;
for(int x1095=x1092; x1095 < x1093; x1095++) {
int32_t x1096 = x111[x1095];
char* x1097 = x112[x1095];
int32_t x1098 = x113[x1095];
char* x1099 = x114[x1095];
int32_t x1100 = x115[x1095];
char* x1101 = x116[x1095];
int32_t x1102 = x117[x1095];
char* x1103 = x118[x1095];
int32_t x1104 = x119[x1095];
int32_t x1105 = x120[x1095];
char* x1106 = x121[x1095];
int32_t x1107 = x122[x1095];
double x1108 = x123[x1095];
char* x1109 = x124[x1095];
int32_t x1110 = x125[x1095];
int32_t x1111 = x104;
x61[x1111] = x1096;
x62[x1111] = x1097;
x63[x1111] = x1098;
x64[x1111] = x1099;
x65[x1111] = x1100;
x66[x1111] = x1101;
x67[x1111] = x1102;
x68[x1111] = x1103;
x69[x1111] = x1104;
x70[x1111] = x1105;
x71[x1111] = x1106;
x72[x1111] = x1107;
x73[x1111] = x1108;
x74[x1111] = x1109;
x75[x1111] = x1110;
x76[x1111] = x1043;
x77[x1111] = x1044;
x78[x1111] = x1045;
x79[x1111] = x1046;
x80[x1111] = x1047;
x81[x1111] = x1048;
x82[x1111] = x1049;
x83[x1111] = x1050;
x84[x1111] = x1051;
x85[x1111] = x1052;
x86[x1111] = x1053;
x87[x1111] = x1054;
x88[x1111] = x1055;
x89[x1111] = x1056;
x90[x1111] = x1057;
x91[x1111] = x1058;
x92[x1111] = x1059;
x93[x1111] = x1060;
x94[x1111] = x1061;
x95[x1111] = x1062;
x96[x1111] = x1063;
x97[x1111] = x1064;
x98[x1111] = x1065;
x99[x1111] = x1066;
x100[x1111] = x1067;
x101[x1111] = x1068;
x102[x1111] = x1069;
x104 += 1;
int32_t x1155 = x104;
bool x1156 = x1155 == 16;
if (x1156) {
__m512d x1157 = _mm512_loadu_pd(x81);
__m512d x1158 = _mm512_loadu_pd(x81+8);
__m512d x1159 = _mm512_loadu_pd(x82);
__m512d x1160 = _mm512_loadu_pd(x82+8);
__m512d x1165 = _mm512_sub_pd(x1162,x1159);
__m512d x1166 = _mm512_sub_pd(x1164,x1160);
__m512d x1167 = _mm512_mul_pd(x1157,x1165);
__m512d x1168 = _mm512_mul_pd(x1158,x1166);
_mm512_mask_storeu_pd(x105,x1169,x1167);
_mm512_mask_storeu_pd(x105+8,x1171,x1168);
for(int x1174=0; x1174 < 16; x1174++) {
int32_t x1175 = x61[x1174];
char* x1176 = x62[x1174];
int32_t x1177 = x63[x1174];
char* x1178 = x64[x1174];
int32_t x1179 = x65[x1174];
char* x1180 = x66[x1174];
int32_t x1181 = x67[x1174];
char* x1182 = x68[x1174];
int32_t x1183 = x69[x1174];
int32_t x1184 = x70[x1174];
char* x1185 = x71[x1174];
int32_t x1186 = x72[x1174];
double x1187 = x73[x1174];
char* x1188 = x74[x1174];
int32_t x1189 = x75[x1174];
int32_t x1190 = x76[x1174];
int32_t x1191 = x77[x1174];
int32_t x1192 = x78[x1174];
int32_t x1193 = x79[x1174];
double x1194 = x80[x1174];
double x1195 = x81[x1174];
double x1196 = x82[x1174];
double x1197 = x83[x1174];
char* x1198 = x84[x1174];
int32_t x1199 = x85[x1174];
char* x1200 = x86[x1174];
int32_t x1201 = x87[x1174];
int32_t x1202 = x88[x1174];
int32_t x1203 = x89[x1174];
int32_t x1204 = x90[x1174];
int32_t x1205 = x91[x1174];
int32_t x1206 = x92[x1174];
int32_t x1207 = x93[x1174];
int32_t x1208 = x94[x1174];
int32_t x1209 = x95[x1174];
int32_t x1210 = x96[x1174];
char* x1211 = x97[x1174];
int32_t x1212 = x98[x1174];
char* x1213 = x99[x1174];
int32_t x1214 = x100[x1174];
char* x1215 = x101[x1174];
int32_t x1216 = x102[x1174];
double x1217 = x105[x1174];
bool x1218 = pattern_compare(x1182,"PROMO%");
if (x1218) {
int32_t x1224 = x1223;
for (;;) {
int32_t x1225 = x1224;
bool x1226 = x52[x1225];
bool x1228;
if (x1226) {
x1228 = x1227;
} else {
x1228 = false;
}
if (!x1228) break;
x1224 += 1;
}
int32_t x1233 = x1224;
bool x1234 = x1233 == x917;
if (x1234) {
printf("%s\n","LB2HashMap table is full.");
exit(1);
} else {
}
bool x1239 = x52[x1233];
if (x1239) {
double x1240 = x50[x1233];
double x1241 = x51[x1233];
double x1242 = x1240 + x1217;
x50[x1233] = x1242;
double x1243 = x1241 + x1217;
x51[x1233] = x1243;
} else {
int32_t x1247 = x60;
x58[x1247] = x1233;
x60 += 1;
x50[x1233] = x1217;
x51[x1233] = x1217;
x52[x1233] = true;
}
} else {
int32_t x1256 = x1223;
for (;;) {
int32_t x1257 = x1256;
bool x1258 = x52[x1257];
bool x1259;
if (x1258) {
x1259 = x1227;
} else {
x1259 = false;
}
if (!x1259) break;
x1256 += 1;
}
int32_t x1264 = x1256;
bool x1265 = x1264 == x917;
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
double x1273 = x1272 + x1217;
x51[x1264] = x1273;
} else {
int32_t x1277 = x60;
x58[x1277] = x1264;
x60 += 1;
x50[x1264] = 0.0;
x51[x1264] = x1217;
x52[x1264] = true;
}
}

}
x104 = 0;
} else {
}

}

}
x159 = 0;
} else {
}

}
int32_t x1301 = x159;
for(int x1303=0; x1303 < x1301; x1303++) {
int32_t x1304 = x131[x1303];
int32_t x1305 = x132[x1303];
int32_t x1306 = x133[x1303];
int32_t x1307 = x134[x1303];
double x1308 = x135[x1303];
double x1309 = x136[x1303];
double x1310 = x137[x1303];
double x1311 = x138[x1303];
char* x1312 = x139[x1303];
int32_t x1313 = x140[x1303];
char* x1314 = x141[x1303];
int32_t x1315 = x142[x1303];
int32_t x1316 = x143[x1303];
int32_t x1317 = x144[x1303];
int32_t x1318 = x145[x1303];
int32_t x1319 = x146[x1303];
int32_t x1320 = x147[x1303];
int32_t x1321 = x148[x1303];
int32_t x1322 = x149[x1303];
int32_t x1323 = x150[x1303];
int32_t x1324 = x151[x1303];
char* x1325 = x152[x1303];
int32_t x1326 = x153[x1303];
char* x1327 = x154[x1303];
int32_t x1328 = x155[x1303];
char* x1329 = x156[x1303];
int32_t x1330 = x157[x1303];
int32_t x1331 = x1316 * 10000;
int32_t x1332 = x1317 * 100;
int32_t x1333 = x1331 + x1332;
int32_t x1334 = x1333 + x1318;
bool x1335 = x1334 >= 19950901;
bool x1337;
if (x1335) {
bool x1336 = x1334 < 19951001;
x1337 = x1336;
} else {
x1337 = false;
}
if (x1337) {
int32_t x1338 = (int32_t)x1305;
bool x1339 = x1338 >= 0;
int32_t x1341;
if (x1339) {
x1341 = x1338;
} else {
int32_t x1340 = 0 - x1338;
x1341 = x1340;
}
int32_t x1342 = x1341 % x49;
int32_t x1343 = x1342;
for (;;) {
int32_t x1344 = x1343;
int32_t x1345 = x126[x1344];
bool x1346 = x1345 > 0;
bool x1351;
if (x1346) {
int32_t x1347 = x109[x1344];
bool x1348 = x1347 == x1305;
bool x1349 = !x1348;
x1351 = x1349;
} else {
x1351 = false;
}
if (!x1351) break;
int32_t x1353 = x1343;
int32_t x1354 = x1353 + 1;
x1343 = x1354;
}
int32_t x1358 = x1343;
int32_t x1359 = x126[x1358];
int32_t x1360 = x1358 * x108;
int32_t x1361 = x1360 + x1359;
for(int x1363=x1360; x1363 < x1361; x1363++) {
int32_t x1364 = x111[x1363];
char* x1365 = x112[x1363];
int32_t x1366 = x113[x1363];
char* x1367 = x114[x1363];
int32_t x1368 = x115[x1363];
char* x1369 = x116[x1363];
int32_t x1370 = x117[x1363];
char* x1371 = x118[x1363];
int32_t x1372 = x119[x1363];
int32_t x1373 = x120[x1363];
char* x1374 = x121[x1363];
int32_t x1375 = x122[x1363];
double x1376 = x123[x1363];
char* x1377 = x124[x1363];
int32_t x1378 = x125[x1363];
int32_t x1379 = x104;
x61[x1379] = x1364;
x62[x1379] = x1365;
x63[x1379] = x1366;
x64[x1379] = x1367;
x65[x1379] = x1368;
x66[x1379] = x1369;
x67[x1379] = x1370;
x68[x1379] = x1371;
x69[x1379] = x1372;
x70[x1379] = x1373;
x71[x1379] = x1374;
x72[x1379] = x1375;
x73[x1379] = x1376;
x74[x1379] = x1377;
x75[x1379] = x1378;
x76[x1379] = x1304;
x77[x1379] = x1305;
x78[x1379] = x1306;
x79[x1379] = x1307;
x80[x1379] = x1308;
x81[x1379] = x1309;
x82[x1379] = x1310;
x83[x1379] = x1311;
x84[x1379] = x1312;
x85[x1379] = x1313;
x86[x1379] = x1314;
x87[x1379] = x1315;
x88[x1379] = x1316;
x89[x1379] = x1317;
x90[x1379] = x1318;
x91[x1379] = x1319;
x92[x1379] = x1320;
x93[x1379] = x1321;
x94[x1379] = x1322;
x95[x1379] = x1323;
x96[x1379] = x1324;
x97[x1379] = x1325;
x98[x1379] = x1326;
x99[x1379] = x1327;
x100[x1379] = x1328;
x101[x1379] = x1329;
x102[x1379] = x1330;
x104 += 1;
int32_t x1423 = x104;
bool x1424 = x1423 == 16;
if (x1424) {
__m512d x1425 = _mm512_loadu_pd(x81);
__m512d x1426 = _mm512_loadu_pd(x81+8);
__m512d x1427 = _mm512_loadu_pd(x82);
__m512d x1428 = _mm512_loadu_pd(x82+8);
__m512d x1429 = _mm512_sub_pd(x1162,x1427);
__m512d x1430 = _mm512_sub_pd(x1164,x1428);
__m512d x1431 = _mm512_mul_pd(x1425,x1429);
__m512d x1432 = _mm512_mul_pd(x1426,x1430);
_mm512_mask_storeu_pd(x105,x1169,x1431);
_mm512_mask_storeu_pd(x105+8,x1171,x1432);
for(int x1435=0; x1435 < 16; x1435++) {
int32_t x1436 = x61[x1435];
char* x1437 = x62[x1435];
int32_t x1438 = x63[x1435];
char* x1439 = x64[x1435];
int32_t x1440 = x65[x1435];
char* x1441 = x66[x1435];
int32_t x1442 = x67[x1435];
char* x1443 = x68[x1435];
int32_t x1444 = x69[x1435];
int32_t x1445 = x70[x1435];
char* x1446 = x71[x1435];
int32_t x1447 = x72[x1435];
double x1448 = x73[x1435];
char* x1449 = x74[x1435];
int32_t x1450 = x75[x1435];
int32_t x1451 = x76[x1435];
int32_t x1452 = x77[x1435];
int32_t x1453 = x78[x1435];
int32_t x1454 = x79[x1435];
double x1455 = x80[x1435];
double x1456 = x81[x1435];
double x1457 = x82[x1435];
double x1458 = x83[x1435];
char* x1459 = x84[x1435];
int32_t x1460 = x85[x1435];
char* x1461 = x86[x1435];
int32_t x1462 = x87[x1435];
int32_t x1463 = x88[x1435];
int32_t x1464 = x89[x1435];
int32_t x1465 = x90[x1435];
int32_t x1466 = x91[x1435];
int32_t x1467 = x92[x1435];
int32_t x1468 = x93[x1435];
int32_t x1469 = x94[x1435];
int32_t x1470 = x95[x1435];
int32_t x1471 = x96[x1435];
char* x1472 = x97[x1435];
int32_t x1473 = x98[x1435];
char* x1474 = x99[x1435];
int32_t x1475 = x100[x1435];
char* x1476 = x101[x1435];
int32_t x1477 = x102[x1435];
double x1478 = x105[x1435];
bool x1479 = pattern_compare(x1443,"PROMO%");
if (x1479) {
int32_t x1480 = x1223;
for (;;) {
int32_t x1481 = x1480;
bool x1482 = x52[x1481];
bool x1483;
if (x1482) {
x1483 = x1227;
} else {
x1483 = false;
}
if (!x1483) break;
x1480 += 1;
}
int32_t x1488 = x1480;
bool x1489 = x1488 == x917;
if (x1489) {
printf("%s\n","LB2HashMap table is full.");
exit(1);
} else {
}
bool x1494 = x52[x1488];
if (x1494) {
double x1495 = x50[x1488];
double x1496 = x51[x1488];
double x1497 = x1495 + x1478;
x50[x1488] = x1497;
double x1498 = x1496 + x1478;
x51[x1488] = x1498;
} else {
int32_t x1502 = x60;
x58[x1502] = x1488;
x60 += 1;
x50[x1488] = x1478;
x51[x1488] = x1478;
x52[x1488] = true;
}
} else {
int32_t x1511 = x1223;
for (;;) {
int32_t x1512 = x1511;
bool x1513 = x52[x1512];
bool x1514;
if (x1513) {
x1514 = x1227;
} else {
x1514 = false;
}
if (!x1514) break;
x1511 += 1;
}
int32_t x1519 = x1511;
bool x1520 = x1519 == x917;
if (x1520) {
printf("%s\n","LB2HashMap table is full.");
exit(1);
} else {
}
bool x1525 = x52[x1519];
if (x1525) {
double x1526 = x50[x1519];
double x1527 = x51[x1519];
x50[x1519] = x1526;
double x1528 = x1527 + x1478;
x51[x1519] = x1528;
} else {
int32_t x1532 = x60;
x58[x1532] = x1519;
x60 += 1;
x50[x1519] = 0.0;
x51[x1519] = x1478;
x52[x1519] = true;
}
}

}
x104 = 0;
} else {
}

}
} else {
}

}
int32_t x1553 = x104;
for(int x1555=0; x1555 < x1553; x1555++) {
int32_t x1556 = x61[x1555];
char* x1557 = x62[x1555];
int32_t x1558 = x63[x1555];
char* x1559 = x64[x1555];
int32_t x1560 = x65[x1555];
char* x1561 = x66[x1555];
int32_t x1562 = x67[x1555];
char* x1563 = x68[x1555];
int32_t x1564 = x69[x1555];
int32_t x1565 = x70[x1555];
char* x1566 = x71[x1555];
int32_t x1567 = x72[x1555];
double x1568 = x73[x1555];
char* x1569 = x74[x1555];
int32_t x1570 = x75[x1555];
int32_t x1571 = x76[x1555];
int32_t x1572 = x77[x1555];
int32_t x1573 = x78[x1555];
int32_t x1574 = x79[x1555];
double x1575 = x80[x1555];
double x1576 = x81[x1555];
double x1577 = x82[x1555];
double x1578 = x83[x1555];
char* x1579 = x84[x1555];
int32_t x1580 = x85[x1555];
char* x1581 = x86[x1555];
int32_t x1582 = x87[x1555];
int32_t x1583 = x88[x1555];
int32_t x1584 = x89[x1555];
int32_t x1585 = x90[x1555];
int32_t x1586 = x91[x1555];
int32_t x1587 = x92[x1555];
int32_t x1588 = x93[x1555];
int32_t x1589 = x94[x1555];
int32_t x1590 = x95[x1555];
int32_t x1591 = x96[x1555];
char* x1592 = x97[x1555];
int32_t x1593 = x98[x1555];
char* x1594 = x99[x1555];
int32_t x1595 = x100[x1555];
char* x1596 = x101[x1555];
int32_t x1597 = x102[x1555];
bool x1600 = pattern_compare(x1563,"PROMO%");
if (x1600) {
int32_t x1601 = x1223;
for (;;) {
int32_t x1602 = x1601;
bool x1603 = x52[x1602];
bool x1604;
if (x1603) {
x1604 = x1227;
} else {
x1604 = false;
}
if (!x1604) break;
x1601 += 1;
}
int32_t x1609 = x1601;
bool x1610 = x1609 == x917;
if (x1610) {
printf("%s\n","LB2HashMap table is full.");
exit(1);
} else {
}
bool x1615 = x52[x1609];
if (x1615) {
double x1616 = x50[x1609];
double x1617 = x51[x1609];
double x1598 = 1.0 - x1577;
double x1599 = x1576 * x1598;
double x1618 = x1616 + x1599;
x50[x1609] = x1618;
double x1619 = x1617 + x1599;
x51[x1609] = x1619;
} else {
int32_t x1623 = x60;
x58[x1623] = x1609;
x60 += 1;
double x1598 = 1.0 - x1577;
double x1599 = x1576 * x1598;
x50[x1609] = x1599;
x51[x1609] = x1599;
x52[x1609] = true;
}
} else {
int32_t x1632 = x1223;
for (;;) {
int32_t x1633 = x1632;
bool x1634 = x52[x1633];
bool x1635;
if (x1634) {
x1635 = x1227;
} else {
x1635 = false;
}
if (!x1635) break;
x1632 += 1;
}
int32_t x1640 = x1632;
bool x1641 = x1640 == x917;
if (x1641) {
printf("%s\n","LB2HashMap table is full.");
exit(1);
} else {
}
bool x1646 = x52[x1640];
if (x1646) {
double x1647 = x50[x1640];
double x1648 = x51[x1640];
x50[x1640] = x1647;
double x1598 = 1.0 - x1577;
double x1599 = x1576 * x1598;
double x1649 = x1648 + x1599;
x51[x1640] = x1649;
} else {
int32_t x1653 = x60;
x58[x1653] = x1640;
x60 += 1;
x50[x1640] = 0.0;
double x1598 = 1.0 - x1577;
double x1599 = x1576 * x1598;
x51[x1640] = x1599;
x52[x1640] = true;
}
}

}
int32_t x1665 = x60;
for(int x1667=0; x1667 < x1665; x1667++) {
int32_t x1668 = x58[x1667];
double x1669 = x50[x1668];
double x1670 = x51[x1668];
printf("%f",x1669);
printf(",");
printf("%f",x1670);
printf(",");
double x1671 = 100.0 * x1669;
double x1672 = x1671 / x1670;
printf("%f",x1672);
printf("%s\n","");

}
end = cur_time();
print_performance(begin, end);
}
/*****************************************
  End of C Generated Code                  
*******************************************/

