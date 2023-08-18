#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "image.h"
#include "point3.h"
#include "ray.h"
#include "utility.h"
#include "vec3.h"

#include <stdio.h>
#include <stdlib.h>

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
	FILE *image = fopen(IMAGE_PATH, "w");
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

	/* Cleanup */
	fclose(image);
	hittable_list_free(world);
	return EXIT_SUCCESS;
}
