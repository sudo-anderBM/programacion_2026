#ifndef CUSTOM_STACK_H
#define CUSTOM_STACK_H

#include <vector>

class CustomStack {

private:
    std::vector<int> datos;

public:
    CustomStack();
    ~CustomStack();

    bool empty();
    void pop();
    int size();
    int top();
    void push(int valor);
};

#endif