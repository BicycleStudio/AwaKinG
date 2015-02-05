#pragma once
#include "../render/D3dRender.h"

using namespace std;

#define tryOpenStream(fileName, spec)if(!Parser::getInstance().openFile(fileName, spec)){ ErrorMessage = "openStream error. Parser"; return false; }
#define tryCloseStream()if(!Parser::getInstance().closeFile(fileName)){ ErrorMessage = "closeStream error. Parser"; return false; }
#define tryReadInt(valuePointer) if(!Parser::getInstance().readInt(valuePointer)){ ErrorMessage = Parser::getInstance().ErrorMessage;  tryCloseStream(); return false;}
#define tryReadFloat(valuePointer) if(!Parser::getInstance().readFloat(valuePointer)){ ErrorMessage = Parser::getInstance().ErrorMessage;  tryCloseStream(); return false;}
#define tryReadString(valuePointer) if(!Parser::getInstance().readString(valuePointer)){ ErrorMessage = Parser::getInstance().ErrorMessage;  tryCloseStream(); return false;}

#define tryWriteInt(value) if(!Parser::getInstance().writeInt(value)){ ErrorMessage = Parser::getInstance().ErrorMessage;  tryCloseStream(); return false;}
#define tryWriteFloat(value) if(!Parser::getInstance().writeFloat(value)){ ErrorMessage = Parser::getInstance().ErrorMessage;  tryCloseStream(); return false;}
#define tryWriteString(value, len) if(!Parser::getInstance().writeString(value, len)){ ErrorMessage = Parser::getInstance().ErrorMessage;  tryCloseStream(); return false;}

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
	bool openFile(string fileName, string spec);
	bool closeFile(string fileName);

	void newLine();
	bool writeInt(int var);
	bool writeFloat(float var);
	bool writeString(char* var, int len);

	bool readInt(int* var);
	bool readFloat(float* var);
	bool readString(char** var);
private:
	vector<FILE*>	_fileStreams;
};

