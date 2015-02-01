#include "Parser.h"

Parser::Parser()
{

}
bool Parser::readInt(int* var)
{
	try
	{
		fscanf_s(_fileStreams[_fileStreams.size() - 1], "%d ", var);
		return true;
	}
	catch(exception ex_)
	{
		ErrorMessage = ex_.what();
		return false;
	}
}
bool Parser::readFloat(float* var)
{
	try
	{
		fscanf_s(_fileStreams[_fileStreams.size() - 1], "%f ", var);
		return true;
	}
	catch(exception ex_)
	{
		ErrorMessage = ex_.what();
		return false;
	}
}
bool Parser::openFile(string fileName)
{
	FILE* file;
	if(fopen_s(&file, fileName.c_str(), "r"))
		return false;
	_fileStreams.push_back(file);
	return true;
}
bool Parser::closeFile(string fileName)
{
	if(fclose(_fileStreams[_fileStreams.size() - 1]))
	{
		_fileStreams.pop_back();
		return false;
	}
	_fileStreams.pop_back();
	return true;
}