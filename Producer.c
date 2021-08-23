#include "shmbuf.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s /shm_path /string \n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *path = argv[1];
    char *string = argv[2];

    size_t len = strlen(string);

    if (len > BUFFER_SIZE) {
        fprintf(stderr, "String is too long\n");
        exit(EXIT_FAILURE);
    }

    int fd = shm_open(path, O_CREAT | O_EXCL  | O_RDWR,
                      S_IRUSR | S_IWUSR);
    if (fd == -1)
        perror("shm_open");

    if (ftruncate(fd, sizeof(struct shmbuf)) == -1)
        perror("ftruncate");


    struct shmbuf *data = (struct shmbuf *) mmap(NULL, sizeof(struct shmbuf),
                               PROT_READ | PROT_WRITE,
                               MAP_SHARED, fd, 0);
    if (data == MAP_FAILED){
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    data->size = len;
    memcpy(&data->buffer, string, len);
    printf("Producer: release initial data\n");


    if (munmap(data,sizeof ( struct shmbuf)) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);

    };

    close(fd);
    printf("Producer: job is done.\n");
    return EXIT_SUCCESS;
}