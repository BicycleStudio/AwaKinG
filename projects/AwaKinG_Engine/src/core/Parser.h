#ifndef __PARSER_H
#define __PARSER_H

#include <string>
using namespace std;

class Parser {
public:
  string errorMessage;

  static Parser& getInstance() {
    static Parser parser_;
    return parser_;
  }
private:
  Parser();
  Parser(const Parser&);
};

#endif