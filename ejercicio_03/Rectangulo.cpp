#include "Rectangulo.h"
#include <iostream>

// constructor de Rectangulo
Rectangulo::Rectangulo(std::string nombre, double base, double altura) : Figura(nombre) {
    this->base = base;
    this->altura = altura;
}

// destructor de Rectangulo
Rectangulo::~Rectangulo() {
}

// calculo para el area del rectangulo: A = base * altura
double Rectangulo::calcularArea() {
    return base * altura;
}

//muestreo de los datos del rectangulo
void Rectangulo::descubrir(){
    std::cout << "Figura: " << nombre 
    << " , base: " << base 
    << " , altura: " << altura << std::endl;
}

// getters
double Rectangulo::obtenerBase(){
    return base;

}

double Rectangulo::obtenerAltura(){
    return altura;

}


