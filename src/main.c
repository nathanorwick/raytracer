#include "color.h"
#include "point3.h"
#include "vec3.h"
#include <stdio.h>
#include <stdlib.h>

#define IMAGE_WIDTH 1920
#define IMAGE_HEIGHT 1080

int main(void) {
	FILE *image = fopen("./render.ppm", "w");
	fprintf(image, "P3\n%d %d\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);

	for (int j = IMAGE_HEIGHT - 1; j >= 0; --j) {
		fprintf(stdout, "\rScanlines remaining: %d ", j);
		for (int i = 0; i < IMAGE_WIDTH; ++i) {
            color pixel_color = color_new(
				(double) i / (IMAGE_WIDTH - 1),
				(double) j / (IMAGE_HEIGHT - 1),
				0.25
			);
			write_color(image, pixel_color);
		}
	}
	
	fprintf(stdout, "\nDone.\n");
	fclose(image);
	return EXIT_SUCCESS;
}
