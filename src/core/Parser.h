#pragma once
#include "../render/D3dRender.h"

using namespace std;
using namespace DirectX;

#define tryOpenStream(fileName)if(!_parser->openFile(fileName)){ ErrorMessage = "openStream error. Parser"; return false; }
#define tryCloseStream()if(!_parser->closeFile(fileName)){ ErrorMessage = "closeStream error. Parser"; return false; }
#define tryReadInt(valuePointer) if(!_parser->readInt(valuePointer)){ ErrorMessage = _parser->ErrorMessage;  tryCloseStream(); return false;}
#define tryReadFloat(valuePointer) if(!_parser->readFloat(valuePointer)){ ErrorMessage = _parser->ErrorMessage;  tryCloseStream(); return false;}
#define tryReadString(valuePointer) if(!_parser->readString(valuePointer)){ ErrorMessage = _parser->ErrorMessage;  tryCloseStream(); return false;}

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
	bool openFile(string fileName);
	bool closeFile(string fileName);

	bool readInt(int* var);
	bool readFloat(float* var);
	bool readString(char** var);
private:
	vector<FILE*>	_fileStreams;
};

