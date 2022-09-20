#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "ray.h"
#include "vec3.h"

#include <cmath>
#include <limits>
#include <cstdlib>
#include <memory>

using std::sqrt;

const double pi = 3.1415926535897932385;
const double infinity = std::numeric_limits<double>::infinity();

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double rand_double() {

    return rand() / (RAND_MAX + 1.0);

}

inline double rand_double(double min, double max) {
    
    return min + (max - min) * rand_double();

}

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

#endif