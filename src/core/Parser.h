#pragma once
#include "../render/D3dRender.h"

using namespace std;
using namespace DirectX;

class Parser
{
#pragma region singleton
public:
	std::string ErrorMessage;
	static Parser& getInstance()
	{
		static Parser parser;
		return parser;
	};

private:
	Parser();
	Parser(const Parser&);
#pragma endregion
public:
	bool readFromFile(string str);
};

