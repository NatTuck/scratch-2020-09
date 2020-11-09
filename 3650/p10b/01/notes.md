
free-list = [(0x21k, 3k)]

(0x21k, 3k) => [(0x21k, 1k), (0x22k, 2k)]

(0x20k, 4k) => [(0x20k, 1k), (0x21k, 3k)]

(0x20k, 4096)  <- mmap(4096)


a = malloc(1000)   => (0x20k, 1k)
b = malloc(1000)   => (0x21k, 1k) (invalid because freed)
c = malloc(1000)   => (0x22k, 1k)

free(b)
free(c)

