#include <iostream>
#include "colour.h"
#include "Raytracer.h"
#include "sphere.h"
#include "hittable_list.h"
#include "constants.h"
#include "camera.h"
#include "material.h"

colour ray_colour(const ray& r, const hittable_list& world, int depth)
{ /*Calculating the colour of the pixel on the viewport based on the direction of the ray hitting that point*/

    hit_record rec;
    bool ray_outside = true;

    //Recursion depth limit (number of ray bounces)
    if (depth <= 0) {
        return colour(0, 0, 0);
    }

    //Checking if the ray has hit any objects in our world
    if (world.hit(r, 0.001, infinity, rec)) {

        ray scattered;
        colour attenuation;

        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {

            return attenuation * ray_colour(scattered, world, depth - 1);

        }

        return colour(0, 0, 0);
    }
    
    //Sky background (brings light into the scene)

    vec3 unit_direction = unit_vector(r.get_direction());
    double t = 0.5*(unit_direction.y() + 1);
    return (1.0 - t) * colour(1.0, 1.0, 1.0) + t * colour(0.5, 0.7, 1.0);

}


int main(void) {

    //Image 
    const double aspect_ratio = 16.0 / 9.0;

    const int image_width = 400;
    const int image_height = static_cast<int>(image_width/aspect_ratio);
    const int samples = 100;
    const int max_depth = 10;

    //World
    hittable_list world;

    auto material_centre = std::make_shared<metal>(colour(0.8, 0.8, 0.8));
    auto material_ground = std::make_shared<lambertian>(colour(0.7, 0.3, 0.3));
    auto material_side = std::make_shared<lambertian>(colour(1, 0.5, 0.5));

    world.add(std::make_unique<sphere>(0.5, point3(0, 0, -1), material_centre));
    world.add(std::make_unique<sphere>(100, point3(0, -100.5, -1), material_ground));
    world.add(std::make_unique<sphere>(0.5, point3(1, 0, -1), material_centre));
    world.add(std::make_unique<sphere>(0.5, point3(-1, 0, -1), material_centre));

    Camera cam;

    //Render

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << " " << std::flush;
        for (int i = 0; i < image_width; ++i) {

            colour pixel_colour(0, 0, 0);

            for (int s = 0; s < samples; ++s) {

                double u = double(i + rand_double()) / (image_width - 1);
                double v = double(j + rand_double()) / (image_height - 1);

                ray r = cam.get_ray(u, v);
                pixel_colour += ray_colour(r, world, max_depth);
            }

            write_colour(std::cout, pixel_colour, samples);
        }
    }

    std::cerr << "\nDone.\n";

}