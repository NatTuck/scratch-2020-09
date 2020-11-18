SO := libclock_plugin.so

SRCS := $(wildcard *.cc)
OBJS := $(SRCS:.cc=.o)
HDRS := $(wildcard *.hh)

CFLAGS := -g -fPIC $(shell pkg-config --cflags gazebo)
LIBS   := $(shell pkg-config --libs gazebo)

$(SO): $(OBJS)
	g++ -o $(SO) -shared $(CFLAGS) $(OBJS) $(LIBS)

%.o: %.cc $(HDRS) Makefile
	g++ -c $(CFLAGS) -o $@ $<

clean:
	rm -f *.o $(SO)

.PHONY: clean
