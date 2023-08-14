#include "hittable.h"
#include "material.h"
#include "ray.h"
#include "vec3.h"

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
	*scattered = ray_new(rec.p, reflected);
	*attenuation = mat.albedo;
	return (dot(scattered->direction, rec.normal) > 0);
}
