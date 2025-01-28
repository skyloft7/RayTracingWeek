#include "renderer.h"
#include <iostream>
#include "materials/material.h"
#include "materials/metal.h"
#include "materials/lambertian.h"
#include "util.h"


glm::vec3 renderer::linear_to_gamma(glm::vec3& input) {

	if (input.r > 0) input.r = sqrt(input.r);
	if (input.g > 0) input.g = sqrt(input.g);
	if (input.b > 0) input.b = sqrt(input.b);

	return input;
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

	
	

	

	spheres.emplace_back<sphere>({ 
		glm::vec3(0.0, 100.5, -1), 
		100, 
		new lambertian(glm::vec3(1.0, 1.0, 1.0))
	});
	
	spheres.emplace_back<sphere>({
		glm::vec3(0.0, 0.3, -1),
		0.2,
		new lambertian(glm::vec3(0.3, 0.0, 1.0))
	});
	
	spheres.emplace_back<sphere>({
		glm::vec3(1.0, -0.45, -1),
		0.2,
		new lambertian(glm::vec3(0.3, 0.9, 1.0))
	});

	spheres.emplace_back<sphere>({
		glm::vec3(1.0, 0.0, -1),
		0.2,
		new metal(glm::vec3(0.7, 0.2, 1.0))
	});

	spheres.emplace_back<sphere>({
		glm::vec3(1.0, 0.3, -0.7),
		0.2,
		new lambertian(glm::vec3(0.9, 0.2, 0.4))
	});

	spheres.emplace_back<sphere>({
		glm::vec3(-1.0, 0.45, 0.5),
		0.2,
		new lambertian(glm::vec3(0.9, 0.5, 0.2))
	});
	
	spheres.emplace_back<sphere>({
		glm::vec3(-0.5, 0.45, -0.5),
		0.1,
		new metal(glm::vec3(0.3, 0.5, 1.0))
	});


	for (int j = 0; j < camera.screenHeight; j++) {
		int scanlinesRemaining = camera.screenHeight - j;



		for (int i = 0; i < camera.screenWidth; i++) {


			glm::vec3 color;

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
					hitresult rayResult = trace_ray(ray, spheres, camera);

					color += rayResult.color;
				}

				color /= 9;
				

			}

			else {
				ray ray(camera.pos, glm::normalize(camera.screenToWorld(i, j)));
				hitresult rayResult = trace_ray(ray, spheres, camera);
				color = rayResult.color;
			}

			color.r = clamp(color.r, 0.0, 1.0);
			color.g = clamp(color.g, 0.0, 1.0);
			color.b = clamp(color.b, 0.0, 1.0);

			output << (int)(color.r * 255) << ' ' << (int)(color.g * 255) << ' ' << (int)(color.b * 255) << '\n';

		}
	}

	output.close();

	
	
	

}