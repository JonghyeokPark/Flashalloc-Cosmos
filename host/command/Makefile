all: debug non-debug

debug:
	gcc -g -o ioctl_debug -DDEBUG nvme_main.c nvme_ioctl.c libpalloc.c

non-debug:
	gcc -g -o ioctl nvme_main.c nvme_ioctl.c libpalloc.c

library: nvme_ioctl.o libpalloc.o
	gcc -shared -o libpalloc.so nvme_ioctl.o libpalloc.o
