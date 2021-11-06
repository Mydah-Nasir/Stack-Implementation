// Assignment 2.0.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <string>
#include <vector>
#include <string.h>
using namespace std;

//defining a function strtok to tokenize a string passed in function parameter and return a vector of string tokens
vector<string> strtok(string strtok, char delimitor) {
	vector<string> tokens; //initializing a vector class object with data type string
	string tempstr = ""; //initializng an empty string to store tokens of string passed
	for (int i = 0; i < strtok.length(); i++) { //applying for loop to traverse the string
		if (strtok[i] == delimitor) { //checking if a delimiting charachter is found in string
			tokens.push_back(tempstr); // pushing the temporary string in the vector tokens
			tempstr = "";  // resetting the value of temporary string
		}
		else
			tempstr += strtok[i]; // else if delimitor is not found keep adding the strtok charachter to temporary string
	}
	tokens.push_back(tempstr); //finally pushing back the last string to tokens vector
	return tokens; // return vector tokens
}
// creating a template class of stack to operate for different data types
template <typename T>
class Stack {
public:
	static const int size = 100; //defining a constant size of stack
	T stack[size]; //declaring an array of fixed size
	int top = -1; // declaring initial value of top as -1

	//declaring function isFull() to check whether stack is full
	bool isFull() {
		return top == size - 1;
	}
	//declaring function isEmpty() to check whether stack is empty
	bool isEmpty() {
		return top < 0;
	}
	//defining push method to insert an element in the stack
	void push(T obj) {
		if (!isFull()) { //insert the element only if there is space in stack
			stack[++top] = obj; //insert element at the top most position of stack
		}
	}
	//defining function to pop the top most element in stack
	void pop() {
		if (!isEmpty()) {
			top--; //decrementing value of top to reduce size of stack after popping
		}
	}
	//defining function to return element at top of stack
	T peak() {
		return stack[top];
	}
	//defining function to clear all stack
	void clear() {
		top = -1; //redefining top to -1
	}
};
// defining a function precedence to assign precedence to each operator
int precedence(string op) {
	if (op == "+" || op == "-") { //if string passed is + or - then return 1
		return 1;
	}
	if (op == "*" || op == "/") {
		return 2; //returning 2 if the operator is multiplier or divider
	}
	if (op == "^") {
		return 3; //returning 3 if operator is power
	}
	else
		return 0; // returing 0 in case of invalid operator
}
//defining function to convert a string passed in function paramter from infix to postfix
string InfixToPostFix(string infix) {
	Stack<string> stack; // initializing a stack of type string
	string postfix = ""; // initializing a string to store the postfix expression
	vector<string> expression = strtok(infix, ' '); //tokenizing the infix string and storing it in vector expression
	for (int i = 0; i < expression.size(); i++) { //using for loop to traverse the vector expression
		if (expression[i] == "{" || expression[i] == "(" || expression[i] == "[") { //checking if the string obtained is one of the opening brackets
			stack.push(expression[i]); //pushing opening brackets to stack
		}
		else if (expression[i] == "}" || expression[i] == ")" || expression[i] == "]") { //checking if the string obtained is a closing bracket
			if (expression[i] == "}") { // checking if a curly closing bracket is found
				while (stack.peak() != "{") { //using while loop to pop the elements of stack until a curly opening bracket is found
					postfix = postfix + " " + stack.peak(); //adding the element at top of stack to postfix string
					stack.pop(); // popping the stack
				}

			}
			if (expression[i] == ")") { // checking if a round closing bracket is found
				while (stack.peak() != "(") { //using while loop to pop the elements of stack until a round opening bracket is found
					postfix = postfix + " " + stack.peak(); //adding the element at top of stack to postfix string
					stack.pop();  // popping the stack
				}

			}
			if (expression[i] == "]") { // checking if a square closing bracket is found
				while (stack.peak() != "[") { //using while loop to pop the elements of stack until a square opening bracket is found
					postfix = postfix + " " + stack.peak(); //adding the element at top of stack to postfix string
					stack.pop(); // popping the stack
				}

			}
			stack.pop(); // popping the opening bracket left from stack
		}
		else if (expression[i] == "*" || expression[i] == "/" || expression[i] == "+" || expression[i] == "-" || expression[i] == "^") { //checking if the string obtained is an operator
			while (!stack.isEmpty() && precedence(expression[i]) <= precedence(stack.peak())) { //using while loop to pop the elements of stack until the operator at top of stack has lower precedence than incoming operator
				postfix = postfix + " " + stack.peak(); //adding top of stack operator to postfix expression
				stack.pop();
			}
			stack.push(expression[i]); //pushing the incoming operator in stack


		}
		else { //checking if the incoming string is an operand 
			postfix = postfix + " " + expression[i]; // adding operand to postfix expression
		}
	}
	while (!stack.isEmpty()) { //using while loop to add elements of the stack to postfix expression
		postfix = postfix + " " + stack.peak();
		stack.pop();
	}

	return postfix; //returning postfix expression
}
// defining a function to evaluate postfix expression
double PostFixEvaluation(string postfix) {
	vector<string> exp = strtok(postfix, ' '); //using strtok function to tokenize the postfix expression passed in paramter
	Stack<int> result; //creating a stack of type int to store result of postfix expression
	for (int i = 0; i < exp.size(); i++) { //using for loop to traverse the contents of vector
		char* ch = const_cast<char*>(exp[i].c_str()); //casting the string obtained to a charachter array
		int size = strlen(ch); //taking size of charachter array ch
		if (size == 2) { //if size of charachter is 2
			if (isdigit(ch[0]) && isdigit(ch[1])) { //checking if both the charachters are digit
				int num = atoi(ch); //converting the charachter array to number using inbuilt function atoi
				result.push(num);  //pushing the number in result stack
			}
		}
		else if (size == 1) { //checking if there is only one charachter in ch
			if (isdigit(ch[0])) { //checking if that is a digit
				int num = atoi(ch); //converting the charachter to a number
				result.push(num); //pushing the number in result stack

			}
			else { //else if the charachter is an operator
				if (!result.isEmpty()) { //checking if the result is not empty
					int num1 = result.peak(); //assigning top of stack as num1
					result.pop(); //popping the stack
					int num2 = result.peak(); //assigning new top of stack as num2
					result.pop(); //popping the stack
					switch (ch[0]) //using switch case to evaluate two numbers obtained
					{

					case '+': result.push(num2 + num1); break; //if the operator is + add both numbers
					case '-': result.push(num2 - num1); break; //if the operator is - subtract both numbers
					case '/': result.push(num2 / num1); break; //if the operator is / divide both numbers
					case '*': result.push(num2 * num1); break; //if the operator is * multiply both numbers
					case '^': result.push(num2 ^ num1); break; //if the operator is ^ evaluate num2 raise to power num1
					default: //if any other expression found break the switch case
						break;
					}

				}
			}

		}
	}
	return result.peak(); //returning the result
	result.pop(); //emptying the result stack

}






int main() {
	string input; //initializing a string to store input of user
	cout << "Please enter a infix expression for conversion to postfix.\nPlease add spaces between each operand and operator:" << endl;
	getline(cin, input); //taking input using getline() function
	cout << "Post Fix Expression: " << InfixToPostFix(input) << endl;
	cout << "Post Fix Expression Evaluation Answer: " << PostFixEvaluation(InfixToPostFix(input)) << endl;
}








