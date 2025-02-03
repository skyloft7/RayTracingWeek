#pragma once
#include "glm.hpp"

struct hitresult {
	bool valid = false;
	glm::vec3 hit;
	float t;
	glm::vec3 normal;


};