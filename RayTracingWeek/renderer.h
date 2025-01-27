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
	double linear_to_gamma(double input);
	double clamp(double input, double min, double max);
	
public:
	void render(camera& camera, std::ofstream& output);
};

