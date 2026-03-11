#include "empleado_tiempo_completo.h"
#include <iostream>

EmpleadoTiempoCompleto::EmpleadoTiempoCompleto() : Empleado() {
    horasSemanales = 0.0;
    bono = 0.0;
}

EmpleadoTiempoCompleto::EmpleadoTiempoCompleto(string nombre, string id, float salarioBase, int horasSemanales, float bono)
    : Empleado(nombre, id, salarioBase) {
        this->horasSemanales = horasSemanales;
        this->bono = bono;
    }

    void EmpleadoTiempoCompleto::actualizarHorasSemanales(int nuevasHorasSemanales){
        horasSemanales = nuevasHorasSemanales;
    }

    void EmpleadoTiempoCompleto::actualizarBono(float nuevoBono){
        bono = nuevoBono;
    }

    void EmpleadoTiempoCompleto::mostrarInformacion(){
        Empleado::mostrarInformacion();
        std::cout << "Horas Semanales: " << horasSemanales << std::endl;
        std::cout << "Bono: " << bono << std::endl;
    }

    float EmpleadoTiempoCompleto::calcularSalarioTotal(){
        return salarioBase + bono;
    }

    int EmpleadoTiempoCompleto::obtenerHorasSemanales(){
        return horasSemanales;
    }

    float EmpleadoTiempoCompleto::obtenerBono(){
        return bono;
    }