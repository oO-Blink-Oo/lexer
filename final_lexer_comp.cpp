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

int stateFSM[13][24] = { //Fix table
 /*state 0*/  {1, 3, 2 ,5, 6, 0, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
/*state 1*/   {1, 12, 12, 2, 2, 2, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
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

		switch (currentState) {
		case 0: //TODO, this case is only hit when your initial char is a space when you're in the initial state
			break;
		case 1:
			currentToken += currentChar;
			break;
		case 2: //keyword
			acc.token = currentToken;
			acc.lexeme = 0;
			acc.lexemeName = getLexemeName(acc.lexeme);
			tokens.push_back(acc);
			currentToken = "";
			currentState = 0;
			break;
		case 3:
			currentToken += currentChar;
			break;
		case 4:
			acc.token = currentToken;
			acc.lexeme = 1;
			acc.lexemeName = getLexemeName(acc.lexeme);
			tokens.push_back(acc);
			currentToken = "";
			currentState = 0;
			break;
		case 5:
			currentToken += currentChar;
			break;
		case 6:
			currentToken += currentChar;
			break;
		case 7:
			acc.token = currentToken;
			acc.lexeme = 2;
			acc.lexemeName = getLexemeName(acc.lexeme);
			tokens.push_back(acc);
			currentToken = "";
			currentState = 0;
			break;
		case 8:
			//currentToken += currentChar;
			acc.token = currentToken;
			acc.lexeme = 4; //should be 4
			acc.lexemeName = getLexemeName(acc.lexeme);
			tokens.push_back(acc);
			currentToken = "";
			currentState = 0;
			break;
		case 9:
			currentToken += currentChar;
			acc.token = currentToken;
			acc.lexeme = 3;
			acc.lexemeName = getLexemeName(acc.lexeme);
			tokens.push_back(acc);
			currentToken = "";
			currentState = 0;
			break;
		case 10:
			acc.token = currentToken;
			acc.lexeme = 5;
			acc.lexemeName = getLexemeName(acc.lexeme);
			tokens.push_back(acc);
			currentToken = "";
			currentState = 0;
			break;
		case 11:
			currentToken += currentChar;
			break;
		case 12:
			if (isdigit(currentChar) || currentChar == '$') {
				currentToken += currentChar;
			}
			acc.token = currentToken;
			acc.lexeme = 6;
			acc.lexemeName = getLexemeName(acc.lexeme);
			tokens.push_back(acc);
			currentToken = "";
			currentState = 0;
			break;
		default:
			break;
		}
		
		/*if (currentState == 2 || currentState == 4 || currentState == 7 || currentState == 8 || currentState == 9 || currentState == 10 || currentState == 12) {
			acc.token = currentToken;
			acc.lexeme = prevState;
			acc.lexemeName = getLexemeName(acc.lexeme);
			tokens.push_back(acc);
		}*/

		
	}
	return tokens;
}

int getFsmCol(char currentChar) {

	if (isalpha(currentChar)) {
		return 0;
	}else if (isdigit(currentChar)) {
		return 1;
	}else if (isspace(currentChar)) {
		return 5;
	}

	switch (currentChar)
	{
	case '$':
		return 2;
		break;
	case '.':
		return 3;
		break;
	case '!':
		return 4;
		break;
	case '\'':
		return 6;
		break;
	case '(':
		return 7;
		break;
	case ')':
		return 8;
		break;
	case '{':
		return 9;
		break;
	case '}':
		return 10;
		break;
	case '[':
		return 11;
		break;
	case ']':
		return 12;
		break;
	case ',':
		return 13;
		break;
	case ':':
		return 14;
		break;
	case ';':
		return 15;
		break;
	case '*':
		return 16;
		break;
	case '/':
		return 17;
		break;
	case '+':
		return 18;
		break;
	case '-':
		return 19;
		break;
	case '<':
		return 20;
		break;
	case '>':
		return 21;
		break;
	case '=':
		return 22;
		break;
	case '%':
		return 23;
		break;
	default:
		cout << "default case" << endl;
		break;
	}

}

string getLexemeName(int lexeme) {
	switch (lexeme) {
	case 0:
		return "KEYWORD";
		break;
	case 1: 
		return "NUMBER";
		break;
	case 2:
		return "COMMENT";
		break;
	case 3: 
		return "SEPARATOR";
		break;
	case 4: 
		return "OPERATOR";
		break;
	case 5:
		return "ERROR";
		break;
	case 6:
		return "IDENTIFIER";
		break;

	default:
		return "DEFAULT LEXEME NAME";
		break;
	}
}