#ifndef __XMLAUTOMATONPARSER_H__
#define __XMLAUTOMATONPARSER_H__

#include "Automaton.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool XMLparser( char* filename, Automaton* jiffy );
int tagCheck( char* c );
bool automParse( );
bool alphSetParse( );
bool stateSetParse( );
bool transSetParse( );
bool sStateParse( );
bool accStateParse( );

#endif // __XMLAUTOMATONPARSER_H__