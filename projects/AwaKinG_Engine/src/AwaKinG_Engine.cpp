#include "AwaKinG_Engine.h"

#pragma warning(push)
#pragma warning(disable:4273)

bool initialize(HWND mainHwnd, HWND hwnd){
	if (!Render::getInstance().initialize(hwnd, 2000, 2000)) return false;
	if (!Input::getInstance().initialize(mainHwnd)) return false;
	if(!Engine::getInstance().initialize()) return false;
  if(!Map::getInstance().initialize()) return false;
  //if(!Map::getInstance().initializeTestScene1()) return false;

	return true;
}
void release(){
	Map::getInstance().shutdown();
	Engine::getInstance().shutdown();
	Input::getInstance().shutdown();
	Render::getInstance().shutdown();
}
void update(){
	if(Engine::getInstance().getActive()) {
		Input::getInstance().update();
    Camera::getInstance().update();
    Map::getInstance().update();
		Engine::getInstance().update();
		Render::getInstance().update();
	}
}
void setActive(bool value){
	Engine::getInstance().setActive(value);
}
void resizeBuffer(int sizeX, int sizeY){
	Render::getInstance().resizeBuffer(sizeX, sizeY);
}
void setCameraType(int type) {
  switch(type) {
  case 0:
    Map::getInstance().setCameraType(PCT_GAME);
    break;
  case 1:
    Map::getInstance().setCameraType(PCT_FIRST_PERSON_FREE);
    break;
  case 2:
    Map::getInstance().setCameraType(PCT_REDACTOR);
    break;
  case 3:
    Map::getInstance().setCameraType(PCT_FIRST_PERSON);
    break;
  default:
    break;
  }
}
bool openMap(const char* fileName, int lenght) {
  char* str = new char[lenght * 2];
  for(int i = 0; i < lenght * 2; i++)
    str[i] = fileName[i * 2];

  return Map::getInstance().initialize(str);
}
bool saveMap(const char* fileName, int lenght) {
  char* str = new char[lenght * 2];
  for(int i = 0; i < lenght * 2; i++)
    str[i] = fileName[i * 2];

  return Map::getInstance().save(str);
}
void newMap() {
  Map::getInstance().initialize();
}
int createTerrain(int sizeX, int sizeY) {
  if(!Terrain::getInstance().create(sizeX, sizeY)) 
    return -1;
  return 0;
}

#pragma warning(pop)