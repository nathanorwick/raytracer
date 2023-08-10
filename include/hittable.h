#ifndef HITTABLE_H
#define HITTABLE_H

#include "point3.h"
#include "ray.h"
#include "vec3.h"

typedef struct hit_record {
	point3 p;
	vec3 normal;
	double t;
	double front_face;
} hit_record;

void set_face_normal(hit_record *rec, ray r, vec3 outward_normal);

/* Define `object_hit` in the file including this, e.g. `sphere_hit` */

#endif
