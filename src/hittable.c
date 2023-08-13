#include "hittable.h"
#include "ray.h"

void set_face_normal(hit_record *rec, const ray r, const vec3 outward_normal) {
	rec->front_face = dot(r.direction, outward_normal) < 0;
	rec->normal = (rec->front_face) ? outward_normal : negative(outward_normal);
}
