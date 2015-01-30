#pragma once
#include <string>

class Scene
{
public:
	std::string ErrorMessage;
	static Scene& getInstance()
	{
		static Scene scene;
		return scene;
	};
	bool initialize();
	void shutdown();
private:
	Scene();
	Scene(const Scene&);
private:
};

