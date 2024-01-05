#include "string_utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char* string;

const string GAME_DELIM = ":";
const string COLOUR_DELIM = "bgr"; 
const string DRAW_DELIM = ",;\n";
const string LINE_DELIM = "\n";

int count_valid_games(char *input) {
	int valids = 0;
	while (*input != '\0') {
		// get id
		input = skip_to_number(input);
		int id = atoi(input);
		printf("id: %d\t", id);
		input = skip_to_tokens(input, GAME_DELIM);
		input++;
		while (*input != '\0' && !char_in_tokens(*input, LINE_DELIM)) {
			// number
			int ball_total = atoi(input);
			// colour
			input = skip_to_tokens(input, COLOUR_DELIM);
			printf("%c:%d ", *input, ball_total);
			if (*input == 'b' && ball_total > 14) { id = 0; }
			if (*input == 'g' && ball_total > 13) { id = 0; }
			if (*input == 'r' && ball_total > 12) { id = 0; }
			// semicolon or comma or newline?
			input = skip_to_tokens(input, DRAW_DELIM);
			if (*input != '\0' && !char_in_tokens(*input, LINE_DELIM))
				input++;
		}
		printf("valid? %d\n", id > 0 ? 1 : 0);
		valids += id;
		if (*input == '\n')
			input++;
	}
	return valids;
}

const char colours[] = { 'b', 'g', 'r' };
const int colour_amount = 3;

int power_valid_games(char *input) {
	int total = 0;
	while (*input != '\0') {
		// get id
		input = skip_to_number(input);
		int id = atoi(input);
		printf("id: %d\t", id);
		input = skip_to_tokens(input, GAME_DELIM);
		input++;
		int max_colours[colour_amount];
		for (int i = 0;i < colour_amount;i++)
			max_colours[i] = 0;
		while (*input != '\0' && !char_in_tokens(*input, LINE_DELIM)) {
			// number
			int ball_total = atoi(input);
			// colour
			input = skip_to_tokens(input, colours);
			printf("%c:%d ", *input, ball_total);
			int ci = 0;
			while (colours[ci] != *input) {
				ci++;
			}
			max_colours[ci] = ball_total > max_colours[ci] ? ball_total : max_colours[ci];
			// semicolon or comma or newline?
			input = skip_to_tokens(input, DRAW_DELIM);
			if (*input != '\0' && !char_in_tokens(*input, LINE_DELIM))
				input++;
		}
		int sub_total = 1;
		for (int i = 0;i < colour_amount; i++) {
			printf("max-%c:%d ", colours[i], max_colours[i]);
			sub_total *= max_colours[i];
		}
		printf("\n");
		total += sub_total;
		if (*input == '\n')
			input++;
	}
	return total;
}

int main(int argc, char **argv) {
	char *contents;
	if (argc > 2) {
		contents = string_from_file(argv[2]);
	} else {
		contents = string_from_file("day02inp.txt");
	}
	if (argc > 1 && argv[1][0] == 'b') {
		printf("Part B Total: %d\n", power_valid_games(contents));
	} else {
		printf("Part A Total: %d\n", count_valid_games(contents));
	}
	free(contents);
}

