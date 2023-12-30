#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
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

bool is_symbol(unsigned char c) {
	return (!isdigit(c) && c != '.');
}

bool touches_symbol(int rows, int columns, char map[rows][columns], int y, int x, int width) {
	int minX = x - 1 < 0 ? 0 : x - 1;
	int maxX = x + width >= columns ? columns - 1 : x + width;
	int minY = y - 1 < 0 ? 0 : y - 1;
	int maxY = y + 1 >= rows ? rows - 1 : y + 1;

	// printf("minX: %d, maxX: %d, minY: %d, maxY: %d\n", minX, maxX, minY, maxY);
	
	// left
	if (is_symbol(map[y][minX]))
		return true;
	// right
	if (is_symbol(map[y][maxX]))
		return true;
	// top
	if (minY != y) {
		for (int i = minX;i <= maxX; i++) {
			if (is_symbol(map[minY][i]))
				return true;
		}
	}
	// bottom
	if (maxY != y) {
		for (int i = minX;i <= maxX; i++) {
			if (is_symbol(map[maxY][i]))
				return true;
		}
	}
	return false;
}

int read_number(int rows, int columns, char map[rows][columns], int y, int x) {
	char nums[20];
	char *writer = nums;
	for (int i = x;i < columns && isdigit(map[y][i]); i++) {
		*writer = map[y][i];
		writer++;
	}
	*writer = '\0';
	return atoi(nums);
}

int count_connected(int rows, int columns, char map[rows][columns]) {
	printf("Rows: %d, Columns: %d\n", rows, columns);
	int y = 0;
	int total = 0;
	while (y < rows) {
		int x = 0;
		while (x < columns) {
			if (isdigit(map[y][x])) {
				// find end of digit set
				int width = 1;
				while(x + width < columns && isdigit(map[y][x + width]))
					width++;
				printf("Digit: %c, x: %d y: %d w: %d\n", map[y][x], x, y, width);
				if (touches_symbol(rows, columns, map, y, x, width)) {
					// collect number
					int num = read_number(rows, columns, map, y, x);
					total += num;
					printf("Touches symbol: %d\n", num);
				}

				// skip past number
				x += width;
			}
			x++;
		}
		y++;
	}
	return total;
}

int count_parts(char *input) {
	int rows = count_token(input, '\n');
	int columns = index_of(input, '\n');
	char map[rows][columns];
	copy_map(rows, columns, map, input);
	print_map(rows, columns, map);
	return count_connected(rows, columns, map);
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
