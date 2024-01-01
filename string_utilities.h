#include <string.h>
#include <stdio.h>
#include <stdbool.h>

char *string_from_file(const char *filename);

bool in_list(char input, const char *tokens);
bool is_digit(char c);
bool is_symbol(char c);

char *skip_to(char *input, const char *tokens);
char *skip_to_number(char *input);

int count_token(char *input, char token);
int index_of(char *input, char token);
