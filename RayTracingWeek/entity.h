#pragma once
#include "glm.hpp"
#include "materials/material.h"
#include "hitresult.h"
#include "ray.h"

class entity {
private:
	glm::vec3 pos;
	material* mat = nullptr;

public:

	entity(glm::vec3 pos, material* mat) : pos(pos), mat(mat) {

	}

	~entity() {
		std::cout << "baibai" << std::endl;
	}

	glm::vec3& get_pos() {
		return pos;
	}

	material* get_mat() {
		return mat;
	}

	virtual hitresult scatter(ray& incidentRay) {
		hitresult res;
		return res;
	}

};