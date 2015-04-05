#include "Parser.h"

Parser::Parser() {
  errorMessage = ED_UNDEFINED;
}
Parser& Parser::getInstance() {
  static Parser parser_;
  return parser_;
}
void Parser::newLine() {
  if(_fileStreams.size())
    fprintf_s(_fileStreams[_fileStreams.size() - 1], "\n");
}
bool Parser::writeInt(int var) {
  if(_fileStreams.size()) {
    fprintf_s(_fileStreams[_fileStreams.size() - 1], "%d ", var);
    return true;
  }
  return false;
}
bool Parser::writeFloat(float var) {
  if(_fileStreams.size()) {
    fprintf_s(_fileStreams[_fileStreams.size() - 1], "%f ", var);
    return true;
  }
  return false;
}
bool Parser::writeString(const char* var, int len) {
  if(_fileStreams.size()) {
    fprintf_s(_fileStreams[_fileStreams.size() - 1], "%s ", var, len);
    return true;
  }
  return false;
}
bool Parser::readString(char** var) {
  if(_fileStreams.size()) {
    fscanf_s(_fileStreams[_fileStreams.size() - 1], "%s ", var[0], 255);
    return true;
  }
  return false;
}
bool Parser::readInt(int* var) {
  if(_fileStreams.size()) {
    fscanf_s(_fileStreams[_fileStreams.size() - 1], "%d ", var);
    return true;
  }
  return false;
}
bool Parser::readFloat(float* var) {
  if(_fileStreams.size()) {
    fscanf_s(_fileStreams[_fileStreams.size() - 1], "%f ", var);
    return true;
  }
  return false;
}
bool Parser::openFile(string fileName, string spec) {
  FILE* file;
  if(fopen_s(&file, fileName.c_str(), spec.c_str())) {
    errorMessage = EDP_FILE + fileName + EDP_DOESNT_EXIST;
    return false;
  }
  _fileStreams.push_back(file);
  return true;
}
bool Parser::closeFile(string fileName) {
  if(fclose(_fileStreams[_fileStreams.size() - 1])) {
    _fileStreams.pop_back();
    return false;
  }
  _fileStreams.pop_back();
  return true;
}