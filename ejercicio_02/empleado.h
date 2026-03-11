#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <string>
using std::string;

class Empleado{
    protected:
        string nombre;
        string id;
        float salarioBase;

        public:
        Empleado();
        Empleado(string nombre, string id, float salarioBase);

        void actualiarNombre(string nuevoNombre);
        void actualizarId(string nuevoId);
        void actualizarSalarioBase(float nuevosalarioBase);

        void mostrarInformacion();

        std::string obtenerNombre();
        std::string obtenerId();
        float obtenerSalarioBase();
};

#endif