#pragma once
#include "Entity.h"

class Map {
public:
	void update();
	void shutdown();
	bool initialize();

	static Map* getInstance() {
		static Map *map_ = new Map();
		return map_;
	}
private:
	Map();
	Map(const Map&);

private:
	vector<Entity*>			_entities;
};

