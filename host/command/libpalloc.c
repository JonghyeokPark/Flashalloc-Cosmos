#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdint.h>

#include "nvme.h"
#include "libpalloc.h"

#define QUERY_LEN 4096
#define MiB (uint64_t)(1024 * 1024)
#define GiB (1024 * MiB)
static char *buffer;
static uint32_t num_pairs;

int init_palloc(const char *path)
{
	int ret = posix_memalign((void **)&buffer, 4096, 16384);
	if (ret != 0)
	{
		printf("[DEBUG] memalign error\n");
	}
	num_pairs = 0;
	return init_ioctl(path);
}

// lba: 4KiB-based offset
// len: The number of 4KiB-based pages
void pallocate(uint32_t lba, uint32_t len)
{
	int err;

	err = submit_ioctl(IO_NVM_ALLOCATE, NULL, len, lba, 0, 0);
	if (err != 0)
	{
		printf("[DEBUG] WRITE ERROR While submitting Query %u %u\n", lba, len);
	}
}

void SwapBytes(void *pv, size_t n)
{
	char *p = pv;
	size_t lo, hi;
	for (lo = 0, hi = n - 1; hi > lo; lo++, hi--)
	{
		char tmp = p[lo];
		p[lo] = p[hi];
		p[hi] = tmp;
	}
}
void pallocate_prepare(uint32_t lba, uint32_t len)
{
	// SwapBytes(&lba, sizeof(uint32_t));
	// SwapBytes(&len, sizeof(uint32_t));
	memcpy(buffer + 4 + num_pairs * 8, &lba, sizeof(uint32_t));
	memcpy(buffer + 4 + num_pairs * 8 + 4, &len, sizeof(uint32_t));
	// sprintf(buffer + 4 + num_pairs * 8, lba, sizeof(uint32_t));
	// sprintf(buffer + 4 + num_pairs * 8 + 4, &len, sizeof(uint32_t));
	num_pairs++;
}
void pallocate_submit()
{
	int err;
	// SwapBytes(&num_pairs, sizeof(uint32_t));
	memcpy(buffer, &num_pairs, sizeof(uint32_t));
	err = submit_multiple_allocate(buffer, num_pairs);
	num_pairs = 0;
}
void pallocate_with_fd(uint32_t fd, uint32_t lba, uint32_t len)
{
}

void print_stat()
{
	int err;
	err = submit_ioctl(IO_NVM_PRINT_STAT, NULL, 0, MAGIC_NUM, 0, 0);
	if (err != 0)
	{
		printf("[DEBUG] PRINT STAT ERROR\n");
	}
}

void reset()
{
	int err;
	err = submit_ioctl(IO_NVM_RESET, NULL, 0, MAGIC_NUM, 0, 0);

	if (err != 0)
	{
		printf("[DEBUG] RESET ERROR\n");
	}
}

void set_level()
{
	int err;
	err = submit_ioctl(IO_NVM_SET_LEVEL, NULL, 0, MAGIC_NUM, 0, 0);

	if (err != 0)
	{
		printf("[DEBUG] RESET ERROR\n");
	}
}

void set_file()
{
	int err;
	err = submit_ioctl(IO_NVM_SET_FILE, NULL, 0, MAGIC_NUM, 0, 0);

	if (err != 0)
	{
		printf("[DEBUG] RESET ERROR\n");
	}
}
