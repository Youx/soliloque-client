#ifndef __DECODER_H__
#define __DECODER_H__


#include <speex/speex.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "compat.h"
#include "toolbox.h"


void decode_audio_packet(void * input);

#endif
