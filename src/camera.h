#ifndef CAMERA_H
#define CAMERA_H
#include "constants.h"

class Camera
{
private:

    point3 origin, bottom_left_corner;
    vec3 horizontal, vertical, plane;

public:

    Camera() {

        const double aspect_ratio = 16.0 / 9.0;
        const double focal_length = 1.0;
        const double viewport_height = 2.0;
        const double viewport_width = aspect_ratio * viewport_height;

        origin = point3(0, 0, 0);
        horizontal = vec3(viewport_width, 0, 0);
        vertical = vec3(0, viewport_height, 0);
        plane = vec3(0, 0, focal_length);

        bottom_left_corner = origin - horizontal / 2 - vertical / 2 - plane;

    };

    ray get_ray(double u, double v) {

        return ray(origin, bottom_left_corner + u * horizontal + v * vertical - origin);

    }

};

#endif