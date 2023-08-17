#include "camera.h"
#include "point3.h"
#include "ray.h"
#include "utility.h"
#include "vec3.h"
#include <math.h>

camera camera_new(double vfov, double aspect_ratio) {
	camera cam;

	double theta = degrees_to_radians(vfov);
	double h = tan(theta / 2);
	double viewport_height = 2.0 * h;
	double viewport_width = aspect_ratio * viewport_height;

	double focal_length = 1.0;

	cam.origin = point3_new(0, 0, 0);
	cam.horizontal = vec3_new(viewport_width, 0, 0);
	cam.vertical = vec3_new(0, viewport_height, 0);
	cam.lower_left_corner = subtract(subtract(subtract(
		cam.origin, divide_d(cam.horizontal, 2)), divide_d(cam.vertical, 2)), vec3_new(0, 0, focal_length)
	);

	return cam;
}

ray get_ray(const camera cam, const double u, const double v) {
	return ray_new(
		cam.origin,
		subtract(
			add(
				add(cam.lower_left_corner, multiply_d(cam.horizontal, u)),
				multiply_d(cam.vertical, v)
			),
			cam.origin
		)
	);
}
