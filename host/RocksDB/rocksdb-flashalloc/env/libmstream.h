#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdint.h>

#include <inttypes.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/nvme_ioctl.h>

#define NVME_IOCTL_IO_CMD _IOWR('N', 0x43, struct nvme_passthru_cmd)
#define MiB (uint64_t)(1024 * 1024)
#define GiB (1024 * MiB)


#define IO_NVM_STREAM 0x83
#define DEV_NAME "/dev/nvme1n1"

int mstream_write(int fd, uint32_t stream_id, uint32_t slba, uint32_t nblocks, const void* buffer);
int mstream_set_stream(int fd, uint32_t stream_id, uint32_t slba, uint32_t nblocks);
