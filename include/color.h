#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "stdio.h"

typedef vec3 color;

color (*color_new)(double e1, double e2, double e3);

int r(color point_color);
int g(color point_color);
int b(color point_color);

void write_color(FILE *out, color pixel);

/* See "vec3.h" for more API */

#endif
