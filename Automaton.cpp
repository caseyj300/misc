#include "Automaton.h"

// Default constructor
Automaton::Automaton( ) {
	startState = NULL;
	currentState = NULL;
	input = "";
	stateSet = NULL;
}


// Calls the Symbol class's addSymbol function
// To add the char c to the alphabet set string.
void Automaton::addSymbol(char c) {
	alphabetSet.addSymbol( c );
}


// Calls the Symbol class's removeSymbol function
// to remove a char c from the alphabet set string.
void Automaton::removeSymbol(char c) {
	alphabetSet.removeSymbol( c );
}


// Prints out the individual characters that are in the alphabetSet
void Automaton::printAlphabet( ) {
	int count = 0;
	int length = alphabetSet.Alphabet.length();

	cout << "The alphabet set currently holds:\n"
		 << "----------------------------------------";
	while( count < length ) {
		if( count % 8 == 0 )
			cout << endl;
		cout << "'" << alphabetSet.Alphabet[count] << "'  ";
		count++;
	}
	cout << "\n----------------------------------------\n" << endl;

	return;
}


// Creates and adds a state with the name of passed string to the stateSet list.
// - If the stateSet is empty, just creates the state and points to it from stateSet
// - If the stateSet is not empty, check that a state with matching name
//   does not already exist in stateSet.
// - If a matching state exists, print an appropriate message and end the function early.
// - Otherwise, create the state and add it to the end of the pointer list of stateSet.
void Automaton::addState(string name) {
	State* temp;

	// Empty stateSet
	if( stateSet == NULL ) {
		//cout << "stateSet is empty." << endl;
		stateSet = new State(name);
		//cout << "just added " << stateSet->name << endl;
		return;
	}

	// Non-empty stateSet
	// Check for matching state
	if( matchState(name) ) {
		// State name already exists
		cout << "A state named " << name << " already exists in the state set." << endl;
		return;
	}
	else {
		// Add state to stateSet
		temp = stateSet;
		while( temp->next != NULL ) {
			//cout << "temp = temp->next" << endl;
			temp = temp->next;
		}
		temp->next = new State(name);
	}
}


// Goes through the states in stateSet until a name
// matching the passed argument is found or the end
// of the stateSet is reached (NULL).
// - Returns true if a match is found.
// - Returns false otherwise.

bool Automaton::matchState(string name) {
	State* temp = stateSet;

	while( temp != NULL ) {
		if( temp->name.compare(name) == 0 )
			return true;
		temp = temp->next;			
	}
	return false;
}


// Searches the stateSet for a state with a name matching the passed string argument.
// - If a match is found, the state is removed and stateSet is updated.
// - If there is no match found, an appropriate message is printed and the function is ended.
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


// Searches the stateSet for a state whose name matches the passed string argument.
// - If a match is found, its sets its accept attribute to the passed boolean value x.
// - If no match is found, an appropriate message is printed and the function ended.
void Automaton::setAcceptance(string name, bool x) {
	State* temp = stateSet;

	// Empty stateSet
	if( stateSet == NULL ) {
		cout << "The state set is empty." << endl;
		return;
	}

	while( temp != NULL ) {
		if( temp->name.compare(name) == 0 ) {
			temp->accept = x;
			return;
		}
		temp = temp->next;
	}

	cout << "The state " << name << " could not be found in the state set." << endl;
	return;
}


// Searches the stateSet for a state whose name matches the passed string argument.
// - If a match is found, the state is set to be the startState.
//   The stateSet is updated accordingly.
// - If no match is found, an appropriate message is printed and the function ended.
void Automaton::makeStart(string name) {
	State* temp = stateSet;

	// Empty stateSet
	if( stateSet == NULL ) {
		cout << "The state set is empty." << endl;
		return;
	}

	// Non-first state in stateSet to start
	while( temp->next != NULL ) {
		if( temp->next->name.compare(name) == 0 ) {
			startState = temp;
			return;
		}
		temp = temp->next;
	}

	cout << "The state " << name << " could not be found in the state set." << endl;
	return;
}


// Goes through the stateSet printing out each state's
// name and whether it is accepting or not.
void Automaton::printStateSet( ) {
	State* temp = stateSet;

	cout << "The state set currently holds:\n"
		 << "----------------------------------------" << endl;
	while( temp != NULL ) {
		cout << "Name : " << temp->name << " | Accept : " << temp->accept << endl;
		temp = temp->next;
	}
	cout << "----------------------------------------\n" << endl;

	return;
}


// Creates a transition between two states with names matching
// arguments startName and endName, triggered by the passed char c.
// - If one or more of the states matching the passed string arguments
//   cannot be found, print an appropriate message and end the creation.
void Automaton::addTransition(string startName, string endName, char c) {
	State* temp1 = stateSet;
	State* temp2 = stateSet;

	// Empty stateSet
	if( stateSet == NULL ) {
		cout << "The stateSet is empty." << endl;
		return;
	}

	// Search for starting state
	while( temp1 != NULL ) {
		if( temp1->name.compare(startName) == 0 ) {
			// Search for ending state
			while( temp2 != NULL ) {
				if( temp2->name.compare(endName) == 0 ) {
					// Check for a matching transition character.
					if( matchTrans(startName, c) ) {
						cout << "A transition starting at state " << startName
							 << " with trigger character " << c << " already exists." << endl;
						return;
					}
					else {
						temp1->addTransition(temp2, c);
						//cout << "Transition on " << c << " made between states " << startName
						//     << " and " << endName << " made." << endl;
						return;
					}
				}
				temp2 = temp2->next;
			}
			cout << "No state matching the destination name " << endName << " could be found in the stateSet." << endl;
			return;
		}
		temp1 = temp1->next;
	}

	cout << "No state matching the starting name " << startName << " could be found in the stateSet." << endl;

	return;
}


// Searches for a state whose name matches passed string argument name
// and has a transition that is triggered by char c.
// - Returns true if a matching state and trigger are found.
// - Returns false otherwise.
bool Automaton::matchTrans(string name, char c) {
	State* tmpState = stateSet;
	Transition* tmpTran;

	// Find matching state.
	while( tmpState != NULL ) {
		if( tmpState->name.compare(name) == 0 ) {
			// Matching state found. Search state's transitions for trigger match.
			tmpTran = tmpState->trans;
			while( tmpTran != NULL ) {
				if( tmpTran->trigger == c ) {
					return true;
				}
				tmpTran = tmpTran->next;
			}
		}
		tmpState = tmpState->next;			
	}

	return false;
}


// Removes a transition based on the name of the origin state and the transition's trigger character.
// If the state or trigger cannot be found, print an appropriate message and end the function.
void Automaton::removeTransition(string name, char c) {
	State* tempS = stateSet;
	Transition* tempT1;
	Transition* tempT2;

	// Empty stateSet
	if( stateSet == NULL ) {
		cout << "The stateSet is empty." << endl;
		return;
	}

	// Non-empty stateSet
	// Search for matching origin state
	while( tempS != NULL ) {
		if( tempS->name.compare(name) == 0 ) {
			// Search for matching transition trigger
			
			// Empty transition set
			if( tempS->trans == NULL ) {
				cout << "The state " << name << " has no transitions." << endl;
				return;
			}

			// First trigger match
			if( tempS->trans->trigger == c ) {
				tempT1 = tempS->trans;
				tempS->trans = tempS->trans->next;
				delete tempT1;
				cout << "State " << name << " transition with trigger " << c << " has been removed." << endl;
				return;
			}

			// Non-first trigger match
			tempT1 = tempS->trans;
			while( tempT1->next != NULL ) {
				if( tempT1->next->trigger == c ) {
					tempT2 = tempT1->next;
					tempT1->next = tempT1->next->next;
					delete tempT2;
					cout << "State " << name << " transition with trigger " << c << " has been removed." << endl;
					return;
				}
				tempT1 = tempT1->next;
			}
			cout << "State " << name << " does not have a transition with trigger " << c << "." << endl;
			return;

		}
		tempS = tempS->next;
	}
	cout << "State " << name << " does not exist in the stateSet." << endl;

	return;
}


// Prints the transitions of the automaton
// Goes through the stateSet and prints the transitions of each state.
void Automaton::printTransitionSet( ) {
	State* tempS = stateSet;
	Transition* tempT;

	cout << "The transitions set currently holds:\n"
		 << "----------------------------------------" << endl;

	// Empty stateSet
	if( stateSet == NULL ) {
		return;
	}

	// Non-empty stateSet
	while( tempS != NULL ) {
		tempT = tempS->trans;
		while( tempT != NULL ) {
			cout << "Start: " << tempT->startState->name
				 << "  End: " << tempT->endState->name
				 << "  Trigger: '" << tempT->trigger << "'" << endl;
			tempT = tempT->next;
		}
		tempS = tempS->next;
	}
	cout << "----------------------------------------\n" << endl;

	return;
}


// Prompts user for the input string.
void Automaton::getInput( ) {
	cout << "Enter the input string : ";
	cin >> input;
	return;
}