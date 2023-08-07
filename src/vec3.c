#include "vec3.h"

struct vec3 vec_new(double e1, double e2, double e3);

double x(struct vec3 v);
double y(struct vec3 v);
double z(struct vec3 v);

struct vec3 at(struct vec3 v, int index);
struct vec3 update(struct vec3 v, int index, double e);

struct vec3 negative(struct vec3 v);
double magnitute(struct vec3 v);
struct vec3 normalize(struct vec3 v);

struct vec3 add_d(struct vec3 v, double d);
struct vec3 multiply_d(struct vec3 v, double d);
struct vec3 divide_d(struct vec3 v, double d);

struct vec3 add(struct vec3 v1, struct vec3 v2);
struct vec3 multiply(struct vec3 v1, struct vec3 v2);
struct vec3 divide(struct vec3 v1, struct vec3 v2);

double dot(struct vec3 v1, struct vec3 v2);
double cross(struct vec3 v1, struct vec3 v2);
