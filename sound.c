#include <portaudio.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <strings.h>
#include "ringbuffer.h"

#define SAMPLE_RATE 8000
#define FRAME_SIZE 160
#define RINGBUFFER_SIZE 1024 // 64
// 64 frames @ 20ms/frame = 1.2 sec
// 64 frames @ 320B/frame = 20kB


ringbuffer_t * speakers;
ringbuffer_t * microphone;

struct myAudio {
	ringbuffer_t * speakers;
	ringbuffer_t * microphone;
} audioIO;

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


static int paCallback( const void *inputBuffer, void *outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void *userData )
{
	long long moy = 0;
	int i;
	int16_t frame[160];
	int16_t * out = (int16_t *)outputBuffer;
	int16_t * in = (int16_t *)inputBuffer;
	int16_t * tmp;
  // Cast data passed through stream to our structure.
	struct myAudio * data = (struct myAudio *)userData;
	
  ringbuffer_t * dataIn = data->microphone;
  ringbuffer_t * dataOut = data->speakers;

	/* Data in */
	for(i=0;i<framesPerBuffer;i++) {
		moy += in[i];
	}
	moy/=framesPerBuffer;

  if(abs(moy) > 30) {
		printf("Microphone to ringbuffer\n");
		ringbuffer_write(dataIn, in);
	}
	
	/* Data out */
  if( (tmp=ringbuffer_read(dataOut, frame)) != NULL) {
		printf("Ringbuffer to speakers\n");
    for( i=0; i<framesPerBuffer; i++ ) {
      *out++ = frame[i];  // left
      *out++ = frame[i];  // right
    }    
  } else {
		printf("No sound.\n");
    bzero(out, sizeof(int16_t) * framesPerBuffer * 2);
  }
	
  return 0;
}

void audio_init() {
  //int fd = open("test.raw",O_RDONLY);
  speakers = ringbuffer_new(FRAME_SIZE, RINGBUFFER_SIZE);
  microphone = ringbuffer_new(FRAME_SIZE, RINGBUFFER_SIZE);
	
	audioIO.speakers = speakers;
	audioIO.microphone = microphone;
	
  Pa_Initialize();

  // Open an audio I/O stream.
  Pa_OpenDefaultStream( &stream,
      1,          // one input channels
      2,          // no output
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
      paCallback, /* this is your callback function */
      &audioIO ); /*This is a pointer that will be passed to
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
