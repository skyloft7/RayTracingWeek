#pragma once
#include "glm.hpp"
#include "../ray.h"
#include <iostream>

class material {
public:
	
	glm::vec3 albedo;

	material(glm::vec3 albedo) : albedo(albedo) {

	}
	
	virtual glm::vec3 color(ray& incidentRay, glm::vec3& normal, glm::vec3& childRayDir) {
		return glm::vec3(0.0);
	}
	
	
};