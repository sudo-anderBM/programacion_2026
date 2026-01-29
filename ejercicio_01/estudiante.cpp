#include <iostream>
#include "estudiante.h"

// Constructor por defecto
Estudiante::Estudiante() {
    nombre = "Sin nombre";
    codigo = "N/A";
    edad = 0;
    promedio = 0.0;
    activo = false;
}

// Constructor con parámetros
Estudiante::Estudiante(std::string nombre, std::string codigo, int edad, double promedio, bool activo) {
    this->nombre = nombre;
    this->codigo = codigo;
    this->edad = edad;
    this->promedio = promedio;
    this->activo = activo;
}

// Mostrar información completa
void Estudiante::mostrarInformacionCompleta() {
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "Código: " << codigo << std::endl;
    std::cout << "Edad: " << edad << std::endl;
    std::cout << "Promedio: " << promedio << std::endl;
    std::cout << "Activo: " << (activo ? "Sí" : "No") << std::endl;
}

// Estado académico
void Estudiante::calcularEstadoAcademico() {
    if (promedio >= 8.0) {
        std::cout << "Estado académico: Excelente" << std::endl;
    } else if (promedio >= 6.0) {
        std::cout << "Estado académico: Regular" << std::endl;
    } else {
        std::cout << "Estado académico: Reprobado" << std::endl;
    }
}

// Métodos de actualización
void Estudiante::actualizarNombre(std::string nombre) {
    this->nombre = nombre;
}

void Estudiante::actualizarCodigo(std::string codigo) {
    this->codigo = codigo;
}

void Estudiante::actualizarEdad(int edad) {
    if (edad > 0) {
        this->edad = edad;
    }
}

void Estudiante::actualizarPromedio(double promedio) {
    if (promedio >= 0.0 && promedio <= 10.0) {
        this->promedio = promedio;
    } else {
        std::cout << "Promedio inválido. Debe estar entre 0 y 10." << std::endl;
    }
}

void Estudiante::actualizarActivo(bool activo) {
    this->activo = activo;
}

// Otros métodos
void Estudiante::incrementarEdad() {
    edad++;
}

void Estudiante::mostrarEdad() {
    std::cout << "Edad actual: " << edad << std::endl;
}

void Estudiante::mostrarPromedio() {
    std::cout << "Promedio actual: " << promedio << std::endl;
}
