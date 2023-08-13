#include "color.h"
#include "utility.h"
#include <math.h>
#include <stdio.h>

color (*color_new)(const double e1, const double e2, const double e3) = vec3_new;

void write_color(FILE *out, const color color_pixel, const int samples_per_pixel) {
	double r = at_index(color_pixel, 0);
	double g = at_index(color_pixel, 1);
	double b = at_index(color_pixel, 2);
	
	double scale = 1.0 / samples_per_pixel;
	r = sqrt(scale * r);
	g = sqrt(scale * g);
	b = sqrt(scale * b);

	r = 256 * clamp(r, 0.0, 0.999);
	g = 256 * clamp(g, 0.0, 0.999);
	b = 256 * clamp(b, 0.0, 0.999);

	fprintf(out, "%d %d %d\n", (int) r, (int) g, (int) b);
}
