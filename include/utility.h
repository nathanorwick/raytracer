#ifndef UTILITY_H
#define UTILITY_H

double degrees_to_radians(const double degrees);

/* [0, 1) */
double random_double(void);

/* [min, max) */
double random_double_range(const double min, const double max);

double clamp(const double x, const double min, const double max);

#endif
