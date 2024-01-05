#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include "string_utilities.h"

const char *GAME_TOKENS = "0123456789|\n";
const int MAX_NUM = 100;

int calculate_wins(char *input) {
	uint8_t draws[MAX_NUM];
	int score = 0;
	while (*input != '\0') {
		// clear existing draws
		for (int i = 0; i < MAX_NUM;i++) {
			draws[i] = 0;
		}
		// capture card details
		input = skip_to_number(input);
		// int cardNumber = atoi(input);
		input = skip_to_tokens(input, " ");
		// numbers until separator
		input = skip_to_tokens(input, GAME_TOKENS);
		while (is_digit(*input)) {
			int n = atoi(input);
			draws[n] = 1;
			// skip past current number
			while(is_digit(*input))
				input++;
			// skip to next or sep
			input = skip_to_tokens(input, GAME_TOKENS);
		}
		// at separator
		input++;
		// score game
		input = skip_to_tokens(input, GAME_TOKENS);
		int match_counter = 0;
		while (is_digit(*input)) {
			int n = atoi(input);
			if (draws[n] == 1)
				match_counter++;
			// skip past current number
			while(is_digit(*input))
				input++;
			// skip to next or end
			input = skip_to_tokens(input, GAME_TOKENS);
		}
		if (*input == '\n')
			input++;
		// calculate individual score
		if (match_counter == 1)
			score += 1;
		else
			score += pow(2, match_counter - 1);
	}
	return score;
}

int part_a(char *content) {
	return calculate_wins(content);
}

int part_b(char *content) {
	return calculate_wins(content);
}

int main(int argc, char **argv) {
	printf("2 score: %d\n", (int)pow(2, 1));
	printf("3 score: %d\n", (int)pow(2, 2));
	printf("4 score: %d\n", (int)pow(2, 3));
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
