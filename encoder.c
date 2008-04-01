#include "encoder.h"
#include "celp/celp.h"
#include "gsm/gsm.h"
#include "sound.h"
#include <sys/types.h>
#include <arpa/inet.h>

#define FRAME_SIZE 160



int encode_speex(int16_t * input_frame, uint8_t nbframes, char * output) {
	int i, bytesToWrite, nbBytes;
  SpeexBits bits;
  void * state;
  int quality = 9; // 16.9kbps
  long long total;

  speex_bits_init(&bits);
  state = speex_encoder_init(&speex_nb_mode);
  speex_encoder_ctl(state, SPEEX_SET_QUALITY, &quality);
  speex_bits_reset(&bits);
  
  total = 0;
  for(i=0;i<5*160;i++) {
    total += input_frame[i];
  }
  total /= (5*160);
  if(abs(total) < 10)
    return 0;

  for(i=0;i<5;i++) {
	  speex_encode_int(state, input_frame + (i*160), &bits);
  }

	bytesToWrite = speex_bits_nbytes(&bits);
  nbBytes = speex_bits_write(&bits, output, bytesToWrite);
  speex_bits_destroy(&bits);
  speex_decoder_destroy(state);
	return nbBytes;
}

void send_audio(int32_t public_id, int32_t private_id, int32_t counter, char * data, int data_size, int s, const struct sockaddr * to) {
	char buff[1000];
	char * ptr = buff;

  if(data_size == 0) {
    printf("data_size == 0\n");
    //usleep(90000); // 100ms
    return;
  }
	*(int32_t *)ptr = GUINT32_TO_LE(0x0b00bef2);
  ptr += 4;
	*(int32_t *)ptr = GUINT32_TO_LE(private_id);
  ptr += 4;
	*(int32_t *)ptr = GUINT32_TO_LE(public_id);
  ptr += 4;
	*(int32_t *)ptr = counter;
  ptr += 4;
	* ptr = 5;
  ptr ++;

	memcpy(ptr, data, data_size); 
  printf("audio sent\n");
	sendto(s, buff, 245, 0, to, sizeof(*to));
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
