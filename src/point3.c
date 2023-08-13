#include "point3.h"

point3 (*point3_new)(const double e1, const double e2, const double e3) = vec3_new;

double x(const vec3 v) {
	return (v.e)[0];
}

double y(const vec3 v) {
	return (v.e)[1];
}

double z(const vec3 v) {
	return (v.e)[2];
}
