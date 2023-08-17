#include "camera.h"
#include "point3.h"
#include "ray.h"
#include "utility.h"
#include "vec3.h"
#include <math.h>

camera camera_new(point3 lookfrom, point3 lookat, vec3 vup, double vfov, double aspect_ratio, double aperture, double focus_dist) {
	camera cam;

	double theta = degrees_to_radians(vfov);
	double h = tan(theta / 2);
	double viewport_height = 2.0 * h;
	double viewport_width = aspect_ratio * viewport_height;

	cam.w = normalized(subtract(lookfrom, lookat));
	cam.u = normalized(cross(vup, cam.w));
	cam.v = cross(cam.w, cam.u);

	cam.origin = lookfrom;
	cam.horizontal = multiply_d(cam.u, viewport_width * focus_dist);
	cam.vertical = multiply_d(cam.v, viewport_height * focus_dist);
	cam.lower_left_corner = subtract(
		subtract(subtract(cam.origin, multiply_d(cam.horizontal, 0.5)), multiply_d(cam.vertical, 0.5)),
		multiply_d(cam.w, focus_dist)
	);

	cam.lens_radius = aperture / 2;

	return cam;
}

ray get_ray(const camera cam, const double s, const double t) {
	vec3 rd = multiply_d(random_in_unit_disk(), cam.lens_radius);
	vec3 offset = add(
		multiply_d(cam.u, x(rd)),
		multiply_d(cam.v, y(rd))
	);

	return ray_new(
		add(cam.origin, offset),
		subtract(
			subtract(add(add(cam.lower_left_corner, multiply_d(cam.horizontal, s)), multiply_d(cam.vertical, t)), cam.origin),
			offset
		)
	);
}
