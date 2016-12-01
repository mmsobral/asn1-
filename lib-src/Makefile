all: lib32 lib64
CFLAGS=-fPIC -I. -c

lib32:
	g++ $(CFLAGS) -m32 *.cc
	gcc $(CFLAGS) -m32 *.c
	ar r libasn1++_32.a

lib64:
	g++ $(CFLAGS) *.cc
	gcc $(CFLAGS) *.c
	ar r libasn1++_64.a
