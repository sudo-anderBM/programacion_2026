#include<iostream>
#include<stdlib.h>

using namespace std;

class Persona{
    private:
        string nombre;
        int edad;
    public:
        Persona(string, int);
        virtual void mostrar();    
};

// constructor
Persona::Persona(string _nombre, int _edad){
    nombre = _nombre;
    edad = _edad;
}

void Persona::mostrar(){
    cout<<"Nombre: "<<nombre<<endl;
    cout<<"Edad: "<<edad<<endl;
}

// clase derivada Alumno
class Alumno : public Persona{
    private:
        float notaFinal;
    public:
        Alumno(string, int, float);
        void mostrar();    
};

Alumno::Alumno(string _nombre, int _edad, float _notaFinal) 
: Persona(_nombre, _edad) {
    notaFinal = _notaFinal;
}

void Alumno::mostrar(){
    Persona::mostrar();
    cout<<"Nota Final: "<<notaFinal<<endl;
}

// clase derivada Profesor
class Profesor : public Persona{
    private:
        string materia;
    public:
        Profesor(string, int, string);
        void mostrar();
};

Profesor::Profesor(string _nombre, int _edad, string _materia) 
: Persona(_nombre, _edad){
    materia = _materia;
}

void Profesor::mostrar(){
    Persona::mostrar();
    cout<<"Materia: "<<materia<<endl;
}

int main(){
    Persona *vector[3];

    vector[0] = new Alumno("Herberth", 20, 8.5);
    vector[0]->mostrar();
    cout << "\n";

    vector[1] = new Profesor("Rocio", 35, "Matematicas");
    vector[1]->mostrar();
    cout << "\n";

    return 0;
}
