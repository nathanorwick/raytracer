#ifndef RAY_H
#define RAY_H

#include "point3.h"
#include "vec3.h"

typedef struct ray {
	point3 origin;
	vec3 direction;
} ray;

#endif
