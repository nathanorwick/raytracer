#include "camera.h"
#include "point3.h"
#include "ray.h"
#include "vec3.h"

camera camera_new(void) {
	camera cam;

	double viewport_height = 2.0;
	double viewport_width = ASPECT_RATIO * viewport_height;
	double focal_length = 1.0;

	cam.origin = point3_new(0, 0, 0);
	cam.horizontal = vec3_new(viewport_width, 0, 0);
	cam.vertical = vec3_new(0, viewport_height, 0);
	cam.lower_left_corner = subtract(subtract(subtract(
		cam.origin, divide_d(cam.horizontal, 2)), divide_d(cam.vertical, 2)), vec3_new(0, 0, focal_length)
	);

	return cam;
}

ray get_ray(camera cam, double u, double v) {
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
