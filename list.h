#include <stdbool.h>

typedef struct {
	int *ns;
	int max_len;
	int curr_len;
} int_list;

int_list* new_int_list(int max);
void free_int_list(int_list *l);

void print_int_list(int_list *ns);

bool insert_number_sorted(int n, int_list *nums);
