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
} camera;

camera camera_new(void);

ray get_ray(camera cam, double u, double v);

#endif
