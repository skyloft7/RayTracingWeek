#include <iostream>
#include <fstream>
#include "camera.h"
#include "ray.h"
#include "renderer.h"


int main() {
	
	auto aspectRatio = (float)16.0 / 9.0;


	int imageWidth = 1920;
	int imageHeight = int(imageWidth / aspectRatio);
	imageHeight = (imageHeight < 1) ? 1 : imageHeight;

	std::ofstream output;
	output.open("image.ppm");

	output << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";



	glm::vec3 cameraPos = glm::vec3(0.0, 0.0, 1.0);

	float vfov = 45;

	float h = glm::tan((vfov / 2.0) * (3.14 / 180)) * 2 * 1;

	camera camera(h * aspectRatio, h, imageWidth, imageHeight, cameraPos, -1);
	
	renderer ren;

	ren.render(camera, output);

	


	return 0;
}