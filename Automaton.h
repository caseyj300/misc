#ifndef __AUTOMATON_H__
#define __AUTOMATON_H__

#include "State.h"
//#include "Transition.h"
#include "Symbol.h"
#include <string>
#include <cstdio>
#include <cstdlib>

using namespace std;

typedef struct node {
	State state;
	struct node* next;
} Node;

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

	void addTransition(string name, char c);
	void removeTransition(string name, char c);

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
	//Node* stateSet;
	State* stateSet;
	Symbol alphabetSet;

private:
	// create node function with passed name
	Node makeNode(string name);
	bool matchState(string name);

	
};

#endif // __AUTOMATON_H__