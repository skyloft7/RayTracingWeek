#pragma once
#include <string>
#include "entity.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "materials/material.h"
#include "vertex.h"
#include "triangle.h"
#include "glm.hpp"

class mesh : public entity {
private:
	std::vector<triangle> triangles;


public:
	mesh(glm::vec3 pos, const std::string& modelPath, material* mat) : entity(pos, mat) {

		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

		std::string warn;
		std::string err;

		bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, modelPath.c_str(),
			".", false);

		if (!warn.empty()) {
			std::cout << "WARN: " << warn << std::endl;
		}
		if (!err.empty()) {
			std::cerr << err << std::endl;
		}

		if (!ret) {
			std::cerr << "Failed to load " << modelPath.c_str() << std::endl;
			exit(1);
		}

		std::vector<glm::vec3> vertices;

		{
			tinyobj::ObjReaderConfig reader_config;
			reader_config.mtl_search_path = "./"; // Path to material files

			tinyobj::ObjReader reader;

			if (!reader.ParseFromFile(modelPath, reader_config)) {
				if (!reader.Error().empty()) {
					std::cerr << "TinyObjReader: " << reader.Error();
				}
				exit(1);
			}

			if (!reader.Warning().empty()) {
				std::cout << "TinyObjReader: " << reader.Warning();
			}

			auto& attrib = reader.GetAttrib();
			auto& shapes = reader.GetShapes();

			// Loop over shapes
			for (size_t s = 0; s < shapes.size(); s++) {
				// Loop over faces(polygon)
				size_t indexOffset = 0;
				for (size_t faceIndex = 0; faceIndex < shapes[s].mesh.num_face_vertices.size(); faceIndex++) {
					size_t numFaceVertices = size_t(shapes[s].mesh.num_face_vertices[faceIndex]);

					// Loop over vertices in the face.
					for (size_t vertexIndex = 0; vertexIndex < numFaceVertices; vertexIndex++) {
						// access to vertex
						tinyobj::index_t idx = shapes[s].mesh.indices[indexOffset + vertexIndex];
						tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
						tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
						tinyobj::real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];

						vertices.emplace_back((glm::vec3(vx, vy, vz) * 5.0f) + glm::vec3(0, -0.5, 0));
						//vertices.emplace_back((glm::vec3(vx, vy, vz) * 0.03f));
						//vertices.emplace_back((glm::vec3(vx, vy, vz) * 1000.0f) + glm::vec3(10, 0, 0));

					}
					indexOffset += numFaceVertices;
				}
			}




		}

		for (int t = 0; t < vertices.size() / 3; t++) {
			glm::vec3 v1 = vertices[(t * 3) + 0];
			glm::vec3 v2 = vertices[(t * 3) + 1];
			glm::vec3 v3 = vertices[(t * 3) + 2];

			triangles.emplace_back(triangle{v1, v2, v3});
		}
	

	}

	bool ray_triangle_intersects(
		const glm::vec3& orig, const glm::vec3& dir,
		const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2,
		float& t, glm::vec3& N)
	{
		glm::vec3 v0v1 = v1 - v0;
		glm::vec3 v0v2 = v2 - v0;
		N = glm::cross(v0v1, v0v2);

		float NdotRayDirection = glm::dot(N, dir);

		if (glm::dot(dir, N) > 0.0) N = -N;


		float d = glm::dot(-N, v0);

		t = -(glm::dot(N, orig) + d) / NdotRayDirection;

		if (t < 0) return false; 

		glm::vec3 P = orig + t * dir;

		glm::vec3 Ne; 

		glm::vec3 v0p = P - v0;
		Ne = glm::cross(v0v1, v0p);
		if (glm::dot(N, Ne) < 0) return false; 

		glm::vec3 v2v1 = v2 - v1;
		glm::vec3 v1p = P - v1;
		Ne = glm::cross(v2v1, v1p); 
		if (glm::dot(N, Ne) < 0) return false;

		glm::vec3 v2v0 = v0 - v2;
		glm::vec3 v2p = P - v2;
		Ne = glm::cross(v2v0, v2p);
		if (glm::dot(N, Ne) < 0) return false; 



		return true;
	}

	hitresult scatter(ray& incidentRay) {
		hitresult res;
		float closestZ = -1000;



		for (triangle& triangle : triangles) {
			float t;
			glm::vec3 normal;

			if (ray_triangle_intersects(incidentRay.orig, incidentRay.dir, triangle.vertices[0].pos, triangle.vertices[1].pos, triangle.vertices[2].pos, t, normal)) {
				if (t >= 0) {

					glm::vec3 hit = incidentRay.orig + t * incidentRay.dir;



					if (hit.z > closestZ) {
						res.valid = true;
						res.t = t;
						res.normal = glm::normalize(normal);
						res.hit = hit;
						closestZ = hit.z;
					}
					
				}
			}

		}

		return res;
	}


};