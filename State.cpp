#include "State.h"

State::State( ) {
	name = "";
	accept = false;
	next = NULL;
}

State::State(string s) {
	name = s;
	accept = false;
	next = NULL;
}

State* State::makeState(string s) {
	State* temp = new State(s);
	
	return temp;
}