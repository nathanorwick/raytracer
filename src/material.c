#include "hittable.h"
#include "material.h"
#include "ray.h"
#include "vec3.h"

material lambertian_new(color albedo) {
	material mat;
	mat.albedo = albedo;
	mat.scatter = lambertian_scatter;
	return mat;
}

material metal_new(color albedo, double fuzz) {
	material mat;
	mat.albedo = albedo;
	mat.fuzz = fuzz;
	mat.scatter = metal_scatter;
	return mat;
}

material dielectric_new(double index_of_refraction) {
	material mat;
	mat.ir = index_of_refraction;
	mat.scatter = dielectric_scatter;
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

bool dielectric_scatter(const material mat, const ray r_in, const struct hit_record rec, color *attenuation, ray *scattered) {
	*attenuation = color_new(1.0, 1.0, 1.0);
	double refraction_ratio = rec.front_face ? (1.0 / mat.ir) : mat.ir;
	vec3 unit_direction = normalized(r_in.direction);
	vec3 refracted = refract(unit_direction, rec.normal, refraction_ratio);
	*scattered = ray_new(rec.p, refracted);
	return true;
}
