#ifndef POINT3_H
#define POINT3_H

#include "vec3.h"

typedef vec3 point3;

point3 (*point3_new)(double e1, double e2, double e3);

double x(vec3 v);
double y(vec3 v);
double z(vec3 v);

/* See "vec3.h" for more API */

#endif
