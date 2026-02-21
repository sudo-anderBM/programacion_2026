#include "EmpleadoTiempoCompleto.h"
#include <iostream>

EmpleadoTiempoCompleto::EmpleadoTiempoCompleto(std::string nombre, std::string id, float salarioBase, float bono)
    : Empleado(nombre, id, salarioBase), bono(bono) {}

void EmpleadoTiempoCompleto::mostrarInformacion() const {
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Salario Base: " << salarioBase << std::endl;
    std::cout << "Bono: " << bono << std::endl;
    std::cout << "Salario Total: " << salarioBase + bono << std::endl;
}
