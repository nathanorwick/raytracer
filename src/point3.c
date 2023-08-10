#include "point3.h"

point3 (*point3_new)(double e1, double e2, double e3) = vec3_new;

double x(vec3 v) {
	return (v.e)[0];
}

double y(vec3 v) {
	return (v.e)[1];
}

double z(vec3 v) {
	return (v.e)[2];
}
