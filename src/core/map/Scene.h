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

public:
	bool initialize();
	void update();
	void shutdown();
#pragma endregion

private:
	vector<Entity*>			_entities;
};

