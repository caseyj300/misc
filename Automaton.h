#ifndef __AUTOMATON_H__
#define __AUTOMATON_H__

#include "State.h"
#include "Transition.h"
#include "Symbol.h"
#include <string>
#include <cstdio>
#include <cstdlib>


class Automaton {
public:
	/* Operations */
	Automaton(); // Constructor
	//void ~Automaton(); // Deconstructor

	void addSymbol(char c);
	void removeSymbol(char c);

	void addState(string name);
	void removeState(string name);
	void makeAccept(string name);
	void makeStart(string name);

	void printStateSet( );

	void addTransition(string startName, string endName, char c);
	void removeTransition(string startName, char c);

	void getInput();

	/*
	bool evalInput(string);
	bool checkAutomaton();
	void saveAutomaton();
	void loadAutomaton(FILE*);
	void deleteAutomaton();
	*/

	/* Attributes */
	State* startState;
	State* currentState;
	string input;
	State* stateSet;
	Symbol alphabetSet;

private:
	/* Operations */
	bool matchState(string name);
	bool matchTrans(string name, char c);

	
};

#endif // __AUTOMATON_H__