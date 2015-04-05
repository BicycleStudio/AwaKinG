#pragma once
#include "Entity.h"
#include "Terrain.h"
#include "../../ErrorDefines.h"
#include "../Parser.h"
#include "../../render/Render.h"
enum PlayerCameraType {
  PCT_FIRST_PERSON_FREE,
  PCT_FIRST_PERSON,
  PCT_REDACTOR,
  PCT_GAME
};

class Map {
public:
	string errorMessage;

	void update();
	void shutdown();
  bool initializeTestScene1();
  bool initialize();
  bool initialize(string fileName);
  bool save(string fileName);
  void addEntity(Entity* entity);
  void setCameraType(PlayerCameraType type);

	static Map& getInstance() {
		static Map map_;
		return map_;
	}
private:
	Map();
	Map(const Map&);
  void _clear();

private:
	vector<Entity*>			_entities;
  Entity*             _cameraManager;
};

