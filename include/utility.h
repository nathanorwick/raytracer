#ifndef UTILITY_H
#define UTILITY_H

double degrees_to_radians(double degrees);

/* [0, 1) */
double random_double(void);

/* [min, max) */
double random_double_range(double min, double max);

double clamp(double x, double min, double max);

#endif
