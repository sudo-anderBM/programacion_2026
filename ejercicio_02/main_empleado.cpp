#include <iostream>
#include "empleado_tiempo_completo.h"

int main() {
    std::cout << "=== Sistema de Gestion de Empleados ===" << std::endl;
    std::cout << std::endl;

    Empleado emp1("Armando Perez", "EMP-001", 15000.0);
    std::cout << "Empleado (clase base):" << std::endl;
    emp1.mostrarInformacion();
    std::cout << std::endl;

    EmpleadoTiempoCompleto etc1;
    std::cout << "Empleado tiempo completo (constructor por defecto):" << std::endl;
    etc1.mostrarInformacion();
    std::cout << std::endl;

    EmpleadoTiempoCompleto etc2("Carin Leon", "EMP-002", 20000.0, 40, 2000.0);
    std::cout <<"Empleado tempo completo (constructor con parametros):" << std::endl;
    etc2.mostrarInformacion();
    std::cout << "salario total: " << etc2.calcularSalarioTotal() << std::endl;
    std::cout << std::endl;

    etc2.actualizarBono(3000.0);
    std::cout << "despues de atualizar bono:" << std::endl;
    etc2.mostrarInformacion();
    std::cout << "Salario total: " << etc2.calcularSalarioTotal() << std::endl;

    return 0;
}