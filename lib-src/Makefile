install64: lib64
	cp libasn1++_64.a ../lib/

install32: lib32
	cp libasn1++_32.a ../lib/

#all: lib64
all: lib32 lib64
CFLAGS=-fPIC -g -I. -c
CXXFLAGS=-std=c++11

lib32:
	g++ $(CFLAGS) $(CXXFLAGS) -m32 *.cc
	gcc $(CFLAGS) -m32 *.c
	ar r libasn1++_32.a *.o

lib64:
	g++ $(CFLAGS) $(CXXFLAGS) *.cc
	gcc $(CFLAGS) *.c
	ar r libasn1++_64.a *.o
