#ifndef EMPLEADO_TIEMPO_COMPLETO_H
#define EMPLEADO_TIEMPO_COMPLETO_H

#include <string>
#include "empleado.h"

class EmpleadoTiempoCompleto : public Empleado {
    private:
        int horasSemanales;
        float bono;

        public:
        EmpleadoTiempoCompleto();
        EmpleadoTiempoCompleto(string nombre, string id, float salarioBase, int horasSemanales, float bono);

        void actualizarHorasSemanales(int nuevasHorasSemanales);
        void actualizarBono(float nuevoBono);

        void mostrarInformacion();

        float calcularSalarioTotal();
        int obtenerHorasSemanales();
        float obtenerBono();
};

#endif