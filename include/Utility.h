#ifndef UTILITY_H
#define UTILITY_H

#include <memory>
#include <limits>
#include <cstdlib>

const double INF = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;
const double epsilon = 1e-8; // used for precision checks

/*
    Convert from degrees to radians
*/
inline double degrees_to_radians(double degrees) {
    return degrees * PI / 180.0;
}

/*
    Random double in [0,1)
*/
inline double random_double()
{
    return rand() / (RAND_MAX + 1.0);
}

/*
    Random double in [min, max)
*/
inline double random_double(double min, double max)
{
    return min + (max - min)*random_double();
}

inline double clamp(double x, double min, double max)
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline bool approx_equals(double x, double y)
{
    return std::fabs(x-y) < epsilon;
}

#endif