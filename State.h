#ifndef __STATE_H__
#define __STATE_H__

#include "Transition.h"

#include <string>
using namespace std;

class Transition; // forward declaration

class State {
public:
	State();
	State(string s); // Constructor
	State(char* c);

	void addTransition(State* dest, char c);

	/* Attributes */
	string name; // Name of the State
	bool accept; // whether State is accepting or not
	Transition* trans; // Array of transitions originating from the State
	State* next; // address of whatever State is created after this one	
};

#endif // __STATE_H__