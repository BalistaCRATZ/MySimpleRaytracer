# CMakeList.txt : CMake project for Raytracer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (Raytracer  "Raytracer.h" "vec3.h" "Raytracer.cpp" "colour.h" "ray.h" "hittable.h" "sphere.h" "hittable_list.h" "constants.h" "camera.h")

# TODO: Add tests and install targets if needed.
