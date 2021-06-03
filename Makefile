LUA_VERSION = 5.4
LUA_DIRECTORY = -I/usr/include/lua$(LUA_VERSION) -I/usr/include/lua/$(LUA_VERSION)

CC = gcc
CCFLAGS = $(LUA_DIRECTORY) -fPIC

all: clean ldes.so

ldes.so: ldes.o
	$(CC) $(CCFLAGS) -shared ldes.o -o ldes.so

ldes.o: ldes.c
	$(CC) $(CCFLAGS) -c ldes.c -o ldes.o

clean:
	rm -f ldes.so ldes.o

