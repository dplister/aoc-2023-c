#include "string_utilities.h"
#include <stdlib.h>
#include <stdbool.h>

typedef char* string;

static string numbers[] = {"one","two","three","four","five","six","seven","eight","nine",NULL };

bool is_digit(char c) {
	return c >= '0' && c <= '9';
}

bool is_eol(char c) {
	return c == '\n' || c == '\0';
}

bool match_num(char *input, int *num) {
	int index = 0;
	while (numbers[index] != NULL) {
		char *pn = numbers[index];
		char *inp = input;
		while (*pn != '\0' && *inp != '\0' && *pn == *inp) {
			pn++; inp++;
		}
		if (*pn == '\0') {
			*num = (index + 1);
			return true;
		}
		index++;
	}
	return false;
}

int process_line(char *input, int len, bool include_words) {
	char *p = input;
	// find first int at start
	int fnum = 0;
	while (*p != '\0') {
		if (is_digit(*p)) {
			fnum = *p - '0';
			break;
		} else if (include_words && match_num(p, &fnum)) {
			break;
		}
		p++;
	}
	p = input + len;
	// work backwards to find int
	int snum = 0;
	while (!is_digit(*p) && (!include_words || !match_num(p, &snum))) {
		p--;
	}
	if (is_digit(*p)) {
		snum = *p - '0';
	}
	return (fnum * 10) + snum;
}

int run_file(char *input, bool includeWords) {
	// for each line
	char *start = input;
	int len = 0;
	int total = 0;
	while (*input != '\0') {
		while (!is_eol(*input)) {
			input++;
			len++;
		}
		bool isNewLine = *input == '\n';
		*input = '\0';
		total += process_line(start, len, includeWords);
		// move past newline (unless end)
		if (isNewLine) {
			input++;
		}
		start = input;
		len = 0;
	}
	return total;
}

int main (int argc, char **argv) {
	char *contents;
	if (argc > 2) {
		contents = string_from_file(argv[2]);
	} else {
		contents = string_from_file("day01inp.txt");
	}
	if (argc > 1 && argv[1][0] == 'b') {
		printf("Part B Total: %d\n", run_file(contents, true));
	} else {
		printf("Part A Total: %d\n", run_file(contents, false));
	}
	free(contents);
}
