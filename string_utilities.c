#include <glib.h>
#include <string.h>
#include "string_utilities.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h> //abort

char *string_from_file(char const *filename){
	char *out;
	GError *e = NULL;
	GIOChannel *f = g_io_channel_new_file(filename, "r", &e);
	if (!f) {
		fprintf(stderr, "failed to open file '%s'.\n", filename);
		return NULL;
	}
	if (g_io_channel_read_to_end(f, &out, NULL, &e) != G_IO_STATUS_NORMAL){
		fprintf(stderr, "found file '%s' but couldn't read it.\n", filename);
		return NULL;
	}
	return out;
}

bool in_list(char input, const char *tokens) {
	while (*tokens != '\0') {
		if (*tokens == input)
			return true;
		tokens++;
	}
	return false;
}

char* skip_to(char *input, const char *tokens) {
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

int count_token(char *input, char token) {
	int count = 0;
	char *c = input;
	while (*c != '\0') {
		if (*c == token)
			count++;
		c++;
	}
	return count;
}

int index_of(char *input, char token) {
	int index = 0;
	while (input[index] != '\0' && input[index] != token) {
		index++;
	}
	return input[index] == token ? index : -1;
}
