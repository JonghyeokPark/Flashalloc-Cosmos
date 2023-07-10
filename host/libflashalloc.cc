#include "libflashalloc.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int flashalloc_cmd(int fd, uint32_t lba, uint32_t len) {
  int err;
  struct nvme_passthru_cmd cmd;
  memset(&cmd, 0, sizeof(cmd));
  cmd.opcode = IO_NVM_ALLOCATE;
  cmd.nsid = 0;
  cmd.cdw10 = lba;
  cmd.cdw14 = len;

  err = ioctl(fd, NVME_IOCTL_IO_CMD, &cmd);
  return err;
}

void call_flashalloc(struct fiemap* blockmap, uint64_t offset, uint64_t len) {
  // open cosmos+ board
  int fd = open("/dev/nvme1n1", O_RDWR | O_DIRECT);
  if (fd < 0) {
    fprintf(stderr, "Cosmos+ Board Open Error!\n");
  }

  // call flashalloc
  for (__u32 i=0; i< blockmap->fm_mapped_extents; i++) {
    flashalloc_cmd(fd, blockmap->fm_extents[i].fe_physical / 4096 
                     , blockmap->fm_extents[i].fe_length / 4096);
  }

  return;
}
