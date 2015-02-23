#ifndef __INPUT_H
#define __INPUT_H

#include <Windows.h>

class Input
{
public:
	void update();
	void shutdown();

	bool initialize(HWND hwnd);
	static Input* getInstance()  {
		static Input *input_ = new Input();
		return input_;
	}
private:
	Input();
	Input(const Input&);
};

#endif // __INPUT_H 