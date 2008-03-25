#include "encoder.h"
#include "celp/celp.h"
#include "gsm/gsm.h"
#include "sound.h"
#include <sys/types.h>
#include <arpa/inet.h>

#define FRAME_SIZE 160


char encode_speex(int16_t * input_frame, uint8_t nbframes, char * output) {
	int i, bytesToWrite, nbBytes;
  SpeexBits bits;
  void * state;
  int quality = 6; // 16.4

  speex_bits_init(&bits);
  state = speex_encoder_init(&speex_nb_mode);
  speex_encoder_ctl(state, SPEEX_SET_QUALITY, &quality);
  speex_bits_reset(&bits);

  for(i=0;i<5;i++) {
	  speex_encode_int(state, input_frame + (i*160), &bits);
  }

	bytesToWrite = speex_bits_nbytes(&bits);
	printf("Encoded size : %i bytes\n", bytesToWrite);
  nbBytes = speex_bits_write(&bits, output, bytesToWrite);

	return nbBytes;
}

void send_audio(int32_t public_id, int32_t private_id, int32_t counter, char * data, char data_size, int s, const struct sockaddr * to) {
	char buff[1000];
	char * ptr = buff;
	
	*(int32_t * )ptr++ = GUINT32_TO_LE(0x0b00bef2);
	*(int32_t *)ptr++ = private_id;
	*(int32_t *)ptr++ = public_id;
	*(int32_t *)ptr++ = counter;
	* ptr++ = 5;
	memcpy(ptr, data, data_size);
	sendto(s, buff, 17+data_size, 0, to, sizeof(*to));
}

/*void encode_audio_packet(int16_t * input) {
  uint8_t nbframes;
  int16_t * out;
  char * ptr = (char *)input;
  uint8_t codec;
	int i;
	
	
  ptr+=3;
  codec = *ptr;
  ptr+=19;
  nbframes = *ptr; 
  ptr++;

	//  printf(">>>> CODEC : 0x%x\n", *((char *)(&codec)));
  switch(codec) {
    case CODEC_SPEEX_25_9:
      out = decode_speex(ptr, nbframes, 492);
      break;
    case CODEC_SPEEX_19_6:
      out = decode_speex(ptr, nbframes, 364);
      break;
    case CODEC_SPEEX_16_3:
      out = decode_speex(ptr, nbframes, 300);
      break;
    case CODEC_SPEEX_12_3:
      out = decode_speex(ptr, nbframes, 220);
      break;
    case CODEC_SPEEX_9_3:
      out = decode_speex(ptr, nbframes, 160);
      break;
    case CODEC_SPEEX_7_2:
      out = decode_speex(ptr, nbframes, 119);
      break;
    case CODEC_SPEEX_5_2:
      out = decode_speex(ptr, nbframes, 79);
      break;
    case CODEC_SPEEX_3_4:
      out = decode_speex(ptr, nbframes, 43);
      break;
    case CODEC_GSM_14_8:
      nbframes = 5;
      out = decode_gsm(ptr,nbframes);
      break;
    case CODEC_GSM_16_4:
      nbframes = 3;
      out = decode_gsm(ptr,nbframes);
      break;
    case CODEC_CELP_6_3:
      nbframes = 3;
      out = decode_celp(ptr, nbframes);
      break;
    case CODEC_CELP_5_1:
      nbframes = 9;
      out = decode_celp(ptr, nbframes);
      break;
    default:
      nbframes = 0;
      out = NULL;
  }
  append(out, sizeof(short) * FRAME_SIZE * nbframes, "data/decoded_audio.raw");
	
	for(i=0;i<nbframes;i++) {
		while(!audio_to_speakers(out+(FRAME_SIZE*i), FRAME_SIZE));
	}
  free(out);
}*/
