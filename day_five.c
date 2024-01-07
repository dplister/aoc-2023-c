#include <stdio.h>
#include <stdlib.h>
#include "string_utilities.h"

typedef long long int big_int;

#define BIG_INT_FORMAT "%lld"
#define BIG_INT_PARSE(x) atoll(x)

const int HEADINGS = 7;

big_int map_seed_range(big_int seed_start, big_int seed_end, int current_heading, int heading_index[HEADINGS], int matching_row, int lines, big_int mapping[lines][3]);
big_int split_seed_range(big_int seed_start, big_int seed_end, int current_heading, int heading_index[HEADINGS], int lines, big_int mapping[lines][3]);

big_int minl(big_int len, big_int nums[len]) {
	big_int mn = nums[0];
	for (int i = 1; i < len;i++) {
		if (nums[i] < mn)
			mn = nums[i];
	}
	return mn;
}

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

void collect_seeds(char *content, int amount, big_int seeds[amount]) {
	while (*content != '\n') {
		content = skip_to_number(content);
		if (*content != '\n') {
			*seeds = BIG_INT_PARSE(content);
			seeds++;
		} else {
			return;
		}
		// skip past number
		content = skip_to_tokens(content, " \n\0");
	}
}

void populate_map(char *content, int heading_index[HEADINGS], int rows, big_int mappings[rows][3]) {
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
			mappings[line_count][0] = BIG_INT_PARSE(content);
			content = skip_to_tokens(content, " ");
			content = skip_to_number(content);
			mappings[line_count][1] = BIG_INT_PARSE(content);
			content = skip_to_tokens(content, " ");
			content = skip_to_number(content);
			mappings[line_count][2] = BIG_INT_PARSE(content);
			line_count++;
			// skip to end of line
			content = skip_to_tokens(content, "\n\0");
			if (*content == '\n')
				content++;
		}
	}
}

big_int map_seed(big_int seed, int current_heading, int heading_index[HEADINGS], int lines, big_int mapping[lines][3]) {
	if (current_heading == HEADINGS) {
		return seed;
	}
	int section_end = current_heading == HEADINGS - 1 ? lines : heading_index[current_heading + 1];
	// see if seed maps to range
	for (int i = heading_index[current_heading];i < section_end;i++) {
		if (seed >= mapping[i][1] && seed < mapping[i][1] + mapping[i][2]) {
			big_int offset = seed - mapping[i][1];
			return map_seed(mapping[i][0] + offset, current_heading + 1, heading_index, lines, mapping);
		}
	}
	// didn't find it, direct mapping
	return map_seed(seed, current_heading + 1, heading_index, lines, mapping);
}

big_int part_a(char *contents) {
	// seeds
	int seed_count = count_seeds(contents);
	big_int seeds[seed_count];
	collect_seeds(contents, seed_count, seeds);
	printf("Seeds: ");
	for (int i = 0;i < seed_count;i++) {
		printf(BIG_INT_FORMAT "%c", seeds[i], i == seed_count - 1 ? '\n' : ',');
	}
	// mapping
	contents = skip_to_tokens(contents, "\n");
	contents++;
	int lines = count_string_token(contents, '\n') - 14;
	printf("Total Lines: %d\n", lines);
	big_int mappings[lines][3];
	int heading_index[HEADINGS];
	populate_map(contents, heading_index, lines, mappings);
	int hi = 0;
	for (int i = 0;i < lines;i++) {
		if (hi < HEADINGS && i == heading_index[hi]) {
			printf("\n");
			hi++;
		}
		printf(BIG_INT_FORMAT " " BIG_INT_FORMAT " " BIG_INT_FORMAT "\n", mappings[i][0], mappings[i][1], mappings[i][2]);
	}
	// find smallest out of seed mappings
	big_int min = -1;
	for (int i = 0;i < seed_count;i++) {
		printf("Seed " BIG_INT_FORMAT " -> ", seeds[i]);
		big_int res = map_seed(seeds[i], 0, heading_index, lines, mappings);
		printf(BIG_INT_FORMAT "\n", res);
		min = min == -1 || res < min ? res : min;
	}
	printf("Min: " BIG_INT_FORMAT "\n", min);
	return min;
}

big_int map_seed_range(big_int seed_start, big_int seed_end, int current_heading, int heading_index[HEADINGS], int matching_row, int lines, big_int mapping[lines][3]) {
	if (matching_row > -1) {
		big_int offset = seed_start - mapping[matching_row][1];
		big_int range = seed_end - seed_start;
		return split_seed_range(mapping[matching_row][0] + offset, mapping[matching_row][0] + offset + range, current_heading + 1, heading_index, lines, mapping);
	} 
	// just bump heading and continue
	return split_seed_range(seed_start, seed_end, current_heading + 1, heading_index, lines, mapping);
}

big_int split_seed_range(big_int seed_start, big_int seed_end, int current_heading, int heading_index[HEADINGS], int lines, big_int mapping[lines][3]) {
	if (current_heading == HEADINGS) {
		return seed_start;
	}
	int section_end = current_heading == HEADINGS - 1 ? lines : heading_index[current_heading + 1];
	// see if seed maps to range
	for (int i = heading_index[current_heading];i < section_end;i++) {
		big_int start_map = mapping[i][1];
		big_int end_map = mapping[i][1] + mapping[i][2] - 1;
		// range surrounds the almanac
		if (start_map > seed_start && end_map < seed_end) {
			big_int leaves[] = {
				split_seed_range(seed_start, start_map - 1, current_heading, heading_index, lines, mapping),
				map_seed_range(start_map, end_map, current_heading, heading_index, i, lines, mapping),
				split_seed_range(end_map + 1, seed_end, current_heading, heading_index, lines, mapping)
			};
			return minl(3, leaves);
		}
		// almanac starts before range and ends inside range
		else if (start_map < seed_start && end_map >= seed_start && end_map <= seed_end) {
			big_int leaves[] = {
				map_seed_range(seed_start, end_map, current_heading, heading_index, i, lines, mapping),
				split_seed_range(end_map + 1, seed_end, current_heading, heading_index, lines, mapping)
			};
			return minl(2, leaves);
		}
		// almanac starts inside range and ends outside it
		else if (start_map > seed_start && start_map <= seed_end && end_map >= seed_end) {
			big_int leaves[] = {
				split_seed_range(seed_start, start_map - 1, current_heading, heading_index, lines, mapping),
				map_seed_range(start_map, seed_end, current_heading, heading_index, i, lines, mapping),
			};
			return minl(2, leaves);
		}
		// almanac surrounds range
		else if (start_map <= seed_start && end_map >= seed_end) {
			return map_seed_range(seed_start, seed_end, current_heading, heading_index, i, lines, mapping);
		}
	}
	// if we reached here, no mapping at all, pass range on as direct mapping
	return map_seed_range(seed_start, seed_end, current_heading, heading_index, -1, lines, mapping);
}

big_int part_b(char *contents) {
	// seeds
	int seed_count = count_seeds(contents);
	big_int seeds[seed_count];
	collect_seeds(contents, seed_count, seeds);
	printf("Seeds: ");
	for (int i = 0;i < seed_count;i++) {
		printf(BIG_INT_FORMAT "%c", seeds[i], i == seed_count - 1 ? '\n' : ',');
	}
	// mapping
	contents = skip_to_tokens(contents, "\n");
	contents++;
	int lines = count_string_token(contents, '\n') - 14;
	printf("Total Lines: %d\n", lines);
	big_int mappings[lines][3];
	int heading_index[HEADINGS];
	populate_map(contents, heading_index, lines, mappings);
	int hi = 0;
	for (int i = 0;i < lines;i++) {
		if (hi < HEADINGS && i == heading_index[hi]) {
			printf("\n");
			hi++;
		}
		printf(BIG_INT_FORMAT " " BIG_INT_FORMAT " " BIG_INT_FORMAT "\n", mappings[i][0], mappings[i][1], mappings[i][2]);
	}
	// find smallest out of seed mappings
	big_int min = -1;
	for (int i = 0;i < seed_count;i += 2) {
		printf("Seed " BIG_INT_FORMAT "-" BIG_INT_FORMAT " -> ", seeds[i], seeds[i] + seeds[i + 1] - 1);
		big_int res = split_seed_range(seeds[i], seeds[i] + seeds[i + 1] - 1, 0, heading_index, lines, mappings);
		printf(BIG_INT_FORMAT "\n", res);
		min = min == -1 || res < min ? res : min;
	}
	printf("Min: " BIG_INT_FORMAT "\n", min);
	return min;
}

int main(int argc, char **argv) {
	char *contents;
	if (argc > 2) {
		contents = string_from_file(argv[2]);
	} else {
		contents = string_from_file("day05ex.txt");
	}
	if (argc > 1 && argv[1][0] == 'b') {
		printf("Part B Total: " BIG_INT_FORMAT "\n", part_b(contents));
	} else {
		printf("Part A Total: " BIG_INT_FORMAT "\n", part_a(contents));
	}
	free(contents);
}
