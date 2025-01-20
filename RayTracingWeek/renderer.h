#pragma once


#include "camera.h"
#include <fstream>
#include "color3.h"
#include "sphere.h"
#include "ray.h"



class renderer {
public:
	color3 trace_ray(ray& ray, sphere& sphere);
	void render(camera& camera, std::ofstream& output);
};

