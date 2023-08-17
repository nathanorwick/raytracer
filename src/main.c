#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "hittable.h"
#include "point3.h"
#include "ray.h"
#include "sphere.h"
#include "utility.h"
#include "vec3.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SAMPLES_PER_PIXEL 100
#define MAX_DEPTH 50

color ray_color(ray r, hittable_list *world, int depth) {
    hit_record rec;

	if (depth <= 0)
		return color_new(0, 0, 0);

    if (sphere_list_hit(world, r, 0.001, INFINITY, &rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat.scatter(rec.mat, r, rec, &attenuation, &scattered))
            return multiply(attenuation, ray_color(scattered, world, depth - 1));
        return color_new(0, 0, 0);
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

	if (!(world && world->objects))
		return EXIT_FAILURE;

	material material_left = lambertian_new(color_new(0, 0, 1));
	material material_right = lambertian_new(color_new(1, 0, 0));

	double R = cos(M_PI / 4);

	sphere sphere1 = sphere_new(point3_new(-1 * R, 0, -1), R, material_left);
	sphere sphere2 = sphere_new(point3_new(R, 0, -1), R, material_right);

	vec_push_back(world->objects, &sphere1);
	vec_push_back(world->objects, &sphere2);

	/* Camera */
	camera cam = camera_new(90.0, ASPECT_RATIO);

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
				pixel_color = add(pixel_color, ray_color(r, world, MAX_DEPTH));
			}

			write_color(image, pixel_color, SAMPLES_PER_PIXEL);
		}
	}
	
	fprintf(stdout, "\nDone.\n");
	fclose(image);
	hittable_list_free(world);
	return EXIT_SUCCESS;
}
