#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <stdio.h>

using namespace std;

enum transitions { INITIAL = 0, LETTER, DIGIT, DOT, EXPOINT, PUNCT, SPACE };

struct tokenType {
	string token; // token name for the lexeme
	int lexeme;
	string lexemeName; // this prints out the actual lexeme character

};
/*l   d  .  !  p  sp*/
int stateFSM[][9] = { /*state 0*/   {1, 3, 5 ,6, 8, 0},
/*state 1*/   {1, 1, 2, 2, 2, 2},
/*Fstate 2*/  {0, 0, 0, 0, 0, 0},   /*Identifier*/
/*state 3*/   {4, 3, 4, 4, 4, 4},
/*Fstate 4*/  {0, 0, 0, 0, 0, 0},   /*End Number*/
/*state 5*/   {8, 3, 8, 8, 8, 8},
/*state 6*/   {6, 6, 6, 7, 6, 6},
/*Fstate 7*/  {0, 0, 0, 0, 0, 0},   /*Comment*/
/*Fstate 8*/  {0, 0, 0, 0, 0, 0} }; /*Punctuation*/

//FUNCTION PROTOTYPES
vector<tokenType> lexer(string words);
int getFsmCol(char currentChar);
string getLexemeName(int lexeme);

int main() {

	ifstream inFile("sample.txt");

	if (!inFile.is_open()) {
		cout << "The file was not opened properly!\n";
		exit(1);
	}

	string stringExp = "";
	vector<tokenType> tokens;

	while (getline(inFile, stringExp)) { //getline(inFile,stringExp) 
		tokens = lexer(stringExp);

		//print out tokens vector
		for (size_t i = 0; i < tokens.size(); ++i) {

			cout << tokens[i].token << "=" << tokens[i].lexemeName << endl;

		}
	}

	inFile.close();

	return 0;
}

vector<tokenType> lexer(string words) {
	tokenType acc;
	vector<tokenType> tokens; // will be returned
	char currentChar = ' ';
	int col = 0;			  // column number
	int currentState = 0;
	int prevState = 0;
	string currentToken = "";
	string keywords[] = { "int","float","bool","if","else","then","do","while","whileend","do","doend","for","and","or","function" };

	//READS WORDS CHARACTER BY CHARACTER
	for (size_t i = 0; i < words.length(); i++) {
		//cout << "Current state --> " << currentState << endl;

		currentChar = words[i];

		col = getFsmCol(currentChar);

		currentState = stateFSM[currentState][col];
		/*if ((currentState == 6 && prevState == 0) || (currentState == 6 && prevState == 6)) {
			prevState == 6;
			i++;
			if (prevState == 6 && currentState == 7) {
				currentState == 0;
			}
		}*/

		if (currentState == 2 || currentState == 4 || currentState == 7 || currentState == 8) {
			if ((prevState != 5 || prevState != 4) && currentToken != "" /*space*/) { // when you have successfully parsed a token
				acc.token = currentToken;
				acc.lexeme = prevState;
				acc.lexemeName = getLexemeName(acc.lexeme);
				tokens.push_back(acc);
			}
			/*if ((currentState == 6 && prevState == 0) || (currentState == 6 && prevState == 6)) {
				prevState == 6;
				i++;
				if (prevState == 6 && currentState == 7) {
					currentState == 0;
				}
			}*/
			currentToken = "";
		}
		else if ((currentState == 6 && prevState == 0) || (currentState == 6 && prevState == 6) || (prevState == 6 && currentState == 7)) {

			prevState = 6;
			i++;

			if (prevState == 6 && currentState == 7) {
				currentState = 0;
			}
		}
		else {
			if (currentChar != ' ') {
				currentToken += currentChar;
			}
			//i++;//something might need to happen here
		}
		prevState = currentState;
	}
	//if space or separator
	if (currentState != 5 && currentToken != "") {
		acc.token = currentToken;
		acc.lexeme = currentState;
		acc.lexemeName = getLexemeName(acc.lexeme);
		tokens.push_back(acc);
	}
	return tokens;
}

int getFsmCol(char currentChar) {

	if (isspace(currentChar)) {
		return 5;
	}
	else if (isalpha(currentChar)) {
		return 0;
	}
	else if (isdigit(currentChar)) {
		return 1;
	}
	else if (ispunct(currentChar)) {

		if (currentChar == '!') {
			return 3;
		}
		if (currentChar == '.') {
			return 2;
		}
		else {

			return 4;
		}
	}
}

string getLexemeName(int lexeme) {
	switch (lexeme) {
	case 1:
		return "IDENTIFIER";
		break;
	case 2: // identifier or keyword?
		return "KEYWORD";
		break;
	case 4: // Number
		return "NUMBER";
		break;
		/*case 6:
			return " ";
			break;*/
	case 7: // Comment
		return "COMMENT";
		break;
	case 8: // Punctuation
		return "PUNCTUATION";
		break;

	default:
		return "ERROR";
		break;
	}
}