#include "AwaKinG_Engine.h" 
Engine* EngineGetPointer()
{
	return &Engine::getInstance();
}
bool EngineInitialize(Engine* pointer, HWND mainHwnd, HWND hwnd, int sizeX, int sizeY)
{
	if(pointer->initialize(mainHwnd, hwnd, sizeX, sizeY))
		return true;
	pointer->shutdown();
	return false;
}
void EngineRelease(Engine* pointer)
{
	pointer->shutdown();
}
bool EngineUpdate(Engine* pointer)
{
	return pointer->update();
}
void EngineCreateMapFromFile(Engine* pointer, const char* fileName, int len)
{
	char* str = new char[len*2];
	for(int i = 0; i < len * 2; i++)
	{
		str[i] = fileName[i*2];
	}
	if(!pointer->createMapFromFile(str));
}
int EngineSetActive(Engine* pointer, int value)
{
	bool val = true;
	if(value == 0)
		val = false;
	pointer->setActive(val);
	return value;
}
bool EngineGetActive(Engine* pointer)
{
	return pointer->active();
}
void EngineSetCameraManagerType(Engine* pointer, int type)
{
	Engine::CameraManagerType type_;
	switch(type)
	{
	case 0:		type_ = Engine::CameraManagerType::CMT_REDACTOR; break;
	case 1:		type_ = Engine::CameraManagerType::CMT_REDACTORFREE; break;
	default:		type_ = Engine::CameraManagerType::CMT_REDACTOR; break;
	}
	pointer->setCameraManagerType(type_);
}
bool EngineRenderResizeBuffer(Engine* pointer, int sizeX, int sizeY)
{
	return pointer->resizeRenderBuffer(sizeX, sizeY);
}
bool EngineTerrainGenerate(Engine* pointer, int sizeX, int sizeY)
{
	return pointer->createTerrain(sizeX, sizeY);
}
void EngineTerrainRandomize(Engine* pointer, int diapazon)
{
	pointer->randomizeTerrain(diapazon);
}
void EngineTerrainBlur(Engine* pointer, int value)
{
	pointer->blurTerrain(value);
}