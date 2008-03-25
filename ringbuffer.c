/*
 *  ringbuffer.c
 *  Freespeak
 *
 *  Created by Hugo Camboulive on 03/03/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "ringbuffer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int16_t * ringbuffer_read(ringbuffer_t * buffer, int16_t * dest) {
  if(buffer->readidx == buffer->writeidx) {
    return 0; // buffer empty
  } else {
		memcpy(dest, buffer->data + (buffer->readidx * buffer->frame_size), buffer->frame_size * sizeof(int16_t));
    //res = (buffer->data + (buffer->readidx * buffer->frame_size));
		buffer->readidx = (buffer->readidx + 1) % buffer->buffer_size;
    return dest;
  }
}

short ringbuffer_canRead(ringbuffer_t * buffer, int nbFrames) {
	int i;
	for(i=0;i<nbFrames;i++) {
		if((buffer->readidx + i) % buffer->buffer_size == buffer->writeidx)
			return 0;
	}
	return 1;
}

int ringbuffer_write(ringbuffer_t * buffer, int16_t * data) {
  if( ((buffer->writeidx + 1) % buffer->buffer_size) == buffer->readidx ) {
    fprintf(stderr, "Buffer full!\n");
    return 0; // buffer full
  } else {
    memcpy( (buffer->data + (buffer->writeidx * buffer->frame_size)), data, buffer->frame_size * sizeof(int16_t));
    buffer->writeidx++;
    buffer->writeidx %= buffer->buffer_size;
    return 1;
  }
}

ringbuffer_t * ringbuffer_new(int framesize, int buffersize) {
  ringbuffer_t * buff = (ringbuffer_t *)calloc(1, sizeof(ringbuffer_t));
  buff->readidx = 0;
  buff->writeidx = 0;
  buff->buffer_size = buffersize;
  buff->frame_size = framesize;
  buff->data = (int16_t *)calloc(framesize * buffersize, sizeof(int16_t));
  
  return buff;
}
