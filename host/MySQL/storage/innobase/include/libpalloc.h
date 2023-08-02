#include <stdint.h>
#include <sys/ioctl.h>

int init_palloc(const char *path);
void pallocate(uint32_t lba, uint32_t len);
void pallocate_prepare(uint32_t lba, uint32_t len);
void pallocate_submit();

void print_stat();
void reset();

// SALLOCATE INTERFACE //
void call_sallocate(struct fiemap* fiemap, uint64_t offset);
void dump_fiemap(struct fiemap* fiemap, const char* filename);
struct fiemap* read_fiemap(int fd);

void desallocate(uint32_t lba, uint32_t len);
void call_desallocate(struct fiemap* fiemap, uint64_t offset);

