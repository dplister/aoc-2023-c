#include <stdbool.h>

typedef struct {
	int *ns;
	int max_len;
	int curr_len;
} int_list;

int_list* new_int_list(int max);
void free_int_list(int_list *ls);

void clear_int_list(int_list *ls);
void print_int_list(int_list *ls);

bool insert_number_sorted(int n, int_list *ls);
int index_of(int n, int_list *ls);
