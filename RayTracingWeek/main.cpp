#include <iostream>
#include <fstream>
#include "camera.h"
#include "ray.h"
#include "renderer.h"
#include "scene.h"
#include "materials/lambertian.h"
#include "materials/metal.h"

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

	scene scene;
	{
		scene.add_entity(new sphere(
			glm::vec3(0.0, 100.5, -1),
			100,
			new lambertian(glm::vec3(1.0, 1.0, 1.0))
		));
		

		scene.add_entity(new sphere(
			glm::vec3(0.0, 0.3, -1),
			0.2,
			new lambertian(glm::vec3(0.3, 0.0, 1.0))
		));

		scene.add_entity(new sphere(
			glm::vec3(1.0, -0.45, -1),
			0.2,
			new lambertian(glm::vec3(0.3, 0.9, 1.0))
		));

		scene.add_entity(new sphere(
			glm::vec3(1.0, 0.0, -1),
			0.2,
			new metal(glm::vec3(0.7, 0.2, 1.0))
		));

		scene.add_entity(new sphere(
			glm::vec3(1.0, 0.3, -0.7),
			0.2,
			new lambertian(glm::vec3(0.9, 0.2, 0.4))
		));

		scene.add_entity(new sphere(
			glm::vec3(-1.0, 0.45, 0.5),
			0.2,
			new lambertian(glm::vec3(0.9, 0.5, 0.2))
		));

		scene.add_entity(new sphere(
			glm::vec3(-0.5, 0.415, -0.5),
			0.1,
			new metal(glm::vec3(0.3, 0.5, 1.0))
		));
		

	}
	
	
	renderer ren;

	ren.render(camera, scene, output);

	


	return 0;
}