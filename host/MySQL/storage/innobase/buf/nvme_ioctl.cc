#include <fcntl.h>
#include <inttypes.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>

#include "nvme.h"

#define NVME_IOCTL_IO_CMD _IOWR('N', 0x43, struct nvme_passthru_cmd)

// #define BLKDISCARD _IO(0x12, 119)

static int fd = 0;

struct nvme_passthru_cmd {
  __u8 opcode;
  __u8 flags;
  __u16 rsvd1;
  __u32 nsid;
  __u32 cdw2;
  __u32 cdw3;
  __u64 metadata;
  __u64 addr;
  __u32 metadata_len;
  __u32 data_len;
  __u32 cdw10;
  __u32 cdw11;
  __u32 cdw12;
  __u32 cdw13;
  __u32 cdw14;
  __u32 cdw15;
  __u32 timeout_ms;
  __u32 result;
};

#ifdef DEBUG
void show_command(int opcode, void **buf, __u32 data_len, __u32 lba,
                  int isQuery) {
  printf("opcode       : %02x\n", opcode);
  printf("flags        : %02x\n", 0);
  printf("rsvd1        : %04x\n", 0);
  printf("nsid         : %08x\n", 0);
  printf("cdw2         : %08x\n", 0);
  printf("cdw3         : %08x\n", 0);
  printf("data_len     : %08x\n", data_len);
  printf("metadata_len : %08x\n", 0);
  printf("addr         : %" PRIx64 "\n", (uint64_t)(uintptr_t)buf);
  printf("metadata     : %08x\n", 0);
  printf("cdw10        : %08x\n", lba);
  printf("cdw11        : %08x\n", 0);
  printf("cdw12        : %08x\n", 0);
  printf("cdw13        : %08x\n", (isQuery));
  printf("cdw14        : %08x\n", 0);
  printf("cdw15        : %08x\n", 0);
  printf("timeout_ms   : %08x\n", 0);
}
#endif

int init_ioctl(const char *path) {
  if (!fd) {
    fd = open(path, O_RDWR | O_DIRECT);
    if (fd <= 0) {
      printf("[ERROR] Can not open %s\n", path);
      return 1;
    }
  }

  return 0;
}

int submit_multiple_allocate(char *buffer) {
  struct nvme_passthru_cmd cmd = {
      .opcode = IO_NVM_WRITE,
      .flags = 0,
      .rsvd1 = 0,
      .nsid = 0,
      .cdw2 = 0,
      .cdw3 = 0,
      .metadata = 0,
      .addr = (__u64)(uintptr_t)buffer,
      .metadata_len = 0,
      .data_len = (16 * 1024),
      .cdw10 = 0,
      .cdw11 = 0,
      .cdw12 = (3),
      .cdw13 = 1,
      .cdw14 = 0,
      .cdw15 = 0,
      .timeout_ms = 3000,
      .result = 0,
  };
  int err = ioctl(fd, NVME_IOCTL_IO_CMD, &cmd);
  return err;
}

int submit_ioctl(int opcode, char *query, __u32 data_len, __u32 lba,
                 char **result) {
  int err;
  void *ioctl_buf = NULL;

  switch (opcode) {
    case IO_NVM_SET_LEVEL:
    case IO_NVM_SET_FILE:
      break;
    case IO_NVM_PRINT_STAT:
    case IO_NVM_RESET:
      data_len = 0;
      break;
    case IO_NVM_ALLOCATE:
    case IO_NVM_DEALLOCATE:
      break;
    default:
      break;
  }

  err = posix_memalign(&ioctl_buf, getpagesize(), data_len);
  if (err) {
    printf("Can not allocate payload \n");
    return err;
  }
  if (query && opcode == IO_NVM_WRITE) {
    memcpy(ioctl_buf, query, data_len);
  }

#ifdef DEBUG
  // print command setting when compiled with DEBUG option.
  show_command(opcode, ioctl_buf, data_len, lba, 0);
#endif
  struct nvme_passthru_cmd cmd = {
      .opcode = (uint8_t)opcode,
      .flags = 0,
      .rsvd1 = 0,
      .nsid = 0,
      .cdw2 = 0,
      .cdw3 = 0,
      .metadata = 0,
      .addr = (__u64)(uintptr_t)ioctl_buf,
      .metadata_len = 0,
      .data_len = 0,
      .cdw10 = lba,
      .cdw11 = 0,
      .cdw12 = 0,
      .cdw13 = 0,
      .cdw14 = data_len,
      .cdw15 = 0,
      .timeout_ms = 0,
      .result = 0,
  };

  err = ioctl(fd, NVME_IOCTL_IO_CMD, &cmd);
  // fsync(fd);

  if (ioctl_buf) {
    if (err == 0 && opcode == 2 && result != NULL) {
      *result = (char *)ioctl_buf;
    }
    free(ioctl_buf);
  }
  //	printf("ERRNO: %d\n",err);
  return err;
}

void submit_dummy_discard() {
  //   uint64_t range[2] = {0, 1024};
  perror("discard");
}
