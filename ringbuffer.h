/*
 *  ringbuffer.h
 *  Freespeak
 *
 *  Created by Hugo Camboulive on 03/03/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __RINGBUFFER_H__
#define __RINGBUFFER_H__

#include <inttypes.h>


typedef struct {
  int16_t * data;
  int writeidx;
  int readidx;
  
  int frame_size;  // ex 160 int16 per frame
  int buffer_size; // ex 64 frames
} ringbuffer_t;


int16_t * ringbuffer_read(ringbuffer_t * buffer);
int ringbuffer_write(ringbuffer_t * buffer, int16_t * data);
ringbuffer_t * ringbuffer_new(int framesize, int buffersize);

#endif