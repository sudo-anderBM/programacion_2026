#include <iostream>
#include "Figura.h" 
#include "Circulo.h"
#include "Rectangulo.h"

int main() {


    std::cout << "=== Sistema de Figuras Geometricas (Polimorfismo) ===" << std::endl;
    std::cout << std::endl;

    // creo objetos con new y los guardo en punteros de tipo Figura*
    // aunque f1 apunta a un Circulo, el tipo del puntero es Figura*
    Figura* f1 = new Circulo("Circulo A", 5.0);
    Figura* f2 = new Rectangulo("Rectangulo B", 4.0, 6.0);

      std::cout << "--- Figura 2 (Rectangulo) ---" << std::endl;
    f2->descubrir();
    std::cout << "Area: " << f2->calcularArea() << std::endl;
    std::cout << std::endl;
 
    // aqui se ve mejor el polimorfismo:
    // meto los dos punteros en un arreglo de Figura*
    // y los recorro con el mismo for, llamando a las mismas funciones
    // C++ decide en tiempo de ejecucion cual version ejecutar (enlace dinamico)
    std::cout << "--- Tratamiento uniforme con Figura* ---" << std::endl;
    Figura* figuras[] = { f1, f2 };
 
    for (int i = 0; i < 2; i++) {
        figuras[i]->descubrir();
        std::cout << "Area: " << figuras[i]->calcularArea() << std::endl;
    }
 
    std::cout << std::endl;
 
    // libero la memoria que reserve con new
    // el destructor virtual garantiza que se llame al destructor correcto
    // si no fuera virtual, solo se llamaria al destructor de Figura
    delete f1;
    delete f2;
 
    return 0;
}
