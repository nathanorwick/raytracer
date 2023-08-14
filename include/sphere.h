#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "point3.h"
#include "ray.h"
#include <stdbool.h>

typedef struct sphere {
	point3 center;
	double radius;
	material mat;
} sphere;

sphere sphere_new(const point3 center, const double radius, material m);

bool sphere_hit(const sphere s, const ray r, const double t_min, const double t_max, hit_record *rec);
bool sphere_list_hit(const hittable_list *list, const ray r, const double t_min, const double t_max, hit_record *rec);

#endif
