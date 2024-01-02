CFLAGS = -g -Wall `pkg-config --cflags glib-2.0`
LDLIBS=`pkg-config --libs glib-2.0`
CC=gcc
BINARIES=day_one day_two day_three
TESTS=list_test

all: $(BINARIES)
test: $(TESTS)
day_one: $(OBJECTS)
day_two: $(OBJECTS)
day_three: $(OBJECTS)
list: list.h list.c
	$(CC) $(CFLAGS) list.h list.c -c list.o
list_test: list
	$(CC) $(CFLAGS) $(LDLIBS) list.o list_test.c -o list_test
clean: 
	rm $(BINARIES)
	rm $(TESTS)
