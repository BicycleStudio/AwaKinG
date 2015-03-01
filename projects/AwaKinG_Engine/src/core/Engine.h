#ifndef __ENGINE_H
#define __ENGINE_H
#include <vector>
using namespace std;
#include "../ErrorDefines.h"

class Engine
{
public:
	string errorMessage;

	void update();
	void shutdown();
	bool initialize();
	bool getActive(); 
	void setActive(bool value);

	static Engine& getInstance()  {
		static Engine engine;
		return engine;
	}
private:
	Engine();
	Engine(const Engine&);

private:
	bool			_active;
};

#endif // __ENGINE_H 