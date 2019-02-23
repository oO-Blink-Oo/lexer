/*
1. Read .txt
2. Put it in a char vector
3. Go through the vector and classify each string
4. Scan vector to find comment block and ignore it
5. Print it out

read it string by string
go through each string and read it character by character to check if the last character is a separator
if it is a '$' we shall consider this as an acceptable identifier

Accepted final states:
	Keywords = int, float, bool, if, else, then, do, while, whileend, do, doend, for, and, or, function
	Identifiers = legal identifiers must start with alphabetic character follow by digits, alpha, or $
	Separators = '(){}[],.:;! sp(space)
	Operators = *+-=/><%
	Real = integers whole numbers (1,2,3,...) and reals floats (5.0, 0.9, 1.75, ...)
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <stdio.h>

//using namespace std;
bool isKeyword(std::string c); //done
bool isIdentifier(char c);
bool isSeparator(char c); //done
bool isOperator(char c); //done
bool isRealNum(std::string c);

void printKeywords(std::vector<char> &vec);
void printIdentifiers();
void printSeparators(std::vector<char> &vec);
void printOperators(std::vector<char> &vec);
void printReal();

int main() {
	std::ifstream inFile;
	std::vector<char> myTxt;
	char readChar;
	inFile.open("sample.txt"); // opens txt file

	std::vector<std::string> keyBuf;
	std::vector<char> identBuf;
	std::vector<char> sepBuf;
	std::vector<char> operBuf;


	// Reading char by char  from the .txt file
	if (!inFile.is_open()) { //check if file was opened properly

		std::cout << "The file was not opened properly. \n";
		exit(0);
	}
	
	//READS IN CHARACTER BY CHARACTER
	while (!inFile.eof()) { // while there is something to read keep looping

		inFile >> readChar; //gets a character and stores it at readChar
		myTxt.push_back(readChar); // populates the vector with tokens

	}//after this while-loop the string vector will be populated



	std::string stringBuff; // used to populate a string
	std::vector<std::string> tempStringBuf; // used to populate strings that were tempBuf
	int state = 0;
	
	for (size_t i = 0; i < myTxt.size(); i++) {
		
		if (isalpha(myTxt[i]) || myTxt[i] == '$') {
			stringBuff.push_back(myTxt[i]);
			
		}

		
		/*if (isSeparator(myTxt[i])) {
			sepBuf.push_back(myTxt[i]);
		}
		if (isOperator(myTxt[i])) {
			operBuf.push_back(myTxt[i]);
		}*/

	
		

	}
	std::cout << "TRIAL: " << stringBuff << std::endl;
	
	



	///////////// labeling category & printing 
	std::cout << std::setw(15) << std::left << "  Token" << std::setw(18) << std::right << "Lexeme" << std::endl;
	printSeparators(sepBuf); //print all of the separators in its buffer
	printOperators(operBuf);
	//printKeywords(keyBuf);
	
	// PRINTS EACH STRING/CHARACTER
	/*for (size_t i = 0; i < myTxt.size(); i++)
	{
		std::cout << myTxt[i] << std::endl;
	}*/

	

	system("pause");
	return 0;
}

bool isKeyword(std::string c)
{
	std::vector<std::string> strComp{ "int" , "float" , "bool" , "if" ,"else" , "then" , "do" , "while" , "whileend" , "doend" , "for" , "and" , "or" };
	
	for (size_t i = 0; i < strComp.size(); i++) {
		if (strComp[i] == c) {
			return true;
		}
	}
	return false;
}

bool isSeparator(char c) {

	if (c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}' || c == ';' || c == ':' || c == '!' || c == ' ' || c == '\'') {
		return true;
	}
	return false;
}

bool isOperator(char c)
{
	if (c == '*' || c == '+' || c == '-' || c == '/' || c == '<' || c == '>' || c == '%' || c == '=') {
		return true;
	}
	return false;
}

bool isRealNum(std::string c)
{
	if (true) {
		return true;
	}
	return false;
}

void printKeywords(std::vector<char> &vec) {

	for (size_t i = 0; i < vec.size(); i++) {
		std::cout << std::setw(15) << std::left << "KEYWORD" << std::setw(15) << std::left << "  =" << std::setw(15) << std::left << vec[i] << std::endl;
	}

}

void printSeparators(std::vector<char> &vec)
{
	for (size_t i = 0; i < vec.size(); i++) {
		std::cout << std::setw(15) << std::left << "SEPARATOR" << std::setw(15) << std::left << "  =" << std::setw(15) << std::left << vec[i] << std::endl;
	}
	
}

void printOperators(std::vector<char> &vec)
{
	for (size_t i = 0; i < vec.size(); i++) {
		std::cout << std::setw(15) << std::left << "OPERATOR" << std::setw(15) << std::left << "  =" << std::setw(15) << std::left << vec[i] << std::endl;
	}
}


//GOES THROUGH THE VECTOR THAT HAS CHARACTERS
	//for (size_t i = 0; i < myTxt.size(); i++) {
	//	/*
	//	make a temp string to hold characters
	//	push characters into temp string
	//	check the temp string if keyword or identifier
	//	push the string into keyword buffer or identifier buffer
	//	*/
	//	if (isSeparator(myTxt[i])){
	//		sepBuf.push_back(myTxt[i]);
	//	}
	//	if (isOperator(myTxt[i])) {
	//		operBuf.push_back(myTxt[i]);
	//	}
	//}