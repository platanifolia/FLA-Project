#ifndef FLA_TURING_PROJECT_TURING_MACHINE_H_
#define FLA_TURING_PROJECT_TURING_MACHINE_H_

#include <unordered_set>
#include <string>
#include <vector>
#include <map>

class Tape
{
private:
    int tapeid_;
    int head_;
    char blank_;
    std::map<int, char> tape_;

public:
    Tape(int id, char blank);
    Tape(int id, char blank, std::string inputstring);

    char GetTapeSymbol();
    void SetTapeSymbol(char newsymbol);
    void TapeShift(char direction);
    void CleanBothEnds();
};

class TransferFunction
{
private:
    // int tapeindex_;
    std::string srcstate_;
    std::string deststate_;
    std::vector<char> originalsymbol_;
    std::vector<char> replacesymbol_;
    std::vector<char> direction_;

public:
    TransferFunction(std::string srcstate, std::string deststate, std::string originalsymbol, std::string replacesymbol, std::string direction);

    std::string GetSrcState()
    {
        return this->srcstate_;
    }
    std::string GetDestState()
    {
        return this->deststate_;
    }
    std::vector<char> GetOriginalSymbols()
    {
        return this->originalsymbol_;
    }
    std::vector<char> GetReplaceSymbols()
    {
        return this->replacesymbol_;
    }
    std::vector<char> GetDirections()
    {
        return this->direction_;
    }
};

class TuringMachine
{
private:
    std::unordered_set<std::string> stateset_;
    std::unordered_set<char> inputset_;
    std::unordered_set<char> tapeset_;
    std::string startstate_;
    char blanksymbol_;
    std::unordered_set<std::string> endstateset_;
    int tapenum_;

    std::vector<TransferFunction> storedtransfer_;
    std::vector<Tape> alltape_;

    std::string currentstate_;

public:
    TuringMachine(std::vector<std::string> vaildlines);

    void FillStateSet(std::string statesetline);
    void FillInputSet(std::string inputsetline);
    void FillTapeSet(std::string tapesetline);
    void FillEndStateSet(std::string endstatesetline);

    std::vector<char> GetCurrentTapesSymbols();

    bool StartMachine(std::string input);
    bool StateJump();

    void OutputMachineContent();
};

#endif