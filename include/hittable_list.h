#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "vector.h"

typedef struct hittable_list {
	struct vector *objects;
} hittable_list;

hittable_list *hittable_list_new(void);
void hittable_list_free(hittable_list *list);

/* Define `object_list_hit` in the file including this, e.g. `sphere_list_hit` */

#endif
