#pragma once
#include "Entity.h"
#include "../../ErrorDefines.h"

enum PlayerCameraType {
  PCT_FIRST_PERSON,
  PCT_REDACTOR,
  PCT_GAME
};

class Map {
public:
	string errorMessage;

	void update();
	void shutdown();
	bool initialize();
  void addEntity(Entity* entity);
  void setCameraType(PlayerCameraType type);

	static Map& getInstance() {
		static Map map_;
		return map_;
	}
private:
	Map();
	Map(const Map&);

private:
	vector<Entity*>			_entities;
  Player*             _cameraManager;
};

