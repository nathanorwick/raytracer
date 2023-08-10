#include "color.h"
#include <stdio.h>

color (*color_new)(double e1, double e2, double e3) = vec3_new;

int r(color color_pixel) {
	int r = 255.999 * at_index(color_pixel, 0);
	return r;
}

int g(color color_pixel) {
	int g = 255.999 * at_index(color_pixel, 1);
	return g;
}

int b(color color_pixel) {
	int b = 255.999 * at_index(color_pixel, 2);
	return b;
}

void write_color(FILE *out, color color_pixel) {
	fprintf(out, "%d %d %d\n", r(color_pixel), g(color_pixel), b(color_pixel));
}
