#include "project1.h"
#include <iostream>
#include <cmath>
#include <cctype>
#include <stack>
#include <string>
#include <unordered_map>
#include <locale>

using namespace std;

//_abort will be flipped true when an error occurs (Divide by zero or unknown variable)
//_abort is flipped within the performOperations function and must be reset somewhere in main
bool _abort; //Filthy animal
//Silent will be true when a let is being processed so as to not print any errors... im sorry
//NOTE: Variable is only modified within the let if statement.
bool _silent; //I hate myself
bool _debug = false; //...may aswell

int main() {
	unordered_map<string, double> vars;
	//Add constants
	vars["Pi"] = 3.14169;
	vars["e"] = 2.718;
	string in;
	getline(cin, in);
	while (in.compare("quit") != 0) {
		_abort = false;
		_silent = false; //Safe check for my shitty logic
		if (trim(in).compare("") != 0) {
			double res = evaluateExpression(in, vars);
			if (!_silent && !_abort)
				cout << res << endl;
		}

		getline(cin, in);
	}
	//TODO Check for and reset _abort
}

double evaluateExpression(const string& exp, unordered_map<string, double>& m) {
	if (_debug) cout << "Evaluating: " << exp << endl;
	if (trim(exp).compare("") == 0) {
		//Paranoid safety check
		_abort = true;
		return 0;
	}

	stack<double> result;
	stack<char> operators;
	for (int i=0; i<(int)exp.length(); i++) {
		if (_debug) cout << "Processing: " << exp[i] << endl;
		if (_abort) break; //Sprinkle this around
		if (exp[i] == ' ') {
			continue;
		} else if (exp[i] == '(') {
			operators.push(exp[i]);
		} else if (exp[i] == ')') {
			while (!operators.empty() && operators.top() != '(') {
				double right = result.top();
				result.pop();
				double left = result.top();
				result.pop();
				result.push(performOperation(left, right, operators.top()));
				operators.pop();
			}
			//Operators should not be empty. ( must be present
			operators.pop(); //Remove (
	  } else if (IsOperator(exp[i])) {
			if (!operators.empty()) {
				//Operators is not empty so check if those operators should be done first
				while (!operators.empty() && operators.top() != '(' 
						&& higherPrec(operators.top(), exp[i])) {
					//Operators at the top of the stack should be processed first
					double right = result.top();
					result.pop();
					double left = result.top();
					result.pop();
					result.push(performOperation(left, right, operators.top()));
					operators.pop();
				}
				//Add the operators we are currently processing
				operators.push(exp[i]);
			} else {
				operators.push(exp[i]);
			}
		} else if (IsNumber(exp[i])) {
			string number(1, exp[i]);
			int j = i+1;
			while (j < (int)exp.length() && IsNumber(exp[j])) {
				number = number + exp[j];
				j++;
			}
			//Debug
			if (_debug) cout << "Read number: " << number << endl;
			//Number extracted now fast forward i
			i = j - 1;
			//Turn number into a double and store in result stack
			result.push(stod(number));
		} else if (exp[i] == 'c' && i+3 < (int)exp.length() && exp[i+1] == 'o' && exp[i+2] == 's'
				&& exp[i+3] == '(') {
			//Looks like cos
			i = i + 3; //Should be at the (
			int start = i; //Will be used to snip the function
			stack<char> parens;
			parens.push(exp[i]);
			//Find the next closing parenthesis that matches this one
			while (!parens.empty()) {
				i++;
				//WARNING POSSIBLE INFINITE LOOP
				if (exp[i] == '(') {
					parens.push(exp[i]);
				} else if (exp[i] == ')') {
					parens.pop();
				}
			}
			//i should be at )
			string func = exp.substr(start + 1, i - (start + 1));
			result.push(cos(evaluateExpression(func, m)));
		} else if (exp[i] == 's' && i+3 < (int)exp.length() && exp[i+1] == 'i' && exp[i+2] == 'n'
				&& exp[i+3] == '(') { //sry
			//Looks like sin
			i = i + 3; //Should be at the (
			int start = i; //Will be used to snip the function
			stack<char> parens;
			parens.push(exp[i]);
			//Find the next closing parenthesis that matches this one
			while (!parens.empty()) {
				i++;
				//WARNING POSSIBLE INFINITE LOOP
				if (exp[i] == '(') {
					parens.push(exp[i]);
				} else if (exp[i] == ')') {
					parens.pop();
				}
			}
			//i should be at )
			//func is the bit inside the () of the function
			string func = exp.substr(start + 1, i - (start + 1));
			result.push(sin(evaluateExpression(func, m)));
		} else if (exp[i] == 'l' && i+3 < (int)exp.length() && exp[i+1] == 'o' && exp[i+2] == 'g'
				&& exp[i+3] == '(') { //sry
			//Looks like log
			i = i + 3; //Should be at the (
			int start = i; //Will be used to snip the function
			stack<char> parens;
			parens.push(exp[i]);
			//Find the next closing parenthesis that matches this one
			while (!parens.empty()) {
				i++;
				//WARNING POSSIBLE INFINITE LOOP
				if (exp[i] == '(') {
					parens.push(exp[i]);
				} else if (exp[i] == ')') {
					parens.pop();
				}
			}
			//i should be at )
			//func is the bit inside the () of the function
			string func = exp.substr(start + 1, i - (start + 1));
			double value = evaluateExpression(func, m);
			if (_abort) break; //Sprinkle some _abort
			result.push(log(value));
		} else if (exp[i] == 'l' && i+3 < (int)exp.length() && exp[i+1] == 'e' && exp[i+2] == 't'
				&& exp[i+3] == ' ') { //sry
			//Looks like let (NOTE: Assuming let has a space before the variable name)
			_silent = true; //shhhhh
			i = i + 3; //i should be at the first space
			while (i < (int)exp.length() && exp[i] == ' ') {
				i++;
			}

			//i should now be at the first character of the variable name
			string var = ""; //Store the variable name
			while (i < (int)exp.length() && (isalpha(exp[i]) || IsNumber(exp[i]))) {
				var += exp[i];
				i++;
			}

			//var has full variable name (Letters and numbers included in it
			//Move i to past the =
			while (i < (int)exp.length() && exp[i] == '=') {
				i++;
			}
			i++; //Go 1 past the =

			//Assuming it found the = before ending, evaluate everything past it
			string sub = exp.substr(i+1, (int)exp.length() - (i+1));
			double value = evaluateExpression(sub, m);

			_silent = false; //You may speak now

			if (_abort) break; //Sprinkle some _abort
			//Store/update the variable into our map
			m[var] = value;
			i = exp.length(); //No need to process any futher

			//Logic behind this line below is that it will force the operation
			//processing right after this forloop to skip. Since after setting a 
			//variable, there is no need to process or output anything else.
			_abort = true; //....
			//Debug
			if (_debug) cout << "Stored var: " << var << ":" << value << endl;
		} else {
			//Debug
			if (_debug) cout << "Checking variable" << endl;
			//Is it a variable name?
			//Extract the whole variable name
			string var = "";
			//NOTE: Not sure if isalpha returns true for spaces!
			while (i < (int)exp.length() && (isalpha(exp[i]) || IsNumber(exp[i]))) {
				var += exp[i];
				i++;
			}
			//Debug
			if (_debug) cout << "Got var: " << var << endl;

			//Got the var name now check if it is an existing variable
			if (m.find(var) == m.end()) {
				//Not found
				if (!_silent)
					cout << "Undeclared-Variable";
					if (_debug) cout << ":" << var << endl;
					else cout << endl;
				_abort = true; //You had 1 rule... and you broke it
				break;
			} else {
				//Evaluate the variable
				result.push(m[var]);
			}
			i--; //The for loop is going to add 1
		}
			//Is it a variable?
		//TODO Function handling
		//TODO Variable handling
	}

	//Go through the operators stack
	while (!operators.empty() && !_abort) { //Sprinkle some _abort
		double right = result.top();
		result.pop();
		double left = result.top();
		result.pop();
		result.push(performOperation(left, right, operators.top()));
		operators.pop();
	}
	
	return (_abort) ? 0 : result.top(); //result should have only 1 element
}

bool IsOperator(char c) {
	switch(c) {
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':
			return true;
		default:
			return false;
	}
}

//True if c is a  number or a .
bool IsNumber(char c) {
	if (c == '.') {
		return true;
	} else if (isdigit(c)) {
		return true;
	} else {
		return false;
	}
}

//Check the precedence of f and s and return true of f is higher than s. False otherwise
bool higherPrec(char f, char s) {
	int fP = getPrec(f);
	int sP = getPrec(s);
	if (fP == sP) {
		if (isLeftAss(f))
			return true;
		else
			return false;
	} else if (fP > sP) {
		return true;
	} else {
		return false;
	}
}

int getPrec(char c) {
	int result = 0;
	switch(c) {
		case '^':
			result++;
		case '*':
		case '/':
			result++;
		case '+':
		case '-':
			result++;
	}
	return result;
}

bool isLeftAss(char c) {
	if (c == '^')
		return false;
	return true;
}

double performOperation(double left, double right, char oper) {
	if (_abort) return 0; //Sprinkle this around
	if (oper == '+') {
		return left + right;
	} else if (oper == '-') {
		return left - right;
	} else if (oper == '*') {
		return left * right;
	} else if (oper == '/') {
		if (right == 0) {
			if (!_silent) //...
				cout << "Division-By-Zero" << endl;
			_abort = true; //Filthy
		} else {
			return left / right; //CHECK FOR ZERO
		}
	} else if (oper == '^') {
		return pow(left, right);
	} else {
		cout << "Error performing operation LHS=" 
			<< left << " RHS=" << right << " OPERATOR=" << oper << endl;
	}
	return 0;
}

//Simple trim function I got from the internet :3
string trim(const string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

