CC=gcc
XMPCC=xmpcc -std=gnu11 -DOMNI_CPU_X86_64 -DOMNI_OS_LINUX -D_GNU_SOURCE -D_REENTRANT \
-Wp,-P \
-D"__attribute__(x)=" -D"__extension__=" -D"__restrict=" -D"__inline=" \
-D"__leaf__=" -D"__THROW=" -D"__nonnull(x)=" \
-D"_Float128=long double" -D"_Float64=double" -D"_Float32=float" \
-D"_Float64x=long double" -D"_Float32x=double" \
-D_GCC_MAX_ALIGN_T -D__max_align_t_defined -D_MAX_ALIGN_T

LIBS=-L/usr/local/lib -lmpi
INCL=-I /usr/lib/openmpi/include

OBJP=histo.o

all: histo

histo.o: histo.c
	$(XMPCC) -c histo.c

histo: $(OBJP)
	$(XMPCC) -o histo $(OBJP) $(LIBS)

run: histo 
	mpirun --mca orte_base_help_agregate 0 -host c1 -n 1 /usr/local/var/mpishare/PPCS-CM6-TDXMP/histo
	 

clean:
	rm *.o histo
