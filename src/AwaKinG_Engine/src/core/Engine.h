#ifndef __ENGINE_H
#define __ENGINE_H

class Engine
{
public:
	void update();
	void shutdown();
	bool initialize();
	bool getActive(); 
	void setActive(bool value);

	static Engine* getInstance()  {
		static Engine *engine = new Engine();
		return engine;
	}
private:
	Engine();
	Engine(const Engine&);

private:
	bool			_active;
};

#endif // __ENGINE_H 