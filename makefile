OBJECTS=string_utilities.h string_utilities.c list.h list.c
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
list_test: list.h list.c list_test.c
clean: 
	rm $(BINARIES)
	rm $(TESTS)
