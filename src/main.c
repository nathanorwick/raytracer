#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "hittable.h"
#include "point3.h"
#include "ray.h"
#include "sphere.h"
#include "utility.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SAMPLES_PER_PIXEL 100

color ray_color(ray r, hittable_list *world) {
    hit_record rec;
    if (sphere_list_hit(world, r, 0, INFINITY, &rec)) {
        return multiply_d(
			add(rec.normal, color_new(1, 1, 1)),
			0.5
		);
    }
    vec3 unit_direction = normalized(r.direction);
    double t = 0.5 * (y(unit_direction) + 1.0);
    return add(
		multiply_d(color_new(1.0, 1.0, 1.0), (1.0 -t)),
		multiply_d(color_new(0.5, 0.7, 1.0), t)
	);
}

int main(void) {
	/* World */
	hittable_list *world = hittable_list_new();
	sphere sphere1 = sphere_new(point3_new(0, 0, -1), 0.5);
	sphere sphere2 = sphere_new(point3_new(0, -100.5, -1), 100);
	vec_push_back(world->objects, &sphere1);
	vec_push_back(world->objects, &sphere2);

	/* Camera */
	camera cam = camera_new();

	/* Render */
	FILE *image = fopen("./render.ppm", "w");
	fprintf(image, "P3\n%d %d\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);

	for (int j = IMAGE_HEIGHT - 1; j >= 0; --j) {
		fprintf(stdout, "\rScanlines remaining: %d ", j);
		fflush(stdout);
		for (int i = 0; i < IMAGE_WIDTH; ++i) {
			color pixel_color = color_new(0, 0, 0);
			for (int s = 0; s < SAMPLES_PER_PIXEL; ++s) {
				double u = (i + random_double()) / (IMAGE_WIDTH - 1);
				double v = (j + random_double()) / (IMAGE_HEIGHT - 1);
				ray r = get_ray(cam, u, v);
				pixel_color = add(pixel_color, ray_color(r, world));
			}
			write_color(image, pixel_color, SAMPLES_PER_PIXEL);
		}
	}
	
	fprintf(stdout, "\nDone.\n");
	fclose(image);
	hittable_list_free(world);
	return EXIT_SUCCESS;
}
