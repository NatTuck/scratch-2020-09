SRCS := $(wildcard *.c)
BINS := $(SRCS:.c=)

CC := gcc
CFLAGS := -g

all: $(BINS)

% : %.c

clean:
	rm -f *.o $(BINS)

.PHONY: all clean
