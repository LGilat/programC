#include <stdio.h>
#include <stdlib.h>
#define FILAS 5
#define COLUMNAS 5

void asignar_memstring(char **nombres, int filas, int columnas);

void entrada_nombres(char **nombres, int filas);

void mostrar_nombres(char **nombres, int filas);


int main(int argc, char const *argv[])
{
    char **nombres = (char **) malloc(FILAS * sizeof(char *));
    if (nombres == NULL) {
        printf("Error al asignar memoria\n");
        return 1;
    }

    asignar_memstring(nombres, FILAS, COLUMNAS);
    
    //Si tiene asignada la memoria, se pide los nombres por teclado 
    if (nombres != NULL) {
        entrada_nombres(nombres, FILAS);
    }

    if (nombres != NULL) {
        printf("\n");
        printf("\n");
        printf("Los nombres ingresados son:\n");
        mostrar_nombres(nombres, FILAS);
    }
    /* code */
    return 0;
}


void asignar_memstring(char **nombres, int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        nombres[i] = (char *) malloc(columnas * sizeof(char));
        if (nombres[i] == NULL) {
            printf("Error al asignar memoria\n");
            exit(1);
        }
    }
}

void entrada_nombres(char **nombres, int filas) {
    for (int i = 0; i < filas; i++) {
        printf("Ingrese el nombre %d: ", i + 1);
        scanf(" %[^\n]", nombres[i]);
    }
}

void mostrar_nombres(char **nombres, int filas) {
    for (int i = 0; i < filas; i++) {
        printf("Nombre completo %d: %s\n", i + 1, nombres[i]);
    }
}