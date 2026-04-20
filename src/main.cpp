#include <iostream>
#include "conversacion.h"
#include "mensaje.h"

using namespace std;

int main() {
    Conversacion chat;
    string input;

    cout << "Chatbot iniciado (escribe 'salir')\n";

    while (true) {
        cout << "> ";
        getline(cin, input);

        if (input == "salir") break;

        Mensaje m1("usuario", input);
        chat.agregarMensaje(m1);

        string respuesta = "Dijiste: " + input;
        Mensaje m2("bot", respuesta);
        chat.agregarMensaje(m2);

        cout << "Bot: " << respuesta << endl;
    }

    chat.mostrarHistorial();
    chat.guardarEnArchivo();

    return 0;
}
