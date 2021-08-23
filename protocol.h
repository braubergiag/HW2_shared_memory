//
// Created by marshall on 22.08.2021.
//
#include <stdlib.h>
#include <stddef.h>
#include <stdatomic.h>
#ifndef SHARED_MEM_PROTOCOL_H
#define SHARED_MEM_PROTOCOL_H

#define NAME "/shmem_example"
#define  BUFFER_SIZE 1024
#define  NUM 3
#define SIZE (NUM * sizeof(int))
struct shmbuf {
    char buffer[BUFFER_SIZE];
    atomic_int state;
    size_t size;
};
struct Data {
    atomic_int state;
    int data[];
};
#define SEM_PRODUCER_NAME "/producer"
#define SEM_CONSUMER_NAME "/consumer"
#endif //SHARED_MEM_PROTOCOL_H
