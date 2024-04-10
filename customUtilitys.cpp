// customUtilitys.cpp Ver 0.1.0
// Created by Martin Sharp 28.08.2023
#include <iostream>
#include <iomanip>

void displayComandLineArgs(int argc, char** argv){
    for (int i = 0; i < argc; i++) {
        int ifNotTheLastArg =  i < argc - 1;

        std::cout << argv[i] << (ifNotTheLastArg ? " " : ""); 
    }
    std::cout << "\r\n";
}

void cprintln(const char* str){
    std::cout << str << "\r\n";
}

void cprintln_formattedDouble(int precision, const char* string, double variable){
    std::cout << std::fixed << std::setprecision(precision) << string << variable <<"\r\n";
}