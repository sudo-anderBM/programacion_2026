#ifndef RECTANGULO_H
#define RECTANGULO_H

#include "Figura.h"

class Rectangulo : public Figura {

private:
    double base;
    double altura;

public:
    Rectangulo(std::string nombre, double base, double altura);
    ~Rectangulo();
    double calcularArea() override;
    void descubrir() override;
    double obtenerBase();
    double obtenerAltura();
};

#endif
