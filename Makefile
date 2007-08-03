#CFLAGS = `pkg-config --cflags glib-2.0` -ggdb
#LDFLAGS = `pkg-config --libs glib-2.0` -lm
CFLAGS = `pkg-config --cflags speex`
LDFLAGS = -lm `pkg-config --libs speex`

COPTS = -Wall -ansi

MODULES = crc.o highlevel.o main.o \
          acknowledge.o connection_request.o message2.o \
	  channel_list.o server_info.o player_list.o \
	  keepalive.o decoder.o toolbox.o


default: freespeak
	
dataclean:
	@-rm data/*

freespeak: $(MODULES)
	gcc $(LDFLAGS) $(COPTS) -o freespeak $(MODULES)

.c.o:
	gcc $(CFLAGS) $(COPTS) -c $<

clean: dataclean
	@-rm $(MODULES) 
	@-rm freespeak
