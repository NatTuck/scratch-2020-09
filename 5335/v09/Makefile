
SRCS := $(wildcard *.cpp)
BINS := $(SRCS:.cpp=)

CFLAGS := $(shell pkg-config --cflags opencv)
LDFLAGS := $(shell pkg-config --libs opencv)

all:
	make -j bins

bins: $(BINS)

%: %.cpp
	g++ $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f $(BINS)

.PHONY: all clean bins
