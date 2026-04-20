#ifndef MENSAJE_H
#define MENSAJE_H

#include <string>
using namespace std;

class Mensaje {
private:
    string remitente;
    string contenido;

public:
    Mensaje(string remitente, string contenido);

    string getRemitente();
    string getContenido();
    string toJSON();
};

#endif
