//main.cpp Ver 0.1.0
//Created by Martin Sharp at 29.08.2023
#include <iostream>

#include <string>
#include <stack>
#include <unordered_map>
#include <sstream>
#include <cctype>

#include "customUtilitys.h"

typedef std::unordered_map<char, int> mapFromCharToInt;


void setPrecedence(mapFromCharToInt* precedence){
    (*precedence)['+'] = 1;
    (*precedence)['-'] = 1;
    (*precedence)['*'] = 2;
    (*precedence)['/'] = 2;
}

bool isOperator(char character, mapFromCharToInt* precedence) {
    return (*precedence).find(character) != (*precedence).end();
}

void appendOperatorToRpnWithSpace(std::string* rpn, std::stack<char>* operatorsStack){
    (*rpn) += (*operatorsStack).top();
    (*rpn) += ' ';
    (*operatorsStack).pop();
};

std::string infixToRPN_singleDigitNum(const std::string& infix, mapFromCharToInt* precedence) {
    //here is why the code looks like shit => https://dev.to/quantumsheep/how-calculators-read-mathematical-expression-with-operator-precedence-4n9h
    //                                        ^^^^^^ is an explonetion for the Shunting yard algorithm
    std::string rpn;
    std::stack<char> operatorsStack;

    for (char character : infix) {

        if (std::isdigit(character)) {
            rpn += character;
            rpn += ' '; // Add a space to separate multi-digit numbers

        } else if (isOperator(character, precedence)) {
 
            while (!operatorsStack.empty() && isOperator(operatorsStack.top(), precedence) && (*precedence)[character] <= (*precedence)[operatorsStack.top()]) {
            //          ( !operatorsStack.empty() && isStackTopAlsoAnOperator && isOperatorPrecedenceLeqPrecedenceOfStackTop)
            //^^^^^^^^ i could not refector the while loop conditions because eatch loop iterration is dependend on the state of the stack and the current character, if i dit that then programm will break

                appendOperatorToRpnWithSpace(&rpn, &operatorsStack);
            }
            operatorsStack.push(character);

        } else if (character == '(') {
            operatorsStack.push(character);

        } else if (character == ')') {

            while (!operatorsStack.empty() && operatorsStack.top() != '(') {

                appendOperatorToRpnWithSpace(&rpn, &operatorsStack);
            }
            operatorsStack.pop(); // Pop the '('
        }
    }

    while (!operatorsStack.empty()) {
        appendOperatorToRpnWithSpace(&rpn, &operatorsStack);
    }

    return rpn;
}

void OperationBasedOnTokenAndOperand(std::stack<double>* numbersStack, std::string* token, double* leftOperand, double* rightOperand){
    if ((*token) == "+") {
                (*numbersStack).push((*leftOperand) + (*rightOperand));
            } else if ((*token) == "-") {
                (*numbersStack).push((*leftOperand) - (*rightOperand));
            } else if ((*token) == "*") {
                (*numbersStack).push((*leftOperand) * (*rightOperand));
            } else if ((*token) == "/") {
                (*numbersStack).push((*leftOperand) / (*rightOperand));
            }
}

double calculateRPN_singleDigitNum(const std::string& rpn) {
    //https://dev.to/quantumsheep/how-calculators-read-mathematical-expression-with-operator-precedence-4n9h
    //^^^^^^ is an explonetion for the Shunting yard algorithm the Calc part
    std::stack<double> numbersStack;

    std::istringstream rpnStringStream(rpn);
    std::string token;

    while (rpnStringStream >> token) {
        int ifTokenIsSingedInt = std::isdigit(token[0]) || (token[0] == '-' && std::isdigit(token[1]));

        if (ifTokenIsSingedInt) {
            numbersStack.push(std::stod(token));

        } else {
            double rightOperand = numbersStack.top();
            numbersStack.pop();

            double leftOperand = numbersStack.top();
            numbersStack.pop();

            OperationBasedOnTokenAndOperand(&numbersStack, &token, &leftOperand, &rightOperand);            
        }
    }

    return numbersStack.top();
}


int main(int argc, char** argv){
    displayComandLineArgs(argc, argv);

    mapFromCharToInt precedence;
    setPrecedence(&precedence);

    std::string infix = "5+3*(2+3)";
    std::string RPNstr = infixToRPN_singleDigitNum(infix, &precedence);

    double result = calculateRPN_singleDigitNum(RPNstr);

    std::cout << "RPNstr : " << RPNstr << "\r\n";
    std::cout << "result : " << result << "\r\n";

    return 0;
}