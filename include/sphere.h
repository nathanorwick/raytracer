#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "hittable_list.h"
#include "point3.h"
#include "ray.h"
#include <stdbool.h>

typedef struct sphere {
	point3 center;
	double radius;
} sphere;

sphere sphere_new(point3 center, double radius);

bool sphere_hit(sphere s, ray r, double t_min, double t_max, hit_record *rec);
bool sphere_list_hit(hittable_list *list, ray r, double t_min, double t_max, hit_record *rec);

#endif
