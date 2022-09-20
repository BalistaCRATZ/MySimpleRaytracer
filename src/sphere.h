#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"


class sphere : public hittable
{
public:

	double radius;
	point3 centre;
	std::shared_ptr<material> mat_ptr;

	sphere() {};
	sphere(double rad, const point3& c, std::shared_ptr<material> m)
	: radius(rad), centre(c), mat_ptr(m) {};

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {

	double a = dot(r.get_direction(), r.get_direction());
	double b = 2.0 * dot(r.get_direction(), r.get_origin() - centre);
	double c = dot(r.get_origin() - centre, r.get_origin() - centre) - (radius * radius);

	double discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0.0) return false;

	double sol = (-b - sqrt(discriminant)) / (2.0 * a);

	if (sol < t_min || sol > t_max) {
		sol = (-b + sqrt(discriminant)) / (2.0 * a);
		if (sol < t_min || sol > t_max) {
			return false;
		}
	}

	rec.t = sol;
	rec.p = r.at(sol);
	rec.normal = unit_vector(rec.p - centre);
	rec.mat_ptr = mat_ptr;

	return true;

}


#endif