#pragma once


#include "camera.h"
#include <fstream>
#include "sphere.h"
#include "ray.h"
#include "glm.hpp"
#include "scene.h"
#include <vector>
#include <random>

struct rayresult {
	bool miss;
	glm::vec3 color;
};


class renderer {
private:
	rayresult trace_ray(ray& incidentRay, scene& scene, camera& camera);
	glm::vec3 linear_to_gamma(glm::vec3& input);
	double clamp(double input, double min, double max);
	
public:
	void render(camera& camera, scene& scene, std::ofstream& output);
};

