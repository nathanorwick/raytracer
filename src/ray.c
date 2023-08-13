#include "ray.h"

ray ray_new(const point3 origin, const vec3 direction) {
	ray r = { origin, direction };
	return r;
}

point3 ray_at(const ray r, const double t) {
	return add(r.origin, multiply_d(r.direction, t));
}
