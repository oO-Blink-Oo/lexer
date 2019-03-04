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

int stateFSM[13][24] = {
 /*state 0*/  {1, 3, 2 ,5, 6, 0, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
/*state 1*/   {1, 12, 12, 2, 2, 2, 9, 2, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
/*Fstate 2*/  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
/*state 3*/   {10, 3, 10, 4, 10, 4, 10, 4, 10, 10, 10, 10, 10, 10, 10, 4, 4, 4, 4, 4, 4, 4, 4, 4},
/*Fstate 4*/  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
/*state 5*/   {10, 3, 10, 10, 10, 8, 10, 10, 10, 10, 10, 10, 10, 10 ,10 ,10 ,10, 10, 10 ,10 ,10 ,10, 10, 10},
/*state 6*/   {6, 6, 6, 6, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
/*Fstate 7*/  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
/*Fstate 8*/  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
/*Fstate 9*/  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
/*Fstate 10*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
/*state 11*/  {11, 11, 10, 10, 10, 12, 10, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
/*Fstate 12*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };

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
	tokenType acc; //the token struct we are working with
	vector<tokenType> tokens; // will be returned
	char currentChar = ' ';
	int col = 0;			  // column number
	int currentState = 0;	  //initial state
	//int prevState = 0;
	string currentToken = "";
	string keywords[] = { "int","float","bool","if","else","then","do","while","whileend","do","doend","for","and","or","function" };

	//READS WORDS CHARACTER BY CHARACTER
	for (size_t i = 0; i < words.length(); i++) {
		
		currentChar = words[i];

		col = getFsmCol(currentChar);

		currentState = stateFSM[currentState][col];
		
		if (currentState == 2 || currentState == 4 || currentState == 7 || currentState == 8) {
			if ((prevState != 5 || prevState != 4) && currentToken != "" /*space*/) { // when you have successfully parsed a token
				acc.token = currentToken;
				acc.lexeme = prevState;
				acc.lexemeName = getLexemeName(acc.lexeme);
				tokens.push_back(acc);
			}
			
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