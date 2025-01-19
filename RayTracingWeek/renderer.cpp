#include "renderer.h"


const color3 renderer::trace_ray(ray& ray, sphere& sphere) {
	float aq = dot(ray.dir, ray.dir);
	float bq = 2 * dot(ray.orig, ray.dir);
	float cq = dot(ray.orig, ray.orig) - sphere.radius * sphere.radius;

	float discriminant = bq * bq - 4 * aq * cq;

	if (discriminant >= 0) {

		float t = (-bq - sqrt(discriminant)) / 2 * aq;

		vec3 hit = ray.orig + t * ray.dir;
		vec3 normal = normalize(hit - sphere.pos);

		return color3(normal.x() * 255, normal.y() * 255, normal.z() * 255);
	}
}

void renderer::render(camera& camera, std::ofstream& output) {

	sphere s = { vec3(0.0, 0.0, 2.0), 0.5 };
	

	for (int j = 0; j < camera.screenHeight; j++) {
		int scanlinesRemaining = camera.screenHeight - j;
		for (int i = 0; i < camera.screenWidth; i++) {

			ray ray(camera.pos, camera.screenToWorld(i, j, 2));
			ray.orig = ray.orig - s.pos;


			color3 rayResult = trace_ray(ray, s);

			output << (int) rayResult.x() << ' ' << (int) rayResult.y() << ' ' << (int) rayResult.z() << '\n';

		}
	}

	output.close();
}