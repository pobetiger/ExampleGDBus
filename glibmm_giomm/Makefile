# Makefile for example GDBus applications in C/C++

CXX=clang++
LD=clang++

# the C++ side is mostly our code, no longer need that many libraries
CXXFLAGS=-std=c++17 -O2 -Wall $(shell pkg-config --cflags glibmm-2.4 giomm-2.4)
LDFLAGS=$(shell pkg-config --libs glibmm-2.4 giomm-2.4)


SRC_OBJ = DBusApp.o main.o


all: cpp_interface_app
	$(LD) -o cpp_interface_app ${SRC_OBJ} ${LDFLAGS}


cpp_interface_app: ${SRC_OBJ}

clean:
	rm -fr *.o cpp_interface_app

distclean: clean

.PHONY: clean


