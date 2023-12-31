#ifndef CAMERA_H
#define CAMERA_H

#include "color.h"
#include "hittable_list.h"
#include "image.h"
#include "point3.h"
#include "ray.h"
#include "vec3.h"

typedef struct camera {
	point3 origin;
	point3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	vec3 u, v, w;
	double lens_radius;
} camera;

/* vfov is the vertical fov in degrees (will be converted to radians inside) */
camera camera_new(point3 lookfrom, point3 lookat, vec3 vup, double vfov, double aspect_ratio, double aperture, double focus_dist);

ray get_ray(const camera cam, const double u, const double v);

color ray_color(ray r, hittable_list *world, int depth);

hittable_list *random_scene(void);

#endif
