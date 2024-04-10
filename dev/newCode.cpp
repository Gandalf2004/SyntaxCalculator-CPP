#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cctype>
#include <sstream>
#include <stack>

typedef std::vector<std::string> vectorStr;

class SyntaxCalculator{
    private:

        vectorStr convertToInfixTokens(const std::string& input) {
            vectorStr infixTokens;
            std::string token;

            for (char c : input) {
                if (std::isspace(c)) {
                    continue;
                }

                if (std::isdigit(c)) {
                    token += c;
                } else if (std::isalnum(c)) {
                    token += c;
                } else {
                    if (!token.empty()) {
                        infixTokens.push_back(token);
                        token.clear();
                    }
                    infixTokens.push_back(std::string(1, c));
                }
            }

            if (!token.empty()) {
                infixTokens.push_back(token);
            }

            return infixTokens;
        }

        std::map<char, int> precedence = {
            {'+', 1},
            {'-', 1},
            {'*', 2},
            {'/', 2}
        };

        bool isOperator(char characher) {
            return precedence.find(characher) != precedence.end();
        }

        vectorStr infixToRPN(const vectorStr& infixTokens) {
            vectorStr output;
            std::vector<char> operators;

            for (const std::string& token : infixTokens) {
                if (token.size() == 1 && isOperator(token[0])) {
                    while (!operators.empty() && isOperator(operators.back()) && precedence[operators.back()] >= precedence[token[0]]) {

                        output.push_back(std::string(1, operators.back()));
                        operators.pop_back();
                    }
                    operators.push_back(token[0]);
                } else if (token == "(") {
                    operators.push_back('(');
                } else if (token == ")") {
                    while (!operators.empty() && operators.back() != '(') {

                        output.push_back(std::string(1, operators.back()));
                        operators.pop_back();
                    }
                    operators.pop_back(); // Pop '('

                } else {
                    output.push_back(token);
                }
            }

            while (!operators.empty()) {
                output.push_back(std::string(1, operators.back()));
                operators.pop_back();
            }

            return output;
        }

        void OperationBasedOnTokenAndOperand(std::stack<double>& numbersStack, const std::string& token, double leftOperand, double rightOperand) {
            if (token == "+") {
                numbersStack.push(leftOperand + rightOperand);
            } else if (token == "-") {
                numbersStack.push(leftOperand - rightOperand);
            } else if (token == "*") {
                numbersStack.push(leftOperand * rightOperand);
            } else if (token == "/") {
                numbersStack.push(leftOperand / rightOperand);
            }
        }

        double calculateRPN(const vectorStr& rpnTokens) {
            std::stack<double> numbersStack;

            for (const std::string& token : rpnTokens) {
                if (std::isdigit(token[0]) || (token[0] == '-' && std::isdigit(token[1]))) {
                    numbersStack.push(std::stod(token));
                } else {
                    double rightOperand = numbersStack.top();
                    numbersStack.pop();

                    double leftOperand = numbersStack.top();
                    numbersStack.pop();

                    OperationBasedOnTokenAndOperand(numbersStack, token, leftOperand, rightOperand);
                }
            }

            return numbersStack.top();
        }

    public:
        double calculator(const std::string& string){
            vectorStr infixtokens = convertToInfixTokens(string);
            vectorStr RPN = infixToRPN(infixtokens);
            double result = calculateRPN(RPN);
            return result;
        }
};





int main() {


    std::string input = "1+210-(5+20*4)";
    std::cout << input << std::endl;

    SyntaxCalculator Calc;
    double result = Calc.calculator(input);

    std::cout << "Result: " << result << std::endl;


    return 0;
}
