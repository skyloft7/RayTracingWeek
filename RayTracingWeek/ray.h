#pragma once

#include "vec3.h"

class ray {
public:

	vec3 orig;
	vec3 dir;

	
	ray(const vec3& origin, const vec3& direction) : orig(origin), dir(direction) {

	}

	const vec3& origin() { return orig; }
	const vec3& direction() { return dir; }

	const point3& at(double t) {
		return orig + t * dir;
	}


};


