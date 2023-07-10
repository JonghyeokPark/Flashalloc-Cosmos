#define _GNU_SOURCE
#include "libmstream.h"

// lba: 4KiB-based offset
// len: The number of 4KiB-based pages
int mstream_write(int fd, uint32_t stream_id, uint32_t slba, uint32_t nblocks, const void* buffer)
{
	int err;
  struct nvme_passthru_cmd cmd;

  memset(&cmd, 0, sizeof(cmd));
  cmd.opcode = IO_NVM_STREAM;
  cmd.nsid = 0;
  cmd.addr = (uint64_t)buffer;
  cmd.cdw10 = slba;

  //cmd.cdw10 = slba & 0xFFFFFFFF;         // Starting LBA (Lower 32 bits)
  //cmd.cdw11 = (slba >> 32) & 0xFFFFFFFF; // Starting LBA (Upper 32 bits)

  cmd.cdw12 = nblocks;
  cmd.cdw15 = stream_id; //(stream_id & 0xFFFF) << 16; // Set Stream ID in CDW12 

  return ioctl(fd, NVME_IOCTL_IO_CMD, &cmd);
}

int mstream_set_stream(int fd, uint32_t stream_id, uint32_t slba, uint32_t nblocks) {

  int err;
  struct nvme_passthru_cmd cmd;

  memset(&cmd, 0, sizeof(cmd));
  cmd.opcode = IO_NVM_STREAM;
  cmd.nsid = 0;
  cmd.cdw10 = slba;

  //cmd.cdw10 = slba & 0xFFFFFFFF;         // Starting LBA (Lower 32 bits)
  //cmd.cdw11 = (slba >> 32) & 0xFFFFFFFF; // Starting LBA (Upper 32 bits)

  cmd.cdw12 = nblocks;
  cmd.cdw15 = stream_id; //(stream_id & 0xFFFF) << 16; // Set Stream ID in CDW12 

  return ioctl(fd, NVME_IOCTL_IO_CMD, &cmd);

}
