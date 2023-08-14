#include "hittable.h"
#include "material.h"
#include "ray.h"
#include "vec3.h"

material material_new(enum materials type, color albedo, double fuzz) {
	material mat;

	mat.albedo = albedo;
	mat.fuzz = (fuzz < 1) ? fuzz : 1;
	
	switch(type) {
		case LAMBERTIAN:
			mat.scatter = lambertian_scatter;
			break;
		case METAL:
			mat.scatter = metal_scatter;
			break;
	}

	return mat;	
}

bool lambertian_scatter(const material mat, const ray r_in, const struct hit_record rec, color *attenuation, ray *scattered) {
	(void)r_in;
	vec3 scatter_direction = add(rec.normal, random_unit_vector());
	
	if (near_zero(scatter_direction))
		scatter_direction = rec.normal;

	*scattered = ray_new(rec.p, scatter_direction);
	*attenuation = mat.albedo;

	return true;
}

bool metal_scatter(const material mat, const ray r_in, const struct hit_record rec, color *attenuation, ray *scattered) {
	vec3 reflected = reflect(normalized(r_in.direction), rec.normal);
	*scattered = ray_new(
		rec.p,
		add(reflected, multiply_d(random_vec3_in_unit_sphere(), mat.fuzz))
	);
	*attenuation = mat.albedo;
	return (dot(scattered->direction, rec.normal) > 0);
}
