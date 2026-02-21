#ifndef CELULAR_H
#define CELULAR_H

#include <string>

class Celular {
private:
    std::string marca;
    std::string modelo;
    int almacenamiento;
    float precio;
    int bateria;

public:
    Celular(std::string m, std::string mod, int alm, float p, int bat);

    void mostrarInfo();
    void cargarBateria(int porcentaje);
    void cambiarPrecio(float nuevoPrecio);
};

#endif
