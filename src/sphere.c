#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "point3.h"
#include "ray.h"
#include "sphere.h"
#include <math.h>
#include <stdbool.h>

sphere sphere_new(const point3 center, const double radius, material m) {
	sphere s = { center, radius, m };
	return s;
}

bool sphere_hit(const sphere s, const ray r, const double t_min, const double t_max, hit_record *rec) {
	vec3 oc = subtract(r.origin, s.center);
	double a = dot(r.direction, r.direction);
	double half_b = dot(oc, r.direction);
	double c = dot(oc, oc) - s.radius * s.radius;

	double discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return false;
	double sqrtd = sqrt(discriminant);

	double root = (-1 * half_b - sqrtd) / a;
	if (root < t_min || t_max < root) {
		root = (-1 * half_b + sqrtd) / a;
		if (root < t_min || t_max < root)
			return false;
	}

	rec->t = root;
	rec->p = ray_at(r, rec->t);
	vec3 outward_normal = divide_d(
			subtract(rec->p, s.center),
			s.radius
	);
	set_face_normal(rec, r, outward_normal);
	rec->mat = s.mat;

	return true;
}

bool sphere_list_hit(const hittable_list *list, const ray r, const double t_min, const double t_max, hit_record *rec) {
	hit_record temp_rec;
	bool hit_anything = false;
	double closest_so_far = t_max;

	for (int i = 0; i < vec_length(list->objects); ++i) {
		sphere *object = (sphere *) vec_at(list->objects, i);
		
		if (sphere_hit(*object, r, t_min, closest_so_far, &temp_rec)) {
			hit_anything = true;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
		}
	}

	return hit_anything;
}
