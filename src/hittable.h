#ifndef HITTABLE_H
#define HITTABLE_H

#include "constants.h"

class material;

struct hit_record {
	double t;
	point3 p;
	vec3 normal;
	std::shared_ptr<material> mat_ptr;
};

class hittable {

public:
	//Pure virtual function to define hittable as an abstract class
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif