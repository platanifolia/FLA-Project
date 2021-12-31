#include "stringhandle.h"

#include <iostream>

using namespace std;

// 性能隐患:返回对象有可能由复制产生。考虑使用引用优化
// 处理图灵机文件行注释
string RemoveStringComment(string inputstring)
{
    if (inputstring.empty())
        return inputstring;
    else
    {
        string::size_type commentposition = inputstring.find_first_of(';');
        if (commentposition == string::npos)
            return inputstring;
        else
        {
            string outputstring = inputstring.substr(0, commentposition);
            // cout << outputstring << endl;
            return outputstring;
        }
    }

    cerr << "Misbehavior in stringhandle:RemoveStringComment()" << endl;
    exit(2);
}

string BracketsSubstring(string inputstring)
{
    return inputstring.substr(inputstring.find_first_of('{') + 1, inputstring.find_first_of('}') - inputstring.find_first_of('{') - 1);
}

void IllegalError(int errcode)
{
    cerr << "illegal input" << endl;
    exit(errcode);
}

void SyntaxError(int errcode)
{
    cerr << "syntax input" << endl;
    exit(errcode);
}
