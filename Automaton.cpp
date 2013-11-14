#include "Automaton.h"

// Default constructor
Automaton::Automaton( ) {
	startState = NULL;
	currentState = NULL;
	input = "";
	stateSet = NULL;
}

// Menu interface
void Automaton::menu()
{
	string input;
	string x;
	string s;
	string e;
	char t;
	char* n = "";
	string accept;
	
	// Print menu first time
	cout << "\n**Welcome to Automaton**"<<endl;
	cout << "1. Add State" <<endl;
	cout << "2. Add Transition" <<endl;
	cout << "3. Make Acceptance state" <<endl;
	cout << "4. Make Starting State" << endl;
	cout << "5. Add Symbol to Alpha Set" <<endl;
	cout << "6. Remove Symbol from Alpha Set" <<endl;
	cout << "7. Remove State" <<endl;
	cout << "8. Remove Transition" <<endl;
	cout << "9. Load Automaton from XML file" <<endl;
	cout << "10. Save Automaton"<<endl;
	cout << "11. Print State Set"<<endl;
	cout << "12. Print Alphabet Set" <<endl;
	cout << "13. Print Transition Set" <<endl;
	cout << "14. Print this menu again" << endl;
	cout << "0. Exit" << endl;

	do
	{
	input = "";	
	cout << "\nWhat would you like to do? ";
	cin >> input;

	switch(atoi(input.c_str()))
	{
	case 1:
		{
			cout << "Enter the name of new state: ";
			cin >> s;
			addState(s);
			break;
		}
	case 2:
		{
			cout << "Enter the start state for transition: ";
			cin >> s;
			cout << "Enter the end state for transition: ";
			cin >> e;
			cout << "Enter the trigger character: ";
			cin >> t;
			addTransition(s,e,t);
			break;
		}
	case 3:
		{
			cout << "Which state do you want to look at?: ";
			cin >> x;
			cout << "Is it accepting?(true/false): ";
			cin >> accept;
			if (accept == "true")
				setAcceptance(x, true);
			else
				setAcceptance(x, false);
			break;
		}
	case 4:
		{
			cout << "Which state do you want to make the starting state?: ";
			cin >> x;
			makeStart(x);
			break;
		}
	case 5:
		{
			cout << "What character do you wish to add to Alpha set?: ";
			cin >> s;
			addSymbol(s[0]);
			break;
		}
	case 6:
		{
			cout << "What character do you want to remove?: ";
			cin >> s;
			removeSymbol(s[0]);
			break;
		}
	case 7:
		{
			cout << "Which state do you want to remove?: ";
			cin >> x;
			removeState(x);
			break;
		}
	case 8:
		{
			cout << "Which state do you want to remove a transition?: ";
			cin >> x;
			cout << "Which trigger character is used for the transition?: ";
			cin >> s;
			removeTransition(x, s[0]);
			break;

		}
	case 9:
		{
			/*cout << "Enter the name of XML file: ";
			cin >> x;
			cout << "Trying to load from " << x << endl;
			strcat(n, x.c_str() );
			cout << "Begin attempt. " << endl;
			loadAutomaton(n);*/
			cout << "Not currently implemented" << endl;
			break;
		}
	case 10:
		{
			cout << "Saving...IS NOT CURRENTLY IMPLEMENTED"<<endl;
			break;
		}
	case 11:
		{
			printStateSet();
			break;
		}
	case 12:
		{
			printAlphabet();
			break;
			
		}
	case 13:
		{
			printTransitionSet();
			break;

		}
	case 14:
		{
		cout << "\n**Welcome to Automaton**"<<endl;
		cout << "1. Add State" <<endl;
		cout << "2. Add Transition" <<endl;
		cout << "3. Make Acceptance state" <<endl;
		cout << "4. Make Starting State" << endl;
		cout << "5. Add Symbol to Alpha Set" <<endl;
		cout << "6. Remove Symbol from Alpha Set" <<endl;
		cout << "7. Remove State" <<endl;
		cout << "8. Remove Transition" <<endl;
		cout << "9. Load Automaton from XML file" <<endl;
		cout << "10. Save Automaton"<<endl;
		cout << "11. Print State Set"<<endl;
		cout << "12. Print Alphabet Set" <<endl;
		cout << "13. Print Transition Set" <<endl;
		cout << "14. Print this menu again" << endl;
		cout << "0. Exit" << endl;
		break;
		}
	default:
		cout << "blargha" << endl;
	}
	
	x = "";
	s = "";
	e = "";
	t = '\0';
	accept = "";
	cout<<endl;
	}while ( atoi(input.c_str()) != 0);
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


// For the XML parser which handles char*
void Automaton::setAcceptance(char* name, bool x) {
	string s(name);
	setAcceptance(s, x);
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

	// Check first state
	if( temp->name.compare(name) == 0 ) {
		startState = temp;
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


// For the XML parser which handles char*
void Automaton::makeStart(char* name) {
	string s(name);
	makeStart(s);
	return;
}


// Prints the start state of the Automaton
void Automaton::printStart( ) {
	State* temp = startState;

	if( temp == NULL ) {
		cout << "There is no designated starting state." << endl;
		return;
	}

	cout << "Name: " << temp->name << "  Accept: " << temp->accept << endl;
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

	// Check trigger validity
	if( alphabetSet.Alphabet.find( string(1, c) ) == string::npos ) {
		cout << "The trigger character " << c << " is not in the alphabet set." << endl;
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


// For the XML parser, which handles char*
void Automaton::addTransition(char* startName, char* endName, char c ) {
	string start(startName);
	string end(endName);
	addTransition(start, end, c);
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


// Builds an automaton from an xml text file
void Automaton::loadAutomaton( char* filename ) {
	Automaton* tempA = this;
	if( XMLparser(filename, tempA) )
		cout << "Automaton successfully built from " << filename << endl;
	else
		cout << "Automaton could not be built from " << filename << endl;

	return;
}

// function saves automaton to XML file if one exists
void Automaton::saveAutomaton( ) {
	ofstream file;
	file.open ("output.txt");
	file << "<automaton>\n";
	if (alphabetSet.Alphabet.length() > 0)
	{
		file << "<alphaset>\n"; 
		for(int i =0; i < alphabetSet.Alphabet.length(); i++)
		{
			file << "\t<char>" << alphabetSet.Alphabet[i] << "</char>\n";
		}
		file << "</alphaset>\n";
		
	}
	else
	{
		file << "<alphaset>\n";
		file << "</alphaset>\n";
	}
	State *temp = stateSet;
	if (temp != NULL)
	{
		file << "<stateset>\n";
		while (temp != NULL)
			{
				file << "\t<state>" << temp->name << "</state>\n";
				temp = temp->next;
			}
		file << "</stateset>\n";
	}
	else
	{
		file << "<stateset>\n";
		file << "</stateset>\n";
	}
	State* tempS = stateSet;
	Transition* tempT;
	if ( stateSet != NULL)
	{
		file << "<transset>\n";
		while( tempS != NULL)
		{
			tempT = tempS->trans;
			
			while( tempT != NULL ) {
				file << "\t<trans>\n";
				file << "\t\t<state>" << tempT->startState->name << "</state>\n";
				file << "\t\t<char>" << tempT->trigger << "</char>\n";
				file << "\t\t<state>" << tempT->endState->name << "</state>\n";
				tempT = tempT->next;
				file << "\t</trans>\n";
			}
			
			tempS = tempS->next;
		}
		file << "</transset>\n";
			
	}
	else
	{
		file << "<transset>\n";
		file << "</transset>\n";
	}
	State* temp2 = startState;
	if (temp2 != NULL)
	{
		file << "<startstate>" << temp2->name << "</startstate>\n";
	}
	else
	{
		file << "<startstate>" << "</startstate>\n";
	}
	State* temp3 = stateSet;
	if (stateSet != NULL)
	{
		file << "<acceptstates>\n";
		while (temp3 != NULL)
		{
			if (temp3->accept == true)
			{
				file << "\t<state>" << temp3->name << "</state>\n";
			}
			temp3 = temp3->next;
		}
		file << "</acceptstates>\n";
	}
	else
	{
		file << "<acceptstates>\n";
		file << "</acceptstates>\n";
	}
	file << "</automaton>\n";

}