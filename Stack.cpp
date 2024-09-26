// Implement the template-based stack
#include "Stack.h"


template <typename T>
void Stack<T>::push(const T& elem) {
    elements.push_back(elem);
}

template <typename T>
void Stack<T>::pop() {
    if (!elements.empty()) {
        elements.pop_back();
    } else {
        std::cerr << "Stack is empty, cannot pop!" << std::endl;
    }
}

template <typename T>
T Stack<T>::top() const {
    if (!elements.empty()) {
        return elements.back();
    } else {
        std::cerr << "Stack is empty!" << std::endl;
        return T();  // Return default-constructed value
    }
}

template <typename T>
bool Stack<T>::isEmpty() const {
    return elements.empty();
}

template <typename T>
size_t Stack<T>::size() const {
    return elements.size();
}