#include <stdio.h>
#include <stdlib.h>
#include "string_utilities.h"

typedef struct {
	char cards[5];
	int bid;
} hand;

const int card_priorities[] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' };

void read_hands(char *input, int len, hand hands[len]) {
	int row = 0;
	while (row < len) {
		hand h;
		// read cards
		for (int i = 0; i < 5; i++) {
			h.cards[i] = *input;
			input++;
		}
		// collect bid
		h.bid = atoi(input);
		hands[row] = h;
		row++;
		input = skip_to_tokens(input,"\n");
		input++;
	}
}

int part_a(char *content) {
	int total_hands = count_string_token(content, '\n');
	printf("Hands: %d\n", total_hands);
	return 0;
}

int part_b(char *content) {
	return 0;
}

int main(int argc, char **argv) {
	char *contents;
	if (argc > 2) {
		contents = string_from_file(argv[2]);
	} else {
		contents = string_from_file("day07ex.txt");
	}
	if (argc > 1 && argv[1][0] == 'b') {
		printf("B Total: %d\n", part_b(contents));
	} else {
		printf("A Total: %d\n", part_a(contents));
	}
	free(contents);
}
