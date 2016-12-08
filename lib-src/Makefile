all: lib32 lib64
CFLAGS=-fPIC -g -I. -c
CXXFLAGS=-std=c++0x

lib32:
	g++ $(CFLAGS) $(CXXFLAGS) -m32 *.cc
	gcc $(CFLAGS) -m32 *.c
	ar r libasn1++_32.a *.o

lib64:
	g++ $(CFLAGS) $(CXXFLAGS) *.cc
	gcc $(CFLAGS) *.c
	ar r libasn1++_64.a *.o
