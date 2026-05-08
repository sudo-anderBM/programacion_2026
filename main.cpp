#include "custom_stack.h"
#include <iostream>

using namespace std;

int main() {

    CustomStack s;

    s.push(1);
    s.push(2);
    s.push(3);

    cout << "Tope: " << s.top() << endl;

    s.pop();

    cout << "Nuevo tope: " << s.top() << endl;

    return 0;
}