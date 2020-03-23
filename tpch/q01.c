
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
int32_t x80 = 0;
int32_t x77 = open("/home/jun/tpch-dbgen/sf1/lineitem.tbl",0);
int32_t x78 = fsize(x77);
int32_t x81 = x78;
char* x79 = (char*)mmap(0, x78, PROT_READ, MAP_FILE | MAP_SHARED, x77, 0);
for (;;) {
int32_t x82 = x80;
int32_t x83 = x81;
bool x84 = x82 < x83;
if (!x84) break;
int32_t x86 = x80;
int32_t x87 = 0;
for (;;) {
int32_t x88 = x80;
char x89 = x79[x88];
bool x90 = x89 != '|';
if (!x90) break;
int32_t x92 = x87;
int32_t x94 = x80;
int32_t x93 = x92 * 10;
char x95 = x79[x94];
char x96 = x95 - '0';
int32_t x97 = x93 + x96;
x87 = x97;
x80 += 1;
}
x80 += 1;
int32_t x103 = x87;
int32_t x104 = x80;
int32_t x105 = 0;
for (;;) {
int32_t x106 = x80;
char x107 = x79[x106];
bool x108 = x107 != '|';
if (!x108) break;
int32_t x110 = x105;
int32_t x112 = x80;
int32_t x111 = x110 * 10;
char x113 = x79[x112];
char x114 = x113 - '0';
int32_t x115 = x111 + x114;
x105 = x115;
x80 += 1;
}
x80 += 1;
int32_t x121 = x105;
int32_t x122 = x80;
int32_t x123 = 0;
for (;;) {
int32_t x124 = x80;
char x125 = x79[x124];
bool x126 = x125 != '|';
if (!x126) break;
int32_t x128 = x123;
int32_t x130 = x80;
int32_t x129 = x128 * 10;
char x131 = x79[x130];
char x132 = x131 - '0';
int32_t x133 = x129 + x132;
x123 = x133;
x80 += 1;
}
x80 += 1;
int32_t x139 = x123;
int32_t x140 = x80;
int32_t x141 = 0;
for (;;) {
int32_t x142 = x80;
char x143 = x79[x142];
bool x144 = x143 != '|';
if (!x144) break;
int32_t x146 = x141;
int32_t x148 = x80;
int32_t x147 = x146 * 10;
char x149 = x79[x148];
char x150 = x149 - '0';
int32_t x151 = x147 + x150;
x141 = x151;
x80 += 1;
}
x80 += 1;
int32_t x157 = x141;
int32_t x158 = x80;
double x159 = 0.0;
double x160 = 10.0;
for (;;) {
int32_t x161 = x80;
char x162 = x79[x161];
bool x164 = x162 == '.';
bool x166;
if (x164) {
x166 = false;
} else {
bool x165 = x162 != '|';
x166 = x165;
}
if (!x166) break;
double x168 = x159;
int32_t x170 = x80;
double x169 = x168 * 10.0;
char x171 = x79[x170];
char x172 = x171 - '0';
double x174 = (double)x172;
double x175 = x169 + x174;
x159 = x175;
x80 += 1;
}
int32_t x180 = x80;
char x181 = x79[x180];
bool x183 = x181 == '|';
if (x183) {
} else {
x80 += 1;
for (;;) {
int32_t x185 = x80;
char x186 = x79[x185];
bool x187 = x186 != '|';
if (!x187) break;
double x189 = x159;
int32_t x190 = x80;
double x193 = x160;
char x191 = x79[x190];
char x192 = x191 - '0';
double x195 = (double)x192;
double x196 = x195 / x193;
double x197 = x189 + x196;
x159 = x197;
double x199 = x193 * 10.0;
x160 = x199;
x80 += 1;
}
}
x80 += 1;
double x207 = x159;
int32_t x208 = x80;
double x209 = 0.0;
double x210 = 10.0;
for (;;) {
int32_t x211 = x80;
char x212 = x79[x211];
bool x214 = x212 == '.';
bool x216;
if (x214) {
x216 = false;
} else {
bool x215 = x212 != '|';
x216 = x215;
}
if (!x216) break;
double x218 = x209;
int32_t x220 = x80;
double x219 = x218 * 10.0;
char x221 = x79[x220];
char x222 = x221 - '0';
double x224 = (double)x222;
double x225 = x219 + x224;
x209 = x225;
x80 += 1;
}
int32_t x230 = x80;
char x231 = x79[x230];
bool x233 = x231 == '|';
if (x233) {
} else {
x80 += 1;
for (;;) {
int32_t x235 = x80;
char x236 = x79[x235];
bool x237 = x236 != '|';
if (!x237) break;
double x239 = x209;
int32_t x240 = x80;
double x243 = x210;
char x241 = x79[x240];
char x242 = x241 - '0';
double x245 = (double)x242;
double x246 = x245 / x243;
double x247 = x239 + x246;
x209 = x247;
double x249 = x243 * 10.0;
x210 = x249;
x80 += 1;
}
}
x80 += 1;
double x257 = x209;
int32_t x258 = x80;
double x259 = 0.0;
double x260 = 10.0;
for (;;) {
int32_t x261 = x80;
char x262 = x79[x261];
bool x264 = x262 == '.';
bool x266;
if (x264) {
x266 = false;
} else {
bool x265 = x262 != '|';
x266 = x265;
}
if (!x266) break;
double x268 = x259;
int32_t x270 = x80;
double x269 = x268 * 10.0;
char x271 = x79[x270];
char x272 = x271 - '0';
double x274 = (double)x272;
double x275 = x269 + x274;
x259 = x275;
x80 += 1;
}
int32_t x280 = x80;
char x281 = x79[x280];
bool x283 = x281 == '|';
if (x283) {
} else {
x80 += 1;
for (;;) {
int32_t x285 = x80;
char x286 = x79[x285];
bool x287 = x286 != '|';
if (!x287) break;
double x289 = x259;
int32_t x290 = x80;
double x293 = x260;
char x291 = x79[x290];
char x292 = x291 - '0';
double x295 = (double)x292;
double x296 = x295 / x293;
double x297 = x289 + x296;
x259 = x297;
double x299 = x293 * 10.0;
x260 = x299;
x80 += 1;
}
}
x80 += 1;
double x307 = x259;
int32_t x308 = x80;
double x309 = 0.0;
double x310 = 10.0;
for (;;) {
int32_t x311 = x80;
char x312 = x79[x311];
bool x314 = x312 == '.';
bool x316;
if (x314) {
x316 = false;
} else {
bool x315 = x312 != '|';
x316 = x315;
}
if (!x316) break;
double x318 = x309;
int32_t x320 = x80;
double x319 = x318 * 10.0;
char x321 = x79[x320];
char x322 = x321 - '0';
double x324 = (double)x322;
double x325 = x319 + x324;
x309 = x325;
x80 += 1;
}
int32_t x330 = x80;
char x331 = x79[x330];
bool x333 = x331 == '|';
if (x333) {
} else {
x80 += 1;
for (;;) {
int32_t x335 = x80;
char x336 = x79[x335];
bool x337 = x336 != '|';
if (!x337) break;
double x339 = x309;
int32_t x340 = x80;
double x343 = x310;
char x341 = x79[x340];
char x342 = x341 - '0';
double x345 = (double)x342;
double x346 = x345 / x343;
double x347 = x339 + x346;
x309 = x347;
double x349 = x343 * 10.0;
x310 = x349;
x80 += 1;
}
}
x80 += 1;
double x357 = x309;
int32_t x358 = x80;
for (;;) {
int32_t x359 = x80;
char x360 = x79[x359];
bool x361 = x360 != '|';
if (!x361) break;
x80 += 1;
}
int32_t x366 = x80;
x80 += 1;
int32_t x370 = x80;
for (;;) {
int32_t x371 = x80;
char x372 = x79[x371];
bool x373 = x372 != '|';
if (!x373) break;
x80 += 1;
}
int32_t x378 = x80;
x80 += 1;
int32_t x382 = x80;
int32_t x383 = 0;
int32_t x384 = 0;
int32_t x385 = 0;
for (;;) {
int32_t x386 = x80;
char x387 = x79[x386];
bool x388 = x387 != '-';
if (!x388) break;
int32_t x390 = x383;
int32_t x392 = x80;
int32_t x391 = x390 * 10;
char x393 = x79[x392];
char x394 = x393 - '0';
int32_t x395 = x391 + x394;
x383 = x395;
x80 += 1;
}
x80 += 1;
for (;;) {
int32_t x401 = x80;
char x402 = x79[x401];
bool x403 = x402 != '-';
if (!x403) break;
int32_t x405 = x384;
int32_t x407 = x80;
int32_t x406 = x405 * 10;
char x408 = x79[x407];
char x409 = x408 - '0';
int32_t x410 = x406 + x409;
x384 = x410;
x80 += 1;
}
x80 += 1;
for (;;) {
int32_t x416 = x80;
char x417 = x79[x416];
bool x418 = x417 != '|';
if (!x418) break;
int32_t x420 = x385;
int32_t x422 = x80;
int32_t x421 = x420 * 10;
char x423 = x79[x422];
char x424 = x423 - '0';
int32_t x425 = x421 + x424;
x385 = x425;
x80 += 1;
}
x80 += 1;
int32_t x431 = x383;
int32_t x432 = x384;
int32_t x433 = x385;
int32_t x434 = x80;
int32_t x435 = 0;
int32_t x436 = 0;
int32_t x437 = 0;
for (;;) {
int32_t x438 = x80;
char x439 = x79[x438];
bool x440 = x439 != '-';
if (!x440) break;
int32_t x442 = x435;
int32_t x444 = x80;
int32_t x443 = x442 * 10;
char x445 = x79[x444];
char x446 = x445 - '0';
int32_t x447 = x443 + x446;
x435 = x447;
x80 += 1;
}
x80 += 1;
for (;;) {
int32_t x453 = x80;
char x454 = x79[x453];
bool x455 = x454 != '-';
if (!x455) break;
int32_t x457 = x436;
int32_t x459 = x80;
int32_t x458 = x457 * 10;
char x460 = x79[x459];
char x461 = x460 - '0';
int32_t x462 = x458 + x461;
x436 = x462;
x80 += 1;
}
x80 += 1;
for (;;) {
int32_t x468 = x80;
char x469 = x79[x468];
bool x470 = x469 != '|';
if (!x470) break;
int32_t x472 = x437;
int32_t x474 = x80;
int32_t x473 = x472 * 10;
char x475 = x79[x474];
char x476 = x475 - '0';
int32_t x477 = x473 + x476;
x437 = x477;
x80 += 1;
}
x80 += 1;
int32_t x483 = x435;
int32_t x484 = x436;
int32_t x485 = x437;
int32_t x486 = x80;
int32_t x487 = 0;
int32_t x488 = 0;
int32_t x489 = 0;
for (;;) {
int32_t x490 = x80;
char x491 = x79[x490];
bool x492 = x491 != '-';
if (!x492) break;
int32_t x494 = x487;
int32_t x496 = x80;
int32_t x495 = x494 * 10;
char x497 = x79[x496];
char x498 = x497 - '0';
int32_t x499 = x495 + x498;
x487 = x499;
x80 += 1;
}
x80 += 1;
for (;;) {
int32_t x505 = x80;
char x506 = x79[x505];
bool x507 = x506 != '-';
if (!x507) break;
int32_t x509 = x488;
int32_t x511 = x80;
int32_t x510 = x509 * 10;
char x512 = x79[x511];
char x513 = x512 - '0';
int32_t x514 = x510 + x513;
x488 = x514;
x80 += 1;
}
x80 += 1;
for (;;) {
int32_t x520 = x80;
char x521 = x79[x520];
bool x522 = x521 != '|';
if (!x522) break;
int32_t x524 = x489;
int32_t x526 = x80;
int32_t x525 = x524 * 10;
char x527 = x79[x526];
char x528 = x527 - '0';
int32_t x529 = x525 + x528;
x489 = x529;
x80 += 1;
}
x80 += 1;
int32_t x535 = x487;
int32_t x536 = x488;
int32_t x537 = x489;
int32_t x538 = x80;
for (;;) {
int32_t x539 = x80;
char x540 = x79[x539];
bool x541 = x540 != '|';
if (!x541) break;
x80 += 1;
}
int32_t x546 = x80;
x80 += 1;
int32_t x550 = x80;
for (;;) {
int32_t x551 = x80;
char x552 = x79[x551];
bool x553 = x552 != '|';
if (!x553) break;
x80 += 1;
}
int32_t x558 = x80;
x80 += 1;
int32_t x562 = x80;
for (;;) {
int32_t x563 = x80;
char x564 = x79[x563];
bool x565 = x564 != '\n';
if (!x565) break;
x80 += 1;
}
int32_t x570 = x80;
x80 += 1;
int32_t x574 = x30;
x2[x574] = x103;
x3[x574] = x121;
x4[x574] = x139;
x5[x574] = x157;
x6[x574] = x207;
x7[x574] = x257;
x8[x574] = x307;
x9[x574] = x357;
char* x369 = x79 + x358;
x10[x574] = x369;
int32_t x367 = x366 - x358;
x11[x574] = x367;
char* x381 = x79 + x370;
x12[x574] = x381;
int32_t x379 = x378 - x370;
x13[x574] = x379;
x14[x574] = x431;
x15[x574] = x432;
x16[x574] = x433;
x17[x574] = x483;
x18[x574] = x484;
x19[x574] = x485;
x20[x574] = x535;
x21[x574] = x536;
x22[x574] = x537;
char* x549 = x79 + x538;
x23[x574] = x549;
int32_t x547 = x546 - x538;
x24[x574] = x547;
char* x561 = x79 + x550;
x25[x574] = x561;
int32_t x559 = x558 - x550;
x26[x574] = x559;
char* x573 = x79 + x562;
x27[x574] = x573;
int32_t x571 = x570 - x562;
x28[x574] = x571;
x30 += 1;
}
close(x77);
int32_t x704 = x52 - 1;
struct timeval begin, end;
begin = cur_time();
int32_t x606 = x30;
for(int x608=0; x608 < x606; x608++) {
int32_t x609 = x2[x608];
int32_t x610 = x3[x608];
int32_t x611 = x4[x608];
int32_t x612 = x5[x608];
double x613 = x6[x608];
double x614 = x7[x608];
double x615 = x8[x608];
double x616 = x9[x608];
char* x617 = x10[x608];
int32_t x618 = x11[x608];
char* x619 = x12[x608];
int32_t x620 = x13[x608];
int32_t x621 = x14[x608];
int32_t x622 = x15[x608];
int32_t x623 = x16[x608];
int32_t x624 = x17[x608];
int32_t x625 = x18[x608];
int32_t x626 = x19[x608];
int32_t x627 = x20[x608];
int32_t x628 = x21[x608];
int32_t x629 = x22[x608];
char* x630 = x23[x608];
int32_t x631 = x24[x608];
char* x632 = x25[x608];
int32_t x633 = x26[x608];
char* x634 = x27[x608];
int32_t x635 = x28[x608];
int32_t x636 = x621 * 10000;
int32_t x637 = x622 * 100;
int32_t x638 = x636 + x637;
int32_t x639 = x638 + x623;
bool x640 = x639 <= 19980902;
if (x640) {
int64_t x645 = hash(x617,x618);
int64_t x646 = x645 * 41L;
int64_t x647 = hash(x619,x620);
int64_t x648 = x646 + x647;
int32_t x649 = (int32_t)x648;
bool x650 = x649 >= 0;
int32_t x652;
if (x650) {
x652 = x649;
} else {
int32_t x651 = 0 - x649;
x652 = x651;
}
int32_t x653 = x652 % x52;
int32_t x654 = x653;
for (;;) {
int32_t x655 = x654;
bool x656 = x68[x655];
bool x698;
if (x656) {
char* x657 = x53[x655];
int32_t x658 = x54[x655];
char* x659 = x55[x655];
int32_t x660 = x56[x655];
bool x662 = x658 == x618;
bool x677;
if (x662) {
int32_t x663 = 0;
for (;;) {
int32_t x664 = x663;
bool x665 = x664 < x658;
bool x669;
if (x665) {
char x666 = x657[x664];
char x667 = x617[x664];
bool x668 = x666 == x667;
x669 = x668;
} else {
x669 = false;
}
if (!x669) break;
x663 += 1;
}
int32_t x674 = x663;
bool x675 = x674 == x658;
x677 = x675;
} else {
x677 = false;
}
bool x695;
if (x677) {
bool x679 = x660 == x620;
bool x694;
if (x679) {
int32_t x680 = 0;
for (;;) {
int32_t x681 = x680;
bool x682 = x681 < x660;
bool x686;
if (x682) {
char x683 = x659[x681];
char x684 = x619[x681];
bool x685 = x683 == x684;
x686 = x685;
} else {
x686 = false;
}
if (!x686) break;
x680 += 1;
}
int32_t x691 = x680;
bool x692 = x691 == x660;
x694 = x692;
} else {
x694 = false;
}
x695 = x694;
} else {
x695 = false;
}
bool x696 = !x695;
x698 = x696;
} else {
x698 = false;
}
if (!x698) break;
x654 += 1;
}
int32_t x703 = x654;
bool x705 = x703 == x704;
if (x705) {
printf("%s\n","LB2HashMap table is full.");
exit(1);
} else {
}
bool x710 = x68[x703];
if (x710) {
double x711 = x57[x703];
double x712 = x58[x703];
double x713 = x59[x703];
double x714 = x60[x703];
double x715 = x61[x703];
int32_t x716 = x62[x703];
double x717 = x63[x703];
int32_t x718 = x64[x703];
double x719 = x65[x703];
int32_t x720 = x66[x703];
int32_t x721 = x67[x703];
double x722 = x711 + x613;
x57[x703] = x722;
double x723 = x712 + x614;
x58[x703] = x723;
double x641 = 1.0 - x615;
double x642 = x614 * x641;
double x724 = x713 + x642;
x59[x703] = x724;
double x643 = 1.0 + x616;
double x644 = x642 * x643;
double x725 = x714 + x644;
x60[x703] = x725;
double x726 = x715 + x613;
x61[x703] = x726;
int32_t x727 = x716 + 1;
x62[x703] = x727;
double x728 = x717 + x614;
x63[x703] = x728;
int32_t x729 = x718 + 1;
x64[x703] = x729;
double x730 = x719 + x615;
x65[x703] = x730;
int32_t x731 = x720 + 1;
x66[x703] = x731;
int32_t x732 = x721 + 1;
x67[x703] = x732;
} else {
int32_t x745 = x76;
x74[x745] = x703;
x76 += 1;
x53[x703] = x617;
x54[x703] = x618;
x55[x703] = x619;
x56[x703] = x620;
x57[x703] = x613;
x58[x703] = x614;
double x641 = 1.0 - x615;
double x642 = x614 * x641;
x59[x703] = x642;
double x643 = 1.0 + x616;
double x644 = x642 * x643;
x60[x703] = x644;
x61[x703] = x613;
x62[x703] = 1;
x63[x703] = x614;
x64[x703] = 1;
x65[x703] = x615;
x66[x703] = 1;
x67[x703] = 1;
x68[x703] = true;
}
} else {
}

}
int32_t x770 = x76;
for(int x772=0; x772 < x770; x772++) {
int32_t x773 = x74[x772];
char* x774 = x53[x773];
int32_t x775 = x54[x773];
char* x776 = x55[x773];
int32_t x777 = x56[x773];
double x778 = x57[x773];
double x779 = x58[x773];
double x780 = x59[x773];
double x781 = x60[x773];
double x782 = x61[x773];
int32_t x783 = x62[x773];
double x784 = x63[x773];
int32_t x785 = x64[x773];
double x786 = x65[x773];
int32_t x787 = x66[x773];
int32_t x788 = x67[x773];
int32_t x789 = x49;
x32[x789] = x774;
x33[x789] = x775;
x34[x789] = x776;
x35[x789] = x777;
x36[x789] = x778;
x37[x789] = x779;
x38[x789] = x780;
x39[x789] = x781;
x40[x789] = x782;
x41[x789] = x783;
x42[x789] = x784;
x43[x789] = x785;
x44[x789] = x786;
x45[x789] = x787;
x46[x789] = x788;
x47[x789] = x789;
x49 += 1;

}
x50[0] = 0;
int32_t x810 = x49;
int32_t x811 = x810 - 1;
x51[0] = x811;
int32_t x813 = 1;
int32_t x814 = 1;
for (;;) {
int32_t x815 = x814;
bool x816 = x815 > 0;
if (!x816) break;
int32_t x818 = x814;
int32_t x819 = x818 - 1;
x814 = x819;
int32_t x821 = x50[x819];
int32_t x822 = x51[x819];
int32_t x823 = x821;
int32_t x824 = x822;
int32_t x828 = x47[x821];
char* x829 = x32[x828];
int32_t x830 = x33[x828];
char* x831 = x34[x828];
int32_t x832 = x35[x828];
double x833 = x36[x828];
double x834 = x37[x828];
double x835 = x38[x828];
double x836 = x39[x828];
double x837 = x40[x828];
int32_t x838 = x41[x828];
double x839 = x42[x828];
int32_t x840 = x43[x828];
double x841 = x44[x828];
int32_t x842 = x45[x828];
int32_t x843 = x46[x828];
int32_t x844 = x47[x822];
char* x845 = x32[x844];
int32_t x846 = x33[x844];
char* x847 = x34[x844];
int32_t x848 = x35[x844];
double x849 = x36[x844];
double x850 = x37[x844];
double x851 = x38[x844];
double x852 = x39[x844];
double x853 = x40[x844];
int32_t x854 = x41[x844];
double x855 = x42[x844];
int32_t x856 = x43[x844];
double x857 = x44[x844];
int32_t x858 = x45[x844];
int32_t x859 = x46[x844];
int32_t x860 = 0;
int32_t x861 = 0;
bool* x862 = (bool*)malloc(2 * sizeof(bool));
bool* x863 = (bool*)malloc(2 * sizeof(bool));
int32_t x864 = 0;
for (;;) {
int32_t x865 = x864;
bool x866 = x865 < x830;
bool x868;
if (x866) {
bool x867 = x865 < x846;
x868 = x867;
} else {
x868 = false;
}
bool x872;
if (x868) {
char x869 = x829[x865];
char x870 = x845[x865];
bool x871 = x869 == x870;
x872 = x871;
} else {
x872 = false;
}
if (!x872) break;
x864 += 1;
}
int32_t x877 = x864;
char x878 = x829[x877];
char x879 = x845[x877];
bool x880 = x878 < x879;
x862[0] = x880;
bool x883 = x830 == x846;
bool x898;
if (x883) {
int32_t x884 = 0;
for (;;) {
int32_t x885 = x884;
bool x886 = x885 < x830;
bool x890;
if (x886) {
char x887 = x829[x885];
char x888 = x845[x885];
bool x889 = x887 == x888;
x890 = x889;
} else {
x890 = false;
}
if (!x890) break;
x884 += 1;
}
int32_t x895 = x884;
bool x896 = x895 == x830;
x898 = x896;
} else {
x898 = false;
}
x863[0] = x898;
x861 += 1;
int32_t x901 = x861;
int32_t x902 = 0;
for (;;) {
int32_t x903 = x902;
bool x904 = x903 < x832;
bool x906;
if (x904) {
bool x905 = x903 < x848;
x906 = x905;
} else {
x906 = false;
}
bool x910;
if (x906) {
char x907 = x831[x903];
char x908 = x847[x903];
bool x909 = x907 == x908;
x910 = x909;
} else {
x910 = false;
}
if (!x910) break;
x902 += 1;
}
int32_t x915 = x902;
char x916 = x831[x915];
char x917 = x847[x915];
bool x918 = x916 < x917;
x862[x901] = x918;
bool x921 = x832 == x848;
bool x936;
if (x921) {
int32_t x922 = 0;
for (;;) {
int32_t x923 = x922;
bool x924 = x923 < x832;
bool x928;
if (x924) {
char x925 = x831[x923];
char x926 = x847[x923];
bool x927 = x925 == x926;
x928 = x927;
} else {
x928 = false;
}
if (!x928) break;
x922 += 1;
}
int32_t x933 = x922;
bool x934 = x933 == x832;
x936 = x934;
} else {
x936 = false;
}
x863[x901] = x936;
x861 += 1;
bool x939 = x862[0];
bool x941 = x863[0];
bool x942 = x862[1];
bool x940;
if (x939) {
x940 = true;
} else {
x940 = false;
}
bool x943;
if (x942) {
x943 = x941;
} else {
x943 = false;
}
bool x944 = x940 || x943;
int32_t x825 = x822 - x821;
int32_t x826 = x825 / 2;
int32_t x827 = x821 + x826;
int32_t x1325;
if (x944) {
int32_t x945 = x47[x827];
char* x946 = x32[x945];
int32_t x947 = x33[x945];
char* x948 = x34[x945];
int32_t x949 = x35[x945];
double x950 = x36[x945];
double x951 = x37[x945];
double x952 = x38[x945];
double x953 = x39[x945];
double x954 = x40[x945];
int32_t x955 = x41[x945];
double x956 = x42[x945];
int32_t x957 = x43[x945];
double x958 = x44[x945];
int32_t x959 = x45[x945];
int32_t x960 = x46[x945];
int32_t x961 = 0;
int32_t x962 = 0;
bool* x963 = (bool*)malloc(2 * sizeof(bool));
bool* x964 = (bool*)malloc(2 * sizeof(bool));
int32_t x965 = 0;
for (;;) {
int32_t x966 = x965;
bool x967 = x966 < x846;
bool x969;
if (x967) {
bool x968 = x966 < x947;
x969 = x968;
} else {
x969 = false;
}
bool x973;
if (x969) {
char x970 = x845[x966];
char x971 = x946[x966];
bool x972 = x970 == x971;
x973 = x972;
} else {
x973 = false;
}
if (!x973) break;
x965 += 1;
}
int32_t x978 = x965;
char x979 = x845[x978];
char x980 = x946[x978];
bool x981 = x979 < x980;
x963[0] = x981;
bool x984 = x846 == x947;
bool x999;
if (x984) {
int32_t x985 = 0;
for (;;) {
int32_t x986 = x985;
bool x987 = x986 < x846;
bool x991;
if (x987) {
char x988 = x845[x986];
char x989 = x946[x986];
bool x990 = x988 == x989;
x991 = x990;
} else {
x991 = false;
}
if (!x991) break;
x985 += 1;
}
int32_t x996 = x985;
bool x997 = x996 == x846;
x999 = x997;
} else {
x999 = false;
}
x964[0] = x999;
x962 += 1;
int32_t x1002 = x962;
int32_t x1003 = 0;
for (;;) {
int32_t x1004 = x1003;
bool x1005 = x1004 < x848;
bool x1007;
if (x1005) {
bool x1006 = x1004 < x949;
x1007 = x1006;
} else {
x1007 = false;
}
bool x1011;
if (x1007) {
char x1008 = x847[x1004];
char x1009 = x948[x1004];
bool x1010 = x1008 == x1009;
x1011 = x1010;
} else {
x1011 = false;
}
if (!x1011) break;
x1003 += 1;
}
int32_t x1016 = x1003;
char x1017 = x847[x1016];
char x1018 = x948[x1016];
bool x1019 = x1017 < x1018;
x963[x1002] = x1019;
bool x1022 = x848 == x949;
bool x1037;
if (x1022) {
int32_t x1023 = 0;
for (;;) {
int32_t x1024 = x1023;
bool x1025 = x1024 < x848;
bool x1029;
if (x1025) {
char x1026 = x847[x1024];
char x1027 = x948[x1024];
bool x1028 = x1026 == x1027;
x1029 = x1028;
} else {
x1029 = false;
}
if (!x1029) break;
x1023 += 1;
}
int32_t x1034 = x1023;
bool x1035 = x1034 == x848;
x1037 = x1035;
} else {
x1037 = false;
}
x964[x1002] = x1037;
x962 += 1;
bool x1040 = x963[0];
bool x1042 = x964[0];
bool x1043 = x963[1];
bool x1041;
if (x1040) {
x1041 = true;
} else {
x1041 = false;
}
bool x1044;
if (x1043) {
x1044 = x1042;
} else {
x1044 = false;
}
bool x1045 = x1041 || x1044;
int32_t x1133;
if (x1045) {
x1133 = x822;
} else {
int32_t x1046 = 0;
int32_t x1047 = 0;
bool* x1048 = (bool*)malloc(2 * sizeof(bool));
bool* x1049 = (bool*)malloc(2 * sizeof(bool));
int32_t x1050 = 0;
for (;;) {
int32_t x1051 = x1050;
bool x1052 = x1051 < x947;
bool x1054;
if (x1052) {
bool x1053 = x1051 < x830;
x1054 = x1053;
} else {
x1054 = false;
}
bool x1058;
if (x1054) {
char x1055 = x946[x1051];
char x1056 = x829[x1051];
bool x1057 = x1055 == x1056;
x1058 = x1057;
} else {
x1058 = false;
}
if (!x1058) break;
x1050 += 1;
}
int32_t x1063 = x1050;
char x1064 = x946[x1063];
char x1065 = x829[x1063];
bool x1066 = x1064 < x1065;
x1048[0] = x1066;
bool x1069 = x947 == x830;
bool x1084;
if (x1069) {
int32_t x1070 = 0;
for (;;) {
int32_t x1071 = x1070;
bool x1072 = x1071 < x947;
bool x1076;
if (x1072) {
char x1073 = x946[x1071];
char x1074 = x829[x1071];
bool x1075 = x1073 == x1074;
x1076 = x1075;
} else {
x1076 = false;
}
if (!x1076) break;
x1070 += 1;
}
int32_t x1081 = x1070;
bool x1082 = x1081 == x947;
x1084 = x1082;
} else {
x1084 = false;
}
x1049[0] = x1084;
x1047 += 1;
int32_t x1087 = x1047;
int32_t x1088 = 0;
for (;;) {
int32_t x1089 = x1088;
bool x1090 = x1089 < x949;
bool x1092;
if (x1090) {
bool x1091 = x1089 < x832;
x1092 = x1091;
} else {
x1092 = false;
}
bool x1096;
if (x1092) {
char x1093 = x948[x1089];
char x1094 = x831[x1089];
bool x1095 = x1093 == x1094;
x1096 = x1095;
} else {
x1096 = false;
}
if (!x1096) break;
x1088 += 1;
}
int32_t x1101 = x1088;
char x1102 = x948[x1101];
char x1103 = x831[x1101];
bool x1104 = x1102 < x1103;
x1048[x1087] = x1104;
bool x1107 = x949 == x832;
bool x1122;
if (x1107) {
int32_t x1108 = 0;
for (;;) {
int32_t x1109 = x1108;
bool x1110 = x1109 < x949;
bool x1114;
if (x1110) {
char x1111 = x948[x1109];
char x1112 = x831[x1109];
bool x1113 = x1111 == x1112;
x1114 = x1113;
} else {
x1114 = false;
}
if (!x1114) break;
x1108 += 1;
}
int32_t x1119 = x1108;
bool x1120 = x1119 == x949;
x1122 = x1120;
} else {
x1122 = false;
}
x1049[x1087] = x1122;
x1047 += 1;
bool x1125 = x1048[0];
bool x1127 = x1049[0];
bool x1128 = x1048[1];
bool x1126;
if (x1125) {
x1126 = true;
} else {
x1126 = false;
}
bool x1129;
if (x1128) {
x1129 = x1127;
} else {
x1129 = false;
}
bool x1130 = x1126 || x1129;
int32_t x1131;
if (x1130) {
x1131 = x821;
} else {
x1131 = x827;
}
x1133 = x1131;
}
x1325 = x1133;
} else {
int32_t x1135 = x47[x827];
char* x1136 = x32[x1135];
int32_t x1137 = x33[x1135];
char* x1138 = x34[x1135];
int32_t x1139 = x35[x1135];
double x1140 = x36[x1135];
double x1141 = x37[x1135];
double x1142 = x38[x1135];
double x1143 = x39[x1135];
double x1144 = x40[x1135];
int32_t x1145 = x41[x1135];
double x1146 = x42[x1135];
int32_t x1147 = x43[x1135];
double x1148 = x44[x1135];
int32_t x1149 = x45[x1135];
int32_t x1150 = x46[x1135];
int32_t x1151 = 0;
int32_t x1152 = 0;
bool* x1153 = (bool*)malloc(2 * sizeof(bool));
bool* x1154 = (bool*)malloc(2 * sizeof(bool));
int32_t x1155 = 0;
for (;;) {
int32_t x1156 = x1155;
bool x1157 = x1156 < x830;
bool x1159;
if (x1157) {
bool x1158 = x1156 < x1137;
x1159 = x1158;
} else {
x1159 = false;
}
bool x1163;
if (x1159) {
char x1160 = x829[x1156];
char x1161 = x1136[x1156];
bool x1162 = x1160 == x1161;
x1163 = x1162;
} else {
x1163 = false;
}
if (!x1163) break;
x1155 += 1;
}
int32_t x1168 = x1155;
char x1169 = x829[x1168];
char x1170 = x1136[x1168];
bool x1171 = x1169 < x1170;
x1153[0] = x1171;
bool x1174 = x830 == x1137;
bool x1189;
if (x1174) {
int32_t x1175 = 0;
for (;;) {
int32_t x1176 = x1175;
bool x1177 = x1176 < x830;
bool x1181;
if (x1177) {
char x1178 = x829[x1176];
char x1179 = x1136[x1176];
bool x1180 = x1178 == x1179;
x1181 = x1180;
} else {
x1181 = false;
}
if (!x1181) break;
x1175 += 1;
}
int32_t x1186 = x1175;
bool x1187 = x1186 == x830;
x1189 = x1187;
} else {
x1189 = false;
}
x1154[0] = x1189;
x1152 += 1;
int32_t x1192 = x1152;
int32_t x1193 = 0;
for (;;) {
int32_t x1194 = x1193;
bool x1195 = x1194 < x832;
bool x1197;
if (x1195) {
bool x1196 = x1194 < x1139;
x1197 = x1196;
} else {
x1197 = false;
}
bool x1201;
if (x1197) {
char x1198 = x831[x1194];
char x1199 = x1138[x1194];
bool x1200 = x1198 == x1199;
x1201 = x1200;
} else {
x1201 = false;
}
if (!x1201) break;
x1193 += 1;
}
int32_t x1206 = x1193;
char x1207 = x831[x1206];
char x1208 = x1138[x1206];
bool x1209 = x1207 < x1208;
x1153[x1192] = x1209;
bool x1212 = x832 == x1139;
bool x1227;
if (x1212) {
int32_t x1213 = 0;
for (;;) {
int32_t x1214 = x1213;
bool x1215 = x1214 < x832;
bool x1219;
if (x1215) {
char x1216 = x831[x1214];
char x1217 = x1138[x1214];
bool x1218 = x1216 == x1217;
x1219 = x1218;
} else {
x1219 = false;
}
if (!x1219) break;
x1213 += 1;
}
int32_t x1224 = x1213;
bool x1225 = x1224 == x832;
x1227 = x1225;
} else {
x1227 = false;
}
x1154[x1192] = x1227;
x1152 += 1;
bool x1230 = x1153[0];
bool x1232 = x1154[0];
bool x1233 = x1153[1];
bool x1231;
if (x1230) {
x1231 = true;
} else {
x1231 = false;
}
bool x1234;
if (x1233) {
x1234 = x1232;
} else {
x1234 = false;
}
bool x1235 = x1231 || x1234;
int32_t x1323;
if (x1235) {
x1323 = x821;
} else {
int32_t x1236 = 0;
int32_t x1237 = 0;
bool* x1238 = (bool*)malloc(2 * sizeof(bool));
bool* x1239 = (bool*)malloc(2 * sizeof(bool));
int32_t x1240 = 0;
for (;;) {
int32_t x1241 = x1240;
bool x1242 = x1241 < x1137;
bool x1244;
if (x1242) {
bool x1243 = x1241 < x846;
x1244 = x1243;
} else {
x1244 = false;
}
bool x1248;
if (x1244) {
char x1245 = x1136[x1241];
char x1246 = x845[x1241];
bool x1247 = x1245 == x1246;
x1248 = x1247;
} else {
x1248 = false;
}
if (!x1248) break;
x1240 += 1;
}
int32_t x1253 = x1240;
char x1254 = x1136[x1253];
char x1255 = x845[x1253];
bool x1256 = x1254 < x1255;
x1238[0] = x1256;
bool x1259 = x1137 == x846;
bool x1274;
if (x1259) {
int32_t x1260 = 0;
for (;;) {
int32_t x1261 = x1260;
bool x1262 = x1261 < x1137;
bool x1266;
if (x1262) {
char x1263 = x1136[x1261];
char x1264 = x845[x1261];
bool x1265 = x1263 == x1264;
x1266 = x1265;
} else {
x1266 = false;
}
if (!x1266) break;
x1260 += 1;
}
int32_t x1271 = x1260;
bool x1272 = x1271 == x1137;
x1274 = x1272;
} else {
x1274 = false;
}
x1239[0] = x1274;
x1237 += 1;
int32_t x1277 = x1237;
int32_t x1278 = 0;
for (;;) {
int32_t x1279 = x1278;
bool x1280 = x1279 < x1139;
bool x1282;
if (x1280) {
bool x1281 = x1279 < x848;
x1282 = x1281;
} else {
x1282 = false;
}
bool x1286;
if (x1282) {
char x1283 = x1138[x1279];
char x1284 = x847[x1279];
bool x1285 = x1283 == x1284;
x1286 = x1285;
} else {
x1286 = false;
}
if (!x1286) break;
x1278 += 1;
}
int32_t x1291 = x1278;
char x1292 = x1138[x1291];
char x1293 = x847[x1291];
bool x1294 = x1292 < x1293;
x1238[x1277] = x1294;
bool x1297 = x1139 == x848;
bool x1312;
if (x1297) {
int32_t x1298 = 0;
for (;;) {
int32_t x1299 = x1298;
bool x1300 = x1299 < x1139;
bool x1304;
if (x1300) {
char x1301 = x1138[x1299];
char x1302 = x847[x1299];
bool x1303 = x1301 == x1302;
x1304 = x1303;
} else {
x1304 = false;
}
if (!x1304) break;
x1298 += 1;
}
int32_t x1309 = x1298;
bool x1310 = x1309 == x1139;
x1312 = x1310;
} else {
x1312 = false;
}
x1239[x1277] = x1312;
x1237 += 1;
bool x1315 = x1238[0];
bool x1317 = x1239[0];
bool x1318 = x1238[1];
bool x1316;
if (x1315) {
x1316 = true;
} else {
x1316 = false;
}
bool x1319;
if (x1318) {
x1319 = x1317;
} else {
x1319 = false;
}
bool x1320 = x1316 || x1319;
int32_t x1321;
if (x1320) {
x1321 = x822;
} else {
x1321 = x827;
}
x1323 = x1321;
}
x1325 = x1323;
}
int32_t x1326 = x47[x1325];
for (;;) {
int32_t x1327 = x823;
int32_t x1328 = x824;
bool x1329 = x1327 <= x1328;
if (!x1329) break;
for (;;) {
int32_t x1331 = x823;
int32_t x1332 = x47[x1331];
char* x1333 = x32[x1332];
int32_t x1334 = x33[x1332];
char* x1335 = x34[x1332];
int32_t x1336 = x35[x1332];
double x1337 = x36[x1332];
double x1338 = x37[x1332];
double x1339 = x38[x1332];
double x1340 = x39[x1332];
double x1341 = x40[x1332];
int32_t x1342 = x41[x1332];
double x1343 = x42[x1332];
int32_t x1344 = x43[x1332];
double x1345 = x44[x1332];
int32_t x1346 = x45[x1332];
int32_t x1347 = x46[x1332];
char* x1348 = x32[x1326];
int32_t x1349 = x33[x1326];
char* x1350 = x34[x1326];
int32_t x1351 = x35[x1326];
double x1352 = x36[x1326];
double x1353 = x37[x1326];
double x1354 = x38[x1326];
double x1355 = x39[x1326];
double x1356 = x40[x1326];
int32_t x1357 = x41[x1326];
double x1358 = x42[x1326];
int32_t x1359 = x43[x1326];
double x1360 = x44[x1326];
int32_t x1361 = x45[x1326];
int32_t x1362 = x46[x1326];
int32_t x1363 = 0;
int32_t x1364 = 0;
bool* x1365 = (bool*)malloc(2 * sizeof(bool));
bool* x1366 = (bool*)malloc(2 * sizeof(bool));
int32_t x1367 = 0;
for (;;) {
int32_t x1368 = x1367;
bool x1369 = x1368 < x1334;
bool x1371;
if (x1369) {
bool x1370 = x1368 < x1349;
x1371 = x1370;
} else {
x1371 = false;
}
bool x1375;
if (x1371) {
char x1372 = x1333[x1368];
char x1373 = x1348[x1368];
bool x1374 = x1372 == x1373;
x1375 = x1374;
} else {
x1375 = false;
}
if (!x1375) break;
x1367 += 1;
}
int32_t x1380 = x1367;
char x1381 = x1333[x1380];
char x1382 = x1348[x1380];
bool x1383 = x1381 < x1382;
x1365[0] = x1383;
bool x1386 = x1334 == x1349;
bool x1401;
if (x1386) {
int32_t x1387 = 0;
for (;;) {
int32_t x1388 = x1387;
bool x1389 = x1388 < x1334;
bool x1393;
if (x1389) {
char x1390 = x1333[x1388];
char x1391 = x1348[x1388];
bool x1392 = x1390 == x1391;
x1393 = x1392;
} else {
x1393 = false;
}
if (!x1393) break;
x1387 += 1;
}
int32_t x1398 = x1387;
bool x1399 = x1398 == x1334;
x1401 = x1399;
} else {
x1401 = false;
}
x1366[0] = x1401;
x1364 += 1;
int32_t x1404 = x1364;
int32_t x1405 = 0;
for (;;) {
int32_t x1406 = x1405;
bool x1407 = x1406 < x1336;
bool x1409;
if (x1407) {
bool x1408 = x1406 < x1351;
x1409 = x1408;
} else {
x1409 = false;
}
bool x1413;
if (x1409) {
char x1410 = x1335[x1406];
char x1411 = x1350[x1406];
bool x1412 = x1410 == x1411;
x1413 = x1412;
} else {
x1413 = false;
}
if (!x1413) break;
x1405 += 1;
}
int32_t x1418 = x1405;
char x1419 = x1335[x1418];
char x1420 = x1350[x1418];
bool x1421 = x1419 < x1420;
x1365[x1404] = x1421;
bool x1424 = x1336 == x1351;
bool x1439;
if (x1424) {
int32_t x1425 = 0;
for (;;) {
int32_t x1426 = x1425;
bool x1427 = x1426 < x1336;
bool x1431;
if (x1427) {
char x1428 = x1335[x1426];
char x1429 = x1350[x1426];
bool x1430 = x1428 == x1429;
x1431 = x1430;
} else {
x1431 = false;
}
if (!x1431) break;
x1425 += 1;
}
int32_t x1436 = x1425;
bool x1437 = x1436 == x1336;
x1439 = x1437;
} else {
x1439 = false;
}
x1366[x1404] = x1439;
x1364 += 1;
bool x1442 = x1365[0];
bool x1444 = x1366[0];
bool x1445 = x1365[1];
bool x1443;
if (x1442) {
x1443 = true;
} else {
x1443 = false;
}
bool x1446;
if (x1445) {
x1446 = x1444;
} else {
x1446 = false;
}
bool x1447 = x1443 || x1446;
if (!x1447) break;
int32_t x1449 = x823;
int32_t x1450 = x1449 + 1;
x823 = x1450;
}
for (;;) {
char* x1454 = x32[x1326];
int32_t x1455 = x33[x1326];
char* x1456 = x34[x1326];
int32_t x1457 = x35[x1326];
double x1458 = x36[x1326];
double x1459 = x37[x1326];
double x1460 = x38[x1326];
double x1461 = x39[x1326];
double x1462 = x40[x1326];
int32_t x1463 = x41[x1326];
double x1464 = x42[x1326];
int32_t x1465 = x43[x1326];
double x1466 = x44[x1326];
int32_t x1467 = x45[x1326];
int32_t x1468 = x46[x1326];
int32_t x1469 = x824;
int32_t x1470 = x47[x1469];
char* x1471 = x32[x1470];
int32_t x1472 = x33[x1470];
char* x1473 = x34[x1470];
int32_t x1474 = x35[x1470];
double x1475 = x36[x1470];
double x1476 = x37[x1470];
double x1477 = x38[x1470];
double x1478 = x39[x1470];
double x1479 = x40[x1470];
int32_t x1480 = x41[x1470];
double x1481 = x42[x1470];
int32_t x1482 = x43[x1470];
double x1483 = x44[x1470];
int32_t x1484 = x45[x1470];
int32_t x1485 = x46[x1470];
int32_t x1486 = 0;
int32_t x1487 = 0;
bool* x1488 = (bool*)malloc(2 * sizeof(bool));
bool* x1489 = (bool*)malloc(2 * sizeof(bool));
int32_t x1490 = 0;
for (;;) {
int32_t x1491 = x1490;
bool x1492 = x1491 < x1455;
bool x1494;
if (x1492) {
bool x1493 = x1491 < x1472;
x1494 = x1493;
} else {
x1494 = false;
}
bool x1498;
if (x1494) {
char x1495 = x1454[x1491];
char x1496 = x1471[x1491];
bool x1497 = x1495 == x1496;
x1498 = x1497;
} else {
x1498 = false;
}
if (!x1498) break;
x1490 += 1;
}
int32_t x1503 = x1490;
char x1504 = x1454[x1503];
char x1505 = x1471[x1503];
bool x1506 = x1504 < x1505;
x1488[0] = x1506;
bool x1509 = x1455 == x1472;
bool x1524;
if (x1509) {
int32_t x1510 = 0;
for (;;) {
int32_t x1511 = x1510;
bool x1512 = x1511 < x1455;
bool x1516;
if (x1512) {
char x1513 = x1454[x1511];
char x1514 = x1471[x1511];
bool x1515 = x1513 == x1514;
x1516 = x1515;
} else {
x1516 = false;
}
if (!x1516) break;
x1510 += 1;
}
int32_t x1521 = x1510;
bool x1522 = x1521 == x1455;
x1524 = x1522;
} else {
x1524 = false;
}
x1489[0] = x1524;
x1487 += 1;
int32_t x1527 = x1487;
int32_t x1528 = 0;
for (;;) {
int32_t x1529 = x1528;
bool x1530 = x1529 < x1457;
bool x1532;
if (x1530) {
bool x1531 = x1529 < x1474;
x1532 = x1531;
} else {
x1532 = false;
}
bool x1536;
if (x1532) {
char x1533 = x1456[x1529];
char x1534 = x1473[x1529];
bool x1535 = x1533 == x1534;
x1536 = x1535;
} else {
x1536 = false;
}
if (!x1536) break;
x1528 += 1;
}
int32_t x1541 = x1528;
char x1542 = x1456[x1541];
char x1543 = x1473[x1541];
bool x1544 = x1542 < x1543;
x1488[x1527] = x1544;
bool x1547 = x1457 == x1474;
bool x1562;
if (x1547) {
int32_t x1548 = 0;
for (;;) {
int32_t x1549 = x1548;
bool x1550 = x1549 < x1457;
bool x1554;
if (x1550) {
char x1551 = x1456[x1549];
char x1552 = x1473[x1549];
bool x1553 = x1551 == x1552;
x1554 = x1553;
} else {
x1554 = false;
}
if (!x1554) break;
x1548 += 1;
}
int32_t x1559 = x1548;
bool x1560 = x1559 == x1457;
x1562 = x1560;
} else {
x1562 = false;
}
x1489[x1527] = x1562;
x1487 += 1;
bool x1565 = x1488[0];
bool x1567 = x1489[0];
bool x1568 = x1488[1];
bool x1566;
if (x1565) {
x1566 = true;
} else {
x1566 = false;
}
bool x1569;
if (x1568) {
x1569 = x1567;
} else {
x1569 = false;
}
bool x1570 = x1566 || x1569;
if (!x1570) break;
int32_t x1572 = x824;
int32_t x1573 = x1572 - 1;
x824 = x1573;
}
int32_t x1577 = x823;
int32_t x1578 = x824;
bool x1579 = x1577 <= x1578;
if (x1579) {
int32_t x1580 = x47[x1577];
int32_t x1581 = x47[x1578];
x47[x1577] = x1581;
x47[x1578] = x1580;
int32_t x1584 = x1577 + 1;
x823 = x1584;
int32_t x1586 = x1578 - 1;
x824 = x1586;
} else {
}
}
int32_t x1592 = x824;
bool x1593 = x821 < x1592;
if (x1593) {
x50[x819] = x821;
x51[x819] = x1592;
int32_t x1596 = x819 + 1;
x814 = x1596;
} else {
}
int32_t x1600 = x823;
bool x1601 = x1600 < x822;
if (x1601) {
int32_t x1602 = x814;
x50[x1602] = x1600;
x51[x1602] = x822;
int32_t x1605 = x1602 + 1;
x814 = x1605;
} else {
}
}
for(int x1612=0; x1612 < x810; x1612++) {
int32_t x1613 = x47[x1612];
char* x1614 = x32[x1613];
int32_t x1615 = x33[x1613];
char* x1616 = x34[x1613];
int32_t x1617 = x35[x1613];
double x1618 = x36[x1613];
double x1619 = x37[x1613];
double x1620 = x38[x1613];
double x1621 = x39[x1613];
double x1622 = x40[x1613];
int32_t x1623 = x41[x1613];
double x1624 = x42[x1613];
int32_t x1625 = x43[x1613];
double x1626 = x44[x1613];
int32_t x1627 = x45[x1613];
int32_t x1628 = x46[x1613];
int32_t x1629 = printll(x1614);
printf(",");
int32_t x1631 = printll(x1616);
printf(",");
printf("%f",x1618);
printf(",");
printf("%f",x1619);
printf(",");
printf("%f",x1620);
printf(",");
printf("%f",x1621);
printf(",");
double x1642 = (double)x1623;
double x1643 = x1622 / x1642;
printf("%f",x1643);
printf(",");
double x1647 = (double)x1625;
double x1648 = x1624 / x1647;
printf("%f",x1648);
printf(",");
double x1652 = (double)x1627;
double x1653 = x1626 / x1652;
printf("%f",x1653);
printf(",");
printf("%d",x1628);
printf("%s\n","");

}
end = cur_time();
print_performance(begin, end);
}
/*****************************************
  End of C Generated Code                  
*******************************************/

