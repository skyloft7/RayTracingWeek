#ifndef CAMERA
#define CAMERA
#include "vec3.h"

class camera {
public: 
	float viewportWidth;
	float viewportHeight;
	vec3 pos;

	float screenWidth;
	float screenHeight;

	camera(float viewportW, float viewportH, float screenWidth, float screenHeight, vec3& pos) : viewportWidth(viewportW), 
		viewportHeight(viewportH), screenWidth(screenWidth), screenHeight(screenHeight), pos(pos) {

	}

	const vec3 worldToScreen(vec3 worldPos) {

		float x = (worldPos.x() + (viewportWidth / 2) / viewportWidth) * screenWidth;
		float y = (worldPos.y() + (viewportHeight / 2) / viewportHeight) * screenHeight;


		return vec3(x, y, 0.0f);
	}

	const vec3 screenToWorld(int screenX, int screenY, float defaultZ) {

		float x = (screenX / screenWidth) * viewportWidth - (viewportWidth / 2.0);
		float y = (screenY / screenHeight) * viewportHeight - (viewportHeight / 2.0);



		return vec3(x, y, defaultZ);
	}


};






#endif