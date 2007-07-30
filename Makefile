#CFLAGS = `pkg-config --cflags glib-2.0` -ggdb
#LDFLAGS = `pkg-config --libs glib-2.0` -lm
CFLAGS = -I./
LDFLAGS = -lm

COPTS = -Wall -ansi
MODULES = crc.o highlevel.o main.o \
          acknowledge.o connection_request.o message2.o \
	  channel_list.o server_info.o player_list.o \
	  keepalive.o

default: freespeak decoder
	
freespeak: $(MODULES)
	gcc $(LDFLAGS) $(COPTS) -o freespeak $(MODULES)

.c.o:
	gcc $(CFLAGS) $(COPTS) -c $<

decoder: test.o crc.o
	gcc -lspeex $(LDFLAGS) $(COPTS) -o decoder test.o crc.o

clean:
	rm $(MODULES) test.o
	rm freespeak
	rm decoder
