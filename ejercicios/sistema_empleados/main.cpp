#include "Empleado.h"
#include "EmpleadoTiempoCompleto.h"
#include <iostream>

int main() {

    Empleado emp1("Carlos Gomez", "001", 15000);
    emp1.mostrarInformacion();

    std::cout << "---------------------" << std::endl;

    EmpleadoTiempoCompleto emp2("Ana Lopez", "002", 20000, 5000);
    emp2.mostrarInformacion();

    return 0;
}
