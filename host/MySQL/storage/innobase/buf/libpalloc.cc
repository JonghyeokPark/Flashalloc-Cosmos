#include "libpalloc.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <linux/fiemap.h>
#include <linux/fs.h>

#include "nvme.h"

#define QUERY_LEN 4096
#define MiB (uint64_t)(1024 * 1024)
#define GiB (1024 * MiB)
static char *buffer;
static uint32_t num_pairs;

int init_palloc(const char *path) {
  int ret = posix_memalign((void **)&buffer, 4096, 16384);
  if (ret != 0) {
    printf("[DEBUG] memalign error\n");
  }
  num_pairs = 0;
  return init_ioctl(path);
}

// lba: 4KiB-based offset
// len: The number of 4KiB-based pages
void pallocate(uint32_t lba, uint32_t len) {
  int err;
  err = submit_ioctl(IO_NVM_ALLOCATE, NULL, len, lba, 0);
  if (err != 0) {
    printf("[DEBUG] WRITE ERROR While submitting Query %u %u\n", lba, len);
  }
}

// lba: 4KiB-based offset
// len: The number of 4KiB-based pages
void desallocate(uint32_t lba, uint32_t len) {
  int err;
  err = submit_ioctl(IO_NVM_DEALLOCATE, NULL, len, lba, 0);
  if (err != 0) {
    printf("[DEBUG] DESALLOCATE ERROR While submitting Query %u %u\n", lba, len);
  }
}

void SwapBytes(void *pv, size_t n) {
  char *p = (char *)pv;
  size_t lo, hi;
  for (lo = 0, hi = n - 1; hi > lo; lo++, hi--) {
    char tmp = p[lo];
    p[lo] = p[hi];
    p[hi] = tmp;
  }
}
void pallocate_prepare(uint32_t lba, uint32_t len) {
  // SwapBytes(&lba, sizeof(uint32_t));
  // SwapBytes(&len, sizeof(uint32_t));
  memcpy(buffer + 4 + num_pairs * (sizeof(uint32_t) * 2), &lba,
         sizeof(uint32_t));
  memcpy(buffer + 4 + num_pairs * (sizeof(uint32_t) * 2) + sizeof(uint32_t),
         &len, sizeof(uint32_t));
  // sprintf(buffer + 4 + num_pairs * 8, lba, sizeof(uint32_t));
  // sprintf(buffer + 4 + num_pairs * 8 + 4, &len, sizeof(uint32_t));
  num_pairs++;
}
void pallocate_submit() {
  // SwapBytes(&num_pairs, sizeof(uint32_t));
  memcpy(buffer, &num_pairs, sizeof(uint32_t));
  submit_multiple_allocate(buffer);
  num_pairs = posix_memalign((void **)&buffer, 4096, 16384);
  num_pairs = 0;
  free((void *)buffer);
}

void print_stat() {
  int err;
  err = submit_ioctl(IO_NVM_PRINT_STAT, NULL, 0, MAGIC_NUM, 0);
  if (err != 0) {
    printf("[DEBUG] PRINT STAT ERROR\n");
  }
}

void reset() {
  int err;
  err = submit_ioctl(IO_NVM_RESET, NULL, 0, MAGIC_NUM, 0);

  if (err != 0) {
    printf("[DEBUG] RESET ERROR\n");
  }
}

void set_level() {
  int err;
  err = submit_ioctl(IO_NVM_SET_LEVEL, NULL, 0, MAGIC_NUM, 0);

  if (err != 0) {
    printf("[DEBUG] RESET ERROR\n");
  }
}

void set_file() {
  int err;
  err = submit_ioctl(IO_NVM_SET_FILE, NULL, 0, MAGIC_NUM, 0);

  if (err != 0) {
    printf("[DEBUG] RESET ERROR\n");
  }
}


// SALLOCATE INTERFACE //
struct fiemap* read_fiemap(int fd) {
  struct fiemap* fiemap;
  int extents_size;

  if ((fiemap = (struct fiemap*)malloc(sizeof(struct fiemap))) == NULL) {
    fprintf(stderr, "Out of memory allocating fiemap\n");
    return NULL;
  }
  memset(fiemap, 0, sizeof(struct fiemap));

  fiemap->fm_start = 0;
  fiemap->fm_length = ~0; /* Lazy */
  fiemap->fm_flags = 0;
  fiemap->fm_extent_count = 0;
  fiemap->fm_mapped_extents = 0;

  /* Find out how many extents there are */
  if (ioctl(fd, FS_IOC_FIEMAP, fiemap) < 0) {
    fprintf(stderr, "fiemap ioctl() failed\n");
    return NULL;
  }

  /* Read in the extents */
  extents_size = sizeof(struct fiemap_extent) * (fiemap->fm_mapped_extents);

  /* Resize fiemap to allow us to read in the extents */
  if ((fiemap = (struct fiemap*)realloc(
           fiemap, sizeof(struct fiemap) + extents_size)) == NULL) {
    fprintf(stderr, "Out of memory allocating fiemap\n");
    return NULL;
  }

  memset(fiemap->fm_extents, 0, extents_size);
  fiemap->fm_extent_count = fiemap->fm_mapped_extents;
  fiemap->fm_mapped_extents = 0;

  if (ioctl(fd, FS_IOC_FIEMAP, fiemap) < 0) {
    fprintf(stderr, "fiemap ioctl() failed\n");
    return NULL;
  }

  return fiemap;
}

void dump_fiemap(struct fiemap* fiemap, const char* filename) {
  __u32 i;

  printf("File %s has %d extents:\n", filename, fiemap->fm_mapped_extents);

  printf("#\tLogical          Physical         Length           Flags\n");
  for (i = 0; i < fiemap->fm_mapped_extents; i++) {
    printf("%d:\t%llu\t %llu\t %llu\t %u\n", i,
           (fiemap->fm_extents[i].fe_logical / 4096),
           (fiemap->fm_extents[i].fe_physical / 4096),
           (fiemap->fm_extents[i].fe_length / 4096),
           fiemap->fm_extents[i].fe_flags);
  }
  printf("\n");
}

void call_sallocate(struct fiemap* fiemap, uint64_t offset) {
#ifndef COSMOS_DEV
#define COSMOS_DEV "/dev/nvme1n1"
#endif

  init_palloc(COSMOS_DEV);
  // (jhpark): simple sallocate call interface
  //fprintf(stderr, "[DEBUG] sallocate offset %u length %u \n", fiemap->fm_extents[0].fe_physical / 4096
  //                                                              , fiemap->fm_extents[0].fe_length / 4096); 

  //pallocate(fiemap->fm_extents[0].fe_physical / 4096, 256);

  uint64_t length = 0;
  for (__u32 i = 0; i < fiemap->fm_mapped_extents; i++) {
      pallocate(fiemap->fm_extents[i].fe_physical / 4096,
             (fiemap->fm_extents[i].fe_length / 4096 ));   
  }


/*
  uint64_t length = 0;
  for (__u32 i = 0; i < fiemap->fm_mapped_extents; i++) {

  // TODO(jhpark): we fix the sallocate call only one !!!! fix this problem; set DWB file size as 2MB
  //for (__u32 i = 0; i < 1; i++) {
#ifdef SALLOCATE_OPTIMIZATION 
  // (jhpark): 64MB sst file -> call sallocate with 2MB chunk size
        __u32 j = 0;
        for (j=0; j < (fiemap->fm_extents[i].fe_length / 4096); j += 512) {
          pallocate((fiemap->fm_extents[i].fe_physical / 4096) + j, 512);
        }
#else
//      fprintf(stderr, "[DEBUG] sallocate offset %u length %u \n", fiemap->fm_extents[i].fe_physical / 4096
//                                                                , fiemap->fm_extents[i].fe_length / 4096);
      // (jhpark): DWB use only 1MB  
      if ((fiemap->fm_extents[i].fe_length / 4096 ) / 2 == 256) {
        pallocate(fiemap->fm_extents[i].fe_physical / 4096,
             (fiemap->fm_extents[i].fe_length / 4096 )/ 2);
      }

      //pallocate(fiemap->fm_extents[i].fe_physical / 4096,
      //          (fiemap->fm_extents[i].fe_length / 4096 )/ 2);
#endif

#if 0
      printf("[DEBUG] Sallocate prepare lba %llu, length %llu\n",
             fiemap->fm_extents[i].fe_physical / 4096,
             fiemap->fm_extents[i].fe_length / 4096);
#endif

    length += fiemap->fm_extents[i].fe_length;
  }
*/

}

void call_desallocate(struct fiemap* fiemap, uint64_t offset) {
#ifndef COSMOS_DEV
#define COSMOS_DEV "/dev/nvme1n1"
#endif

  init_palloc(COSMOS_DEV);

  uint64_t length = 0;
  for (__u32 i = 0; i < fiemap->fm_mapped_extents; i++) {
//      fprintf(stderr, "[DEBUG] desallocate offset %u length %u \n", fiemap->fm_extents[i].fe_physical / 4096
//                                                                , fiemap->fm_extents[i].fe_length / 4096);
//    for (__u32 i = 0; i < 1; i++) {

      desallocate(fiemap->fm_extents[i].fe_physical / 4096,
                fiemap->fm_extents[i].fe_length / 4096);
#if 0
      printf("[DEBUG] Sallocate prepare lba %llu, length %llu\n",
             fiemap->fm_extents[i].fe_physical / 4096,
             fiemap->fm_extents[i].fe_length / 4096);
#endif

    length += fiemap->fm_extents[i].fe_length;
  }
}

