#ifndef __TRANSITION_H__
#define __TRANSITION_H__

#include "State.h"

#include <string>

class State; // forward declaration

class Transition {
public:
	/* Attributes */
	State* startState; // starting state of transition
	State* endState;   // ending state of transition
	char trigger;     // character which triggers the transition
};

#endif // __TRANSITION_H__