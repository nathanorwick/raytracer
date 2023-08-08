#include "color.h"
#include <stdio.h>

int r(color color_pixel) {
	int r = 255.999 * x(color_pixel);
	return r;
}

int g(color color_pixel) {
	int g = 255.999 * y(color_pixel);
	return g;
}

int b(color color_pixel) {
	int b = 255.999 * z(color_pixel);
	return b;
}

void write_color(FILE *out, color color_pixel) {
	fprintf(out, "%d %d %d\n", r(color_pixel), g(color_pixel), b(color_pixel));
}
