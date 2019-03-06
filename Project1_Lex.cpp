#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <stdio.h>

using namespace std;


struct tokenType {
	string token; // token name for the lexeme
	int lexeme;
	string lexemeName; // this prints out the actual lexeme character

};

//FSM table
int stateFSM[13][24] = { 
 /*state 0*/  {1, 3, 2 ,5, 6, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8},
/*state 1*/   {1, 11, 12, 2, 2, 2, 9, 2, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
/*Fstate 2*/  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
/*state 3*/   {10, 3, 10, 4, 10, 4, 10, 4, 10, 10, 10, 10, 10, 10, 10, 4, 4, 4, 4, 4, 4, 4, 4, 4},
/*Fstate 4*/  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
/*state 5*/   {10, 3, 10, 10, 10, 8, 10, 10, 10, 10, 10, 10, 10, 10 ,10 ,10 ,10, 10, 10 ,10 ,10 ,10, 10, 10},
/*state 6*/   {6, 6, 6, 6, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
/*Fstate 7*/  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
/*Fstate 8*/  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
/*Fstate 9*/  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
/*Fstate 10*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
/*state 11*/  {11, 11, 12, 10, 10, 12, 10, 8, 12, 10, 10, 10, 10, 12, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
/*Fstate 12*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };

//FUNCTION PROTOTYPES
vector<tokenType> lexer(string words);
int getFsmCol(char currentChar);
string getLexemeName(int lexeme);

int main() {

	string input;
	cout << "Please input the name of the file you wish to analyze (please have .txt at the end of name)" << endl;
	cin >> input;
	ifstream inFile(input);

	if (!inFile.is_open()) {
		cout << "The file was not opened properly!\n";
		exit(1);
	}

	string stringExp = "";
	vector<tokenType> tokens;

	cout << setw(15) << left << "TOKENS:" <<  setw(18) << right << "LEXEMES:" << endl;
	cout << endl;

	while (getline(inFile, stringExp)) { //getline(inFile,stringExp) 
		tokens = lexer(stringExp);

		//print out tokens vector
		for (size_t i = 0; i < tokens.size(); ++i) {
			if (tokens[i].lexemeName != "COMMENT") {
				cout << setw(15) << left << tokens[i].lexemeName << " =" << setw(15) << right << tokens[i].token << endl;
			}

		}
	}

	inFile.close();
	system("pause");
	return 0;
}


vector<tokenType> lexer(string words) {
	tokenType acc; //the token struct we are working with
	vector<tokenType> tokens; // vector filled with tokens to output in the main function
	char currentChar = ' ';
	int col = 0;			  // column number
	int currentState = 0;	  //initial state
	string currentToken = "";
	vector<string> keywords = { "int","float","bool","if","else","then","do","while","whileend","do","doend","for","and","or","function" }; //vector of keywords in order to differentiate between identifier and keyword
	bool isKey = false; //boolean key to determine if the current token is a keyword or identifier

	//READS WORDS CHARACTER BY CHARACTER
	for (size_t i = 0; i < words.length(); i++) {
		

		currentChar = words[i];


		col = getFsmCol(currentChar);

		currentState = stateFSM[currentState][col];

		//finishing states at 2,4,7-10,12
		switch (currentState) {
		case 0: //if the state is a space, break out of the switch
			break;
		case 1:
			currentToken += currentChar; //adds a validated character into the token for it to be pushed into the tokens vector later
			break;
		case 2: //keyword state, branches out to identifier if isKey is false
			for (int i = 0; i < keywords.size(); i++) {
				if (currentToken == keywords[i]) {
					acc.token = currentToken;
					acc.lexeme = 0;
					acc.lexemeName = getLexemeName(acc.lexeme);
					tokens.push_back(acc);
					isKey = true;
				}
			}
			if (isKey != true) {
				acc.token = currentToken;
				acc.lexeme = 6;
				acc.lexemeName = getLexemeName(acc.lexeme);
				tokens.push_back(acc);
			}
			break;
		case 3:
			currentToken += currentChar;
			break;
		case 4:
			acc.token = currentToken;
			acc.lexeme = 1;
			acc.lexemeName = getLexemeName(acc.lexeme);
			tokens.push_back(acc);
			break;
		case 5:
			currentToken += currentChar;
			break;
		case 6:
			currentToken += currentChar;
			break;
		case 7:
			currentToken += currentChar;
			acc.token = currentToken;
			acc.lexeme = 2;
			acc.lexemeName = getLexemeName(acc.lexeme);
			tokens.push_back(acc);
			break;
		case 8:
			currentToken += currentChar;
			acc.token = currentToken;
			acc.lexeme = 4; 
			acc.lexemeName = getLexemeName(acc.lexeme);
			tokens.push_back(acc);
			break;
		case 9:
			currentToken += currentChar;
			acc.token = currentToken;
			acc.lexeme = 3;
			acc.lexemeName = getLexemeName(acc.lexeme);
			tokens.push_back(acc);
			break;
		case 10:
			acc.token = currentToken;
			acc.lexeme = 5;
			acc.lexemeName = getLexemeName(acc.lexeme);
			tokens.push_back(acc);
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
			break;
		default:
			break;
		}

		//will clear token and adds current character to the token if these separators are found
		//we decided to separate the clearing and adding from the switch statements because it would cause the FSM to confuse certain cases.
		if ((currentChar == '(' && currentState == 2) || (currentChar == ',' && currentState == 12) || (currentChar == ')' && currentState == 12)) {
			currentToken = "";
			currentToken += currentChar;
		}


		if ((currentState == 2 && currentToken == "(") || (currentState == 12 && currentToken == ",") || (currentState == 12 && currentToken == ")")) {
			acc.token = currentToken;
			acc.lexeme = 3;
			acc.lexemeName = getLexemeName(acc.lexeme);
			tokens.push_back(acc);
		}


		//resets the token and state if an end state is found
		if (currentState == 2 || currentState == 4 || currentState == 7 || currentState == 8 || currentState == 9 || currentState == 10 || currentState == 12) {
			currentToken = "";
			currentState = 0;
		}
		
	}
	//shortcoming: the program wasn't able to detect a space after "else" so it would break out of the loop.  This if statement
	//handles that specific problem.
	if (currentState == 1 && currentToken != "") {
		acc.token = currentToken;
		acc.lexeme = 0;
		acc.lexemeName = getLexemeName(acc.lexeme);
		tokens.push_back(acc);
	}
	//create a case if currentToken is populated so that it does not get deleted later

	return tokens;
}

//gets the column depending on the current character
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
	case '\n':
		return 0;
		break;
	case '\t':
		return 5;
		break;
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


//get lexeme name depending on the current state
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