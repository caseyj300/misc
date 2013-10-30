#include "Automaton.h"

// Default constructor
Automaton::Automaton( ) {
	startState = NULL;
	currentState = NULL;
	input = "";
	stateSet = NULL;
}

void Automaton::addSymbol(char c) {
	alphabetSet.addSymbol( c );
}

void Automaton::removeSymbol(char c) {
	alphabetSet.removeSymbol( c );
}

void Automaton::addState(string name) {
	State* temp;

	// Empty stateSet
	if( stateSet == NULL ) {
		cout << "stateSet is empty." << endl;
		stateSet = new State(name);
		cout << "just added " << stateSet->name << endl;
		return;
	}

	// Non-empty stateSet
	if( matchState(name) ) {
		cout << "A state named " << name << " already exists in the state set." << endl;
		return;
	}
	else {
		temp = stateSet;
		while( temp->next != NULL ) {
			cout << "temp = temp->next" << endl;
			temp = temp->next;
		}
		temp->next = new State(name);
	}
}

bool Automaton::matchState(string name) {
	State* temp = stateSet;

	while( temp != NULL ) {
		if( temp->name.compare(name) == 0 )
			return true;
		temp = temp->next;			
	}
	return false;
}

void Automaton::removeState(string name) {
	State* temp = stateSet;
	State* temp2;

	cout << "Attempting to remove " << name << endl;
	// Empty state set
	if( temp == NULL ) {
		cout << "The state set is empty." << endl;
		return;
	}

	// Removing first State
	if( temp->name.compare(name) == 0 ) {
		stateSet = stateSet->next;
		delete temp;
		return;
	}
	
	while( temp->next != NULL ) {
		if( temp->next->name.compare(name) == 0 ) {
			cout << "Removing the state " << name << endl;
			temp2 = temp->next;
			temp->next = temp->next->next;
			delete temp2;
			return;
		}
		temp = temp->next;
	}
	
	cout << "The state set did not contain a state named " << name << endl;
	
	return;
}

void Automaton::makeAccept(string name) {
	State* temp = stateSet;

	// Empty stateSet
	if( stateSet == NULL ) {
		cout << "The state set is empty." << endl;
		return;
	}

	while( temp != NULL ) {
		if( temp->name.compare(name) == 0 ) {
			temp->accept = true;
			return;
		}
		temp = temp->next;
	}

	cout << "The state " << name << " could not be found in the state set." << endl;
	return;
}

void Automaton::makeStart(string name) {
	State* temp = stateSet;

	// Empty stateSet
	if( stateSet == NULL ) {
		cout << "The state set is empty." << endl;
		return;
	}

	while( temp != NULL ) {
		if( temp->name.compare(name) == 0 ) {
			startState = temp;
			return;
		}
		temp = temp->next;
	}

	cout << "The state " << name << " could not be found in the state set." << endl;
	return;
}