#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

template <typename T>
class Stack {
private:
    std::vector<T> elements;

public:
    void push(const T& elem);
    T pop();
    T top() const;
    bool isEmpty() const;
    size_t size() const;
};

template <typename T>
void Stack<T>::push(const T& elem) {
    elements.push_back(elem);
}

template <typename T>
T Stack<T>::pop() {
    if (elements.empty()) {
        throw std::out_of_range("Stack<>::pop(): empty stack");
    }
    T temp = elements.back();
    elements.pop_back();
    return temp;
}

template <typename T>
T Stack<T>::top() const {
    if (elements.empty()) {
        throw std::out_of_range("Stack<>::top(): empty stack");
    }
    return elements.back();
}

template <typename T>
bool Stack<T>::isEmpty() const {
    return elements.empty();
}

template <typename T>
size_t Stack<T>::size() const {
    return elements.size();
}

#endif
