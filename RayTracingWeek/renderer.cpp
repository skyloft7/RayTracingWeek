#include "renderer.h"
#include <iostream>
#include "materials/material.h"
#include "materials/metal.h"
#include "materials/lambertian.h"
#include "util.h"


double renderer::linear_to_gamma(double input) {
	if (input > 0) {
		return glm::sqrt(input);
	}
	
	return 0;
}

hitresult renderer::trace_ray(ray& incidentRay, std::vector<sphere> spheres, camera& camera) {

	


	float closestZ = -100;
	sphere* closestSphere = nullptr;
	glm::vec3* closestHit = nullptr;
	glm::vec3* closestNormal = nullptr;

	for (sphere& sphere : spheres) {
		float aq = glm::dot(incidentRay.dir, incidentRay.dir);
		float bq = 2 * glm::dot(incidentRay.orig - sphere.pos, incidentRay.dir);
		float cq = glm::dot(incidentRay.orig - sphere.pos, incidentRay.orig - sphere.pos) - sphere.radius * sphere.radius;

		float discriminant = bq * bq - 4 * aq * cq;

		if (discriminant >= 0) {

			float t = (-bq - sqrt(discriminant)) / 2 * aq;

			if (t >= 0) {


				glm::vec3 hit = incidentRay.orig + t * incidentRay.dir;
				glm::vec3 normal = glm::normalize(hit - sphere.pos);


				if (hit.z > closestZ) {
					closestHit = &hit;
					closestNormal = &normal;
					closestSphere = &sphere;
					closestZ = hit.z;
				}


			}

		}
	}

	
	

	hitresult res;


	if (closestSphere != nullptr) {
		res.miss = false;

		glm::vec3 childRayDir;
		
		res.color = closestSphere->mat->color(incidentRay, *closestNormal, childRayDir);

		
		ray childRay(*closestHit * 1.01f, childRayDir);

		hitresult childHitResult = trace_ray(childRay, spheres, camera);

		if (!childHitResult.miss) {
			res.color = 0.3f * blend(childRay, res.color, childHitResult.color);
			return res;
		}


		

	
		return res;

	}
	

	res.miss = true;
	res.color = glm::vec3{ 0.0, 0.0, 0.0 };

	return res;
}

double renderer::clamp(double input, double min, double max) {
	if (input <= min) return min;
	if (input >= max) return max;

	return input;
}



void renderer::render(camera& camera, std::ofstream& output) {
	
	std::vector<sphere> spheres;

	material* mat1 = new lambertian(glm::vec3(1.0, 1.0, 1.0));
	material* mat2 = new lambertian(glm::vec3(0.7, 0.2, 0.4));
	material* mat3 = new metal(glm::vec3(0.2, 0.3, 0.7));
	material* mat4 = new metal(glm::vec3(0.7, 0.6, 0.4));
	material* mat5 = new metal(glm::vec3(0.3, 0.9, 0.4));
	material* mat6 = new lambertian(glm::vec3(0.9, 0.3, 0.2));

	
	

	

	spheres.emplace_back<sphere>({ 
		glm::vec3(0.0, 100.5, -1), 
		100, 
		mat1 
	});
	spheres.emplace_back<sphere>({
		glm::vec3(1.0, -0.5, -1),
		0.3,
		mat5
	});

	spheres.emplace_back<sphere>({ 
		glm::vec3(0.0, 0.15, -1), 
		0.5, 
		mat2
	});
	spheres.emplace_back<sphere>({
		glm::vec3(-0.5, 0.2, -0.5),
		0.1,
		mat6
	});
	spheres.emplace_back<sphere>({ 
		glm::vec3(0.3, 0.2, -0.5), 
		0.1, 
		mat3
	});
	spheres.emplace_back<sphere>({
		glm::vec3(-0.4, 0.2, -0.8),
		0.1,
		mat4
	});
	
	

	


	for (int j = 0; j < camera.screenHeight; j++) {
		int scanlinesRemaining = camera.screenHeight - j;



		for (int i = 0; i < camera.screenWidth; i++) {

			ray ray(camera.pos, glm::normalize(camera.screenToWorld(i, j)));

			hitresult rayResult = trace_ray(ray, spheres, camera);

			float r = clamp(linear_to_gamma(rayResult.color.r), 0.0, 1.0);
			float g = clamp(linear_to_gamma(rayResult.color.g), 0.0, 1.0);
			float b = clamp(linear_to_gamma(rayResult.color.b), 0.0, 1.0);

			


			output << (int)(r * 255) << ' ' << (int)(g * 255) << ' ' << (int)(b * 255) << '\n';

		}
	}

	output.close();

	
	
	

}