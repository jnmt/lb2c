TGTS = q01 \
       q14
OBJS = $(TGTS:%=%.o)

SIMD_TGTS = q01_simd_f q01_simd_fc \
            q14_simd_f q14_simd_fc
SIMD_OBJS = $(SIMD_TGTS:%=%.o)

CC = g++
CFLAGS = -g -c  -Wall -O2
SIMD_CFLAGS = -g -c  -Wall -O2 -mavx512f -mavx512dq
LDFLAGS =

define COMPILE
	sed -i -e "s/Users\/jun\/src\/tpch-dbgen/home\/jun\/tpch-dbgen\/sf1/g" $(1).c
	$(CC) $(CFLAGS) $(1).c
	$(CC) $(LDFLAGS) -o $(1) $(1).o

endef

define SIMD_COMPILE
	sed -i -e "s/Users\/jun\/src\/tpch-dbgen/home\/jun\/tpch-dbgen\/sf1/g" $(1).c
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
