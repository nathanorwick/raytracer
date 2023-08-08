#include "ray.h"

ray ray_new(point3 origin, vec3 direction) {
	ray r = { origin, direction };
	return r;
}

point3 ray_at(ray r, double t) {
	return add(r.origin, multiply_d(r.direction, t));
}
