#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class State
{
public:
    State();
    State( State & );
    void setNum( size_t );
    void addInput( string, size_t );
    void addNex( string, size_t );
    void addOutput( string, size_t );
    void setCurState( string );
    string getCurState() const;
    string getInput( size_t ) const;
    string getNexState( size_t ) const;
    string getOutput( size_t ) const;
    int getSit() const;
    bool determine( State ) const;
    bool newDetermine( State ) const;
    void replace( string, string );
    void changeSit( int );
    void newReplace( string, size_t );
    void newPrint() const;
private:
    string *input;
    string curState;
    string *nexState;
    string *output;
    size_t num;//num-situation
    int situation;//0 original, 1 different, 2 invalid
};

State::State()
{
    situation = 2;
}

State::State( State &a )
{
    curState = a.getCurState();
    num = a.num;
    input = new string[ num ];
    nexState = new string[ num ];
    output = new string[ num ];
    
    for( size_t _index = 0; _index < num; _index++ )
    {
        input[ _index ] = "-";
        nexState[ _index ] = "-";
        output[ _index ] = "-";
    }
    for( size_t index = 0; index < num; index++ )
    {
        input[ index ] = a.input[ index ];
        nexState[ index ] = a.nexState[ index ];
        output[ index ] = a.output[ index ];
    }
}

void State::setNum( size_t i )
{
    num = i;
    input = new string[ num ];
    nexState = new string[ num ];
    output = new string[ num ];
    
    for( size_t index = 0; index < i; index++ )
    {
        input[ index ] = "-";
        nexState[ index ] = "-";
        output[ index ] = "-";
    }
}

void State::addInput( string a, size_t i )
{
    input[ i ] = a;
}

void State::addNex( string a, size_t i )
{
    nexState[ i ] = a;
}

void State::addOutput( string a, size_t i )
{
    output[ i ] = a;
}

void State::setCurState( string s )
{
    curState = s;
}

string State::getCurState() const
{
    return curState;
}

string State::getInput( size_t i ) const
{
    return input[ i ];
}

string State::getNexState( size_t i ) const
{
    return nexState[ i ];
}

string State::getOutput( size_t i ) const
{
    return output[ i ];
}

int State::getSit() const
{
    return situation;
}

bool State::determine( State right ) const
{
    for( size_t i = 0; i < num; i++ )
    {
        if( nexState[ i ] != right.nexState[ i ] || output[ i ] != right.output[ i ] )
        {
            if( nexState[ i ] != "-" && right.nexState[ i ] != "-" )
                return false;
        }
    }
    
    return true;
}

bool State::newDetermine( State right ) const
{
    for( size_t i = 0; i < num; i++ )
    {
        if( output[ i ] != right.output[ i ] )
        {
            if( output[ i ] != "-" && right.output[ i ] != "-" )
                return false;
        }
    }
    
    return true;
}

void State::replace( string a , string b )//replace b by a
{
    for( size_t i = 0; i < num; i++ )
    {
        if( nexState[ i ] == b )
           nexState[ i ] = a;
    }
}

void State::changeSit( int a )
{
    situation = a;
}

void State::newReplace( string a, size_t i )
{
    nexState[ i ] = a;
}

void State::newPrint() const
{
    for( int i = 0; i < num; i++ )
    {
        if( nexState[ i ] != "-" || output[ i ] != "-" )
        cout << input[ i ] << " " << curState << " " << nexState[ i ] << " " << output[ i ] << "\n";
    }
}
#endif // STATE_H 

