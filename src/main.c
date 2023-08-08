#include "color.h"
#include "point3.h"
#include "ray.h"
#include "vec3.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ASPECT_RATIO (16.0 / 9.0)
#define IMAGE_WIDTH 1920
#define IMAGE_HEIGHT (int) (IMAGE_WIDTH / ASPECT_RATIO)

bool hit_sphere(point3 center, double radius, ray r) {
    vec3 oc = subtract(r.origin, center);
	double a = dot(r.direction, r.direction);
	double b = 2.0 * dot(oc, r.direction);
	double c = dot(oc, oc) - radius * radius;
	double discriminant = b * b - 4 * a * c;
	return (discriminant > 0);
}

color ray_color(ray r) {
	if (hit_sphere(point3_new(0, 0, -1), 0.5, r))
		return color_new(1, 0, 0);
	vec3 unit_direction = normalized(r.direction);
	double t = 0.5 * ((unit_direction.e)[1] + 1.0);
	return add(
		multiply_d(color_new(1.0, 1.0, 1.0), (1.0 - t)),
		multiply_d(color_new(0.5, 0.7, 1.0), t)
	);
}

int main(void) {
	/* Camera */
	double viewport_height = 2.0;
	double viewport_width = ASPECT_RATIO * viewport_height;
	double focal_length = 1.0;

	point3 origin = point3_new(0, 0, 0);
	vec3 horizontal = vec3_new(viewport_width, 0, 0);
	vec3 vertical = vec3_new(0, viewport_height, 0);
	point3 lower_left_corner = subtract(subtract(subtract(
		origin, divide_d(horizontal, 2)), divide_d(vertical, 2)), vec3_new(0, 0, focal_length)
	);

	/* Render */
	FILE *image = fopen("./render.ppm", "w");
	fprintf(image, "P3\n%d %d\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);

	for (int j = IMAGE_HEIGHT - 1; j >= 0; --j) {
		fprintf(stdout, "\rScanlines remaining: %d ", j);
		for (int i = 0; i < IMAGE_WIDTH; ++i) {
			double u = (double) i / (IMAGE_WIDTH - 1);
			double v = (double) j / (IMAGE_HEIGHT - 1);
			ray r = ray_new(
				origin,
				subtract(
					add(
						add(lower_left_corner, multiply_d(horizontal, u)),
						multiply_d(vertical, v)
					),
					origin
				)
			);
			color pixel_color = ray_color(r);
			write_color(image, pixel_color);
		}
	}
	
	fprintf(stdout, "\nDone.\n");
	fclose(image);
	return EXIT_SUCCESS;
}
