#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "stdio.h"

typedef vec3 color;

color (*color_new)(double e1, double e2, double e3);

void write_color(FILE *out, color pixel, int samples_per_pixel);

/* See "vec3.h" for more API */

#endif
