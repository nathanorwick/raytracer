#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"
#include "hittable.h"
#include "ray.h"
#include <stdbool.h>

struct hit_record;

typedef struct material {
	color albedo;
	bool (*scatter)(const struct material mat, const ray r_in, const struct hit_record rec, color *attenuation, ray *scattered);
} material;

/* Scatter functions */

bool lambertian_scatter(const material mat, const ray r_in, const struct hit_record rec, color *attenuation, ray *scattered);


bool metal_scatter(const material mat, const ray r_in, const struct hit_record rec, color *attenuation, ray *scattered);

#endif
