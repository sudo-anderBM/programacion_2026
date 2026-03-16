#ifndef CIRCULO_H
#define CIRCULO_H

#include "Figura.h"

class Circulo : public Figura {

private:
    double radio;

public:
    Circulo(std::string nombre, double radio);
    ~Circulo();
    double calcularArea() override;
    void descubrir() override;
    double obtenerRadio();
};

#endif
