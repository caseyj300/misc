#include "Transition.h"

// Default constructor
Transition::Transition( ) {
	startState = NULL;
	endState = NULL;
	trigger = NULL;
	next = NULL;
}


// Constructor
Transition::Transition(State* s1, State* s2, char c) {
	startState = s1;
	endState = s2;
	trigger = c;
	next = NULL;
}