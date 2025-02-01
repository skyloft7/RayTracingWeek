#pragma once
#include "material.h"
#include "../util.h"

class lambertian : public material {

public:
	lambertian(glm::vec3 albedo) : material(albedo) {

	}
	
	glm::vec3 color(ray& incidentRay, glm::vec3& normal, glm::vec3& childRayDir) {

		normal += random_vec3();
		childRayDir = random_vec3_on_sphere(random_vec3(), normal);

		return albedo;
	}

	
	

	
};