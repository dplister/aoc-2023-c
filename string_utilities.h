#include <string.h>
#include <stdio.h>
#include <stdbool.h>

char *string_from_file(const char *filename);

bool in_list(char input, const char *tokens);
char *skip_to(char *input, const char *tokens);
char *skip_to_number(char *input);
