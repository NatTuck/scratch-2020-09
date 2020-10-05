
demo: demo.o set.o
	gcc -g -o demo *.o

demo.o: demo.c set.h
	gcc -c -g -o demo.o demo.c

set.o: set.c set.h
	gcc -c -g -o set.o set.c

clean:
	rm -f *.o demo

.PHONY: clean
