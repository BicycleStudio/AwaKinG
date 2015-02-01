#include "Scene.h"


Scene::Scene()
{
	ErrorMessage = "Scene";
}
void Scene::shutdown()
{

}
bool Scene::initialize()
{
	return true;
}
void Scene::update()
{
	for(unsigned int i = 0; i < _entities.size(); i++)
	{
		_entities[i]->update();
	}
}
