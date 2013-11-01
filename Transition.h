#ifndef __TRANSITION_H__
#define __TRANSITION_H__

#include "State.h"

#include <string>

class State; // forward declaration

class Transition {
public:
	/* Operations */
	Transition();
	Transition(State* s1, State* s2, char c);

	/* Attributes */
	State* startState;	// starting state of transition
	State* endState;	// ending state of transition
	char trigger;		// character which triggers the transition
	Transition* next;	// pointer to a transition added to the state after
};

#endif // __TRANSITION_H__