#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "turingmachine.h"
#include "stringhandle.h"

using namespace std;

bool verboseflag = false;

int main(int argc, char *argv[])
{
    vector<string> vaildlines;
    int fileargv = 0;

    if (argc > 1)
    {
        string eachargv = argv[1];
        if (eachargv == "-v" || eachargv == "--verbose")
        {
            verboseflag = true;
            fileargv = 2;
        }
        else if(eachargv == "-h" || eachargv == "--help")
        {
            OutputHelp();
            return 0;
        }
        else{
            fileargv = 1;
        }
        ifstream turingmachinefile;
        turingmachinefile.open(argv[fileargv]);
        if (!turingmachinefile)
        {
            cerr << "error:no file" << endl;
            exit(1);
        }
        string turingmachinefileline;
        while (getline(turingmachinefile, turingmachinefileline))
        {
            string testline = RemoveStringComment(turingmachinefileline);
            if (testline.empty())
                continue;
            else
                vaildlines.emplace_back(testline);
        }
        TuringMachine testmachine(vaildlines);
        bool answer = testmachine.StartMachine(argv[fileargv + 1]);
    }

    return 0;
}