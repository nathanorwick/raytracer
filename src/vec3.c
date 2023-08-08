#include "vec3.h"
#include <math.h>

vec3 vec3_new(double e1, double e2, double e3) {
	vec3 v = { {e1, e2, e3} };
	return v;
}

double at_index(vec3 v, int index) {
	if (index > -1 && index < 3)
		return (v.e)[index];
	else
		return 0.0;
}

void update_index(vec3 *v, int index, double e) {
	if (index > -1 && index < 3)
		(v->e)[index] = e;
}

vec3 negative(vec3 v) {
	return vec3_new(-1 * (v.e)[0], -1 * (v.e)[1], -1 * (v.e)[2]);
}

double magnitude(vec3 v) {
	return sqrt(dot(v, v));
}

vec3 normalized(vec3 v) {
	double mag = magnitude(v);
	return vec3_new((v.e)[0] / mag, (v.e)[1] / mag, (v.e)[2] / mag);
}

vec3 add_d(vec3 v, double d) {
	return vec3_new((v.e)[0] + d, (v.e)[1] + d, (v.e)[2] + d);
}

vec3 subtract_d(vec3 v, double d) {
	return add_d(v, -1 * d);
}

vec3 multiply_d(vec3 v, double d) {
	return vec3_new((v.e)[0] * d, (v.e)[1] * d, (v.e)[2] * d);
}

vec3 divide_d(vec3 v, double d) {
	if (d == 0)
		return vec3_new(0, 0, 0);
	else
		return multiply_d(v, 1 / d);
}

vec3 add(vec3 u, vec3 v) {
	return vec3_new((u.e)[0] + (v.e)[0], (u.e)[1] + (v.e)[1], (u.e)[2] + (v.e)[2]);
}

vec3 subtract(vec3 u, vec3 v) {
	return add(u, negative(v));
}

double dot(vec3 u, vec3 v) {
	return (u.e)[0] * (v.e)[0] + (u.e)[1] * (v.e)[1] + (u.e)[2] * (v.e)[2];
}

vec3 cross(vec3 u, vec3 v) {
	return vec3_new(
		(u.e)[1] * (v.e)[2] - (u.e)[2] * (v.e)[1],
		(u.e)[2] * (v.e)[0] - (u.e)[0] * (v.e)[2],
		(u.e)[0] * (v.e)[1] - (u.e)[1] * (v.e)[0]
	);
}
