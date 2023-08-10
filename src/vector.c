/**
 * @file vector.c
 * @brief implementation of vector.h.
 * @author Nathan Orwick
 * @date July 30, 2023
 */
#include "vector.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define VEC_STARTING_ENTRIES 8

struct vector {
	int max_length;
	int current_length;
	void **values;
};

struct vector *vec_new(void) {
	struct vector *new_vec = malloc(sizeof(*new_vec));
	if (new_vec != NULL) {
		new_vec->max_length = VEC_STARTING_ENTRIES;
		new_vec->current_length = 0;
		new_vec->values = calloc(sizeof(void *), VEC_STARTING_ENTRIES);
	}
	return new_vec;
}

void vec_free(struct vector *v) {
	if (v != NULL) {
		free(v->values);
		free(v);
	}
}

bool vec_push_back(struct vector *v, void *value) {
	if (v == NULL || v->values == NULL) {
		return false;
	} else if (v->current_length < v->max_length) {
		v->values[v->current_length] = value;
		++(v->current_length);
		return true;
	} else {
		v->max_length = v->max_length * 2;
		v->values = realloc(v->values, sizeof(void *) * v->max_length);
		return vec_push_back(v, value);
	}
}

int vec_length(struct vector *v) {
	return (v == NULL) ? 0 : v->current_length;
}

void *vec_at(struct vector *v, int index) {
	if (v != NULL && index >= 0 && index < v->current_length) {
		return v->values[index];
	} else {
		fprintf(stderr, "[vector] @ `vec_at`: error attempting to access index %d with current size of %d\n", index, vec_length(v));
		return NULL;
	}
}

bool vec_empty(struct vector *v) {
	return (v == NULL) ? true : v->current_length == 0;
}

bool vec_clear(struct vector *v) {
	if (!vec_empty(v)) {
		v->max_length = VEC_STARTING_ENTRIES;
		v->current_length = 0;
		v->values = realloc(v->values, sizeof(void *) * 8);
	}
	return v != NULL;
}
