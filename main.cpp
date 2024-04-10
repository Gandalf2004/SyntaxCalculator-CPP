//main.cpp Ver 0.1.0
//Created by Martin Sharp at 29.08.2023
#include <iostream>

#include "SyntaxCalculator.h"
#include "customUtilitys.h"

int main(int argc, char** argv){
    displayComandLineArgs(argc, argv);
    
    std::string input = "1+210-(5+20*4)";
    std::cout << input << std::endl;

    SyntaxCalculator Calc;
    double result = Calc.calculator(input);

    std::cout << "Result: " << result << std::endl;

    return 0;
}