#include "renderer.h"
#include "ray.h"


void renderer::render(camera& camera, std::ofstream& output) {

	vec3 spherePos = vec3(0.0, 0.0, 2.0);
	float radius = 0.5;

	for (int j = 0; j < camera.screenHeight; j++) {
		int scanlinesRemaining = camera.screenHeight - j;
		for (int i = 0; i < camera.screenWidth; i++) {

			ray ray(camera.pos, camera.screenToWorld(i, j, 2));
			ray.orig = ray.orig - spherePos;

			int r = 0, g = 0, b = 0;

			float aq = dot(ray.dir, ray.dir);
			float bq = 2 * dot(ray.orig, ray.dir);
			float cq = dot(ray.orig, ray.orig) - radius * radius;

			float discriminant = bq * bq - 4 * aq * cq;

			if (discriminant >= 0) {

				float t = (-bq - sqrt(discriminant)) / 2 * aq;

				vec3 hit = ray.orig + t * ray.dir;
				vec3 normal = normalize(hit - spherePos);






				r = normal.x() * 255;
				g = normal.y() * 255;
				b = 100;

			}






			output << r << ' ' << g << ' ' << b << '\n';




		}
	}

	output.close();
}