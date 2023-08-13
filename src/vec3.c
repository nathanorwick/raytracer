#include "utility.h"
#include "vec3.h"
#include <math.h>
#include <stdbool.h>

vec3 vec3_new(const double e1, const double e2, const double e3) {
	vec3 v = { {e1, e2, e3} };
	return v;
}

double at_index(const vec3 v, const int index) {
	if (index > -1 && index < 3)
		return (v.e)[index];
	else
		return 0.0;
}

void update_index(vec3 *v, const int index, const double e) {
	if (index > -1 && index < 3)
		(v->e)[index] = e;
}

vec3 negative(const vec3 v) {
	return vec3_new(-1 * (v.e)[0], -1 * (v.e)[1], -1 * (v.e)[2]);
}

double magnitude(const vec3 v) {
	return sqrt(dot(v, v));
}

vec3 normalized(const vec3 v) {
	double mag = magnitude(v);
	return vec3_new((v.e)[0] / mag, (v.e)[1] / mag, (v.e)[2] / mag);
}

vec3 add_d(const vec3 v, const double d) {
	return vec3_new((v.e)[0] + d, (v.e)[1] + d, (v.e)[2] + d);
}

vec3 subtract_d(const vec3 v, const double d) {
	return add_d(v, -1 * d);
}

vec3 multiply_d(const vec3 v, const double d) {
	return vec3_new((v.e)[0] * d, (v.e)[1] * d, (v.e)[2] * d);
}

vec3 divide_d(const vec3 v, const double d) {
	if (d == 0)
		return vec3_new(0, 0, 0);
	else
		return multiply_d(v, 1 / d);
}

vec3 add(const vec3 u, const vec3 v) {
	return vec3_new((u.e)[0] + (v.e)[0], (u.e)[1] + (v.e)[1], (u.e)[2] + (v.e)[2]);
}

vec3 subtract(const vec3 u, const vec3 v) {
	return add(u, negative(v));
}

double dot(const vec3 u, const vec3 v) {
	return (u.e)[0] * (v.e)[0] + (u.e)[1] * (v.e)[1] + (u.e)[2] * (v.e)[2];
}

vec3 cross(const vec3 u, const vec3 v) {
	return vec3_new(
		(u.e)[1] * (v.e)[2] - (u.e)[2] * (v.e)[1],
		(u.e)[2] * (v.e)[0] - (u.e)[0] * (v.e)[2],
		(u.e)[0] * (v.e)[1] - (u.e)[1] * (v.e)[0]
	);
}

vec3 random_vec3(void) {
	return vec3_new(random_double(), random_double(), random_double());
}

vec3 random_vec3_range(const double min, const double max) {
	return vec3_new(
		random_double_range(min, max), random_double_range(min, max), random_double_range(min, max)
	);
}

vec3 random_vec3_in_unit_sphere(void) {
	while(true) {
		vec3 p = random_vec3_range(-1, 1);
		if (dot(p, p) >= 1)
			continue;
		return p;
	}
}

vec3 random_unit_vector(void) {
	return normalized(random_vec3_in_unit_sphere());
}

vec3 random_in_hemisphere(const vec3 normal) {
    vec3 in_unit_sphere = random_vec3_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0)
        return in_unit_sphere;
    else
        return negative(in_unit_sphere);
}
