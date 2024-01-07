#include <stdio.h>
#include <stdlib.h>
#include "string_utilities.h"

const int HEADINGS = 7;

int count_seeds(char *content) {
	int total = 0;
	while (*content != '\n') {
		content = skip_to_number(content);
		if (*content != '\n')
			total++;
		else
			return total;
		// skip past number
		content = skip_to_tokens(content, " \n\0");
	}
	return total;
}

void collect_seeds(char *content, int amount, int seeds[amount]) {
	while (*content != '\n') {
		content = skip_to_number(content);
		if (*content != '\n') {
			*seeds = atoi(content);
			seeds++;
		} else {
			return;
		}
		// skip past number
		content = skip_to_tokens(content, " \n\0");
	}
}

void populate_map(char *content, int heading_index[HEADINGS], int rows, int mappings[rows][3]) {
	int line_count = 0;
	while (*content != '\0') {
		// eat gap
		content = skip_to_tokens(content, "\n");
		content++;
		// heading
		*heading_index = line_count;
		heading_index++;
		content = skip_to_tokens(content, "\n");
		content++;
		// start collecting numbers until terminus or blank line
		while (*content != '\n' && *content != '\0') {
			// collect three numbers
			mappings[line_count][0] = atoi(content);
			content = skip_to_tokens(content, " ");
			content = skip_to_number(content);
			mappings[line_count][1] = atoi(content);
			content = skip_to_tokens(content, " ");
			content = skip_to_number(content);
			mappings[line_count][2] = atoi(content);
			line_count++;
			// skip to end of line
			content = skip_to_tokens(content, "\n\0");
			if (*content == '\n')
				content++;
		}
	}
}

int map_seed(int seed, int current_heading, int heading_index[HEADINGS], int lines, int mapping[lines][3]) {
	if (current_heading == HEADINGS)
		return seed;
	int section_end = current_heading == HEADINGS - 1 ? lines : heading_index[current_heading + 1];
	// see if seed maps to range
	for (int i = heading_index[current_heading];i < section_end;i++) {
		printf("Checking seed %d fits between %d and %d: ", seed, mapping[i][1], mapping[i][1] + mapping[i][2]);
		if (seed >= mapping[i][1] && seed < mapping[i][1] + mapping[i][2]) {
			int offset = seed - mapping[i][1];
			printf("destination: \n");
			return map_seed(mapping[i][0] + offset, current_heading + 1, heading_index, lines, mapping);
		} else {
			printf("no\n");
		}
	}
	// didn't find it, direct mapping
	return map_seed(seed, current_heading + 1, heading_index, lines, mapping);
}

int part_a(char *contents) {
	// seeds
	int seed_count = count_seeds(contents);
	int seeds[seed_count];
	collect_seeds(contents, seed_count, seeds);
	printf("Seeds: ");
	for (int i = 0;i < seed_count;i++) {
		printf("%d%c", seeds[i], i == seed_count - 1 ? '\n' : ',');
	}
	// mapping
	contents = skip_to_tokens(contents, "\n");
	contents++;
	int lines = count_string_token(contents, '\n') - 14;
	printf("Total Lines: %d\n", lines);
	int mappings[lines][3];
	int heading_index[HEADINGS];
	populate_map(contents, heading_index, lines, mappings);
	int hi = 0;
	for (int i = 0;i < lines;i++) {
		if (hi < HEADINGS && i == heading_index[hi]) {
			printf("\n");
			hi++;
		}
		printf("%d %d %d\n", mappings[i][0], mappings[i][1], mappings[i][2]);
	}
	// find smallest out of seed mappings
	int min = -1;
	for (int i = 0;i < 1;i++) {
		int res = map_seed(seeds[i], 0, heading_index, lines, mappings);
		min = min == -1 || res < min ? res : min;
	}
	return min;
}

int part_b(char *contents) {
	return -1;
}

int main(int argc, char **argv) {
	char *contents;
	if (argc > 2) {
		contents = string_from_file(argv[2]);
	} else {
		contents = string_from_file("day05ex.txt");
	}
	if (argc > 1 && argv[1][0] == 'b') {
		printf("Part B Total: %d\n", part_b(contents));
	} else {
		printf("Part A Total: %d\n", part_a(contents));
	}
	free(contents);
}
