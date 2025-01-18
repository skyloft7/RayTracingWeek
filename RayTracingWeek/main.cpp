#include <iostream>
#include <fstream>
#include "camera.h"
#include "ray.h"



int main() {


	int imageWidth = 640;
	int imageHeight = 480;

	std::ofstream output;
	output.open("image.ppm");

	output << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";


	auto aspectRatio = (float) imageWidth / imageHeight;

	vec3 cameraPos = vec3(0.0, 0.0, 0.0);
	camera camera(2.0 * aspectRatio, 2.0, imageWidth, imageHeight, cameraPos);


	vec3 spherePos = vec3(0.0, 0.0, 2.0);
	float radius = 0.5;

	



	for (int j = 0; j < imageHeight; j++) {
		int scanlinesRemaining = imageHeight - j;
		for (int i = 0; i < imageWidth; i++) {
			
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


	return 0;
}