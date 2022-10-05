#include <iostream>
#include "Calculator.h"
#include "VariableContainer.h"
#include <regex>

int main()
{
    bool exit = false;
    bool showError = false;

    Calculator calc;
    VariableContainer var;
    
    std::cout << "--------------------------------------------------------\n";
    std::cout << "---------               Calculator             ---------\n";
    std::cout << "---------  Infix, RPN expressions evaluation   ---------\n";
    std::cout << "---------     and infix -> RPN conversion      ---------\n";
    std::cout << "---------    Copyright Krzysztof Witkowski     ---------\n";
    std::cout << "--------------------------------------------------------\n\n";
    std::cout << "Type infix expression and press enter. Type help to display commands \nType 'exit' and press enter to quit \n\n";

    std::string in;

    while (!exit) {
        std::cout << ">";
        std::cin >> in;

        if (std::regex_match(in, std::regex("exit"))) { 
            exit = true; 
            continue;
        }
        if (std::regex_match(in, std::regex("showerror"))) { 
            showError = !showError; 
            continue;
        }
        if (std::regex_match(in, std::regex("setvar"))) {
            std::string name;
            float value;

            std::cout << "Write variable name: ";
            std::cin >> name;
            std::cout << "Write variable value: ";
            std::cin >> value;

            var.writeVariable(name, value);

            continue;
        }
        if (std::regex_match(in, std::regex("getvar"))) {
            std::string name;

            std::cout << "Write variable name: ";
            std::cin >> name;

            std::cout << var.getVariable(name) << "\n";

            continue;
        }
        if (std::regex_match(in, std::regex("getallvars"))) {
            std::map<std::string, float> mapa = var.getVariableList();
            std::map<std::string, float>::iterator it;

            for (it = mapa.begin(); it != mapa.end(); it++) {
                std::cout << it->first << " = " << it->second << "\n";
            }

            continue;
        }
        if (std::regex_match(in, std::regex("help"))) {
            std::cout << "HELP - list of commands: \n";
            std::cout << "exit - close program \n";
            std::cout << "showerror - toggle error state display after evaluation \n";
            std::cout << "setvar - create new variable \n";
            std::cout << "getvar - peek variable value \n";
            std::cout << "getallvars - peek all variables value \n";
            std::cout << "\n";
            std::cout << "To start using calculator simple type expression, like 2+2*2 \n";
            std::cout << "If you have variables you can use them in expressions, like: test+test*2 \n";
            continue;
        }

        std::cout << calc.calculate(var.insertVariables(in));
        if (showError) {
            std::string errorName;

            switch (calc.getErrorType()) {
                case OK: errorName = "OK"; break;
                case DivisionByZero: errorName = "Division by 0"; break;
                case RPNconversionFailed: errorName = "Conversion from infix to postfix failed"; break;
                case EvaluationFailed: errorName = "Evaluation failed"; break;
            }

            std::cout << "   Errorstate: " << errorName;
        }
        
        std::cout << "\n";
    }
}
