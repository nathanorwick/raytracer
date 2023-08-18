#include "hittable_list.h"
#include "vector.h"
#include <stdlib.h>

hittable_list *hittable_list_new(void) {
	hittable_list *list = malloc(sizeof(*list));
	list->objects = vec_new();
	return list;
}

void hittable_list_free(hittable_list *list) {
	vec_free(list->objects);
	free(list);
}
