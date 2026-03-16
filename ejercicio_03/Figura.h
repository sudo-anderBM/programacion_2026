#ifndef FIGURA_H
#define FIGURA_H

#include <string>

class Figura {

protected:
    std::string nombre;

public:
    Figura(std::string nombre);
    virtual ~Figura();
    virtual double calcularArea() = 0;
    virtual void descubrir() = 0;
    std::string obtenerNombre();
};

#endif
