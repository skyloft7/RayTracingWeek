#include "renderer.h"
#include <iostream>
#include "materials/material.h"
#include "materials/metal.h"
#include "materials/lambertian.h"
#include "util.h"
#include "scene.h"
#include "entity.h"
#include "hitresult.h"
#include <thread>
#include "raybatch.h"

glm::vec3 renderer::linear_to_gamma(glm::vec3& input) {

	if (input.r > 0) input.r = sqrt(input.r);
	if (input.g > 0) input.g = sqrt(input.g);
	if (input.b > 0) input.b = sqrt(input.b);

	return input;
}

rayresult renderer::trace_ray(ray& incidentRay, scene& scene, camera& camera) {

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
		
		ray childRay(*closestHit * 1.1f, childRayDir);

		rayresult childRayRes = trace_ray(childRay, scene, camera);

		if (!childRayRes.miss) {
			res.color = 0.3f * blend(childRay, res.color, childRayRes.color);
			return res;
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
	

	int numThreads = 6;


	int threadBatchHeight = camera.screenHeight / numThreads;
	
	for (int i = 0; i < numThreads; i++) {

		raybatch* r = new raybatch();
		raybatches.emplace_back(r);

		


		r->height = camera.screenHeight / numThreads;
		r->index = i;


		r->thread = std::thread([r, &camera, &scene, this]() {
			
			int scanlines = r->height * (r->index + 1);

			for (int j = r->height * r->index; j < scanlines; j++) {

				int scanlinesRemaining = j - scanlines;


				for (int i = 0; i < camera.screenWidth; i++) { 

					
					
					
					glm::vec3* color = new glm::vec3();

					ray ray(camera.pos, glm::normalize(camera.screenToWorld(i, j)));
					rayresult rayResult = trace_ray(ray, scene, camera);

					color->r = clamp(rayResult.color.r, 0.0, 1.0);
					color->g = clamp(rayResult.color.g, 0.0, 1.0);
					color->b = clamp(rayResult.color.b, 0.0, 1.0);

					
					r->pixels.emplace_back(color);
					
					

					
				}

				std::cout << r->index << "-" << scanlinesRemaining << std::endl;

			}
			
			


		});

		
	}

	for (raybatch* r : raybatches) {
		r->thread.join();
		std::cout << "raybatch [" << r->index << "] has finished" << std::endl;
	}
	

	for (auto& raybatch : raybatches) {
		std::cout << raybatch->index << " writing " << raybatch->pixels.size() << std::endl;

		for (glm::vec3* color : raybatch->pixels) {
			output << (int)(color->r * 255) << ' ' << (int)(color->g * 255) << ' ' << (int)(color->b * 255) << '\n';
		}

	}


	output.close();

	
	
	

}