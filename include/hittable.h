#ifndef HITTABLE_H
#define HITTABLE_H

#include "material.h"
#include "point3.h"
#include "ray.h"
#include "vec3.h"

typedef struct hit_record {
	point3 p;
	vec3 normal;
	material mat;
	double t;
	double front_face;
} hit_record;

void set_face_normal(hit_record *rec, const ray r, const vec3 outward_normal);

/* Define `object_hit` in the file including this, e.g. `sphere_hit` */

#endif
