// SyntaxCalculator.h Ver 0.1.0
// Created by Martin Sharp 31.08.2023
#ifndef SYNTAXCALCULATOR_H
#define SYNTAXCALCULATOR_H

#include <vector>
#include <map>
#include <string>
#include <cctype>
#include <sstream>
#include <stack>

typedef std::vector<std::string> vectorStr;

class SyntaxCalculator{
    private:

        vectorStr convertToInfixTokens(const std::string& string);

        std::map<char, int> precedence = {
            {'+', 1},
            {'-', 1},
            {'*', 2},
            {'/', 2}
        };

        bool isOperator(char characher);

        vectorStr infixToRPN(const vectorStr& infixTokens);

        void OperationBasedOnTokenAndOperand(std::stack<double>& numbersStack, const std::string& token, double leftOperand, double rightOperand);

        double calculateRPN(const vectorStr& rpnTokens);



    public:
        double calculator(const std::string& string);
};


#endif //SYNTAXCALCULATOR_H