/**
 *  file        : acknowledge.h
 *  license     : GPLV3
 *  copyright   : Hugo Camboulive
 *  description : This header contains information
 *   about functions and structures used to send an
 *   ACK message to a teamspeak server.
 */

#ifndef __ACKNOWLEDGE_H__
#define __ACKNOWLEDGE_H__

#include <glib.h>
#include <stdlib.h>
#include <string.h>


#define TYPE_ACKNOWLEDGE GINT32_TO_LE(0x0000bef1)


struct acknowledge {
  guint32 function;
  guint32 client_id[2];
  guint32 counter;
};

struct acknowledge * init_acknowledge(guint32 * client_id);


#endif