#pragma once


#include "camera.h"
#include <fstream>
#include "sphere.h"
#include "ray.h"
#include "glm.hpp"
#include <vector>
#include <random>

struct hitresult {
	bool miss;
	glm::vec3 color;
};


class renderer {
private:
	hitresult trace_ray(ray& ray, std::vector<sphere> spheres, camera& camera);
	double random_number(double start, double end);
	glm::vec3 random_vec3();
	glm::vec3 random_vec3_on_sphere(glm::vec3 randomVec3, glm::vec3 normal);
	// Create a random device and seed a Mersenne Twister engine
	std::random_device rd;
	std::mt19937 gen;
	std::discrete_distribution<int> dist;


	

public:
	renderer() : gen(rd()), dist({0.7, 0.3}) {

	}

	void render(camera& camera, std::ofstream& output);
};

