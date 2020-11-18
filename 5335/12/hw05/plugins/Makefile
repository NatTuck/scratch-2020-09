
all:
	rm -f *.so
	make libtank_control_plugin.so
	make liblaunch_plugin.so

libtank_control_plugin.so:
	(cd tank_control && make)
	cp tank_control/*.so .

liblaunch_plugin.so:
	(cd launch && make)
	cp launch/*.so .

clean:
	rm -f *.so
	(cd tank_control && make clean)
	(cd launch && make clean)

.PHONY: all clean
