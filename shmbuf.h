
#include <stdlib.h>
#include <stddef.h>
#ifndef SHARED_BUF
#define SHARED_BUF

#define  BUFFER_SIZE 1024

struct shmbuf {
    char buffer[BUFFER_SIZE];
    size_t size;
};


#endif
