/* THE MEATY JELLYFISHES */
#ifndef HEADER_H
#define HEADER_H

// Entity Classes //

class Automaton
{
public:
	/* Operations */
	void addSymbol(char);
	void removeSymbol(char);
	void addState(string);
	void removeState(string);
	void makeAccept(string);
	void makeNonaccept(string);
	void makeStart(string);
	void addTransition(string, string, char);
	void removeTransition(string, char);
	void getInput();
	bool evalInput(string);
	bool checkAutomaton();
	void saveAutomaton();
	void loadAutomaton(FILE*);
	void deleteAutomaton();
	/* Attributes */
	State StartingState; //pass in starting state
	State Current; // pass in current state of automaton
	string input; // given input string
	State stateset[]; // array of states belonging to automaton
}

class State
{
public:
	/* Attributes */
	string Name; // Name of state
	bool accept; // value of acceptance state or not
	Transition tranArray[]; // Array of transitions belonging to each state

}

class Transition
{
public:
	/* Attributes */
	State startTran; //start state of transition
	State endTran; // end state of transition
	char trigger; // char of transition trigger

}

class Symbol
{
public:
	/* Attributes */
	string Alphabet; // Alphabet Set
}














#endif