#ifndef CAMERA_H
#define CAMERA_H

#include "point3.h"
#include "ray.h"
#include "vec3.h"

#define ASPECT_RATIO (16.0 / 9.0)
#define IMAGE_WIDTH 400
#define IMAGE_HEIGHT (int) (IMAGE_WIDTH / ASPECT_RATIO)

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

#endif
