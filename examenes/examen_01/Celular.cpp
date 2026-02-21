#include <iostream>
#include "Celular.h"

Celular::Celular(std::string m, std::string mod, int alm, float p, int bat) {
    marca = m;
    modelo = mod;
    almacenamiento = alm;
    precio = p;
    bateria = bat;
}

void Celular::mostrarInfo() {
    std::cout << "Marca: " << marca << std::endl;
    std::cout << "Modelo: " << modelo << std::endl;
    std::cout << "Almacenamiento: " << almacenamiento << " GB" << std::endl;
    std::cout << "Precio: $" << precio << std::endl;
    std::cout << "Bateria: " << bateria << "%" << std::endl;
}

void Celular::cargarBateria(int porcentaje) {
    bateria += porcentaje;
    if (bateria > 100) {
        bateria = 100;
    }
}

void Celular::cambiarPrecio(float nuevoPrecio) {
    precio = nuevoPrecio;
}
