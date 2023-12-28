#include "string_utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char* string;

static string GAME_DELIM = ":";
static string COLOUR_DELIM = "bgr"; 
static string DRAW_DELIM = ",;\n";
static string LINE_DELIM = "\n";

bool in_list(char input, char *tokens) {
	while (*tokens != '\0') {
		if (*tokens == input)
			return true;
		tokens++;
	}
	return false;
}

char* skip_to(char* input, char* tokens) {
	while (*input != '\0' && !in_list(*input, tokens)) {
		input++;
	}
	return input;
}

char* skip_to_number(char *input) {
	while (*input != '\0' && (*input < '0' || *input > '9'))
		input++;
	return input;
}

int count_valid_games(char *input) {
	int valids = 0;
	while (*input != '\0') {
		// get id
		input = skip_to_number(input);
		int id = atoi(input);
		printf("id: %d\t", id);
		input = skip_to(input, GAME_DELIM);
		input++;
		while (*input != '\0' && !in_list(*input, LINE_DELIM)) {
			// number
			int ball_total = atoi(input);
			// colour
			input = skip_to(input, COLOUR_DELIM);
			printf("%c:%d ", *input, ball_total);
			if (*input == 'b' && ball_total > 14) { id = 0; }
			if (*input == 'g' && ball_total > 13) { id = 0; }
			if (*input == 'r' && ball_total > 12) { id = 0; }
			// semicolon or comma or newline?
			input = skip_to(input, DRAW_DELIM);
			if (*input != '\0' && !in_list(*input, LINE_DELIM))
				input++;
		}
		printf("valid? %d\n", id > 0 ? 1 : 0);
		valids += id;
		if (*input == '\n')
			input++;
	}
	return valids;
}

int main(int argc, char **argv) {
	char *contents;
	if (argc > 2) {
		contents = string_from_file(argv[2]);
	} else {
		contents = string_from_file("day02inp.txt");
	}
	if (argc > 1 && argv[1][0] == 'b') {
		printf("Part B Total: %d\n", count_valid_games(contents));
	} else {
		printf("Part A Total: %d\n", count_valid_games(contents));
	}
	free(contents);
}

