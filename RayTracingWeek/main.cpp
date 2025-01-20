#include <iostream>
#include <fstream>
#include "camera.h"
#include "ray.h"
#include "renderer.h"


int main() {
	

	int imageWidth = 640;
	int imageHeight = 480;

	std::ofstream output;
	output.open("image.ppm");

	output << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";


	auto aspectRatio = (float) imageWidth / imageHeight;

	vec3 cameraPos = vec3(0.0, 0.0, 0.0);
	camera camera(2.0 * aspectRatio, 2.0, imageWidth, imageHeight, cameraPos);
	
	renderer ren;

	ren.render(camera, output);

	


	return 0;
}