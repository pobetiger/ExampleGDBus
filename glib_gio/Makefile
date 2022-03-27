# Makefile for example GDBus applications in C/C++

CC=clang
CXX=clang++
LD=clang++

# the C, generated code requires glib, gio, and gio-unix
CFLAGS=-O2 -Wall $(shell pkg-config --cflags glib-2.0 gio-2.0 gio-unix-2.0)

# the C++ side is mostly our code, no longer need that many libraries
CXXFLAGS=-std=c++17 -O2 -Wall $(shell pkg-config --cflags glib-2.0 gio-2.0)
LDFLAGS=$(shell pkg-config --libs glib-2.0 gio-2.0)


SRC_XML = useful_service.xml
SRC_OBJ = useful_service.o main.o


all: c_interface_app
	$(LD) -o c_interface_app ${SRC_OBJ} ${LDFLAGS}


useful_service.c: ${SRC_XML}
	gdbus-codegen	--interface-prefix com.pobetiger \
					--generate-c-code useful_service \
					${SRC_XML}

c_interface_app: ${SRC_OBJ}

.PHONY: clean
clean:
	rm -fr *.o c_interface_app

.PHONY: distclean
distclean: clean
	rm -fr useful_service.c useful_service.h


