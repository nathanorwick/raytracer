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

	material material_ground = lambertian_new(color_new(0.8, 0.8, 0.0));
	material material_center = lambertian_new(color_new(0.1, 0.2, 0.5));
	material material_left   = dielectric_new(1.5);
	material material_right  = metal_new(color_new(0.8, 0.6, 0.2), 0.0);

	sphere sphere1 = sphere_new(point3_new(0.0, -100.5, -1.0), 100.0, material_ground);
	sphere sphere2 = sphere_new(point3_new(0.0, 0.0, -1.0), 0.5, material_center);
	sphere sphere3 = sphere_new(point3_new(-1.0, 0.0, -1.0), 0.5, material_left);
	sphere sphere4 = sphere_new(point3_new(-1.0, 0.0, -1.0), -0.45, material_left);
	sphere sphere5 = sphere_new(point3_new(1.0, 0.0, -1.0), 0.5, material_right);

	vec_push_back(world->objects, &sphere1);
	vec_push_back(world->objects, &sphere2);
	vec_push_back(world->objects, &sphere3);
	vec_push_back(world->objects, &sphere4);
	vec_push_back(world->objects, &sphere5);

	/* Camera */
	camera cam = camera_new(
		point3_new(-2, 2, 1), point3_new(0, 0, -1), vec3_new(0, 1, 0), 20, ASPECT_RATIO
	);

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
