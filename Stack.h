#ifndef STACK_H
#define STACK_H

#include <vector>
#include <iostream>

// Declare a template class for the Stack
template <typename T>
class Stack {
    private:
        std::vector<T> elements;  // Use vector to store stack elements

    public:
        // Push an element onto the stack
        void push(const T& elem);

        // Pop the top element off the stack
        void pop();

        // Get the top element of the stack
        T top() const;

        // Check if the stack is empty
        bool isEmpty() const;

        // Get the size of the stack
        size_t size() const;
};

#include "Stack.cpp"  // Include the implementation here

#endif
