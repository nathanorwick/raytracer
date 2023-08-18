#include "camera.h"
#include "hittable_list.h"
#include "hittable.h"
#include "material.h"
#include "point3.h"
#include "ray.h"
#include "sphere.h"
#include "utility.h"
#include "vec3.h"
#include <math.h>
#include <stdlib.h>

camera camera_new(point3 lookfrom, point3 lookat, vec3 vup, double vfov, double aspect_ratio, double aperture, double focus_dist) {
	camera cam;

	double theta = degrees_to_radians(vfov);
	double h = tan(theta / 2);
	double viewport_height = 2.0 * h;
	double viewport_width = aspect_ratio * viewport_height;

	cam.w = normalized(subtract(lookfrom, lookat));
	cam.u = normalized(cross(vup, cam.w));
	cam.v = cross(cam.w, cam.u);

	cam.origin = lookfrom;
	cam.horizontal = multiply_d(cam.u, viewport_width * focus_dist);
	cam.vertical = multiply_d(cam.v, viewport_height * focus_dist);
	cam.lower_left_corner = subtract(
		subtract(subtract(cam.origin, multiply_d(cam.horizontal, 0.5)), multiply_d(cam.vertical, 0.5)),
		multiply_d(cam.w, focus_dist)
	);

	cam.lens_radius = aperture / 2;

	return cam;
}

ray get_ray(const camera cam, const double s, const double t) {
	vec3 rd = multiply_d(random_in_unit_disk(), cam.lens_radius);
	vec3 offset = add(
		multiply_d(cam.u, x(rd)),
		multiply_d(cam.v, y(rd))
	);

	return ray_new(
		add(cam.origin, offset),
		subtract(
			subtract(add(add(cam.lower_left_corner, multiply_d(cam.horizontal, s)), multiply_d(cam.vertical, t)), cam.origin),
			offset
		)
	);
}

color ray_color(ray r, hittable_list *world, int depth) {
	hit_record rec;

	if (depth <= 0)
		return color_new(0, 0, 0);

	if (sphere_list_hit(world, r, 0.001, INFINITY, &rec)) {
		ray scattered;
		color attenuation;
		if (rec.mat.scatter(rec.mat, r, rec, &attenuation, &scattered))
			return multiply(attenuation, ray_color(scattered, world, depth - 1));
		return color_new(0, 0, 0);
	}

	vec3 unit_direction = normalized(r.direction);
	double t = 0.5 * (y(unit_direction) + 1.0);
	return add(
		multiply_d(color_new(1.0, 1.0, 1.0), (1.0 -t)),
		multiply_d(color_new(0.5, 0.7, 1.0), t)
	);
}

hittable_list *random_scene(void) {
	hittable_list *world = hittable_list_new();

	if (world == NULL || world->objects == NULL)
		return NULL;

	material ground_material = lambertian_new(color_new(0.5, 0.5, 0.5));
	sphere *ground_sphere = malloc(sizeof(*ground_sphere));
	*ground_sphere = sphere_new(point3_new(0, -1000, 0), 1000, ground_material);
	vec_push_back(world->objects, ground_sphere);

	for (int a = -11; a < 11; ++a) {
		for (int b = -11; b < 11; ++b) {
			double choose_mat = random_double();
			point3 center = point3_new(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

			if (magnitude(subtract(center, point3_new(4, 0.2, 0))) > 0.9) {
				material sphere_material;
				sphere *random_sphere = malloc(sizeof(*random_sphere));

				if (choose_mat < 0.8) {
					// diffuse
					point3 albedo = multiply(random_vec3(), random_vec3());
					sphere_material = lambertian_new(albedo);
					*random_sphere = sphere_new(center, 0.2, sphere_material);
				} else if (choose_mat < 0.95) {
					// metal
					point3 albedo = random_vec3_range(0.5, 1);
					double fuzz = random_double_range(0, 0.5);
					sphere_material = metal_new(albedo, fuzz);
					*random_sphere = sphere_new(center, 0.2, sphere_material);
				} else {
					// glass
					sphere_material = dielectric_new(1.5);
					*random_sphere = sphere_new(center, 0.2, sphere_material);
				}

				vec_push_back(world->objects, random_sphere);
			}
		}
	}

	material material1 = dielectric_new(1.5);
	sphere *sphere1 = malloc(sizeof(*sphere1));
	*sphere1 = sphere_new(point3_new(0, 1, 0), 1.0, material1);
	vec_push_back(world->objects, sphere1);

	material material2 = lambertian_new(color_new(0.4, 0.2, 0.1));
	sphere *sphere2 = malloc(sizeof(*sphere2));
	*sphere2 = sphere_new(point3_new(-4, 1, 0), 1.0, material2);
	vec_push_back(world->objects, sphere2);

	material material3 = metal_new(color_new(0.7, 0.6, 0.5), 0.0);
	sphere *sphere3 = malloc(sizeof(*sphere3));
	*sphere3 = sphere_new(point3_new(4, 1, 0), 1.0, material3);
	vec_push_back(world->objects, sphere3);

	return world;
}
