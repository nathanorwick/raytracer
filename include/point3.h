#ifndef POINT3_H
#define POINT3_H

#include "vec3.h"

typedef vec3 point3;

extern point3 (*point3_new)(const double e1, const double e2, const double e3);

double x(const vec3 v);
double y(const vec3 v);
double z(const vec3 v);

/* See "vec3.h" for more API */

#endif
