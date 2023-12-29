#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "string_utilities.h"

void copy_map(int rows, int columns, char map[rows][columns], char *input) {
	int y = 0;
	char *c = input;
	while (y < rows) {
		int x = 0;
		while (x < columns) {
			map[y][x] = *c;
			x++;
			c++;
		}
		// skip over newline
		c++;
		y++;
	}
}

void print_map(int rows, int columns, char map[rows][columns]) {
	int y = 0;
	while (y < rows) {
		int x = 0;
		while (x < columns) {
			printf("%c", map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

bool touches_symbol(int rows, int columns, char map[rows][columns]) {
	
}

int count_connected(int rows, int columns, char map[rows][columns]) {
	int y = 0;
	while (y < rows) {
		int x = 0;
		while (x < columns) {
			if (isdigit(map[y][x])) {
				if (touches_symbol(rows, columns, map, y, x)) {
					// skip past number
					while (x < columns && isdigit(map[y][x]))
						x++;
				}
			}
			x++;
		}
		y++;
	}
}

int count_parts(char *input) {
	int rows = count_token(input, '\n') + 1;
	int columns = index_of(input, '\n');
	char map[rows][columns];
	copy_map(rows, columns, map, input);
	print_map(rows, columns, map);
	return 0;
}

int main(int argc, char **argv) {
	char *contents;
	if (argc > 2) {
		contents = string_from_file(argv[2]);
	} else {
		contents = string_from_file("day03ex.txt");
	}
	if (argc > 1 && argv[1][0] == 'b') {
		printf("Part B Total: %d\n", count_parts(contents));
	} else {
		printf("Part A Total: %d\n", count_parts(contents));
	}
	free(contents);
}
