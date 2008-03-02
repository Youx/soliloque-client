#include <portaudio.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <strings.h>


#define SAMPLE_RATE 8000
#define FRAME_SIZE 160
#define RINGBUFFER_SIZE 64
// 64 frames @ 20ms/frame = 1.2 sec
// 64 frames @ 320B/frame = 20kB

typedef struct
{
  // TODO : Implement this using a ring buffer...
  int16_t data[RINGBUFFER_SIZE][FRAME_SIZE];
  int writeidx;
  int readidx;
  //char state;
}   
audio_out;

static audio_out speakers;
PaStream *stream;


static int16_t * read_data_from_buffer(audio_out * buffer) {
  int16_t * res;
  if(buffer->readidx == buffer->writeidx) {
    return NULL; // buffer empty
  } else {
    res = buffer->data[buffer->readidx];
    buffer->readidx++;
    buffer->readidx %= RINGBUFFER_SIZE;
    return res;
  }
}

static int write_data_to_buffer(audio_out * buffer, int16_t * data) {
  if( ((buffer->writeidx + 1) % RINGBUFFER_SIZE) == buffer->readidx ) {
    fprintf(stderr, "Buffer full!\n");
    return 0; // buffer full
  } else {
    memcpy(buffer->data[buffer->writeidx], data, FRAME_SIZE * sizeof(int16_t));
    buffer->writeidx++;
    buffer->writeidx %= RINGBUFFER_SIZE;
    return 1;
  }
}



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
  int16_t * tmp;
  if( (tmp = read_data_from_buffer(data)) != NULL) {
    for( i=0; i<framesPerBuffer; i++ ) {
      *out++ = tmp[i];  // left
      *out++ = tmp[i];  // right
    }    
  } else {
    bzero(out, sizeof(int16_t) * framesPerBuffer * 2);
  }

  return 0;
}


void audio_init() {
  //int fd = open("test.raw",O_RDONLY);
	bzero(speakers.data, FRAME_SIZE * sizeof(int16_t));
  speakers.writeidx = 0;
  speakers.readidx = 0;
	
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





int audio_to_speakers(int16_t * data) {
  return write_data_to_buffer(&speakers, data);
}
