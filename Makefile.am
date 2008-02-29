CC=g++
bin_PROGRAMS = freespeak
freespeak_SOURCES = crc.c highlevel.c main.c acknowledge.c connection_request.c message2.c channel_list.c server_info.c player_list.c keepalive.c decoder.c toolbox.c new_player.c player_quit.c sound.c
SUBDIRS = celp gui gsm
LDADD = $(top_builddir)/celp/libcelp.a $(top_builddir)/gui/libgui.a $(top_builddir)/gsm/libgsm.a $(SPEEX_LIBS) $(WX_LIBS)
INCLUDES = -I./include/ $(SPEEX_CFLAGS) -I./gsm/include/ $(WX_CFLAGS) $(WX_CXXFLAGS) $(WX_CPPFLAGS)
