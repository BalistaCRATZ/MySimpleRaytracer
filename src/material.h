#ifndef MATERIAL_H
#define MATERIAL_H

#include "constants.h"

struct hit_record;

class material
{
public:

	//Abstract class material
	virtual bool scatter(const ray& r_in, const hit_record& rec, colour& attenuation, ray& scattered) const = 0;

};

class lambertian : public material
{
public:

	colour albedo;

	lambertian(const colour& a) : albedo(a) {};

	virtual bool scatter(const ray& r_in, const hit_record& rec, colour& attenuation, ray& scattered)
		const override {

		if (dot(r_in.get_direction(), rec.normal) > 0.0) { //Ray is inside sphere
			auto scatter_direction = -rec.normal + random_in_unit_sphere(); //Direction of negative normal
		}

		//Ray is outside sphere, so we go in the direction of positive normal
		auto scatter_direction = rec.normal + random_in_unit_sphere();

		// Catch degenerate scatter direction
		if (scatter_direction.near_zero())
			scatter_direction = rec.normal;

		scattered = ray(rec.p, scatter_direction);
		attenuation = albedo;
		return true;

	}
};

class metal : public material
{
public:

	colour albedo;

	metal(const colour& a) : albedo(a) {};

	virtual bool scatter(const ray& r_in, const hit_record& rec, colour& attenuation, ray& scattered)
		const override {

		if (dot(r_in.get_direction(), rec.normal) > 0.0) { //Ray is inside sphere
			auto reflected_direction = reflect(r_in.get_direction(), -rec.normal); //Direction of negative normal
		}

		//Ray is outside sphere, so we go in the direction of positive normal
		auto reflected_direction = reflect(unit_vector(r_in.get_direction()), rec.normal);

		scattered = ray(rec.p, reflected_direction);
		attenuation = albedo;
		return (dot(scattered.get_direction(), rec.normal) > 0);


	}

};


#endif