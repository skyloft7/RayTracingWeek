#pragma once

#include "glm.hpp"

class camera {
public: 
	float viewportWidth;
	float viewportHeight;
	glm::vec3 pos;

	float screenWidth;
	float screenHeight;
	float far;


	camera(float viewportW, float viewportH, float screenWidth, float screenHeight, glm::vec3& pos, float far) : viewportWidth(viewportW),
		viewportHeight(viewportH), screenWidth(screenWidth), screenHeight(screenHeight), pos(pos), far(far) {

	}

	const glm::vec3 worldToScreen(glm::vec3 worldPos) {

		float x = (worldPos.x + (viewportWidth / 2) / viewportWidth) * screenWidth;
		float y = (worldPos.y + (viewportHeight / 2) / viewportHeight) * screenHeight;


		return glm::vec3(x, y, 0.0f);
	}

	const glm::vec3 screenToWorld(int screenX, int screenY) {

		float x = (screenX / screenWidth) * viewportWidth - (viewportWidth / 2.0);
		float y = (screenY / screenHeight) * viewportHeight - (viewportHeight / 2.0);



		return glm::vec3(x, y, far);
	}


};






