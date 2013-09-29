#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool XMLparser( char* filename );
int tagCheck( char* c );
bool automParse( );
bool alphSetParse( );
bool stateSetParse( );
bool transSetParse( );
bool sStateParse( );
bool accStateParse( );