TGTS = q01 \
       q14
OBJS = $(TGTS:%=%.o)

SIMD_TGTS = q01_simd_f q01_simd_fc q01_simd_f_hw_nomat q01_simd_f_hw_bufsize \
            q14_simd_f q14_simd_fc q14_simd_f_hw_nomat q14_simd_f_hw_bufsize
SIMD_OBJS = $(SIMD_TGTS:%=%.o)

CC = clang
CFLAGS = -g -c  -Wall -O2
SIMD_CFLAGS = -g -c  -Wall -O2 -mavx512f -mavx512dq
LDFLAGS =

define COMPILE
	$(CC) $(CFLAGS) $(1).c
	$(CC) $(LDFLAGS) -o $(1) $(1).o

endef

define SIMD_COMPILE
	$(CC) $(SIMD_CFLAGS) $(1).c
	$(CC) $(LDFLAGS) -o $(1) $(1).o

endef

all: scalar simd

scalar: $(TGTS)

simd: $(SIMD_TGTS)

$(TGTS):
	$(foreach t,$(TGTS),$(call COMPILE,$(t)))

$(SIMD_TGTS):
	$(foreach t,$(SIMD_TGTS),$(call SIMD_COMPILE,$(t)))

clean:
	rm -f *~ *.o $(TGTS) $(SIMD_TGTS)
