#include <iostream>
#include "colour.h"
#include "ray.h"
#include "vec3.h"
#include "Raytracer.h"
#include "sphere.h"

colour ray_colour(const ray& r)
{ /*Calculating the colour of the pixel on the viewport based on the direction of the ray hitting that point*/

    hit_record rec;
    sphere s = sphere(0.5, point3(0.0, 0.0, -1.0));

    if (s.hit(r, 0, 100000, rec)) {
        return 0.5 * colour(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
    }
    
    vec3 unit_direction = unit_vector(r.get_direction());
    double t = 0.5*(unit_direction.y() + 1);
    return (1.0 - t) * colour(1.0, 1.0, 1.0) + t * colour(0.5, 0.7, 1.0);

}


int main(void) {

    //Image 
    const double aspect_ratio = 16.0 / 9.0;

    const int image_width = 400;
    const int image_height = static_cast<int>(image_width/aspect_ratio);

    //Camera
    point3 origin = point3(0, 0, 0);
    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = aspect_ratio * viewport_height;

    //Viewport Axes
    vec3 horizontal = vec3(viewport_width, 0, 0);
    vec3 vertical = vec3(0, viewport_height, 0);
    vec3 plane = vec3(0, 0, focal_length);

    point3 bottom_left_corner = origin - horizontal / 2 - vertical / 2 - plane;

    //Render

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << " " << std::flush;
        for (int i = 0; i < image_width; ++i) {

            double u = double(i) / (image_width - 1);
            double v = double(j) / (image_height - 1);

            ray r(origin, bottom_left_corner + u * horizontal + v * vertical - origin);
            colour pixel_colour = ray_colour(r);
            write_colour(std::cout, pixel_colour);
 
        }
    }

    std::cerr << "\nDone.\n";

}