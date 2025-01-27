#pragma once
#include "glm.hpp"
#include "materials/material.h"


struct sphere {
	glm::vec3 pos;
	float radius;
	material* mat = nullptr;
};


