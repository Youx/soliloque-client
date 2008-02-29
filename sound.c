#include <portaudio.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <strings.h>


#define SAMPLE_RATE 8000
#define FRAME_SIZE 160

typedef struct
{
  int16_t data[FRAME_SIZE];
  char state;
}   
audio_out;

static audio_out speakers;
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
  audio_out *data = (audio_out*)userData; 
  int16_t *out = (int16_t *)outputBuffer;
  unsigned int i;
  (void) inputBuffer; // Prevent unused variable warning.
  if(data->state == 1) {
    for( i=0; i<framesPerBuffer; i++ ) {
      *out++ = data->data[i];  // left
      *out++ = data->data[i];  // right
    }
    data->state = 2;
  } else {
	  /*for( i=0; i<framesPerBuffer; i++ ) {
      *out++ = 0;  // left
      *out++ = 0;  // right
    }*/
		//printf("framesPerBuffer %i\n", framesPerBuffer);
		bzero(out, sizeof(int16_t) * framesPerBuffer * 2);
	}
  return 0;
}


void audio_init() {
  //int fd = open("test.raw",O_RDONLY);
	bzero(speakers.data, FRAME_SIZE * sizeof(int16_t));
  speakers.state = 2;
	
  Pa_Initialize();

  // Open an audio I/O stream.
  Pa_OpenDefaultStream( &stream,
      0,          // no input channels
      2,          // stereo output
      //paFloat32,  // 32 bit floating point output
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
      paOutputCallback, /* this is your callback function */
      &speakers ); /*This is a pointer that will be passed to
                 your callback*/

  Pa_StartStream( stream );
}

void audio_close() {
	Pa_StopStream(stream);
	Pa_CloseStream(stream);
	Pa_Terminate();
} 

int audio_to_speakers(int16_t * data, int size) {
	if(speakers.state == 2) {
		bzero(speakers.data, FRAME_SIZE * sizeof(int16_t));
		memcpy(speakers.data, data, FRAME_SIZE * sizeof(int16_t));
		speakers.state = 1;
		return 1;
	} else {
		return 0;
	}
}
