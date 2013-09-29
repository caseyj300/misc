#include "XMLparser.h"

// Global variables
ifstream infile;
string line;
char* cline;
char* token;

bool XMLparser( char* filename ) {
	int desTag = 1; // represents the desired tag
	int tcheck; // represents the encountered tag
	bool (*fptr[6])() = {automParse, alphSetParse, stateSetParse,
		transSetParse, sStateParse, accStateParse};

	infile.open(filename);
	if( !infile.is_open() ) {
		cout << "Unable to open file." << endl;
		return false;
	}

	// Search for tags in expected order :
	// automaton, alphaset(char), stateset(state),
	// transset(trans(state,char,state)), startstate(state)
	// acceptstates(state)

	while( getline(infile, line) ) {
		cline = (char*)malloc(sizeof(char) * line.size());
		strcpy( cline, line.c_str() );
		// if line is not empty. check for recognized tags.
		if( strcmp(cline, "") != 0 ) {
			token = strtok(cline, " >");
			while( token ) {
				// check if token is the desired tag
				if( desTag == tagCheck(token) || desTag == 10 ) {
					cout << "Encountered the ";
					switch(desTag) {
						case 1: cout << "<automaton>"; break;
						case 2: cout << "<alphaset>"; break;
						case 3: cout << "<stateset>"; break;
						case 4: cout << "<transet>"; break;
						case 5: cout << "<startstate>"; break;
						case 6: cout << "<acceptstates>"; break;
						case 10: 
							cout << "</automaton> tag. Congratulations!" << endl;
							return true;
							break;
					}
					cout << " tag." << endl;
					// execute more specific parsing based on set tag : (function pointers)
					if( !fptr[desTag - 1]( ) )
						return false;

					desTag++; // increment status of desired tag to next in expected order
					if( desTag == 7 ) { // looking for </automaton> tag
						desTag = 10;
					}
				}
				else if( desTag == 7 ) { // wanting </automaton> tag

				}
				else {
					cout << "ERROR: Was expecting ";
					switch(desTag) {
						case 1: cout << "<automaton>"; break;
						case 2: cout << "<alphaset>"; break;
						case 3: cout << "<stateset>"; break;
						case 4: cout << "<transet>"; break;
						case 5: cout << "<startstate>"; break;
						case 6: cout << "<acceptstates>"; break;
						case 7: cout << "</automaton>"; break;
					}
					cout << " tag." << endl;
					return false;
				}
				token = strtok(NULL, " <");
			}
		}
	}

	infile.close();

	return true;
}

// Checks if c matches an expected tag :
// automaton, alphaset, stateset, transet, startstate, acceptstates
// char, state, trans
// Returns an integer corresponding to the identified tag.
// Or 0 if c does not match a tag
int tagCheck( char* c ) {
	if( strcmp(c, "<automaton") == 0 ) return 1;
	else if( strcmp(c, "</automaton") == 0 ) return 10;
	else if( strcmp(c, "<alphaset") == 0 ) return 2;
	else if( strcmp(c, "</alphaset") == 0 ) return -2;
	else if( strcmp(c, "<stateset") == 0 ) return 3;
	else if( strcmp(c, "</stateset") == 0 ) return -3;
	else if( strcmp(c, "<transset") == 0 ) return 4;
	else if( strcmp(c, "</transset") == 0 ) return -4;
	else if( strcmp(c, "<startstate") == 0 ) return 5;
	else if( strcmp(c, "</startstate") == 0 ) return -5;
	else if( strcmp(c, "<acceptstates") == 0 ) return 6;
	else if( strcmp(c, "</acceptstates") == 0 ) return -6;
	else if( strcmp(c, "<char") == 0 ) return 7;
	else if( strcmp(c, "</char") == 0 ) return -7;
	else if( strcmp(c, "<state") == 0 ) return 8;
	else if( strcmp(c, "</state") == 0 ) return -8;
	else if( strcmp(c, "<trans") == 0 ) return 9;
	else if( strcmp(c, "</trans") == 0 ) return -9;
	else return 0;
}

bool automParse( ) {
	//cout << "pointless function call" << endl;
	return true;
}

bool alphSetParse( ) {
	int desTag = 7; // desired tag is <char>
	int step = 1; // 1 = want <char>, 2 = want symbol, 3 = want </char>
	char symbol;
	//cout << "parse the alphaset" << endl;
	// Expects <char> [character] </char> format until </alphaset> encountered

	// If there are still tokens left to be extracted from cline. Process them
	token = strtok(NULL, " >");
	while( token ) {
		if( -2 == tagCheck(token) ) { // </alphaset> tag
			if( desTag == 7 ) // not in middle of creating another alphabet node
				return true;
		}

		if( desTag != tagCheck(token) ) {
			cout << "ERROR: Creating Alphabet. Was expecting ";
			switch(step) {
				case 1: cout << "<char> tag." << endl; break;
				case 2: cout << "a single symbol." << endl; break;
				case 3: cout << "</char> tag." << endl; break;
			}
			return false;
		}

		if( desTag == tagCheck(token) && desTag == 7 ) {
			step = 2; desTag = 0;
		}
		else if( desTag == tagCheck(token) && desTag == 0 ) {
			// symbol for alphabet
			// token should be of legth 1 (symbol is only thing in token) or 7 (symbol + '</char')
			if( strlen(token) == 1 ) {
				step = 3; desTag = -7;
				cout << "Add to alphabet set: " << token << endl;
			}
			else if( strlen(token) == 7 ) {
				if( strcmp( "</char", token + 1 ) == 0 ) {
					step = 1; desTag = 7;
					cout << "Add to alphabet set: " << token[0] << endl;
				}
			}
			else {
				cout << "ERROR: Alphabet entries should be one character in length." << endl;
				return false;
			}
		}
		else if( desTag == tagCheck(token) && desTag == -7 ) {
			step = 1; desTag = 7;
		}

		token = strtok(NULL, " >");
	} // end of tokens from old cline

	// If there are no more tokens to grab from old cline or you process cline
	// and still haven't found the </alphaset> tag, process additional lines
	while( getline(infile, line) ) {
		cline = (char*)malloc(sizeof(char) * line.size());
		strcpy( cline, line.c_str() );
		// If line is not empty, check for desired tag.
		if( strcmp(cline, "") != 0 ) {
			token = strtok(cline, " >");
			while( token ) {
				if( -2 == tagCheck(token) ) { // </alphaset> tag
					if( desTag == 7 ) // not in middle of creating another alphabet node
						return true;
				}

				if( desTag != tagCheck(token) ) {
					cout << "ERROR: Creating Alphabet. Was expecting ";
					switch(step) {
						case 1: cout << "<char> tag." << endl; break;
						case 2: cout << "a single symbol." << endl; break;
						case 3: cout << "</char> tag." << endl; break;
					}
					return false;
				}

				if( desTag == tagCheck(token) && desTag == 7 ) {
					step = 2; desTag = 0;
				}
				else if( desTag == tagCheck(token) && desTag == 0 ) {
					// symbol for alphabet
					// token should be of legth 1 (symbol is only thing in token) or 7 (symbol + '</char')
					if( strlen(token) == 1 ) {
						step = 3; desTag = -7;
						cout << "Add to alphabet set: " << token << endl;
					}
					else if( strlen(token) == 7 ) {
						if( strcmp( "</char", token + 1 ) == 0 ) {
							step = 1; desTag = 7;
							cout << "Add to alphabet set: " << token[0] << endl;
						}
					}
					else {
						cout << "ERROR: Alphabet entries should be one character in length." << endl;
						return false;
					}
				}
				else if( desTag == tagCheck(token) && desTag == -7 ) {
					step = 1; desTag = 7;
				}

				token = strtok(NULL, " >");
			} // end of tokens from cline
		}
	} // end of file reached

	return false;
}

bool stateSetParse( ) {
	int desTag = 8; // desired tag is <state>
	int step = 1; // 1 = want <state>, 2 = want name, 3 and 4 = want </state>
	char* name;
	int count = 0;
	//cout << "Parse the state set" << endl;

	// Expects <state> [name] </state> format until </stateset> encountered

	// If there are still tokens left to be extracted from cline. Process them
	token = strtok(NULL, " >");
	while( token ) {
		if( -3 == tagCheck(token) ) { // </stateset> tag
			if( desTag == 8 ) // not in middle of creating another state node
				return true;
		}

		if( desTag != tagCheck(token) ) {
			cout << "ERROR: Creating State Set. Was expecting ";
			switch(step) {
				case 1: cout << "<state> tag." << endl; break;
				case 2: cout << "a state name." << endl; break;
				case 3: cout << "</state> tag." << endl; break;
				case 4: cout << "/state tag." << endl; break;
			}
			return false;
		}

		if( desTag == tagCheck(token) && desTag == 8 ) {
			step = 2; desTag = 0;
		}
		else if( desTag == tagCheck(token) && desTag == 0 ) {
			// name for state
			// if token is <= 7 characters, it must be the name
			// if token is > 7 characters, it might have </state at the end of the name
			if( strlen(token) > 7 && strcmp("</state", token + strlen(token) - 7) == 0 ) {
				step = 4; desTag = 8;
				name = (char*)malloc(strlen(token) - (sizeof(char) * 7));
				while( count < (strlen(token) - 7) ) {
					name[count] = token[count];
					count ++;
				}
				name[count] = NULL;
				cout << "Add to state set: " << name << endl;
				count = 0;
			}
			else {
				step = 3; desTag = -8;
				cout << "Add to state set: " << token << endl;
			}
		}
		else if( (desTag == tagCheck(token) && desTag == -8) || ( strcmp(token, "/state") == 0 && step == 4 ) ) {
			step = 1; desTag = 8;
		}

		token = strtok(NULL, " >");
	} // end of tokens from old cline

	// If there are no more tokens to grab from old cline or you process cline
	// and still haven't found the </stateset> tag, process additional lines
	while( getline(infile, line) ) {
		cline = (char*)malloc(sizeof(char) * line.size());
		strcpy( cline, line.c_str() );
		// If line is not empty, check for desired tag.
		if( strcmp(cline, "") != 0 ) {
			token = strtok(cline, " >");
			while( token ) {
				if( -3 == tagCheck(token) ) { // </stateset> tag
					if( desTag == 8 ) // not in middle of creating another state node
						return true;
				}

				if( desTag != tagCheck(token) ) {
					cout << "ERROR: Creating State Set. Was expecting ";
					switch(step) {
						case 1: cout << "<state> tag." << endl; break;
						case 2: cout << "a state name." << endl; break;
						case 3: cout << "</state> tag." << endl; break;
						case 4: cout << "/state tag." << endl; break;
					}
					return false;
				}

				if( desTag == tagCheck(token) && desTag == 8 ) {
					step = 2; desTag = 0;
				}
				else if( desTag == tagCheck(token) && desTag == 0 ) {
					// name for state
					// if token is <= 7 characters, it must be the name
					// if token is > 7 characters, it might have </state at the end of the name
					if( strlen(token) > 7 && strcmp("</state", token + strlen(token) - 7) == 0 ) {
						step = 4; desTag = 8;
						name = (char*)malloc(strlen(token) - (sizeof(char) * 7));
						while( count < (strlen(token) - 7) ) {
							name[count] = token[count];
							count ++;
						}
						name[count] = NULL;
						cout << "Add to state set: " << name << endl;
						count = 0;
					}
					else {
						step = 3; desTag = -8;
						cout << "Add to state set: " << token << endl;
					}
				}
				else if( (desTag == tagCheck(token) && desTag == -8) || ( strcmp(token, "/state") == 0 && step == 4 ) ) {
					step = 1; desTag = 8;
				}
				
				token = strtok(NULL, " >");
			} // end of tokens in cline
		}
	} // reached end of file

	return false;
}

bool transSetParse( ) {
	int desTag = 9; // desired tag is <trans>
	int step = 1; // 1 = <trans>, 2&-2 = <state>, 3&-3 = name, 4&-4 = </state>
	              // 5 = <char>, 6 = symbol, 7 = </char>, 8 = </trans>
	char* name1;
	char* name2;
	char symbol;
	int count = 0;

	//cout << "parse the transition set" << endl;

	// If there are still tokens left to be extracted from cline, process them.
	token = strtok(NULL, " >");
	while( token ) {
		if( -4 == tagCheck(token) ) { // </transset> tag
			if( desTag == 1 ) // not in middle of creating transition
				return true;
		}

		if( desTag != tagCheck(token) ) {
			cout << "ERROR: Creating Transition Set. Was expecting ";
			switch(step) {
				case 1: cout << "<trans> tag." << endl; break;
				case 2:
				case -2: cout << "<state> tag." << endl; break;
				case 3:
				case -3: cout << "a state name." << endl; break;
				case 4:
				case -4: cout << "</state> tag." << endl; break;
				case 5: cout << "<char> tag." << endl; break;
				case 6: cout << "a symbol." << endl; break;
				case 7: cout << "</char> tag." << endl; break;
				case 8: cout << "</trans> tag." << endl; break;
			}
			return false;
		}

		switch( desTag ) {
			case 9: // Found the <trans> tag
				step = 2; desTag = 8;
				break;
			case 8: // Found the <state> tag
				if( step == 2 ) { // first set of <state> in transition
					step = 3; desTag = 0;
				}
				else { // second set of <state> in transition
					step = -3; desTag = 0;
				}
				break;
			case 0:
				if( step != 6 ) { 
					// name for state
					// if token is > 7 characters, it might have </state at the end
					if( strlen(token) > 7 && strcmp("</state", token + strlen(token) - 7) == 0 ) {
						if( step == 3 ) { // name of first state in transition
							step = 5; desTag = 7;
							name1 = (char*)malloc(sizeof(char) * (strlen(token)-7));
							while( count < (strlen(token)-7) ) {
								name1[count] = token[count];
								count++;
							}
							name1[count] = NULL;
							count = 0;
						}
						else { // name of second state in transition
							step = 8; desTag = -9;
							name2 = (char*)malloc(sizeof(char) * (strlen(token)-7));
							while( count < (strlen(token)-7) ) {
								name2[count] = token[count];
								count++;
							}
							name2[count] = NULL;
							count = 0;
						}
					}
					else {
						if( step == 3 ) { // first state in transition
							step = 4; desTag = -8;
							strcpy(name1, token);
						}
						else { // second state in transition
							step = -4; desTag = -8;
							strcpy(name2, token);
						}
					}
				}
				else {
					// symbol for transition
					// token should be of length 1 (symbol is only thing in token) or 7 (symbol + '</char')
					if( strlen(token) == 1 ) {
						step = 7; desTag = -7;
						symbol = token[0];
					}
					else if( strlen(token) == 7 ) {
						if( strcmp( "</char", token+1 ) == 0 ) {
							step = 8; desTag = 8;
							symbol = token[0];
						}
					}
					else {
						cout << "ERROR: Transition character should be one character in length." << endl;
						return false;
					}
				}
				break;
			case -8: // Found the </state> tag
				if( step == 4 ) { // first state in transition
					step = 5; desTag = 7;
				}
				else { // second state in transition
					step = 8; desTag = -9;
				}
				break;
			case 7: // Found the <char> tag
				step = 6; desTag = 0;
				break;
			case -7: // Found the </char> tag
				step = -2; desTag = 8;
				break;
			case -9: // Found the </trans> tag
				cout << "Add to transition set: " << symbol << " shifts " << name1 << " to " << name2 << endl;
				step = 1; desTag = 9;
				break;
		}
		token = strtok(NULL, " >");
	} // end of left over tokens in cline

	// If there are no more tokens to grab from old cline or you processed cline
	// and still haven't found the </transet> tag, process additional lines
	while( getline(infile, line) ) {
		cline = (char*)malloc(sizeof(char) * line.size());
		strcpy( cline, line.c_str() );

		// If line is not empty, check for desired tag
		if( strcmp( cline, "") != 0 ) {
			token = strtok(cline, " >");
			while( token ) {
				if( -4 == tagCheck(token) ) { // </transset> tag
					if( desTag == 9 ) // not in middle of creating transition
						return true;
				}

				if( desTag != tagCheck(token) ) {
					cout << "ERROR: Creating Transition Set. Was expecting ";
					switch(step) {
						case 1: cout << "<trans> tag." << endl; break;
						case 2:
						case -2: cout << "<state> tag." << endl; break;
						case 3:
						case -3: cout << "a state name." << endl; break;
						case 4:
						case -4: cout << "</state> tag." << endl; break;
						case 5: cout << "<char> tag." << endl; break;
						case 6: cout << "a symbol." << endl; break;
						case 7: cout << "</char> tag." << endl; break;
						case 8: cout << "</trans> tag." << endl; break;
					}
					return false;
				}

				switch( desTag ) {
					case 9: // Found the <trans> tag
						step = 2; desTag = 8;
						break;
					case 8: // Found the <state> tag
						if( step == 2 ) { // first set of <state> in transition
							step = 3; desTag = 0;
						}
						else { // second set of <state> in transition
							step = -3; desTag = 0;
						}
						break;
					case 0:
						if( step != 6 ) { 
							// name for state
							// if token is > 7 characters, it might have </state at the end
							if( strlen(token) > 7 && strcmp("</state", token + strlen(token) - 7) == 0 ) {
								if( step == 3 ) { // name of first state in transition
									step = 5; desTag = 7;
									name1 = (char*)malloc(sizeof(char) * (strlen(token)-7));
									while( count < (strlen(token)-7) ) {
										name1[count] = token[count];
										count++;
									}
									name1[count] = NULL;
									count = 0;
								}
								else { // name of second state in transition
									step = 8; desTag = -9;
									name2 = (char*)malloc(sizeof(char) * (strlen(token)-7));
									while( count < (strlen(token)-7) ) {
										name2[count] = token[count];
										count++;
									}
									name2[count] = NULL;
									count = 0;
								}
							}
							else {
								if( step == 3 ) { // first state in transition
									step = 4; desTag = -8;
									strcpy(name1, token);
								}
								else { // second state in transition
									step = -4; desTag = -8;
									strcpy(name2, token);
								}
							}
						}
						else {
							// symbol for transition
							// token should be of length 1 (symbol is only thing in token) or 7 (symbol + '</char')
							if( strlen(token) == 1 ) {
								step = 7; desTag = -7;
								symbol = token[0];
							}
							else if( strlen(token) == 7 ) {
								if( strcmp( "</char", token+1 ) == 0 ) {
									step = 8; desTag = 8;
									symbol = token[0];
								}
							}
							else {
								cout << "ERROR: Transition character should be one character in length." << endl;
								return false;
							}
						}
						break;
					case -8: // Found the </state> tag
						if( step == 4 ) { // first state in transition
							step = 5; desTag = 7;
						}
						else { // second state in transition
							step = 8; desTag = -9;
						}
						break;
					case 7: // Found the <char> tag
						step = 6; desTag = 0;
						break;
					case -7: // Found the </char> tag
						step = -2; desTag = 8;
						break;
					case -9: // Found the </trans> tag
						cout << "Add to transition set: " << symbol << " shifts " << name1 << " to " << name2 << endl;
						step = 1; desTag = 9;
						break;
				}
				token = strtok(NULL, " >");
			} // end of tokens in cline
		}
	} // end of file reached

	return false;
}

bool sStateParse( ) {
	int desTag = 0; // wants state name
	int step = 1; // 1 = name, 2 = </startstate>
	char* name;
	int count = 0;
	//cout << "parse the starting states" << endl;

	// Expects single itteration of <state> [name] </state> format before </startstate> encountered
	
	// If there are still tokens left to be extracted from cline, process cline.
	token = strtok(NULL, " >");
	while( token ) {
		if( desTag != tagCheck(token) ) {
			cout << "ERROR: Designating Starting State. Was expecting ";
			switch(step) {
				case 1: cout << "a state name." << endl; break;
				case 2: cout << "</startstate> tag." << endl; break;
			}
			return false;
		}

		switch( desTag ) {
			case 0:
				// name for state
				// if token is > 12 characters, it might have </startstate at the end of the name
				if( strlen(token) > 12 && strcmp("</startstate", token + strlen(token) - 12) == 0 ) {
					name = (char*)malloc(strlen(token) - (sizeof(char) * 12));
					while( count < (strlen(token) - 12) ) {
						name[count] = token[count];
						count ++;
					}
					name[count] = NULL;
					cout << "Designate starting state: " << name << endl;
					count = 0;
					return true;
				}
				else {
					step = 2; desTag = -5;
					cout << "Designate starting state: " << token << endl;
				}
				break;
			case -5: // Found </startstate> tag
				return true;
				break;
		}
		
		token = strtok(NULL, " >");
	} // end of tokens from old cline

	// If there are no more tokens to grab from old cline or cline was processed
	// and </startstate> tag hasn't been found, process additional lines
	while( getline(infile, line) ) {
		cout << "LINE: " << line << endl;
		cline = (char*)malloc(sizeof(char) * line.size());
		strcpy( cline, line.c_str() );
		// If line is not empty, check for desired tag.
		if( strcmp(cline, "") != 0 ) {
			token = strtok(cline, " >");
			while( token ) {
				if( desTag != tagCheck(token) ) {
				cout << "ERROR: Designating Starting State. Was expecting ";
				switch(step) {
					case 1: cout << "a state name." << endl; break;
					case 2: cout << "</startstate> tag." << endl; break;
				}
				return false;
			}

			switch( desTag ) {
				case 0:
					// name for state
					// if token is > 12 characters, it might have </startstate at the end of the name
					if( strlen(token) > 12 && strcmp("</startstate", token + strlen(token) - 12) == 0 ) {
						name = (char*)malloc(strlen(token) - (sizeof(char) * 12));
						while( count < (strlen(token) - 12) ) {
							name[count] = token[count];
							count ++;
						}
						name[count] = NULL;
						cout << "Designate starting state: " << name << endl;
						count = 0;
						return true;
					}
					else {
						step = 2; desTag = -4;
						cout << "Designate starting state: " << token << endl;
					}
					break;
				case -4: // Found </startstate> tag
					return true;
					break;
			}
			
			token = strtok(NULL, " >");
			} // end of tokens from cline
		}
	} // end of file reached

	return false;
}

bool accStateParse( ) {
	int desTag = 8; // desired tag is <state>
	int step = 1; // 1 = <state>, 2 = name, 3 = </state>
	char* name = "";
	int count = 0;

	//cout << "parse the accepting states" << endl;

	// Expects <state> [name] </state> format until </acceptstates> is encountered

	// If there are still tokens left to be extracted from cline, process cline
	token = strtok(NULL, " >");
	while( token ) {
		if( -6 == tagCheck(token) ) { // </acceptstates> tag
			if( desTag == 8 ) // not in middle of designating accepting state
				return true;
		}

		if( desTag != tagCheck(token) ) {
			cout << "ERROR: Designating accepting states. Was expecting ";
			switch(step) {
				case 1: cout << "<state> tag." << endl; break;
				case 2: cout << "a state name." << endl; break;
				case 3: cout << "</state> tag." << endl; break;
			}
			return false;
		}

		switch(desTag) {
			case 8: // Found <state> tag.
				step = 2; desTag = 0;
				break;
			case 0:
				// name for state
				// if token is > 7 characters, it might have </state at end of name
				if( strlen(token) > 7 && strcmp("</state", token + strlen(token) - 7) == 0 ) {
					step = 1; desTag = 8;
					name = (char*)malloc(sizeof(char) * (strlen(token) - 7));
					while( count < (strlen(token) - 7) ) {
						name[count] = token[count];
						count++;
					}
					name[count] = '\0';
					cout << "Designate an accepting state: " << name << endl;
					count = 0;
				}
				else {
					step = 3; desTag = -8;
					cout << "Designate an accepting state: " << token << endl;
				}
				break;
			case -8: // Found </state> tag.
				step = 1; desTag = 8;
				break;
		}
		token = strtok(NULL, " >");
	} // end of tokens from old cline

	// If there are no more tokens to grab from old cline or cline was processed
	// and </acceptstates> tag hasn't been encountered, process additional lines.
	while( getline(infile, line) ) {
		cline = (char*)malloc(sizeof(char) * line.size());
		strcpy( cline, line.c_str() );
		// If line is not empty, check for desired tag.
		if( strcmp(cline, "") != 0 ) {
			token = strtok(cline, " >");
			while( token ) {
				if( -6 == tagCheck(token) ) { // </acceptstates> tag
					if( desTag == 8 ) // not in middle of designating accepting state
						return true;
				}
				if( desTag != tagCheck(token) ) {
					cout << "ERROR: Designating accepting states. Was expecting ";
					switch(step) {
						case 1: cout << "<state> tag." << endl; break;
						case 2: cout << "a state name." << endl; break;
						case 3: cout << "</state> tag." << endl; break;
					}
					return false;
				}

				switch(desTag) {
					case 8: // Found <state> tag.
						step = 2; desTag = 0;
						break;
					case 0:
						// name for state
						// if token is > 7 characters, it might have </state at end of name
						if( strlen(token) > 7 && strcmp("</state", token + strlen(token) - 7) == 0 ) {
							step = 1; desTag = 8;
							name = (char*)malloc(sizeof(char) * (strlen(token) - 7));
							while( count < (strlen(token) - 7) ) {
								name[count] = token[count];
								count++;
							}
							name[count] = '\0';
							cout << "Designate an accepting state: " << name << endl;
							count = 0;
						}
						else {
							step = 3; desTag = -8;
							cout << "Designate an accepting state: " << token << endl;
						}
						break;
					case -8: // Found </state> tag.
						step = 1; desTag = 8;
						break;
				}
				token = strtok(NULL, " >");
			} // end of tokens from cline
		}
	} // end of file reached

	return false;
}