#include "camera.h"
#include "point3.h"
#include "ray.h"
#include "utility.h"
#include "vec3.h"
#include <math.h>

camera camera_new(point3 lookfrom, point3 lookat, vec3 vup, double vfov, double aspect_ratio) {
	camera cam;

	double theta = degrees_to_radians(vfov);
	double h = tan(theta / 2);
	double viewport_height = 2.0 * h;
	double viewport_width = aspect_ratio * viewport_height;

	vec3 w = normalized(subtract(lookfrom, lookat));
	vec3 u = normalized(cross(vup, w));
	vec3 v = cross(w, u);

	cam.origin = lookfrom;
	cam.horizontal = multiply_d(u, viewport_width);
	cam.vertical = multiply_d(v, viewport_height);
	cam.lower_left_corner = subtract(
		subtract(subtract(cam.origin, multiply_d(cam.horizontal, 0.5)), multiply_d(cam.vertical, 0.5)),
		w
	);

	return cam;
}

ray get_ray(const camera cam, const double s, const double t) {
	return ray_new(
		cam.origin,
		subtract(
			add(add(cam.lower_left_corner, multiply_d(cam.horizontal, s)), multiply_d(cam.vertical, t)),
			cam.origin)
	);
}
