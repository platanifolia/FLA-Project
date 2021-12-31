#ifndef FLA_TURING_PROJECT_STRINGHANDLE_H_
#define FLA_TURING_PROJECT_STRINGHANDLE_H_

#include <string>

std::string RemoveStringComment(std::string inputstring);

std::string BracketsSubstring(std::string inputstring);

void IllegalError(int errcode);
void SyntaxError(int errcode);
#endif