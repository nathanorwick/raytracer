#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"
#include "hittable.h"
#include "ray.h"
#include <stdbool.h>

struct hit_record;

typedef struct material {
	color albedo;
	double fuzz;
	double ir;
	bool (*scatter)(const struct material mat, const ray r_in, const struct hit_record rec, color *attenuation, ray *scattered);
} material;

material lambertian_new(color albedo);

material metal_new(color albedo, double fuzz);

material dielectric_new(double index_of_refraction);

bool lambertian_scatter(const material mat, const ray r_in, const struct hit_record rec, color *attenuation, ray *scattered);

bool metal_scatter(const material mat, const ray r_in, const struct hit_record rec, color *attenuation, ray *scattered);

bool dielectric_scatter(const material mat, const ray r_in, const struct hit_record rec, color *attenuation, ray *scattered);

#endif
