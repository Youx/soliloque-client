CFLAGS = `pkg-config --cflags glib-2.0`
LDFLAGS = `pkg-config --libs glib-2.0` -lm
COPTS = -Wall -ansi
MODULES = crc.o highlevel.o test_lowlevel.o main.o \
          acknowledge.o connection_request.o message2.o server_info.o

default: $(MODULES)
	gcc $(LDFLAGS) $(COPTS) -o test $(MODULES)

.c.o:
	gcc $(CFLAGS) $(COPTS) -c $<
	
clean:
	rm $(MODULES)
	rm test