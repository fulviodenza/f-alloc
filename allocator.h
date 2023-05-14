#ifndef HEADER_FILE
#define HEADER_FILE

#define BLOCK_SIZE 4096
#define NULL ((void *)0)

#include <stdint.h>

void *falloc(size_t size);
void ffree(void *ptr);

#endif
