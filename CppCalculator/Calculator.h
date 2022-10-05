#include <math.h>
#include <string>
#include <regex>
#include <queue>
#include <stack>
#include <map>
#include <sstream>

/*--------------------------------------------------------
* ---------               Calculator             ---------
* ---------  Infix, RPN expressions evaluation   ---------
* ---------     and infix -> RPN conversion      ---------
* ---------    Copyright Krzysztof Witkowski     ---------
--------------------------------------------------------*/

#ifndef CALCULATOR
#define CALCULATOR

enum ErrorType {
	OK = 0,
	DivisionByZero,
	RPNconversionFailed,
	EvaluationFailed
};

class Calculator{
public:
	float calculate(std::string input);
	std::queue<std::string> convertToONP(std::string input);
	float calculateONP(std::queue<std::string> wejscie);
	bool isError();
	ErrorType getErrorType();
private:
	std::queue<std::string> inputQueue;
	bool isNumber(std::string input);
	bool isOperator(std::string input);
	int priorytet(std::string c);
	bool errorFlag = false;
	ErrorType errorType = OK;
};

#endif // !Calculator
