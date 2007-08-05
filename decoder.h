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
#include "channel_list.h"

#include <stdlib.h>
#include <gsm.h>

void decode_audio_packet(void * input);

#endif
