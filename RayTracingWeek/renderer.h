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
	hitresult trace_ray(ray& incidentRay, std::vector<sphere> spheres, camera& camera);
	glm::vec3 linear_to_gamma(glm::vec3& input);
	double clamp(double input, double min, double max);
	
public:
	void render(camera& camera, std::ofstream& output);
};

