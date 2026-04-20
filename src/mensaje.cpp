#include "mensaje.h"

Mensaje::Mensaje(string remitente, string contenido) {
    this->remitente = remitente;
    this->contenido = contenido;
}

string Mensaje::getRemitente() {
    return remitente;
}

string Mensaje::getContenido() {
    return contenido;
}

string Mensaje::toJSON() {
    return "{ \"remitente\": \"" + remitente + "\", \"contenido\": \"" + contenido + "\" }";
}
