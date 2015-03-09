#ifndef __PARSER_H
#define __PARSER_H

#include <string>
#include <vector>
#include "../ErrorDefines.h"
using namespace std;
#define OPEN_STREAM(fileName, spec)if(!Parser::getInstance().openFile(fileName, spec)){ ErrorMessage = EDP_OPEN_STREAM; return false; }
#define CLOSE_STREAM()if(!Parser::getInstance().closeFile(fileName)){ ErrorMessage = EDP_CLOSE_STREAM; return false; }
#define READ_INT(valuePointer) if(!Parser::getInstance().readInt(valuePointer)){ ErrorMessage = Parser::getInstance().ErrorMessage;  tryCloseStream(); return false;}
#define READ_FLOAT(valuePointer) if(!Parser::getInstance().readFloat(valuePointer)){ ErrorMessage = Parser::getInstance().ErrorMessage;  tryCloseStream(); return false;}
#define READ_STRING(valuePointer) if(!Parser::getInstance().readString(valuePointer)){ ErrorMessage = Parser::getInstance().ErrorMessage;  tryCloseStream(); return false;}

#define WRITE_INT(value) if(!Parser::getInstance().writeInt(value)){ ErrorMessage = Parser::getInstance().ErrorMessage;  tryCloseStream(); return false;}
#define WRITE_FLOAT(value) if(!Parser::getInstance().writeFloat(value)){ ErrorMessage = Parser::getInstance().ErrorMessage;  tryCloseStream(); return false;}
#define WRITE_STRING(value, len) if(!Parser::getInstance().writeString(value, len)){ ErrorMessage = Parser::getInstance().ErrorMessage;  tryCloseStream(); return false;}

class Parser {
public:
  string errorMessage;
  static Parser& getInstance();

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
  Parser();
  Parser(const Parser&);
  vector<FILE*>	_fileStreams;
};

#endif