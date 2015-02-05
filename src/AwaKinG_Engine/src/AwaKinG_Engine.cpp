#include "AwaKinG_Engine.h" 
RedactorEngine* EngineGetPointer()
{
	return new RedactorEngine();
	//return Engine::getInstance(Engine::ERT_REDACTOR);
}
bool EngineInitialize(RedactorEngine* pointer, HWND mainHwnd, HWND hwnd, int sizeX, int sizeY)
{
	if(pointer->initialize(mainHwnd, hwnd, sizeX, sizeY))
		return true;
	pointer->shutdown();
	return false;
}
void EngineRelease(RedactorEngine* pointer)
{
	pointer->shutdown();
}
bool EngineUpdate(RedactorEngine* pointer)
{
	return pointer->update();
}
void EngineCreateMapFromFile(RedactorEngine* pointer, const char* fileName, int len)
{
	char* str = new char[len*2];
	for(int i = 0; i < len * 2; i++)
		str[i] = fileName[i*2];
	if(!pointer->createMapFromFile(str));
}
int EngineSetActive(RedactorEngine* pointer, int value)
{
	bool val = true;
	if(value == 0)
		val = false;
	pointer->setActive(val);
	return value;
}
bool EngineGetActive(RedactorEngine* pointer)
{
	return pointer->active();
}
void EngineSetCameraManagerType(RedactorEngine* pointer, int type)
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
bool EngineRenderResizeBuffer(RedactorEngine* pointer, int sizeX, int sizeY)
{
	return pointer->resizeRenderBuffer(sizeX, sizeY);
}
bool EngineTerrainGenerate(RedactorEngine* pointer, int sizeX, int sizeY)
{
	return pointer->createTerrain(sizeX, sizeY);
}
void EngineTerrainRandomize(RedactorEngine* pointer, int diapazon)
{
	pointer->randomizeTerrain(diapazon);
}
void EngineTerrainBlur(RedactorEngine* pointer, int value)
{
	pointer->blurTerrain(value);
}
char* EngineTerrainSave(RedactorEngine* pointer, const char* fileName, int len)
{
	char* str = new char[len * 2];
	for(int i = 0; i < len * 2; i++)
		str[i] = fileName[i * 2];
	pointer->saveTerrain(str);
	return str;
}
void EngineTerrainLoad(RedactorEngine* pointer, const char* fileName, int len)
{
	char* str = new char[len * 2];
	for(int i = 0; i < len * 2; i++)
		str[i] = fileName[i * 2];
	pointer->loadTerrain(str);
}
void EngineTerrainSetWorkType(RedactorEngine* pointer, int type)
{
	pointer->setTerrainWorkType(type);
}
int EngineTerrainPick(RedactorEngine* pointer, int posX, int posY)
{
	return pointer->pickTerrain(posX, posY);
}
