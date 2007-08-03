#ifndef __TOOLBOX_H__
#define __TOOLBOX_H__

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void dump(void * str, int len, char * filename);
void append(void * str, int len, char * filename);

#endif
