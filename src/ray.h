/*Ray class has following properties:

-Implemented as a vec3 with an origin and direction (member variables
-Class methods to get the origin and direction of the ray
-A class method to project the ray by scaling it along its direction vector (returns the point the ray reaches)

*/

#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {

public:

	point3 origin;
	vec3 direction;

	ray() {};
	ray(const point3& orig, const vec3& dir) : origin(orig), direction(dir) {}

	point3 get_origin() const { return origin; }
	vec3 get_direction() const { return direction; }

	point3 at(double t) const { //We don't want to change origin or direction in this, so we keep it a const function
		return origin + t * direction;
	}

};

#endif