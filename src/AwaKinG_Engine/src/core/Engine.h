#ifndef __ENGINE_H
#define __ENGINE_H

#include <Windows.h>

class Engine
{
public:
	static Engine* getInstance()  {
		static Engine *engine = new Engine();
		return engine;
	}
private:
	Engine();

};

#endif // __ENGINE_H 