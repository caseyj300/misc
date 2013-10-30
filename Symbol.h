#ifndef __SYMBOL_H__
#define __SYMBOL_H__

#include <iostream>
#include <string>
using namespace std;


class Symbol {
public:
	/* Operators */
	Symbol();
	void addSymbol(char c);
	void removeSymbol(char c);

	/* Attributes */
	string Alphabet; // Alphabet Set
};

#endif // __SYMBOL_H__