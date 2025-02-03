#pragma once
#include "glm.hpp"
#include "ray.h"

inline double random_number(double start, double end) {
	float r = std::rand() / (RAND_MAX + 1.0);
	return start + (end - start) * r;
}

inline glm::vec3 blend(ray& ray, glm::vec3& colorA, glm::vec3& colorB) {
	float a = 0.5;

	return (1.0f - a) * colorA + a * colorB;
}

inline glm::vec3 random_vec3() {
	while (true) {
		auto p = glm::vec3(random_number(-1.0, 1.0), random_number(-1.0, 1.0), random_number(-1.0, 1.0));
		auto lengthSquared = glm::length(p) * glm::length(p);

		if (1e-160 < lengthSquared && lengthSquared <= 1) {
			return p / glm::length(p);
		}
	}

	return glm::vec3(0.0, 0.0, 0.0);
}

inline glm::vec3 random_vec3_on_sphere(glm::vec3 randomVec3, glm::vec3 normal) {
	if (glm::dot(randomVec3, normal) > 0.0) {
		return randomVec3;
	}
	else {
		return -randomVec3;
	}
}

