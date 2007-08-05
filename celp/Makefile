CFLAGS = 
LDFLAGS = -lm -shared
MODULES = celp_decode.o celp_encode.o autohf.o \
	  csub.o gaincode.o ham.o lsp34.o lsptopc.o \
	  pctolsp2.o pctolsp3.o pgain.o pitchvq.o \
	  polefilt.o psearch.o ptcode.o zerofilt.o

default: $(MODULES)
	ar rc libcelp.a $(MODULES)
	ranlib libcelp.a

.c.o:
	gcc $(CFLAGS) $(COPTS) -c $<

clean:
	rm *.o
