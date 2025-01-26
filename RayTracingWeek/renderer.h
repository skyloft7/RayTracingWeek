#pragma once


#include "camera.h"
#include <fstream>
#include "sphere.h"
#include "ray.h"
#include "glm.hpp"
#include <vector>
#include <random>
#include <random>
#include "light.h"

struct hitresult {
	bool miss;
	glm::vec3 color;
};


class renderer {
private:
	hitresult trace_ray(ray& incidentRay, std::vector<sphere> spheres, std::vector<light> lights, camera& camera);
	double random_number(double start, double end);
	double linear_to_gamma(double input);
	double clamp(double input, double min, double max);
	glm::vec3 random_vec3();
	glm::vec3 random_vec3_on_sphere(glm::vec3 randomVec3, glm::vec3 normal);
	// Create a random device and seed a Mersenne Twister engine
	std::random_device rd;
	std::mt19937 gen;
	std::discrete_distribution<int> dist;


	

public:
	renderer() : gen(rd()), dist({0.2, 0.8}) {

	}

	void render(camera& camera, std::ofstream& output);
};

