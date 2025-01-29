#pragma once
#include "glm.hpp"
#include "materials/material.h"
#include "entity.h"

class sphere : public entity {
	float radius;

public:
	sphere(glm::vec3 pos, float radius, material* mat) : entity(pos, mat), radius(radius) {

	}

	
	hitresult scatter(ray& incidentRay) {

		hitresult res;

		float aq = glm::dot(incidentRay.dir, incidentRay.dir);
		float bq = 2 * glm::dot(incidentRay.orig - get_pos(), incidentRay.dir);
		float cq = glm::dot(incidentRay.orig - get_pos(), incidentRay.orig - get_pos()) - radius * radius;

		float discriminant = bq * bq - 4 * aq * cq;

		if (discriminant >= 0) {
			float t = (-bq - glm::sqrt(discriminant)) / 2 * aq;

			if (t >= 0) {


				glm::vec3 hit = incidentRay.orig + t * incidentRay.dir;
				glm::vec3 normal = glm::normalize(hit - get_pos());

				res.t = t;
				res.hit = hit;
				res.normal = normal;
				res.valid = true;

			}
		}

		return res;
	}


};

