#include "Figura.h"

// constructor: guardo el nombre que me pasan en el atributo de la clase
Figura::Figura(std::string nombre){
    this->nombre = nombre; // uso this-> para distinguir el parametro del atributo
}

// destructor vacio pero tiene que estar aqui porque lo declare virtual en el .h
Figura::~Figura() {
    // no necesito hacer nada especial en el destructor
}

// devuelvo el nombre de la figura
std::string Figura::obtenerNombre() {
    return nombre;
}
