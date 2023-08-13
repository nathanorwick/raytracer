#include <math.h>
#include <stdlib.h>

double degrees_to_radians(const double degrees) {
	return (degrees * M_PI) / 180.0;
}

double random_double(void) {
	return rand() / (RAND_MAX + 1.0);
}

double random_double_range(const double min, const double max) {
	return min + (max - min) * random_double();
}

double clamp(const double x, const double min, const double max) {
	if (x < min)
		return min;
	else if (x > max)
		return max;
	else
		return x;
}
