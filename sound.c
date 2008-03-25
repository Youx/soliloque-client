#include <portaudio.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <strings.h>
#include "ringbuffer.h"

#define SAMPLE_RATE 8000
#define FRAME_SIZE 160
#define RINGBUFFER_SIZE 64
// 64 frames @ 20ms/frame = 1.2 sec
// 64 frames @ 320B/frame = 20kB


static ringbuffer_t * speakers;
ringbuffer_t * microphone;

PaStream *stream;


/* This routine will be called by the PortAudio engine when audio is needed.
 ** It may called at interrupt level on some machines so don't do anything
 ** that could mess up the system like calling malloc() or free().
 */ 
static int paOutputCallback( const void *inputBuffer, void *outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void *userData )
{
  // Cast data passed through stream to our structure.
  ringbuffer_t * data = (ringbuffer_t *)userData;
	int16_t frame[160];
	
  int16_t * out = (int16_t *)outputBuffer;
  unsigned int i;
  (void) inputBuffer; // Prevent unused variable warning.
  int16_t * tmp;

  if( (tmp = ringbuffer_read(data, frame)) != NULL) {
    for( i=0; i<framesPerBuffer; i++ ) {
      *out++ = tmp[i];  // left
      *out++ = tmp[i];  // right
    }    
  } else {
    bzero(out, sizeof(int16_t) * framesPerBuffer * 2);
  }

  return 0;
}


static int paInputCallback( const void *inputBuffer, void *outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void *userData )
{
	long long moy = 0;
	int i;
  // Cast data passed through stream to our structure.
  ringbuffer_t * data = (ringbuffer_t *)userData;
	for(i=0;i<framesPerBuffer;i++) {
		moy += ((int16_t *)inputBuffer)[i];
	}
	moy/=framesPerBuffer;

  if(abs(moy) > 30) {
		printf("write\n");
		ringbuffer_write(data, (int16_t *)inputBuffer);
	}
  return 0;
}

void audio_init() {
  //int fd = open("test.raw",O_RDONLY);
  speakers = ringbuffer_new(FRAME_SIZE, RINGBUFFER_SIZE);
  microphone = ringbuffer_new(FRAME_SIZE, RINGBUFFER_SIZE);
	
  Pa_Initialize();

  // Open an audio I/O stream.
  Pa_OpenDefaultStream( &stream,
      1,          // one input channels
      0,          // no output
      paInt16,
      SAMPLE_RATE,
			FRAME_SIZE,
      //256,        // frames per buffer, i.e. the number
                  // of sample frames that PortAudio will
                  // request from the callback. Many apps
                  // may want to use
                  // paFramesPerBufferUnspecified, which
                  // tells PortAudio to pick the best,
                  // possibly changing, buffer size.*/
      paInputCallback, /* this is your callback function */
      microphone ); /*This is a pointer that will be passed to
                 your callback*/

  Pa_StartStream( stream );
}

void audio_close() {
	Pa_StopStream(stream);
	Pa_CloseStream(stream);
	Pa_Terminate();
}





int audio_to_speakers(int16_t * data, int size) {
  return ringbuffer_write(speakers, data);
}
