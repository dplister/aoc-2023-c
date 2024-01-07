#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include "string_utilities.h"

typedef unsigned char uint8_t;

const char *GAME_TOKENS = "0123456789|\n";
const int MAX_NUM = 100;

void calculate_wins(char *input, int max_games, int scores[max_games]) {
	uint8_t draws[MAX_NUM];
	while (*input != '\0') {
		// clear existing draws
		for (int i = 0; i < MAX_NUM;i++) {
			draws[i] = 0;
		}
		// capture card details
		input = skip_to_number(input);
		int card_number = atoi(input);
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
		scores[card_number - 1] = match_counter; // games start at 1
	}
}

int part_a(char *content) {
	int max_games = count_string_token(content, '\n');
	int scores[max_games];
	for (int i = 0;i < max_games;i++) { 
		scores[i] = 0;
	}
	calculate_wins(content, max_games, scores);
	int total_score = 0;
	for (int i = 0;i < max_games;i++) {
		if (scores[i] == 1)
			total_score += 1;
		else if (scores[i] > 1)
			total_score += pow(2, scores[i] - 1);
	}
	return total_score;
}

int part_b(char *content) {
	int max_games = count_string_token(content, '\n');
	int scores[max_games];
	for (int i = 0;i < max_games;i++) { 
		scores[i] = 0;
	}
	calculate_wins(content, max_games, scores);
	int tickets[max_games];
	// 1 original ticket for each game
	for (int i = 0;i < max_games;i++) {
		tickets[i] = 1;
	}
	int total_tickets = 0;
	for (int i = 0;i < max_games;i++) {
		int win_multiplier = tickets[i];
		total_tickets += win_multiplier;
		for (int s = 0; s < scores[i] && i + s + 1 < max_games; s++) {
			tickets[i + s + 1] += win_multiplier;
		}
	}
	return total_tickets;
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
