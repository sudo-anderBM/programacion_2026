#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include <string>

class Estudiante {
private:
    std::string nombre;
    std::string codigo;
    int edad;
    double promedio;
    bool activo;

public:
    Estudiante();
    Estudiante(std::string nombre, std::string codigo, int edad, double promedio, bool activo);

    void mostrarInformacionCompleta();
    void calcularEstadoAcademico();

    void actualizarNombre(std::string nombre);
    void actualizarCodigo(std::string codigo);
    void actualizarEdad(int edad);
    void actualizarPromedio(double promedio);
    void actualizarActivo(bool activo);

    void incrementarEdad();
    void mostrarEdad();
    void mostrarPromedio();
};

#endif
