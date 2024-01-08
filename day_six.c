#include <stdio.h>
#include <stdlib.h>
#include "string_utilities.h"

typedef long long int big_int;

#define BIG_INT_FORMAT "%lld"
#define BIG_INT_PARSE(x) atoll(x)

typedef struct {
	big_int best_start;
	big_int best_end;
} timing;

int count_numbers(char *input) {
	int count = 0;
	while (*input != '\n') {
		if (is_digit(*input)) {
			count++;
			while (is_digit(*input))
				input++;
		} else {
			input++;
		}
	}
	return count;
}

void collect_numbers(char *input, int total, big_int nums[total]) {
	int collected = 0;
	while (collected < total) {
		input = skip_to_number(input);
		nums[collected] = atoi(input);
		input = skip_to_tokens(input, " ");
		collected++;
	}
}

bool meets_distance(big_int wait, big_int time, big_int distance) {
	return (wait * (time - wait)) > distance;
}

timing find_best_ends(big_int time, big_int distance) {
	// from start
	int start = 0;
	for (big_int i = 1;i < time;i++) {
		if (meets_distance(i, time, distance)) {
			start = i;
			break;
		}
	}
	// from end
	int end = 0;
	for (big_int i = time;i > 0;i--) {
		if (meets_distance(i, time, distance)) {
			end = i;
			break;
		}
	}
	timing t = { start, end };
	return t;
}

big_int part_a(char *content) {
	int total = count_numbers(content);
	big_int times[total];
	big_int distances[total];
	collect_numbers(content, total, times);
	content = skip_to_tokens(content, "\n");
	content++;
	collect_numbers(content, total, distances);
	printf("-- Games --\n");
	big_int ways = 1;
	for (int i = 0;i < total;i++) {
		timing ends = find_best_ends(times[i], distances[i]);
		big_int diff = ends.best_end - ends.best_start + 1;
		ways *= diff;
	}
	return ways;
}

big_int join_number(char *input) {
	// count digits
	int digits = 0;
	char *df = input;
	while (*df != '\n' && *df != '\0') {
		if (is_digit(*df))
			digits++;
		df++;
	}
	char digits_arr[digits + 1];
	char *dar = digits_arr;
	df = input;
	while (*df != '\n' && *df != '\0') {
		if (is_digit(*df)) {
			*dar = *df;
			dar++;
		}
		df++;
	}
	*dar = '\0';
	return BIG_INT_PARSE(digits_arr);
}

big_int part_b(char *content) {
	big_int time = join_number(content);
	content = skip_to_tokens(content, "\n");
	content++;
	big_int distance = join_number(content);
	printf("Time: " BIG_INT_FORMAT ", Distance: " BIG_INT_FORMAT "\n", time, distance);
	timing t = find_best_ends(time, distance);
	return t.best_end - t.best_start + 1;
}

int main(int argc, char **argv) {
	char *contents;
	if (argc > 2) {
		contents = string_from_file(argv[2]);
	} else {
		contents = string_from_file("day06ex.txt");
	}
	if (argc > 1 && argv[1][0] == 'b') {
		printf("B Total: " BIG_INT_FORMAT "\n", part_b(contents));
	} else {
		printf("A Total: " BIG_INT_FORMAT "\n", part_a(contents));
	}
	free(contents);
}
