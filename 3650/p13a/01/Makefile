
CFLAGS := -g
LIBS := 

all: mkfs dump

dump: dump.c pages.c
	gcc $(CFLAGS) -o $@ $^ $(LIBS)

mkfs: mkfs.c pages.c
	gcc $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f mkfs dump

.PHONY: clean
