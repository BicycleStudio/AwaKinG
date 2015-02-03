#pragma once
#include <vector>
#include "Entity.h"

class Scene
{
#pragma region singleton
public:
	std::string ErrorMessage;
	static Scene& getInstance()
	{
		static Scene scene;
		return scene;
	};
private:
	Scene();
	Scene(const Scene&);
#pragma endregion

#pragma region public functions
public:
	bool initialize();
	void update();
	void shutdown();
	void addEntity(Entity* ent);
#pragma endregion

private:
	vector<Entity*>			_entities;
};

