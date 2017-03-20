#ifndef PROJECT1_H
#define PROJECT1_H
#include <string>
#include <unordered_map>

bool IsOperator(char c);
bool IsNumber(char c);
//Check the precedence of f and s and return true of f is higher than s. False otherwise
bool higherPrec(char f, char s);
int getPrec(char c);
bool isLeftAss(char c);

//This function will recursively evaluate an expression
//and dive into functions
double evaluateExpression(const std::string& exp, std::unordered_map<std::string, double>& m);
double performOperation(double left, double right, char oper);

std::string trim(const std::string& s);
#endif
