#pragma once
#include "Entity.h"
#include "../../ErrorDefines.h"

class Map {
public:
	string errorMessage;

	void update();
	void shutdown();
	bool initialize();
  void addEntity(Entity* entity);

	static Map& getInstance() {
		static Map map_;
		return map_;
	}
private:
	Map();
	Map(const Map&);

private:
	vector<Entity*>			_entities;
};

