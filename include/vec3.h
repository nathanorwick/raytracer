#ifndef VEC3_H
#define VEC3_H

typedef struct vec3 {
	double e[3];
} vec3;

vec3 vec3_new(double e1, double e2, double e3);

double x(vec3 v);
double y(vec3 v);
double z(vec3 v);

double at(vec3 v, int index);
void update(vec3 *v, int index, double e);

vec3 negative(vec3 v);
double magnitude(vec3 v);
vec3 normalized(vec3 v);

vec3 add_d(vec3 v, double d);
vec3 subtract_d(vec3 v, double d);
vec3 multiply_d(vec3 v, double d);
vec3 divide_d(vec3 v, double d);

vec3 add(vec3 u, vec3 v);
vec3 subtract(vec3 u, vec3 v);

double dot(vec3 u, vec3 v);
struct vec3 cross(vec3 u, vec3 v);

#endif
