// this will be used as OPCODE
#include <linux/types.h>
#include <stdint.h>
#define IO_NVM_WRITE 0x01
#define IO_NVM_READ 0x02

#define IO_NVM_PRINT_STAT 0x80
#define IO_NVM_RESET 0x81
#define IO_NVM_ALLOCATE 0x82
#define IO_NVM_DEALLOCATE 0x85

#define IO_NVM_SET_LEVEL 0x83
#define IO_NVM_SET_FILE 0x84

#define IO_LEN 4096
#define MAGIC_NUM 2621440

int init_ioctl(const char *path);
int submit_ioctl(int opcode, char *query, __u32 data_len, __u32 lba,
                 char **result);
int submit_multiple_allocate(char *buffer);
void submit_dummy_discard();
