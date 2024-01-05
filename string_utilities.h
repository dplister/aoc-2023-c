#include <string.h>
#include <stdio.h>
#include <stdbool.h>

char *string_from_file(const char *filename);

bool char_in_tokens(char input, const char *tokens);
bool is_digit(char c);
bool is_symbol(char c);

char *skip_to_tokens(char *input, const char *tokens);
char *skip_to_number(char *input);

int count_string_token(char *input, char token);
int char_index(char *input, char token);
