#include "Parser.h"

Parser::Parser()
{

}
void Parser::newLine()
{
	fprintf_s(_fileStreams[_fileStreams.size() - 1], "\n");
}
bool Parser::writeInt(int var)
{
	fprintf_s(_fileStreams[_fileStreams.size() - 1], "%d ", var);
	return true;
}
bool Parser::writeFloat(float var)
{
	fprintf_s(_fileStreams[_fileStreams.size() - 1], "%f ", var);
	return true;
}
bool Parser::writeString(char* var, int len)
{
	fprintf_s(_fileStreams[_fileStreams.size() - 1], "%s ", var, len);
	return true;
}
bool Parser::readString(char** var)
{
	try
	{
		fscanf_s(_fileStreams[_fileStreams.size() - 1], "%s ", var[0], 255);
		return true;
	}
	catch(exception ex_)
	{
		ErrorMessage = ex_.what();
		return false;
	}
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
bool Parser::openFile(string fileName, string spec)
{
	FILE* file;
	if(fopen_s(&file, fileName.c_str(), spec.c_str()))
	{
		ErrorMessage = "File "+ fileName + " does not exists!";
		return false;
	}
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