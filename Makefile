#
# makefile
#

ifndef nbyte
NBYTE=-DNBYTE=8
else
NBYTE=-DNBYTE=$(nbyte)
endif

ifndef mpi_bc
MPI_BC=
else
MPI_BC=-DMPI_BC
endif

lib_objs := coll.o

test := test
test_objs := test.o

MPICC := mpicc
CFLAGS := -Wall -O2 -std=c99 -lm $(NBYTE) $(MPI_BC)


.PHONY: all clean

all: $(lib) $(test)

$(test): test.o coll.o
	$(MPICC) $(CFLAGS) $(test_objs) $(lib_objs) -o $@ 

    
%.o: %.c
	$(MPICC) $(CFLAGS) -c $< -o $@

coll.o: coll.c coll.h
test.o: test.c

clean:
	@rm -rf *.o $(test)

