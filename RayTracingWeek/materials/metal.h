#pragma once
#include "material.h"
#include "../util.h"



class metal : public material {
public:
	metal(glm::vec3 albedo) : material(albedo) {

	}

	glm::vec3 color(ray& incidentRay, glm::vec3& normal, glm::vec3& childRayDir) {

		//std::cout << "Foo bar" << std::endl;

		childRayDir = glm::reflect(incidentRay.direction(), normal);

		return albedo;
	}



};