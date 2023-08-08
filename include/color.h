#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "stdio.h"

#define color_new vec3_new

typedef struct vec3 color;

int r(color point_color);
int g(color point_color);
int b(color point_color);

void write_color(FILE *out, color pixel);

/* See "vec3.h" for more API */

#endif
