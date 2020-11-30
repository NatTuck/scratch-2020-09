

all: mkfs dump disk.image

disk.image: mkfs
	./mkfs disk.image
	./dump disk.image

mkfs: mkfs.c pages.c
	rm -f disk.image
	gcc -g -o $@ $^

dump: dump.c pages.c
	gcc -g -o $@ $^

clean:
	rm -f mkfs dump disk.image

.PHONY: all clean
