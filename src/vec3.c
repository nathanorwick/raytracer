#include "vec3.h"
#include <math.h>

vec3 vec3_new(double e1, double e2, double e3) {
	vec3 v = { {e1, e2, e3} };
	return v;
}

double x(vec3 v) {
	return (v.e)[0];
}

double y(vec3 v) {
	return (v.e)[1];
}

double z(vec3 v) {
	return (v.e)[2];
}

double at(vec3 v, int index) {
	if (index > -1 && index < 3)
		return (v.e)[index];
	else
		return -1.0;
}

void update(vec3 *v, int index, double e) {
	if (index > -1 && index < 3)
		(v->e)[index] = e;
}

vec3 negative(vec3 v) {
	return vec3_new(-1 * x(v), -1 * y(v), -1 * z(v));
}

double magnitude(vec3 v) {
	return sqrt(dot(v, v));
}

vec3 normalize(vec3 v) {
	double mag = magnitude(v);
	return vec3_new((v.e)[0] / mag, (v.e)[1] / mag, (v.e)[2] / mag);
}

vec3 add_d(vec3 v, double d) {
	return vec3_new(x(v) + d, y(v) + d, z(v) + d);
}

vec3 subtract_d(vec3 v, double d) {
	return add_d(v, -1 * d);
}

vec3 multiply_d(vec3 v, double d) {
	return vec3_new(x(v) * d, y(v) * d, z(v) * d);
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
	return x(u) * x(v) + y(u) * y(v) + z(u) * z(v);
}

vec3 cross(vec3 u, vec3 v) {
	return vec3_new(
		(u.e)[1] * (v.e)[2] - (u.e)[2] * (v.e)[1],
		(u.e)[2] * (v.e)[0] - (u.e)[0] * (v.e)[2],
		(u.e)[0] * (v.e)[1] - (u.e)[1] * (v.e)[0]
	);
}
