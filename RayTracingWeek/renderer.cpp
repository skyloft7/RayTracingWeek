#include "renderer.h"
#include <iostream>

inline glm::vec3 blend(ray& ray, glm::vec3& colorA, glm::vec3& colorB) {
	float a = 0.5;

	return (1.0f - a) * colorA + a * colorB;
}

glm::vec3 renderer::random_vec3() {
	while (true) {
		auto p = glm::vec3(random_number(-1.0, 1.0), random_number(-1.0, 1.0), random_number(-1.0, 1.0));
		auto lengthSquared = glm::length(p) * glm::length(p);

		if (1e-160 < lengthSquared && lengthSquared <= 1) {
			return p / glm::length(p);
		}
	}
	
	return glm::vec3(0.0, 0.0, 0.0);
}

glm::vec3 renderer::random_vec3_on_sphere(glm::vec3 randomVec3, glm::vec3 normal) {
	if (glm::dot(randomVec3, normal) > 0.0) {
		return randomVec3;
	}
	else {
		return -randomVec3;
	}
}

double renderer::random_number(double start, double end) {
	float r = std::rand() / (RAND_MAX + 1.0);
	return start + (end - start) * r;
}

hitresult renderer::trace_ray(ray& incidentRay, std::vector<sphere> spheres, std::vector<light> lights, camera& camera) {



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
		res.color = closestSphere->color;// *std::max(0.0f, glm::dot(*closestNormal, glm::vec3(0.0, -1, 0)));
		res.miss = false;

		double randomNumber = dist(gen);

		glm::vec3 childRayDir = randomNumber == 0 ? glm::reflect(incidentRay.direction(), *closestNormal) : random_vec3_on_sphere(random_vec3(), *closestNormal);
		
		ray childRay(*closestHit * 1.01f, childRayDir);

		hitresult childHitResult = trace_ray(childRay, spheres, lights, camera);

		if (!childHitResult.miss) {
			res.color = 0.5f * blend(childRay, res.color, childHitResult.color);
			return res;
		}


		

	
		return res;

	}

	res.miss = true;
	res.color = glm::vec3{ 0.0, 0.0, 0.0 };

	return res;
}




void renderer::render(camera& camera, std::ofstream& output) {
	std::vector<sphere> spheres;

	spheres.emplace_back<sphere>({ glm::vec3(0.0, 100.5, -1), 100, glm::vec3 { 1, 1, 1 } });
	spheres.emplace_back<sphere>({ glm::vec3(0.0, 0.0, -1), 0.5, glm::vec3 { 0.5, 0.7, 1.0 } });
	spheres.emplace_back<sphere>({ glm::vec3(0.3, 0.2, -0.5), 0.1, glm::vec3 { 1, 0.7, 1.0 } });

	std::vector<light> lights;

	lights.emplace_back<light>({glm::vec3(0.5, 0.5, -0.5)});
	


	for (int j = 0; j < camera.screenHeight; j++) {
		int scanlinesRemaining = camera.screenHeight - j;



		for (int i = 0; i < camera.screenWidth; i++) {

			ray ray(camera.pos, glm::normalize(camera.screenToWorld(i, j)));

			hitresult rayResult = trace_ray(ray, spheres, lights, camera);


			output << (int)(rayResult.color.r * 255) << ' ' << (int)(rayResult.color.g * 255) << ' ' << (int)(rayResult.color.b * 255) << '\n';

		}
	}

	output.close();
	

}