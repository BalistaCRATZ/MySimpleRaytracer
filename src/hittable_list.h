#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <vector>
#include "constants.h"

class hittable_list : public hittable
{ /*Storing a list of all hittable objects in the scene*/

public:

	std::vector<std::unique_ptr<hittable>> objects; //Vector of unique pointers to hittable objects

	//Constructors
	hittable_list() {};
	hittable_list(std::unique_ptr<hittable> object) { add(std::move(object)); }

	void add(std::unique_ptr<hittable> object) { objects.push_back(std::move(object)); }
	void clear() { objects.clear(); }

	//Override hit function
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

};

bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{

	hit_record temp_rec;
	bool hit_anything = false;
	auto closest_so_far = t_max;

	for (const auto& object : objects) {
		if (object->hit(r, t_min, closest_so_far, temp_rec)) { //Registers the closest hit for a particular Ray
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}

	return hit_anything;

}


#endif