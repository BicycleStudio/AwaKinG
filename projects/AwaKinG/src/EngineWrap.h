#pragma once
#include "../../AwaKinG_Engine/src/AwaKing_Engine.h"
#pragma comment(lib, "../../Lib/AwaKinG_Engine.lib")

#define OUTPUT_ERROR(instance, strClass) {MessageBox(NULL, instance.errorMessage.c_str(), strClass, MB_ICONERROR);return false;}

class EngineWrap;

class DestroyerEngineWrap
{
public:
  ~DestroyerEngineWrap();
  void initialize(EngineWrap *engine);
private:
  EngineWrap *_engine;
};

class EngineWrap
{
public:
	static EngineWrap& getInstance();

	bool getInitialized();
	bool getActive();
	bool initialize(HWND mainHwnd, HWND hwnd);
	void release();
	void update();
	void setActive(bool value);
	void resizeBuffer(int sizeX, int sizeY);
protected:
	EngineWrap();
  EngineWrap(const EngineWrap&);
  ~EngineWrap(){};
  friend class DestroyerEngineWrap;
private:
  static EngineWrap *_engine;
  static DestroyerEngineWrap _destroyer;

	bool _initialized;
	bool _active;
};

