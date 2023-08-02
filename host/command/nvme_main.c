#define _GNU_SOURCE
#include <fcntl.h>
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
char buffer[QUERY_LEN];

// lba: 4KiB-based offset
// len: The number of 4KiB-based pages
int pallocate2(uint32_t lba, uint32_t len)
{
	int err;

	// err = submit_ioctl(IO_NVM_ALLOCATE, NULL, len, lba, 1, NULL);
	// if (err != 0)
	// {
	// 	printf("[DEBUG] WRITE ERROR While submitting Query\n");
	// 	return err;
	// }
	pallocate_prepare(27931456, 144192);
	pallocate_prepare((1221428 * 32), (3686 * 32));
	pallocate_prepare((1225114 * 32), (820 * 32));
	pallocate_prepare((1720320 * 32), (4505 * 32));
	pallocate_submit();

	pallocate_prepare(496026 * 32, 144192);
	pallocate_prepare((851968 * 32), (3686 * 32));
	pallocate_prepare((1204224 * 32), (820 * 32));
	pallocate_prepare((1207500 * 32), (4505 * 32));
	pallocate_prepare((1695744 * 32), (4505 * 32));
	pallocate_submit();

	return err;
}

void print_stat2()
{
	int err;
	err = submit_ioctl(IO_NVM_PRINT_STAT, NULL, QUERY_LEN, MAGIC_NUM, 0, NULL);
}

void reset2()
{
	int err;
	err = submit_ioctl(IO_NVM_RESET, NULL, QUERY_LEN, MAGIC_NUM, 0, NULL);
}

int main(int argc, char **argv)
{
	int err;

	if (init_palloc(argv[1]))
	{
		fprintf(stderr, "Useage: %s dev lba len\n", argv[0]);
		fprintf(stderr, "\tdev - device to send vuc\n");
		fprintf(stderr, "\tlba - 4KiB-based offset\n");
		fprintf(stderr, "\tlen - The number of 4KiB-based pages\n");
		return 1;
	}
	if (argc > 4 || argc < 3)
	{
		fprintf(stderr, "Useage: %s lba len\n", argv[0]);
		fprintf(stderr, "\tdev - device to send vuc\n");
		fprintf(stderr, "\tlba - 4KiB-based offset\n");
		fprintf(stderr, "\tlen - The number of 4KiB-based pages\n");
		return 1;
	}
	else if (argc < 4)
	{
		if (0 == strcmp(argv[2], "reset"))
		{
			reset2();
		}
		else
		{
			print_stat2();
		}
	}
	else
	{
		uint32_t offset = 0, len = 0;
		offset = atoi(argv[2]);
		len = atoi(argv[3]);
		pallocate2(offset, len);
	}

	return 0;
}
