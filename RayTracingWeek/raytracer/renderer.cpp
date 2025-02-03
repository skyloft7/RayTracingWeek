#include "renderer.h"
#include <iostream>
#include "materials/material.h"
#include "materials/metal.h"
#include "materials/lambertian.h"
#include "util.h"
#include "scene.h"
#include "entity.h"
#include "hitresult.h"

glm::vec3 renderer::linear_to_gamma(glm::vec3& input) {

	if (input.r > 0) input.r = sqrt(input.r);
	if (input.g > 0) input.g = sqrt(input.g);
	if (input.b > 0) input.b = sqrt(input.b);

	return input;
}

rayresult renderer::trace_ray(ray& incidentRay, scene& scene, camera& camera) {
	traceRayDepth++;

	
	


	float closestZ = -100;
	entity* closestEntity = nullptr;
	glm::vec3* closestHit = nullptr;
	glm::vec3* closestNormal = nullptr;

	for (entity* entity : scene.get_entities()) {
		hitresult res = entity->scatter(incidentRay);

		if (res.valid) {
			if (res.hit.z > closestZ) {
				closestHit = &res.hit;
				closestNormal = &res.normal;
				closestEntity = entity;
				closestZ = res.hit.z;
			}
		}
	}

	

	
	

	rayresult res;


	if (closestEntity != nullptr) {
		res.miss = false;		
		
		
		
		glm::vec3 childRayDir;
		res.color = closestEntity->get_mat()->color(incidentRay, *closestNormal, childRayDir);
		
		if (true || traceRayDepth <= 10) {
			//std::cout << traceRayDepth << std::endl;

			ray childRay(*closestHit * 1.1f, childRayDir);

			rayresult childRayRes = trace_ray(childRay, scene, camera);

			if (!childRayRes.miss) {
				res.color = 0.3f * blend(childRay, res.color, childRayRes.color);
				return res;
			}
			
		}
		
		

		
		

	
		return res;

	}
	

	res.miss = true;
	res.color = glm::vec3{ 1.0, 0.0, 0.0 };

	return res;
}

double renderer::clamp(double input, double min, double max) {
	if (input <= min) return min;
	if (input >= max) return max;

	return input;
}



void renderer::render(camera& camera, scene& scene, std::ofstream& output) {

	
	
	for (int j = 0; j < camera.screenHeight; j++) {
		int scanlinesRemaining = camera.screenHeight - j;

		std::cout << "Scanlines Remaining: " << scanlinesRemaining << std::endl;



		for (int i = 0; i < camera.screenWidth; i++) {

			//if (i == 64 && j == 24) __debugbreak();

			glm::vec3 color;

#ifdef MULTISAMPLE_ON 

			if (i != 0 && i != camera.screenWidth - 1 && j != 0 && j != camera.screenHeight - 1) {
				glm::vec2 pixels[9] = {
						glm::vec2(i, j),
						glm::vec2(i - 1, j),
						glm::vec2(i + 1, j),
						glm::vec2(i, j - 1),
						glm::vec2(i, j + 1),
						glm::vec2(i - 1, j - 1),
						glm::vec2(i + 1, j + 1),
						glm::vec2(i + 1, j - 1),
						glm::vec2(i - 1, j + 1)
				};

				for (glm::vec2 pixel : pixels) {
					ray ray(camera.pos, glm::normalize(camera.screenToWorld(pixel.x, pixel.y)));
					rayresult rayResult = trace_ray(ray, scene, camera);

					color += rayResult.color;
				}

				color /= 9;
				

			}

			else {
				ray ray(camera.pos, glm::normalize(camera.screenToWorld(i, j)));
				rayresult rayResult = trace_ray(ray, scene, camera);
				color = rayResult.color;
			}
#else 
			ray ray(camera.pos, glm::normalize(camera.screenToWorld(i, j)));
			traceRayDepth = 0;
			rayresult rayResult = trace_ray(ray, scene, camera);
			color = rayResult.color;
#endif

			color.r = clamp(color.r, 0.0, 1.0);
			color.g = clamp(color.g, 0.0, 1.0);
			color.b = clamp(color.b, 0.0, 1.0);

			output << (int)(color.r * 255) << ' ' << (int)(color.g * 255) << ' ' << (int)(color.b * 255) << '\n';

		}
	}

	output.close();

	
	
	

}