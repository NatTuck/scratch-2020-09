
SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)
HDRS := $(wildcard *.h)

calc: $(OBJS)
	gcc -g -o calc $(OBJS)

%.o: %.c $(HDRS)
	gcc -c -g -o $@ $<

clean:
	rm -f calc *.o

.PHONY: clean
