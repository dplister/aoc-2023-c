#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "string_utilities.h"

const char *GAME_TOKENS = "0123456789|\n";
const int MAX_NUM = 10;

int calculate_wins(char *input) {
	while (*input != '\0') {
		input = skip_to_number(input);
		int cardNumber = atoi(input);
		input = skip_to(input, ' ');
		// numbers until separator
		input = skip_to(input, GAME_TOKENS);
		int draws[MAX_NUM];
		draws[0] = -1;
		while (is_digit(*input)) {
			int n = atoi(input);
			insert_number(MAX_NUM, draws, -1, n);
			// skip past current number
			while(is_digit(*input))
				input++;
		}
		input = skip_to(input, GAME_TOKENS);
		while (is_digit(*input)) {
			
		}
	}
}

int main(int argc, char **argv) {
	char *contents;
	if (argc > 2) {
		contents = string_from_file(argv[2]);
	} else {
		contents = string_from_file("day04ex.txt");
	}
	if (argc > 1 && argv[1][0] == 'b') {
		printf("Part B Total: %d\n", part_b(contents));
	} else {
		printf("Part A Total: %d\n", part_a(contents));
	}
	free(contents);
}
