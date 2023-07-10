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
#include <linux/fiemap.h>

#define NVME_IOCTL_IO_CMD _IOWR('N', 0x43, struct nvme_passthru_cmd)
#define MiB (uint64_t)(1024 * 1024)
#define GiB (1024 * MiB)


#define IO_NVM_ALLOCATE 	0x82
#define IO_LEN	4096
#define MAGIC_NUM	2621440
#define DEV_NAME "/dev/nvme1n1"

void call_flashalloc(struct fiemap* block_map, uint64_t offset, uint64_t len);
int flashalloc_cmd(int fd, uint32_t lba, uint32_t len);
