#include "list.h"

#include <stdio.h>
#include <stdlib.h>

int_list* new_int_list(int max) {
	int_list *l = malloc(sizeof(int_list));
	if (l == NULL)
		return NULL;
	l->ns = malloc(max * sizeof(int));
	if (l->ns == NULL) {
		free(l);
		return NULL;
	}
	l->curr_len = 0;
	l->max_len = max;
	return l;
}

void free_int_list(int_list *l) {
	free(l->ns);
	free(l);
}

void print_int_list(int_list *ns) {
	if (ns->curr_len == 0) {
		printf("()");
		return;
	}
	for (int i = 0;i < ns->curr_len; i++) {
		printf("%c%d%c", 
			i == 0 ? '(' : ' ',
			i,
			i == ns->curr_len - 1 ? ')' : ',');
	}
}

bool insert_number_sorted(int n, int_list *nums) {
	// check space is left
	if (nums->curr_len + 1 > nums->max_len)
		return false;

	int index = 0;
	while (index < nums->curr_len && nums->ns[index] < n)
		index++;

	int temp = nums->ns[index];
	nums->ns[index] = n;
	index++;
	while (index < nums->curr_len) {
		int next = nums->ns[index];
		nums->ns[index] = temp;
		temp = next;
		index++;
	}
	nums->ns[index] = temp;
	nums->curr_len++;
	return true;
}
