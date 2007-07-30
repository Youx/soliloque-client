/**
 * file 		:	crc.h
 * creator		:	Hugo Camboulive
 * description	:	Include to generate CRC32s
 */

#ifndef __CRC32_H__
#define __CRC32_H__

#include "compat.h"

guint32 crc_32(void * str, int length, guint32 poly);

#endif

