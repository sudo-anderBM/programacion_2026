#include <iostream>
#include "estudiante.h"

int main() {
    std::cout << "=== Sistema de Gestión de Estudiantes ===\n\n";

    Estudiante estudiante1;
    estudiante1.mostrarInformacionCompleta();
    std::cout << std::endl;

    estudiante1.actualizarNombre("María García López");
    estudiante1.actualizarCodigo("EST-2024-001");
    estudiante1.actualizarEdad(20);
    estudiante1.actualizarPromedio(9.2);
    estudiante1.actualizarActivo(true);

    estudiante1.mostrarInformacionCompleta();
    estudiante1.calcularEstadoAcademico();

    std::cout << "\n";

    Estudiante estudiante2("Juan Pérez Martínez", "EST-2024-002", 22, 7.5, true);
    estudiante2.mostrarInformacionCompleta();
    estudiante2.calcularEstadoAcademico();

    std::cout << "\n";
    estudiante2.incrementarEdad();
    estudiante2.mostrarEdad();

    estudiante2.actualizarPromedio(15.0); // inválido
    estudiante2.mostrarPromedio();

    return 0;
}
