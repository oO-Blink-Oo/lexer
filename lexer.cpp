/*
1. Read .txt
2. Put it in a char vector
3. Go through the vector and classify each string
4. Scan vector to find comment block and ignore it
5. Print it out


read it character by character to check if the last character is a separator
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

void printKeywords(std::vector<std::string> &vec);
void printIdentifiers(std::vector<std::string> &vec);
void printSeparators(std::vector<char> &vec);
void printOperators(std::vector<char> &vec);
void printReal();

int main() {
	std::ifstream inFile;
	std::vector<char> myTxt;
	char readChar;
	inFile.open("sample.txt"); // opens txt file

	std::vector<std::string> keyBuf;
	std::vector<std::string> identBuf;
	std::vector<char> sepBuf;
	std::vector<char> operBuf;


	// Reading char by char  from the .txt file
	if (!inFile.is_open()) { //check if file was opened properly

		std::cout << "The file was not opened properly. \n";
		exit(0);
	}
	
	//READS IN CHARACTER BY CHARACTER
	while (!inFile.eof()) { // while there is something to read keep looping

		inFile >> std::noskipws >> readChar; //gets a character and stores it at readChar
		myTxt.push_back(readChar); // populates the vector with characters

	}//after this while-loop the string vector will be populated


	std::string stringBuff; // used to populate a string
	std::vector<std::string> words; // used to populate words that needs to be classified as identifier or keyword
	
	//do space check here...
	for (size_t i = 0; i < myTxt.size();++i) {
		
		// checks for letters and load to words buffer
		if (isalpha(myTxt[i]) || myTxt[i] == '$') {

			stringBuff.push_back(myTxt[i]);

		} else if (isalpha(myTxt[i-1]) && isdigit(myTxt[i])) // if the previous character is a letter and the current one is a digit push it to stringBuff still
		{
			stringBuff.push_back(myTxt[i]);
		} else if (isalpha(myTxt[i - 1]) && isSeparator(myTxt[i])) {
			sepBuf.push_back(myTxt[i]);

		}
		
		// Problem when we see a separator it clears the stringBuff and pushes a BLANK string into words
		if (myTxt[i] == ' ' || myTxt[i] == '\n'  || isSeparator(myTxt[i])) { //skip if we see a whitespace or a newline
			words.push_back(stringBuff);
			stringBuff.clear();
		}

		// checks for separator and operator
		if (isSeparator(myTxt[i])) {
			sepBuf.push_back(myTxt[i]);
		}
		if (isOperator(myTxt[i])) {
			operBuf.push_back(myTxt[i]);
		}
	}

	// remove whitespaces and newlines in words vector
	auto it = words.begin();
	while (it != words.end())
	{
		// remove odd numbers
		if (*it == "") {
			// erase() invalidates the iterator, use returned iterator
			it = words.erase(it);
		}
		// Notice that iterator is incremented only on the else part (why?)
		else {
			++it;
		}
	}

	// remove whitespaces and newlines in separator vector
	auto ite = sepBuf.begin();
	while (ite != sepBuf.end())
	{
		// remove odd numbers
		if (*ite == ' ') {
			// erase() invalidates the iterator, use returned iterator
			ite = sepBuf.erase(ite);
		}
		// Notice that iterator is incremented only on the else part (why?)
		else {
			++ite;
		}
	}

	// Checks if the words in words buffer is a keyword or an identifier then push it to keyBuf or identBuf

	for (size_t i = 0; i < words.size(); i++) {
		if (isKeyword(words[i])) {

			keyBuf.push_back(words[i]);

		}
		else {

			identBuf.push_back(words[i]);
		}
	}
	


	///////////// labeling category & printing 
	std::cout << std::setw(15) << std::left << "  Token" << std::setw(18) << std::right << "Lexeme" << std::endl;
	printSeparators(sepBuf); //print all of the separators in its buffer
	printOperators(operBuf);
	printKeywords(keyBuf);
	printIdentifiers(identBuf);
	
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

	if (c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}' || c == ';' || c == ':' || c == '!' || c == ' ' || c == '\'' || c == ',') {
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

void printKeywords(std::vector<std::string> &vec) {

	for (size_t i = 0; i < vec.size(); i++) { 
		if (vec[i] == " " || vec[i] == "\n") {
			++i;
		}
		std::cout << std::setw(15) << std::left << "KEYWORD" << std::setw(15) << std::left << "  =" << std::setw(15) << std::left << vec[i] << std::endl;
	}

}
void printIdentifiers(std::vector<std::string> &vec) { // remove space check

	for (size_t i = 0; i < vec.size(); i++) {
		
		std::cout << std::setw(15) << std::left << "IDENTIFIER" << std::setw(15) << std::left << "  =" << std::setw(15) << std::left << vec[i] << std::endl;
	}

}

void printSeparators(std::vector<char> &vec)
{
	for (size_t i = 0; i < vec.size(); i++) {
		if (vec[i] == ' ' || vec[i] == '\n') {
			++i;
		}
		std::cout << std::setw(15) << std::left << "SEPARATOR" << std::setw(15) << std::left << "  =" << std::setw(15) << std::left << vec[i] << std::endl;
	}
	
}

void printOperators(std::vector<char> &vec)
{
	for (size_t i = 0; i < vec.size(); i++) {
		if (vec[i] == ' ' || vec[i] == '\n') {
			++i;
		}
		std::cout << std::setw(15) << std::left << "OPERATOR" << std::setw(15) << std::left << "  =" << std::setw(15) << std::left << vec[i] << std::endl;
	}
}
