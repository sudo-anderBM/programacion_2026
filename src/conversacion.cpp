#include "conversacion.h"
#include "mensaje.h"

#include <fstream>
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

// Crear carpeta en Windows
void crearCarpeta(const string& path) {
    string comando = "cmd /c if not exist \"" + path + "\" mkdir \"" + path + "\"";
    system(comando.c_str());
}

Conversacion::Conversacion() {
    time_t ahora = time(0);
    id = to_string(ahora);

    char buffer[80];
    struct tm* tiempoLocal = localtime(&ahora);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H", tiempoLocal);
    fechaCarpeta = string(buffer);
}

void Conversacion::agregarMensaje(Mensaje mensaje) {
    mensajes.push_back(mensaje);
}

int Conversacion::getCantidadMensajes() {
    return mensajes.size();
}

bool Conversacion::guardarEnArchivo() {
    crearCarpeta("conversaciones");
    crearCarpeta("conversaciones/" + fechaCarpeta);

    string archivoPath = "conversaciones/" + fechaCarpeta + "/" + id + ".json";
    ofstream archivo(archivoPath);

    if (!archivo.is_open()) {
        cerr << "Error al crear archivo\n";
        return false;
    }

    archivo << "{\n";
    archivo << "  \"id\": \"" << id << "\",\n";
    archivo << "  \"fecha_carpeta\": \"" << fechaCarpeta << "\",\n";
    archivo << "  \"total_mensajes\": " << mensajes.size() << ",\n";
    archivo << "  \"mensajes\": [\n";

    for (size_t i = 0; i < mensajes.size(); i++) {
        archivo << "    " << mensajes[i].toJSON();
        if (i < mensajes.size() - 1) archivo << ",";
        archivo << "\n";
    }

    archivo << "  ]\n";
    archivo << "}\n";

    archivo.close();

    cout << "Conversación guardada\n";
    return true;
}

string Conversacion::getId() {
    return id;
}

string Conversacion::getFechaCarpeta() {
    return fechaCarpeta;
}

void Conversacion::mostrarHistorial() {
    cout << "\n=== HISTORIAL ===\n";

    for (size_t i = 0; i < mensajes.size(); i++) {
        if (mensajes[i].getRemitente() == "usuario") {
            cout << "Tú: " << mensajes[i].getContenido() << endl;
        } else {
            cout << "Bot: " << mensajes[i].getContenido() << endl;
        }
    }

    cout << "=================\n";
}
