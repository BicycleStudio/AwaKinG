#ifndef __INPUT_H
#define __INPUT_H

#include <Windows.h>
#include <vector>
using namespace std;

class Input
{
public:
	string errorMessage;
	void update();
	void shutdown();
	bool initialize(HWND hwnd);

	static Input& getInstance()  {
		static Input input_;
		return input_;
	}
private:
	Input();
	Input(const Input&);
};

#endif // __INPUT_H 