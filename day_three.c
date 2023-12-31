#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "string_utilities.h"

typedef struct {
	int x;
	int y;
} point;

const int MAX_POINTS_TOUCHED = 3;

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

int touches(int rows, int columns, char map[rows][columns], int y, int x, int width, bool (*is_kind)(unsigned char c), point found[MAX_POINTS_TOUCHED]) {
	int minX = x - 1 < 0 ? 0 : x - 1;
	int maxX = x + width >= columns ? columns - 1 : x + width;
	int minY = y - 1 < 0 ? 0 : y - 1;
	int maxY = y + 1 >= rows ? rows - 1 : y + 1;

	// printf("minX: %d, maxX: %d, minY: %d, maxY: %d\n", minX, maxX, minY, maxY);
	int total = 0;
	
	// left
	if (is_kind(map[y][minX])) {
		total++;
		point p = { minX, y };
		*found = p;
		found++;
	}

	// right
	if (is_kind(map[y][maxX])) {
		total++;
		point p = { maxX, y };
		*found = p;
		found++;
	}

	// top
	if (minY != y) {
		for (int i = minX;i <= maxX; i++) {
			if (is_kind(map[minY][i])) {
				total++;
				point p = { .x = i, .y = minY };
				*found = p;
				found++;
				// skip past; count each group once
				while (i <= maxX && is_kind(map[minY][i]))
					i++;
			}
		}
	}
	// bottom
	if (maxY != y) {
		for (int i = minX;i <= maxX; i++) {
			if (is_kind(map[maxY][i])) {
				total++;
				point p = { .x = i, .y = maxY };
				*found = p;
				found++;
				// skip past; count each group once
				while (i <= maxX && is_kind(map[maxY][i]))
					i++;
			}
		}
	}
	return total;
}

int read_number(int rows, int columns, char map[rows][columns], int y, int x) {
	char nums[20];
	char *writer = nums;
	// roll back to start of number
	int sx = x == 0 ? x : x - 1;
	while (x > 0 && is_digit(map[y][sx]))
		sx--;
	if (!is_digit(map[y][sx]))
		sx++;
	for (int i = sx;i < columns && is_digit(map[y][i]); i++) {
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
	point touching[MAX_POINTS_TOUCHED];
	while (y < rows) {
		int x = 0;
		while (x < columns) {
			if (is_digit(map[y][x])) {
				// find end of digit set
				int width = 1;
				while(x + width < columns && is_digit(map[y][x + width]))
					width++;
				printf("Digit: %c, x: %d y: %d w: %d\n", map[y][x], x, y, width);
				if (touches(rows, columns, map, y, x, width, is_symbol, touching) > 0) {
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

int count_geared(int rows, int columns, char map[rows][columns]) {
	printf("Rows: %d, Columns: %d\n", rows, columns);
	int y = 0;
	int total = 0;
	point touching[MAX_POINTS_TOUCHED];
	while (y < rows) {
		int x = 0;
		while (x < columns) {
			if (map[y][x] == '*') {
				if (touches(rows, columns, map, y, x, 1, is_digit, touching) == 2) {
					// collect numbers attached
					int num1 = read_number(rows, columns, map, touching[0].y, touching[0].x);
					int num2 = read_number(rows, columns, map, touching[1].y, touching[1].x);
					total += num1 * num2;
					printf("Touches symbol: %d / %d\n", num1, num2);
				}

				// skip past number
				x += 1;
			}
			x++;
		}
		y++;
	}
	return total;
}

int part_a(char *input) {
	int rows = count_token(input, '\n');
	int columns = index_of(input, '\n');
	char map[rows][columns];
	copy_map(rows, columns, map, input);
	print_map(rows, columns, map);
	return count_connected(rows, columns, map);
}

int part_b(char *input) {
	int rows = count_token(input, '\n');
	int columns = index_of(input, '\n');
	char map[rows][columns];
	copy_map(rows, columns, map, input);
	print_map(rows, columns, map);
	return count_geared(rows, columns, map);
}

int main(int argc, char **argv) {
	char *contents;
	if (argc > 2) {
		contents = string_from_file(argv[2]);
	} else {
		contents = string_from_file("day03ex.txt");
	}
	if (argc > 1 && argv[1][0] == 'b') {
		printf("Part B Total: %d\n", part_b(contents));
	} else {
		printf("Part A Total: %d\n", part_a(contents));
	}
	free(contents);
}
