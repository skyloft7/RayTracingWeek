#pragma once

#include "glm.hpp"

class ray {
public:

	glm::vec3 orig;
	glm::vec3 dir;

	
	ray(const glm::vec3& origin, const glm::vec3& direction) : orig(origin), dir(direction) {

	}

	const glm::vec3& origin() { return orig; }
	const glm::vec3& direction() { return dir; }

	const glm::vec3& at(float t) {
		return orig + t * dir;
	}


};


