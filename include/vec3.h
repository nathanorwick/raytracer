#ifndef VEC3_H
#define VEC3_H

typedef struct vec3 {
	double e[3];
} vec3;

vec3 vec3_new(const double e1, const double e2, const double e3);

double at_index(const vec3 v, const int index);
void update_index(vec3 *v, const int index, const double e);

vec3 negative(const vec3 v);
double magnitude(const vec3 v);
vec3 normalized(const vec3 v);

vec3 add_d(const vec3 v, const double d);
vec3 subtract_d(const vec3 v, const double d);
vec3 multiply_d(const vec3 v, const double d);
vec3 divide_d(const vec3 v, const double d);

vec3 add(const vec3 u, const vec3 v);
vec3 subtract(const vec3 u, const vec3 v);

double dot(const vec3 u, const vec3 v);
struct vec3 cross(const vec3 u, const vec3 v);

vec3 random_vec3(void);
vec3 random_vec3_range(const double min, const double max);
vec3 random_vec3_in_unit_sphere(void);

vec3 random_unit_vector(void);
vec3 random_in_hemisphere(const vec3 normal);

#endif
