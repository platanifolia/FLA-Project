#include "turingmachine.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "stringhandle.h"

using namespace std;

TuringMachine::TuringMachine(vector<string> vaildlines)
{
    for (string eachline : vaildlines)
    {
        if (eachline.empty())
        {
            cerr << "TOLOG" << endl;
            exit(1);
        }
        if (eachline.find("#Q = ") != string::npos)
        {
            FillStateSet(eachline);
            continue;
        }
        else if (eachline.find("#S = ") != string::npos)
        {
            FillInputSet(eachline);
            continue;
        }
        else if (eachline.find("#G = ") != string::npos)
        {
            FillTapeSet(eachline);
            continue;
        }
        else if (eachline.find("#q0 = ") != string::npos)
        {
            this->startstate_ = eachline.substr(6, eachline.size());
            continue;
        }
        else if (eachline.find("#B = ") != string::npos)
        {
            this->blanksymbol_ = eachline[5];
            continue;
        }
        else if (eachline.find("#F = ") != string::npos)
        {
            FillEndStateSet(eachline);
            continue;
        }
        else if (eachline.find("#N = ") != string::npos)
        {
            this->tapenum_ = stoi(eachline.substr(5, eachline.size()));
            if (this->tapenum_ < 0)
                cerr << "TOLOG" << endl;
            continue;
        }
        else
        {
            istringstream tempstringstream(eachline);
            string oldstates;
            string oldsymbols;
            string newsymbols;
            string directions;
            string newstates;
            tempstringstream >> oldstates >> oldsymbols >> newsymbols >> directions >> newstates;

            TransferFunction newtransfer(oldstates, newstates, oldsymbols, newsymbols, directions);
            this->storedtransfer_.emplace_back(newtransfer);
        }
    }
    this->currentstate_ = this->startstate_;
}

void TuringMachine::FillStateSet(string statesetline)
{
    string temp = BracketsSubstring(statesetline);
    string::size_type position = temp.find_first_of(",");
    while (position != string::npos)
    {
        temp.replace(position, 1, " ");
        position = temp.find_first_of(",");
    }

    istringstream tempstringstream(temp);
    string eachstate;
    while (tempstringstream >> eachstate)
        this->stateset_.insert(eachstate);

    return;
}
void TuringMachine::FillInputSet(string inputsetline)
{
    string temp = BracketsSubstring(inputsetline);
    string::size_type position = temp.find_first_of(",");
    while (position != string::npos)
    {
        temp.replace(position, 1, " ");
        position = temp.find_first_of(",");
    }

    istringstream tempstringstream(temp);
    char eachinput;
    while (tempstringstream >> eachinput)
        this->inputset_.insert(eachinput);

    return;
}
void TuringMachine::FillTapeSet(string tapesetline)
{
    string temp = BracketsSubstring(tapesetline);
    string::size_type position = temp.find_first_of(",");
    while (position != string::npos)
    {
        temp.replace(position, 1, " ");
        position = temp.find_first_of(",");
    }

    istringstream tempstringstream(temp);
    char eachtape;
    while (tempstringstream >> eachtape)
        this->tapeset_.insert(eachtape);

    return;
}
void TuringMachine::FillEndStateSet(string endstatesetline)
{
    string temp = BracketsSubstring(endstatesetline);
    string::size_type position = temp.find_first_of(",");
    while (position != string::npos)
    {
        temp.replace(position, 1, " ");
        position = temp.find_first_of(",");
    }

    istringstream tempstringstream(temp);
    string eachendstate;
    while (tempstringstream >> eachendstate)
        this->endstateset_.insert(eachendstate);

    return;
}

vector<char> TuringMachine::GetCurrentTapesSymbols()
{
    vector<char> res;
    for (Tape &tape : this->alltape_)
    {
        res.push_back(tape.GetTapeSymbol());
    }
    return res;
}

bool TuringMachine::StartMachine(string input)
{
    // TODO: jian cha input symbol
    bool accept = true;
    this->alltape_.emplace_back(0, this->blanksymbol_, input);
    for (int i = 1; i < this->tapenum_; i++)
    {
        this->alltape_.emplace_back(i, this->blanksymbol_);
    }
    while (this->endstateset_.find(this->currentstate_) == this->endstateset_.end())
    {
        for (Tape &tape : this->alltape_)
        {
            tape.CleanBothEnds();
        }
        if(!this->StateJump())
        {
            accept = false;
            break;
        }
    }
    return accept;
}

bool TuringMachine::StateJump()
{
    for (TransferFunction tf : this->storedtransfer_)
    {
        if (tf.GetSrcState() == this->currentstate_ && tf.GetOriginalSymbols() == this->GetCurrentTapesSymbols())
        {
            for (int i = 0; i < this->tapenum_; i++)
            {
                this->alltape_.at(i).SetTapeSymbol(tf.GetReplaceSymbols().at(i));
            }
            for (int i = 0; i < this->tapenum_; i++)
            {
                this->alltape_.at(i).TapeShift(tf.GetDirections().at(i));
            }
            this->currentstate_ = tf.GetDestState();
            return true;
        }
    }
    return false;
}

void TuringMachine::OutputMachineContent()
{
    for (auto intr : this->stateset_)
    {
        cout << intr << endl;
    }
    cout << "====================================" << endl;
    for (auto intr : this->inputset_)
    {
        cout << intr << endl;
    }
    cout << "====================================" << endl;
    for (auto intr : this->tapeset_)
    {
        cout << intr << endl;
    }
    cout << "====================================" << endl;
    cout << this->startstate_ << endl;
    cout << "====================================" << endl;
    cout << this->blanksymbol_ << endl;
    cout << "====================================" << endl;
    for (auto intr : this->endstateset_)
    {
        cout << intr << endl;
    }
    cout << "====================================" << endl;
    cout << this->tapenum_ << endl;
    return;
}

TransferFunction::TransferFunction(std::string srcstate, std::string deststate, std::string originalsymbol, std::string replacesymbol, std::string direction)
{
    this->srcstate_ = srcstate;
    this->deststate_ = deststate;

    for (char temp : originalsymbol)
    {
        this->originalsymbol_.emplace_back(temp);
    }
    for (char temp : replacesymbol)
    {
        this->replacesymbol_.emplace_back(temp);
    }
    for (char temp : direction)
    {
        this->direction_.emplace_back(temp);
    }
}

Tape::Tape(int id, char blank)
{
    this->tapeid_ = id;
    this->blank_ = blank;
    this->head_ = 0;
    this->tape_.insert(make_pair(0, blank));
}

Tape::Tape(int id, char blank, std::string inputstring)
{
    this->tapeid_ = id;
    this->blank_ = blank;
    this->head_ = 0;

    int i = 0;
    for (char temp : inputstring)
    {
        this->tape_.insert(make_pair(i, temp));
        i += 1;
    }
}

char Tape::GetTapeSymbol()
{
    if (tape_.find(head_) == tape_.end())
        return blank_;
    return tape_.at(head_);
}

void Tape::SetTapeSymbol(char newsymbol)
{
    if (tape_.find(head_) == tape_.end())
        tape_.insert(make_pair(head_, newsymbol));
    else
        tape_.at(head_) = newsymbol;
}

void Tape::TapeShift(char direction)
{
    if (direction == 'l')
    {
        head_ -= 1;
    }
    if (direction == 'r')
    {
        head_ += 1;
    }

    if (tape_.find(head_) == tape_.end())
    {
        tape_.insert(make_pair(head_, blank_));
    }
}

void Tape::CleanBothEnds()
{
    // the left end
    for (auto it = tape_.begin(); it != tape_.end();)
    {
        if (it->second != blank_ or head_ == it->first)
            break;
        it = tape_.erase(it);
    }

    // the right end
    for (auto it = tape_.rbegin(); it != tape_.rend();)
    {
        if (it->second != blank_ or head_ == it->first)
            break;
        tape_.erase((++it).base());
    }
}