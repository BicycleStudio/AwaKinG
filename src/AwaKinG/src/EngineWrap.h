#pragma once
#include "../../AwaKinG_Engine/src/AwaKing_Engine.h"
#pragma comment(lib, "../../Lib/AwaKinG_Engine.lib")

class EngineWrap
{
public:
	static EngineWrap* getInstance(){
		static EngineWrap* engine = new EngineWrap();
		return engine;
	}
	bool getInitialized();
	bool getActive();
	bool initialize(HWND mainHwnd, HWND hwnd);
	void release();
	void update();
	void setActive(bool value);
	void resizeBuffer(int sizeX, int sizeY);
private:
	EngineWrap();

	bool _initialized;
	bool _active;
};

