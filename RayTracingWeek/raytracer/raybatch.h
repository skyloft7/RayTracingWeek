#pragma once
#include <thread>
#include "glm.hpp"
#include <vector>

struct raybatch {
	
	std::vector<glm::vec3*> pixels;
	int height;
	int index;
	std::thread thread;
};