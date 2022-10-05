#include "Calculator.h"

float Calculator::calculate(std::string input) {
	errorFlag = false;
	errorType = OK;
	return calculateONP(convertToONP(input));
}

int Calculator::priorytet(std::string c) {
	if (c == "+") return 1;
	if (c == "-") return 1;
	if (c == "*") return 2;
	if (c == "/") return 2;
	if (c == "^") return 3;
	if (c == "sin") return 4;
	if (c == "cos") return 4;
	if (c == "tan") return 4;
	if (c == "sqrt") return 4;
	if (c == "log") return 4;
	if (c == "abs") return 4;
	if (c == "acos") return 4;
	if (c == "asin") return 4;
	if (c == "atan") return 4;
	if (c == "cosh") return 4;
	if (c == "exp") return 4;
	if (c == "round") return 4;
	if (c == "sinh") return 4;
	if (c == "tanh") return 4;
	return 0;
}

bool Calculator::isNumber(std::string input) {
	return std::regex_match(input, std::regex("[0-9.]+"));
}

bool Calculator::isOperator(std::string input) {
	return std::regex_match(input, std::regex("([*+\/^)(=])|(-)|(sin|cos|tan|sqrt|log|abs|acos|asin|atan|cosh|exp|round|sinh|tanh)"));
}

std::queue<std::string> Calculator::convertToONP(std::string input) {
	std::queue<std::string> wejscie;
	std::stack<std::string> stos;
	std::queue<std::string> answer;

	std::regex opsregex("(([*+\/^)(=])|(-)|(sin|cos|tan|sqrt|log|abs|acos|asin|atan|cosh|exp|round|sinh|tanh)|([0-9.]+)|[a-z])");

	try {
		for (std::sregex_iterator i = std::sregex_iterator(input.begin(), input.end(), opsregex);
			i != std::sregex_iterator();
			++i)
		{
			std::smatch m = *i;
			wejscie.push(m.str());
		}

		while (wejscie.size() > 0) {
			std::string deq = wejscie.front();
			wejscie.pop();

			if (deq == "(") stos.push(deq);

			if (deq == ")") {
				while (stos.size() > 0) {
					if (stos.top() != "(") {
						answer.push(stos.top());
						stos.pop();
					}
					else {
						stos.pop();
					}
				}
			}

			if (isNumber(deq)) answer.push(deq);

			if (isOperator(deq)) {
				if (stos.size() == 0)
				{
					stos.push(deq);
				}
				else
				{
					if ((priorytet(stos.top()) > priorytet(deq)) && std::regex_match(deq, std::regex("([*+\/^)(=])|(-)|(sin|cos|tan|sqrt|log|abs|acos|asin|atan|cosh|exp|round|sinh|tanh)"))) {
						answer.push(stos.top());
						stos.pop();
						stos.push(deq);
					}
					else
					{
						stos.push(deq);
					}
				}
			}
		}

		while (stos.size() > 0)
		{
			if (stos.top() != "(" && stos.top() != ")") answer.push(stos.top());
			stos.pop();
		}
	}
	catch (std::exception& e) {
		errorFlag = true;
		errorType = RPNconversionFailed;
	}
	
	return answer;
}

float Calculator::calculateONP(std::queue<std::string> wejscie) {
	std::stack<std::string> inProgress;
	std::string temp;

	while (wejscie.size() > 0) {
		temp = wejscie.front();
		wejscie.pop();

		float a, b;			//operandy najbli¿szego dzia³ania
		std::ostringstream ss;    //do konwersji float na string

		if (isNumber(temp)) {				//je¿eli liczba - na stos
			inProgress.push(temp);
			continue;
		}

		if (std::regex_match(temp, std::regex("([*+\/^])|(-)"))) {				//operatory dwuargumentowe
			std::string str;

			if (inProgress.size() < 1) {				//pobranie operandów, o ile s¹ - inaczej b³¹d ewaluacji
				errorFlag = true;
				errorType = EvaluationFailed;
				return 0;
			}
			str = inProgress.top();
			a = stof(str);
			inProgress.pop();

			if (inProgress.size() < 1) {
				errorFlag = true;
				errorType = EvaluationFailed;
				return 0;
			}
			str = inProgress.top();
			b = stof(str);
			inProgress.pop();

			if (temp == "+") {
				ss << (a + b);

				inProgress.push(ss.str());

				ss.clear();
				continue;
			}

			if (temp == "-") {
				ss << (b - a);

				inProgress.push(ss.str());

				ss.clear();
				continue;
			}

			if (temp == "*") {
				ss << (a * b);

				inProgress.push(ss.str());

				ss.clear();
				continue;
			}

			if (temp == "/") {
				if (a == 0) {
					errorFlag = true;
					errorType = DivisionByZero;
					return 0;
				}

				ss << (b / a);

				inProgress.push(ss.str());

				ss.clear();
				continue;
			}

			if (temp == "^") {
				ss << (pow(b, a));

				inProgress.push(ss.str());

				ss.clear();
				continue;
			}
		}

		if (std::regex_match(temp, std::regex("(sin|cos|tan|sqrt|log|abs|acos|asin|atan|cosh|exp|round|sinh|tanh)"))) {
			std::string str;

			if (inProgress.size() < 1) {				//pobranie operanda, o ile jest - inaczej b³¹d ewaluacji
				errorFlag = true;
				errorType = EvaluationFailed;
				return 0;
			}
			str = inProgress.top();
			a = stof(str);
			inProgress.pop();

			//dzia³ania jednooperatorowe
			if (temp == "sin") {
				ss << (sin(a));

				inProgress.push(ss.str());

				ss.clear();
				continue;
			}
			if (temp == "cos")
			{
				ss << (cos(a));

				inProgress.push(ss.str());

				ss.clear();
				continue;
			}
			if (temp == "tan")
			{
				ss << (tan(a));

				inProgress.push(ss.str());

				ss.clear();
				continue;
			}
			if (temp == "sqrt")
			{
				ss << (sqrt(a));

				inProgress.push(ss.str());

				ss.clear();
				continue;
			}
			if (temp == "log")
			{
				ss << (log(a));

				inProgress.push(ss.str());

				ss.clear();
				continue;
			}
			if (temp == "abs")
			{
				ss << (abs(a));

				inProgress.push(ss.str());

				ss.clear();
				continue;
			}
			if (temp == "acos")
			{
				ss << (acos(a));

				inProgress.push(ss.str());

				ss.clear();
				continue;
			}
			if (temp == "asin")
			{
				ss << (asin(a));

				inProgress.push(ss.str());

				ss.clear();
				continue;
			}
			if (temp == "atan")
			{
				ss << (atan(a));

				inProgress.push(ss.str());

				ss.clear();
				continue;
			}
			if (temp == "cosh")
			{
				ss << (cosh(a));

				inProgress.push(ss.str());

				ss.clear();
				continue;
			}
			if (temp == "exp")
			{
				ss << (exp(a));

				inProgress.push(ss.str());

				ss.clear();
				continue;
			}
			if (temp == "round")
			{
				ss << (round(a));

				inProgress.push(ss.str());

				ss.clear();
				continue;
			}
			if (temp == "sinh")
			{
				ss << (sinh(a));

				inProgress.push(ss.str());

				ss.clear();
				continue;
			}
			if (temp == "tanh")
			{
				ss << (tanh(a));

				inProgress.push(ss.str());

				ss.clear();
				continue;
			}
		}			
	}

	if (inProgress.size() > 1) {
		errorFlag = true;
		return 0;
	}

	return std::stod(inProgress.top());
}

bool Calculator::isError() {
	return errorFlag;
}

ErrorType Calculator::getErrorType() {
	return errorType;
}