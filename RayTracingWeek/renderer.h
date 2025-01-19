#ifndef RENDERER_H
#define RENDERER_H

#include "camera.h"
#include <fstream>


class renderer {
public:
	void render(camera& camera, std::ofstream& output);

};

#endif