#ifndef CONVERSACION_H
#define CONVERSACION_H

#include <vector>
#include <string>
#include "mensaje.h"

using namespace std;

class Conversacion {
private:
    string id;
    string fechaCarpeta;
    vector<Mensaje> mensajes;

public:
    Conversacion();

    void agregarMensaje(Mensaje mensaje);
    int getCantidadMensajes();
    bool guardarEnArchivo();

    string getId();
    string getFechaCarpeta();

    void mostrarHistorial();
};

#endif
