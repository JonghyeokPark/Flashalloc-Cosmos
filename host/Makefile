CC = gcc
CFLAGS = -Wall -Wextra

SRCS = libflashalloc.cc libmstream.cc playground.cc
OBJS = $(SRCS:.cc=.o)
EXECUTABLE = playground

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

.cc.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXECUTABLE)
