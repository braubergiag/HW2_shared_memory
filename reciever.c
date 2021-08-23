#include "protocol.h"
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <semaphore.h>

int main(int argc, char * argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage : %s /shm_path string \n", argv[0]);
        exit(EXIT_FAILURE);
    }
    char * shmpath= argv[1];
    int fd = shm_open(shmpath,  O_RDWR, 0);
    if (fd == -1) {
        perror("shm_open()");
        exit(EXIT_FAILURE);
    }



    struct shmbuf *data =
            mmap(NULL, sizeof (*data), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (data == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    printf("worker: mapped address: %p\n", data);

    printf("worker: waiting initial data\n");
    while (atomic_load(&data->state) != 1) {}
    printf("worker: acquire initial data\n");

    write(STDOUT_FILENO,&data->buffer,data->size);
    write(STDOUT_FILENO,"\n",1);

    printf("worker: release data\n");
    atomic_store(&data->state, 2);
    munmap(data,sizeof (*data));
    close(fd);

    return EXIT_SUCCESS;

}

