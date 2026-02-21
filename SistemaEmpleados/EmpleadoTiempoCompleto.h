#ifndef EMPLEADOTIEMPOCOMPLETO_H
#define EMPLEADOTIEMPOCOMPLETO_H

#include "Empleado.h"

class EmpleadoTiempoCompleto : public Empleado {
private:
    float bono;

public:
    EmpleadoTiempoCompleto(std::string nombre, std::string id, float salarioBase, float bono);

    void mostrarInformacion() const override;
};

#endif
