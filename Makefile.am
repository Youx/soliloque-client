bin_PROGRAMS = freespeak
freespeak_SOURCES = crc.c highlevel.c main.c acknowledge.c connection_request.c message2.c channel_list.c server_info.c player_list.c keepalive.c decoder.c toolbox.c new_player.c player_quit.c
SUBDIRS = celp gui
LDADD = $(top_builddir)/celp/libcelp.a $(top_builddir)/gui/libgui.a $(SPEEX_LIBS)
INCLUDES = -I./include/ $(SPEEX_CFLAGS)
