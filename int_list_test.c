#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "int_list.h"

typedef struct {
	int_list *ls;
} nfixture;

void setup(nfixture *nf, gconstpointer test_data) {
	nf->ls = new_int_list(5);
}

void setup_prefilled(nfixture *nf, gconstpointer test_data) {
	const int total = 5;
	nf->ls = new_int_list(total);
	for(int i = 0;i < total - 1; i++) {
		nf->ls->ns[i] = i;
		nf->ls->curr_len++;
	}
}

void teardown(nfixture *nf, gconstpointer test_data) {
	free_int_list(nf->ls);
}

void test_create_list(nfixture *nf, gconstpointer ignored) {
	const int size = 5;
	int_list *ls = new_int_list(size);
	g_assert(ls != NULL);
	for (int i = 0;i < size;i++) {
		ls->ns[i] = i;
	}
	for (int i = 0;i < size;i++) {
		g_assert(ls->ns[i] == i);
	}
	free_int_list(ls);
}

void test_index_of_found(nfixture *nf, gconstpointer ignored) {
	const int val = 2;
	int index = index_of(val, nf->ls);
	g_assert(index == val);
}

void test_index_of_not_found(nfixture *nf, gconstpointer ignored) {
	const int val = 99;
	int index = index_of(val, nf->ls);
	g_assert(index == -1);
}

void test_insert_empty(nfixture *nf, gconstpointer ignored) {
	bool response = insert_number_sorted(1, nf->ls);
	g_assert(response);
	g_assert(nf->ls->curr_len == 1);
	g_assert(nf->ls->ns[0] == 1);
}

void test_insert_full(nfixture *nf, gconstpointer ignored) {
	for (int i = 0;i < nf->ls->max_len;i++) {
		nf->ls->ns[i] = i;
		nf->ls->curr_len++;
	}
	bool response = insert_number_sorted(99, nf->ls);
	g_assert(!response);
	// ensure no value was overwritten
	for (int i = 0;i < nf->ls->max_len;i++) {
		g_assert(nf->ls->ns[i] == i);
	}
}

void test_insert_start(nfixture *nf, gconstpointer ignored) {
	bool response = insert_number_sorted(-1, nf->ls);
	g_assert(response);
	g_assert(nf->ls->curr_len == nf->ls->max_len);
	for (int i = -1;i < nf->ls->max_len - 1; i++)
		g_assert(nf->ls->ns[i + 1] == i);
}

void test_insert_end(nfixture *nf, gconstpointer ignored) {
	bool response = insert_number_sorted(nf->ls->curr_len, nf->ls);
	g_assert(response);
	g_assert(nf->ls->curr_len == nf->ls->max_len);
	for (int i = 0;i < nf->ls->max_len; i++) {
		g_assert(nf->ls->ns[i] == i);
	}
}

void test_insert_middle(nfixture *nf, gconstpointer ignored) {
	bool response = insert_number_sorted(2, nf->ls);
	g_assert(response);
	g_assert(nf->ls->curr_len == nf->ls->max_len);
	for (int i = 0;i < nf->ls->max_len; i++)
		g_assert(nf->ls->ns[i] == (i > 2 ? i - 1 : i));
}

void test_clear(nfixture *nf, gconstpointer ignored) {
	clear_int_list(nf->ls);
	g_assert(nf->ls->curr_len == 0);
}

int main (int argc, char **argv) {
	g_test_init(&argc, &argv, NULL);
	g_test_add("/list/create", nfixture, NULL, NULL, test_create_list, NULL);
	g_test_add("/list/index_found", nfixture, NULL, setup_prefilled, test_index_of_found, teardown);
	g_test_add("/list/index_not_found", nfixture, NULL, setup_prefilled, test_index_of_not_found, teardown);
	g_test_add("/list/insert_empty", nfixture, NULL, setup, test_insert_empty, teardown);
	g_test_add("/list/insert_full", nfixture, NULL, setup, test_insert_full, teardown);
	g_test_add("/list/insert_start", nfixture, NULL, setup_prefilled, test_insert_start, teardown);
	g_test_add("/list/insert_end", nfixture, NULL, setup_prefilled, test_insert_end, teardown);
	g_test_add("/list/insert_middle", nfixture, NULL, setup_prefilled, test_insert_middle, teardown);
	g_test_add("/list/clear", nfixture, NULL, setup_prefilled, test_clear, teardown);
	return g_test_run();
}
