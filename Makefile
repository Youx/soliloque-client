#CFLAGS = `pkg-config --cflags glib-2.0` -ggdb
#LDFLAGS = `pkg-config --libs glib-2.0` -lm
CFLAGS = -I./
LDFLAGS = -lm

COPTS = -Wall -ansi
MODULES = crc.o highlevel.o test_lowlevel.o main.o \
          acknowledge.o connection_request.o message2.o \
	  channel_list.o server_info.o player_list.o

default: $(MODULES)
	gcc $(LDFLAGS) $(COPTS) -o test $(MODULES)

.c.o:
	gcc $(CFLAGS) $(COPTS) -c $<
	
clean:
	rm $(MODULES)
	rm test
