#ifndef COLOUR_H
#define COLOUR_H

#include "constants.h"
#include <iostream>

void write_colour(std::ostream& out, colour pixel_colour, int samples)
{

    auto r = pixel_colour.x();
    auto g = pixel_colour.y();
    auto b = pixel_colour.z();

    // Gamma-correction
    auto scale = 1.0 / samples;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

	out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
		<< static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
		<< static_cast<int>(256 * clamp(b, 0.0, 0.999)) << std::endl;

}

#endif 
