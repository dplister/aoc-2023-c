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

void free_int_list(int_list *ls) {
	free(ls->ns);
	free(ls);
}

void clear_int_list(int_list *ls) {
	for (int i = 0;i < ls->curr_len;i++) {
		ls->ns[i] = 0;
	}
	ls->curr_len = 0;
}

void print_int_list(int_list *ls) {
	if (ls->curr_len == 0) {
		printf("()");
		return;
	}
	for (int i = 0;i < ls->curr_len; i++) {
		printf("%c%d%c", 
			i == 0 ? '(' : ' ',
			i,
			i == ls->curr_len - 1 ? ')' : ',');
	}
}

int binary_search(int key, int_list *ls, int low, int high) {
	if (low > high) 
		return -1;
	
	int middle = (low + high) / 2;

	if (ls->ns[middle] == key) {
		return middle;
	}

	if (ls->ns[middle] > key) {
		return binary_search(key, ls, low, middle - 1);
	} else {
		return binary_search(key, ls, middle + 1, high);
	}
}

int index_of_highest(int key, int_list *ls, int low, int high) {
	if (low > high) {
		// search this area back to 0
		while (high > 0 && ls->ns[high] > key)
			high--;
		return high;
	}

	int middle = (low + high) / 2;

	if (ls->ns[middle] == key) {
		return middle;
	}

	if (ls->ns[middle] > key) {
		return index_of_highest(key, ls, low, middle - 1);
	} else {
		return index_of_highest(key, ls, middle + 1, high);
	}
}

int index_of(int n, int_list *ls) {
	return binary_search(n, ls, 0, ls->curr_len - 1);
}

bool insert_number_sorted(int n, int_list *ls) {
	// check space is left
	if (ls->curr_len + 1 > ls->max_len)
		return false;

	int index = index_of_highest(n, ls, 0, ls->curr_len - 1);
	if (index < 0) { // at start
		index = 0;
	} else if (index == ls->curr_len - 1) { // at end
		ls->ns[index + 1] = n;
		ls->curr_len++;
		return true;
	}

	// move items across
	int temp = ls->ns[index];
	ls->ns[index] = n;
	index++;
	while (index < ls->curr_len) {
		int next = ls->ns[index];
		ls->ns[index] = temp;
		temp = next;
		index++;
	}
	ls->ns[index] = temp;
	ls->curr_len++;
	return true;
}
