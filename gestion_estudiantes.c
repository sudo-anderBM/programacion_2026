#include <stdio.h>
#include <string.h>

#define MAX_ESTUDIANTES 100
#define MAX_TEXTO 50

/* ===== ESTRUCTURA ===== */
struct Estudiante {
    char nombre[MAX_TEXTO];
    char codigo[15];   // Ej: A25234567
    int edad;
    float promedio;
    int activo;        // 1 = activo, 0 = inactivo
};

/* ===== FUNCIONES DE ACTUALIZACIÓN ===== */
void actualizarNombre(struct Estudiante *e, char nuevoNombre[]) {
    strcpy(e->nombre, nuevoNombre);
}

void actualizarCodigo(struct Estudiante *e, char nuevoCodigo[]) {
    strcpy(e->codigo, nuevoCodigo);
}

void actualizarEdad(struct Estudiante *e, int nuevaEdad) {
    e->edad = nuevaEdad;
}

void actualizarPromedio(struct Estudiante *e, float nuevoPromedio) {
    if (nuevoPromedio >= 0.0 && nuevoPromedio <= 10.0) {
        e->promedio = nuevoPromedio;
    } else {
        printf("Promedio invalido (0.0 - 10.0)\n");
    }
}

void actualizarActivo(struct Estudiante *e, int nuevoEstado) {
    e->activo = nuevoEstado;
}

/* ===== FUNCIONES DE MOSTRAR ===== */
void mostrarInformacionCompleta(struct Estudiante e) {
    printf("\n--- INFORMACION DEL ESTUDIANTE ---\n");
    printf("Nombre: %s\n", e.nombre);
    printf("Codigo: %s\n", e.codigo);
    printf("Edad: %d\n", e.edad);
    printf("Promedio: %.2f\n", e.promedio);
    printf("Estado: %s\n", e.activo ? "Activo" : "Inactivo");
}

/* ===== AGREGAR ESTUDIANTE ===== */
void agregarEstudiante(struct Estudiante estudiantes[], int *contador) {
    struct Estudiante e;

    printf("Nombre: ");
    getchar(); // limpia buffer
    fgets(e.nombre, MAX_TEXTO, stdin);
    e.nombre[strcspn(e.nombre, "\n")] = 0;

    printf("Codigo: ");
    fgets(e.codigo, 15, stdin);
    e.codigo[strcspn(e.codigo, "\n")] = 0;

    printf("Edad: ");
    scanf("%d", &e.edad);

    printf("Promedio: ");
    scanf("%f", &e.promedio);

    actualizarActivo(&e, 1); // activo por defecto

    estudiantes[*contador] = e;
    (*contador)++;

    printf("Estudiante agregado correctamente.\n");
}

/* ===== MOSTRAR UN ESTUDIANTE ===== */
void mostrarEstudiante(struct Estudiante estudiantes[], int contador) {
    char codigoBuscado[15];

    printf("Ingrese el codigo: ");
    getchar();
    fgets(codigoBuscado, 15, stdin);
    codigoBuscado[strcspn(codigoBuscado, "\n")] = 0;

    for (int i = 0; i < contador; i++) {
        if (strcmp(estudiantes[i].codigo, codigoBuscado) == 0) {
            mostrarInformacionCompleta(estudiantes[i]);
            return;
        }
    }

    printf("Estudiante no encontrado.\n");
}

/* ===== MOSTRAR TODOS ===== */
void mostrarTodos(struct Estudiante estudiantes[], int contador) {
    if (contador == 0) {
        printf("No hay estudiantes registrados.\n");
        return;
    }

    for (int i = 0; i < contador; i++) {
        mostrarInformacionCompleta(estudiantes[i]);
    }
}

/* ===== MAIN ===== */
int main() {
    struct Estudiante estudiantes[MAX_ESTUDIANTES];
    int contador = 0;
    int opcion;

    do {
        printf("\n===== MENU =====\n");
        printf("1. Agregar estudiante\n");
        printf("2. Mostrar un estudiante\n");
        printf("3. Mostrar todos los estudiantes\n");
        printf("4. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregarEstudiante(estudiantes, &contador);
                break;
            case 2:
                mostrarEstudiante(estudiantes, contador);
                break;
            case 3:
                mostrarTodos(estudiantes, contador);
                break;
            case 4:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }

    } while (opcion != 4);

    return 0;
}
