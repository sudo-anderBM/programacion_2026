#include "Circulo.h"
#include <iostream>
#include <cmath> // para usar M_PI 

// constructor de Circulo
// uso lista de inicializacion ": Figura(nombre)" para llamar al constructor de la clase base
Circulo::Circulo(std::string nombre, double radio) : Figura(nombre){
    this->radio = radio;
}

// destructror de Circulo
Circulo::~Circulo() {
}


//calculo para el area del circulo: A = pi * r^2
double Circulo::calcularArea() {
    return M_PI * radio * radio;
}


// muestro los datos del circulo por consola
void Circulo::descubrir(){
    std::cout << "Figura: " << nombre << " , radio: " << radio << std::endl;
}

double Circulo::obtenerRadio()  {
    return radio;
}
