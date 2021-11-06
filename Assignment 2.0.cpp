// Assignment 2.0.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
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


