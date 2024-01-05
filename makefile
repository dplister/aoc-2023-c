CFLAGS = -g -Wall -std=c2x `pkg-config --cflags glib-2.0`
LDLIBS=`pkg-config --libs glib-2.0`
CC=clang
BINARIES=day_one day_two day_three day_four
TESTS=list_test

all: $(BINARIES)

$(BINARIES): %: int_list.o string_utilities.o %.c

int_list.o: int_list.h int_list.c
string_utilities.o: string_utilities.h string_utilities.c

test: $(TESTS)
list_test: int_list.o

clean: 
	rm *.o
	rm $(BINARIES)
	rm $(TESTS)
