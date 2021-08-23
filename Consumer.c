#include "shmbuf.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main(int argc, char * argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Usage: %s /shm-path \n", argv[0]);
        exit(EXIT_FAILURE);
    }
    char * path = argv[1];

    int fd = shm_open(path, O_RDONLY, 0666);
    if (fd < 0 && errno != ENOENT) {
        perror("shm_open()");
        exit(EXIT_FAILURE);
    }

    struct shmbuf *data =(struct shmbuf *)
            mmap(NULL, sizeof ( struct shmbuf), PROT_READ, MAP_SHARED, fd, 0);

    if (data == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    printf("Consumer: mapped address: %p\n", data);

    write(STDOUT_FILENO,&data->buffer,data->size);
    write(STDOUT_FILENO,"\n",1);
    printf("Consumer: job is done\n");

   if (munmap(data,sizeof ( struct shmbuf)) == -1) {
       perror("munmap");
       exit(EXIT_FAILURE);

   };
    shm_unlink(path);
    close(fd);

    return EXIT_SUCCESS;

}

