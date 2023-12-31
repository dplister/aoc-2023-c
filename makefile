OBJECTS=string_utilities.h string_utilities.c
CFLAGS = -g -Wall `pkg-config --cflags glib-2.0`
LDLIBS=`pkg-config --libs glib-2.0`
CC=gcc
binaries=day_one day_two day_three

all: $(binaries)
day_one: $(OBJECTS)
day_two: $(OBJECTS)
day_three: $(OBJECTS)
clean: 
	rm $(binaries)
