CFLAGS = -g -Wall -std=c2x `pkg-config --cflags glib-2.0`
LDLIBS=`pkg-config --libs glib-2.0`
CC=clang
BINARIES=day_one day_two day_three
TESTS=list_test

all: $(BINARIES)
day_one: $(OBJECTS)
day_two: $(OBJECTS)
day_three: $(OBJECTS)

list.o: list.h list.c
string_utilities.o: string_utilities.h string_utilities.c

test: $(TESTS)
list_test: list.o
clean: 
	rm *.o
	rm $(BINARIES)
	rm $(TESTS)
