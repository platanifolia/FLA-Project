#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "turingmachine.h"
#include "stringhandle.h"

using namespace std;

int main(int argc, char *argv[])
{
    vector<string> vaildlines;

    if (argc == 3)
    {
        ifstream turingmachinefile;
        turingmachinefile.open(argv[1]);
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
        // testmachine.OutputMachineContent();
        bool answer = testmachine.StartMachine(argv[2]);
        if (answer)
            cout << "true" << endl;
        else
            cout << "false" << endl;
    }

    return 0;
}