#include "custom_stack.h"
#include <iostream>

CustomStack::CustomStack() {

}

CustomStack::~CustomStack() {

}

bool CustomStack::empty() {
    return datos.empty();
}

int CustomStack::size() {
    return datos.size();
}

int CustomStack::top() {

    if (empty()) {
        std::cout << "La pila esta vacia";
        return -1;
    }

    return datos.back();
}

void CustomStack::push(int valor) {
    datos.push_back(valor);
}

void CustomStack::pop() {

    if (empty()) {
        std::cout << "La pila esta vacia";
        return;
    }

    datos.pop_back();
}