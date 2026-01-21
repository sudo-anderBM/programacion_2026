#include <stdio.h>
#include <string.h>

struct Estudiante {
    char nombre[50];
    char codigo[15];     // Ej: A25234567
    int edad;
    float promedio;
    int activo;          // 1 = activo, 0 = inactivo
};

/* Muestra toda la información del estudiante */
void mostrarInformacionCompleta(struct Estudiante e) {
    printf("\n--- INFORMACIÓN DEL ESTUDIANTE ---\n");
    printf("Nombre: %s", e.nombre);
    printf("Codigo: %s", e.codigo);
    printf("Edad: %d\n", e.edad);
    printf("Promedio: %.2f\n", e.promedio);
    printf("Estado: %s\n", e.activo ? "Activo" : "Inactivo");
}

int main() {
    struct Estudiante estudiante;

    printf("Ingrese el nombre completo: ");
    fgets(estudiante.nombre, 50, stdin);

    printf("Ingrese el codigo del estudiante: ");
    fgets(estudiante.codigo, 15, stdin);

    printf("Ingrese la edad: ");
    scanf("%d", &estudiante.edad);

    printf("Ingrese el promedio (0.0 - 10.0): ");
    scanf("%f", &estudiante.promedio);

    printf("El estudiante esta activo? (1 = Si, 0 = No): ");
    scanf("%d", &estudiante.activo);

    mostrarInformacionCompleta(estudiante);

    return 0;
}
