#include <stdio.h>
#include <stdlib.h>

#define IMAGE_WIDTH 1920
#define IMAGE_HEIGHT 1080

int main(void) {
	FILE *image = fopen("./image.ppm", "w");

	fprintf(image, "P3\n");
	fprintf(image, "%d %d\n", IMAGE_WIDTH, IMAGE_HEIGHT);
	fprintf(image, "255\n");

	for (int j = IMAGE_HEIGHT - 1; j >= 0; --j) {
		fprintf(stdout, "\rScanlines remaining: %d ", j);
		fflush(stdout);

		for (int i = 0; i < IMAGE_WIDTH; ++i) {
			double r = (double) i / (IMAGE_WIDTH - 1);
			double g = (double) j / (IMAGE_HEIGHT - 1);
			double b = 0.25;

			int ir = (int) (255.999 * r);
			int ig = (int) (255.999 * g);
			int ib = (int) (255.999 * b);

			fprintf(image, "%d %d %d\n", ir, ig, ib);
		}
	}
	
	fprintf(stdout, "\nDone.\n");
	fclose(image);
	return EXIT_SUCCESS;
}
