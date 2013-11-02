#include "Symbol.h"

Symbol::Symbol( ) {
	Alphabet = "";
}

void Symbol::addSymbol(char c) {
	// check that char c is not already in Alphabet
	if( Alphabet.find( string(1, c) ) != string::npos && !Alphabet.empty() ) {
		cout << "Character " << c << " is already part of Alphabet." << endl;
		return;
	}

	Alphabet.append( string(1, c) );
}

void Symbol::removeSymbol(char c) {
	// Search for char c in Alphabet
	// If found, remove it.
	// Otherwise, print a message.
	if( Alphabet.find( string(1, c) ) != string::npos ) {
		Alphabet.erase( Alphabet.begin()+(Alphabet.find( string(1,c) )) );
	}
	else {
		cout << "Character " << c << " was not found in the Alphabet." << endl;
	}

	return;
}