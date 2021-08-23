#include "protocol.h"

#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>


main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s /shm-path string\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *shmpath = argv[1];
    char *string = argv[2];
    size_t len = strlen(string);

    if (len > BUFFER_SIZE) {
        fprintf(stderr, "String is too long\n");
        exit(EXIT_FAILURE);
    }

    /* Open the existing shared memory object and map it
       into the caller's address space. */

    int fd = shm_open(shmpath, O_CREAT | O_EXCL | O_RDWR,
                      S_IRUSR | S_IWUSR);
    if (fd == -1)
        perror("shm_open");

    if (ftruncate(fd, sizeof(struct shmbuf)) == -1)
        perror("ftruncate");

    /* Map the object into the caller's address space. */

    struct shmbuf *data = mmap(NULL, sizeof(*data),
                               PROT_READ | PROT_WRITE,
                               MAP_SHARED, fd, 0);
    if (data == MAP_FAILED)
        perror("mmap");


    data->size = len;
    memcpy(&data->buffer, string, len);


    munmap(data, SIZE);

    close(fd);

    return EXIT_SUCCESS;
}