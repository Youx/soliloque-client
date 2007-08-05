#CFLAGS = `pkg-config --cflags glib-2.0` -ggdb
#LDFLAGS = `pkg-config --libs glib-2.0` -lm
CFLAGS = `pkg-config --cflags speex`
LDFLAGS = -lm `pkg-config --libs speex`

COPTS = -Wall -ansi

MODULES = crc.o highlevel.o main.o \
          acknowledge.o connection_request.o message2.o \
	  channel_list.o server_info.o player_list.o \
	  keepalive.o decoder.o toolbox.o new_player.o \
	  player_quit.o


default: freespeak

libcelp.a:
	make -C celp/
	mv celp/libcelp.a ./

libgsm.a:
	make -C gsm
	mv gsm/lib/libgsm.a ./

dataclean:
	-rm data/*

freespeak: $(MODULES) libcelp.a libgsm.a
	gcc $(LDFLAGS) $(COPTS) -o freespeak $(MODULES) libcelp.a libgsm.a

.c.o:
	gcc $(CFLAGS) $(COPTS) -c $<

clean: dataclean
	-make clean -C celp/
	-make clean -C gsm/
	-rm $(MODULES) 
	-rm freespeak
	-rm libcelp.a
	-rm libgsm.a
