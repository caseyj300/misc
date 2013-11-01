#include "State.h"

State::State( ) {
	name = "";
	accept = false;
	next = NULL;
	trans = NULL;
}

State::State(string s) {
	name = s;
	accept = false;
	next = NULL;
	trans = NULL;
}


// State function call to add a transition to its list of transitions.
void State::addTransition(State* dest, char c) {
	Transition* temp = trans;

	// Empty transition set for state
	// Attach new transition to trans
	if( trans == NULL ) {
		trans = new Transition(this, dest, c);
		return;
	}

	// Non-empty transition set for state
	// Move to last transition in state's list
	while( temp->next != NULL ) {
		temp = temp->next;
	}

	// Attach new transition to end of list
	temp->next = new Transition(this, dest, c );

	return;
}