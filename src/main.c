#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "hittable.h"
#include "image.h"
#include "point3.h"
#include "ray.h"
#include "sphere.h"
#include "utility.h"
#include "vec3.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

hittable_list *random_scene(void) {
    hittable_list *world = hittable_list_new();

	if (world == NULL || world->objects == NULL)
		return NULL;

    material ground_material = lambertian_new(color_new(0.5, 0.5, 0.5));
	sphere *ground_sphere = malloc(sizeof(*ground_sphere));
	*ground_sphere = sphere_new(point3_new(0,-1000,0), 1000, ground_material);
	vec_push_back(world->objects, ground_sphere);

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
            double choose_mat = random_double();
            point3 center = point3_new(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if (magnitude(subtract(center, point3_new(4, 0.2, 0))) > 0.9) {
                material sphere_material;
				sphere *random_sphere = malloc(sizeof(*random_sphere));

                if (choose_mat < 0.8) {
                    // diffuse
                    point3 albedo = multiply(random_vec3(), random_vec3());
                    sphere_material = lambertian_new(albedo);
					*random_sphere = sphere_new(center, 0.2, sphere_material);
                } else if (choose_mat < 0.95) {
                    // metal
                    point3 albedo = random_vec3_range(0.5, 1);
                    double fuzz = random_double_range(0, 0.5);
                    sphere_material = metal_new(albedo, fuzz);
                    *random_sphere = sphere_new(center, 0.2, sphere_material);
                } else {
                    // glass
                    sphere_material = dielectric_new(1.5);
					*random_sphere = sphere_new(center, 0.2, sphere_material);
                }

				vec_push_back(world->objects, random_sphere);
            }
        }
    }

    material material1 = dielectric_new(1.5);
	sphere *sphere1 = malloc(sizeof(*sphere1));
    *sphere1 = sphere_new(point3_new(0, 1, 0), 1.0, material1);
	vec_push_back(world->objects, sphere1);

	material material2 = lambertian_new(color_new(0.4, 0.2, 0.1));
	sphere *sphere2 = malloc(sizeof(*sphere2));
	*sphere2 = sphere_new(point3_new(-4, 1, 0), 1.0, material2);
	vec_push_back(world->objects, sphere2);

    material material3 = metal_new(color_new(0.7, 0.6, 0.5), 0.0);
	sphere *sphere3 = malloc(sizeof(*sphere3));
    *sphere3 = sphere_new(point3_new(4, 1, 0), 1.0, material3);
	vec_push_back(world->objects, sphere3);

    return world;
}

int main(void) {
	/* World */
	hittable_list *world = random_scene();

	if (!world)
		return EXIT_FAILURE;

	/* Camera */
	point3 lookfrom = point3_new(13, 2, 3);
	point3 lookat = point3_new(0, 0, 0);
	vec3 vup = vec3_new(0, 1, 0);
	double dist_to_focus = 10.0;
	double aperture = 0.1;

	camera cam = camera_new(lookfrom, lookat, vup, 20, ASPECT_RATIO, aperture, dist_to_focus);

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
