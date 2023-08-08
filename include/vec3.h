#ifndef VEC3_H
#define VEC3_H

struct vec3 {
	double e[3];
};

struct vec3 vec3_new(double e1, double e2, double e3);

double x(struct vec3 v);
double y(struct vec3 v);
double z(struct vec3 v);

double at(struct vec3 v, int index);
void update(struct vec3 *v, int index, double e);

struct vec3 negative(struct vec3 v);
double magnitude(struct vec3 v);
struct vec3 normalized(struct vec3 v);

struct vec3 add_d(struct vec3 v, double d);
struct vec3 subtract_d(struct vec3 v, double d);
struct vec3 multiply_d(struct vec3 v, double d);
struct vec3 divide_d(struct vec3 v, double d);

struct vec3 add(struct vec3 u, struct vec3 v);
struct vec3 subtract(struct vec3 u, struct vec3 v);

double dot(struct vec3 u, struct vec3 v);
struct vec3 cross(struct vec3 u, struct vec3 v);

#endif
