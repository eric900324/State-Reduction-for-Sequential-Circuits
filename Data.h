#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <string>

using namespace std;

class Data
{
public:
    Data();
    Data( string, string, string, string );
    string getInput() const;
    string getCurState() const;
    string getNexState() const;
    string getOutput() const;
private:
    string input;
    string curState;
    string nexState;
    string output;
};

Data::Data()
{
    
}

Data::Data( string i, string cs, string ns, string o )
{
    input = i;
    curState = cs;
    nexState = ns;
    output = o;
}

string Data::getInput() const
{
    return input;
}

string Data::getCurState() const
{
    return curState;
}

string Data::getNexState() const
{
    return nexState;
}

string Data::getOutput() const
{
    return output;
}

#endif // DATA_H 
