#ifndef RAY_H
#define RAY_H

#include "point3.h"
#include "vec3.h"

typedef struct ray {
	point3 origin;
	vec3 direction;
} ray;

ray ray_new(const point3 origin, const vec3 direction);

point3 ray_at(const ray r, const double t);

#endif
