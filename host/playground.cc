#include "libflashalloc.h"
#include "libmstream.h"
#include <stdlib.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int err, fd;
    unsigned int lba, len;

    if (argc > 4 || argc < 3) {
        fprintf(stderr, "Usage: %s dev lba len\n", argv[0]);
        fprintf(stderr, "\tdev - device path\n");
        fprintf(stderr, "\tlba - offset (4KiB-based)\n");
        fprintf(stderr, "\tlen - legnth\n");
        return 1;
    }

    char* path = argv[1];
    lba = strtoul(argv[2], NULL, 0);
    len = strtoul(argv[3], NULL, 0);

    fd = open(path, O_RDWR | O_DIRECT);
    if (fd <= 0) {
        fprintf(stderr, "[ERROR] Can not open %s\n", path);
        return 1;
    }

    flashalloc_cmd(fd, lba, len);

    return 0;
}
