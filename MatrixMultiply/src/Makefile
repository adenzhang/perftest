CC=cc
CFLAGS=-O3

INCDIR=
LNKDIR=
LIBS= -lblas

PROGRAMS = matmult

matmult: matmult.o
	$(CC) -o $@ $^ $(CFLAGS) $(LNKDIR) $(INCDIR) $(LIBS)
	
#################
%.o: %.c
	$(CC) -c $< $(CFLAGS) $(INCDIR)
	
.PHONY: clean

clean:
	rm -f *.o
	
veryclean:
	rm -f *.o $(PROGRAMS)
