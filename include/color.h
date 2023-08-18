#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "stdio.h"

typedef vec3 color;

extern color (*color_new)(const double e1, const double e2, const double e3);

void write_color(FILE *out, const color pixel, const int samples_per_pixel);

/* See "vec3.h" for more API */

#endif
