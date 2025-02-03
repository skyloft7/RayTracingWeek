#pragma once
#include "sphere.h"
#include <vector>

class scene {
private:
	std::vector<entity*> entities;

public: 
	void add_entity(entity* e) {
		entities.emplace_back(e);
	}

	void remove_entity(entity* e) {
		auto it = std::find(entities.begin(), entities.end(), e);
		if (it != entities.end()) entities.erase(it);
	}

	std::vector<entity*>& get_entities() {
		return entities;
	}

};