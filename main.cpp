#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Data.h"
#include "State.h"

using namespace std;

// <input> <current-state> <next-state> <output>
//   00 s0 s1 0
int main()
{
    ifstream file;
    file.open( "t03.kiss", ios::in );
    
    if( !file )
    {
        cerr << "file could not open!\n";
        exit( 1 );
    }
    
    string buf;
    int i = 0;//num-inputs
    int o = 0;//num-outputs
    int s = 0;//num-states
    int p = 0;//num-terms
    string r;//reset-state
    
    while( file >> buf )
    {
        if( buf == ".i" )
            file >> i;
        
        if( buf == ".o" )
            file >> o;
        
        if( buf == ".s" )
            file >> s;
        
        if( buf == ".p" )
            file >> p;
        
        if( buf == ".r" )
        {
            file >> r;
            break;
        }
    }
  
    vector< Data > vec;
    string in;//input
    string cs;//current-state
    string ns;//next-state
    string ou;//output
    for( int index = 0; index < p; index++ )
    {
        file >> in >> cs >> ns >> ou;
        Data *ptr = new Data( in, cs, ns, ou );
        vec.push_back( *ptr );
    }
    
    
    vector<string>vecIn;//vector for inputs
    bool same = false;
    
    for( size_t index = 0; index < vec.size(); index++ )
    {
        same = false;
       for( size_t _index = 0; _index < vecIn.size(); _index++ )
        {
            if( vec[ index ].getInput() == vecIn[ _index ] )
            {
                same = true;
                break;
            }
        }
        if( same == false )
            vecIn.push_back( vec[ index ].getInput() );
    }
    
   
    vector<string>vecState;//vector for inputs
    //bool _same = false;
    
    for( size_t index = 0; index < vec.size(); index++ )
    {
        same = false;
       for( size_t _index = 0; _index < vecState.size(); _index++ )
        {
            if( vec[ index ].getCurState() == vecState[ _index ] )
            {
                same = true;
                break;
            }
        }
        if( same == false )
            vecState.push_back( vec[ index ].getCurState() );
    }
    
    for( size_t index = 0; index < vec.size(); index++ )
    {
        same = false;
       for( size_t _index = 0; _index < vecState.size(); _index++ )
        {
            if( vec[ index ].getNexState() == vecState[ _index ] )
            {
                same = true;
                break;
            }
        }
        if( same == false )
            vecState.push_back( vec[ index ].getNexState() );
    }
    
    
   //---------------------start putting value into class called State vvvv
    
    //num-inputs == vecIn.size() == num;
    //num-state == vecState.size() == s
    
    vector< State >states( s );
    size_t num = vecIn.size();
    
    //set current state and num of input
    for( size_t index = 0; index < s; index++ )
    {
        states[ index ].setCurState( vecState[ index ] );
        states[ index ].setNum( num );
    }
     
    
    //set inputs
    for( size_t index = 0; index < s; index++ )
    {
        for( size_t _index = 0; _index < num; _index++ )
            states[ index ].addInput( vecIn[ _index ], _index );
    }
    
    
    for( size_t index = 0; index < vec.size(); index++ )
    {
        for ( size_t ind = 0; ind < s; ind++ )
        {
            if( vec[ index ].getCurState() == states[ ind ].getCurState() )
            {
                for( size_t _index = 0; _index < num; _index++ )
                {
                    if( vec[ index ].getInput() == states[ ind ].getInput( _index ) )
                    {
                        states[ ind ].addNex( vec[ index ].getNexState(), _index );
                        states[ ind ].addOutput( vec[ index ].getOutput(), _index );
                    }
                }
            }
        }
    }
    

    //----------------------------------start to reduce
    
    State ori( states[ 0 ] );
    states[ 0 ].changeSit( 0 );//0 original, 1 different, 2 invalid
    
    for( size_t l = 1; l < vecState.size() ; l++ )
    {
        if( !( states[ l ].newDetermine( ori ) ) )
        {
            states[ l ].changeSit( 1 );
        }
    }
    
 
    
    //-----------------replace the invalid state
    for( size_t index = 0; index < vecState.size() ; index++ )
    {
        if( states[ index ].getSit() == 1 || states[ index ].getSit() == 0 )//this state is valid
        {
           for( size_t _index = 0; _index < num ; _index++ )
            {
                for( size_t _ind = 0; _ind < vecState.size(); _ind++ )
                {
                    if( states[ index ].getNexState( _index ) == states[ _ind ].getCurState() && states[ _ind ].getSit() == 2 )
                        states[ index ].newReplace( states[ 0 ].getCurState(), _index );
                }
            }
        }
    }
    
    //--------------------some valid states should be invalid
    for( int l = 0; l < vecState.size() ; l++ )
    {
        if( states[ l ].getSit() == 1 || states[ l ].getSit() == 0 )
        {
            for( size_t index = l + 1; index < vecState.size() ; index++ )
            {
                if( states[ l ].determine( states[ index ] ) && ( states[ index ].getSit() == 1 || states[ index ].getSit() == 0 ) )
                {
                    states[ index ].changeSit( 2 );
                    for( size_t _i = 0; _i < vecState.size() ; _i++ )
                    {
                        for( size_t _index = 0; _index < num ; _index++ )
                         {
                             if( states[ _i ].getNexState( _index ) == states[ index ].getCurState() )
                                 states[ _i ].newReplace( states[ l ].getCurState(), _index );
                         }
                    }
                }
            }
        }
    }

    
    for( int l = 0; l < vecState.size() ; l++ )
     {
         if( states[ l ].getSit() == 1 || states[ l ].getSit() == 0 )
             states[ l ].newPrint();
     }
    return 0;
    
}
