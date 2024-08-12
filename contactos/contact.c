#include <sqlite3.h>
#include <stdio.h>
#include <string.h>
#include <crypt.h>
#include <ncurses.h>
#include <stdbool.h>
#include "database.h"
#include "validaciones.h"

void MainMenu();
int watchlist_options(int option);
void prepared_data_contact();
void clear_input_buffer();

int main(int argc, char const *argv[]){
    int option=0;
    int COMENZAR = 1;
    int SALIR = 0;
    int PROGRAMA = 1;
    create_table();
    while ( PROGRAMA == COMENZAR ) {
        MainMenu();
        scanf("%d", &option);
        clear_input_buffer();
        PROGRAMA = watchlist_options(option);
        if ( PROGRAMA == SALIR ) {
            printf("Saliendo del programa...\n\n");
        }
    }

    return 0;
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void MainMenu(){
    printf("1. Agregar contacto\n");
    printf("2. Mostrar contactos\n");
    printf("3. Buscar contacto\n");
    printf("4. Eliminar contacto\n");
    printf("5. Salir\n");
    printf("Ingrese una opción: ");
}

int watchlist_options(int option){
    int accion=1;
   
   
    switch (option)
    {
        case 1:
            prepared_data_contact();
            // agregar_contacto();
            break;
        case 2:
            printf("2. Mostrar contactos\n");
            // mostrar_contactos();
            break;
        case 3:
            printf("3. Buscar contacto\n");
            break;
        case 4:
            printf("4. Eliminar contacto\n");
            break;
        case  5:
            printf("5. Salir\n");
            accion=0;
            break;

        
        default:
            printf("Opción inválida\n");
            break;
    }
    return accion;
}



void prepared_data_contact() {
    char nombre[70], apellido[70], telefono[10], correo[70], direccion[70], fecha_agregado[70];
    bool is_valid = false;

    while (!is_valid) {
        is_valid = true;
        printf("1. Agregar contacto\n");

        printf("Ingrese el nombre del contacto: ");
        if (fgets(nombre, sizeof(nombre), stdin) != NULL) {
            nombre[strcspn(nombre, "\n")] = '\0'; // Elimina el carácter de nueva línea
        }
        if (is_valid && validar_nombre(nombre)) {
            printf("El nombre es válido\n");
        } else {
            is_valid = false;
            printf("El nombre no es válido\n");
        }

        clear_input_buffer();
        printf("Ingrese el apellido del contacto: ");
        if (fgets(apellido, sizeof(apellido), stdin) != NULL) {
            apellido[strcspn(apellido, "\n")] = '\0'; // Elimina el carácter de nueva línea
        }
        if (is_valid && validar_apellido(apellido)) {
            printf("El apellido es válido\n");
        } else {
            is_valid = false;
            printf("El apellido no es válido\n");
        }

        clear_input_buffer();
        printf("Ingrese el teléfono del contacto (965254076): ");
        if (fgets(telefono, sizeof(telefono), stdin) != NULL) {
            telefono[strcspn(telefono, "\n")] = '\0'; // Elimina el carácter de nueva línea
            
        }
        if (is_valid && validar_telefono(telefono)) {
            printf("El teléfono es válido\n");
        } else {
            is_valid = false;
            printf("El teléfono no es válido %zu \n", strlen(telefono));

        }
        clear_input_buffer();
        printf("Ingrese el correo del contacto: ");
        if (fgets(correo, sizeof(correo), stdin) != NULL) {
            correo[strcspn(correo, "\n")] = '\0'; // Elimina el carácter de nueva línea
        }
        if (is_valid && validar_correo(correo)) {
            printf("El correo es válido\n");
        } else {
            is_valid = false;
            printf("El correo no es válido\n");
        }
        clear_input_buffer();
        printf("Ingrese la dirección del contacto: ");
        if (fgets(direccion, sizeof(direccion), stdin) != NULL) {
            direccion[strcspn(direccion, "\n")] = '\0'; // Elimina el carácter de nueva línea
        }
        if (is_valid && validar_direccion(direccion)) {
            printf("La dirección es válida\n");
        } else {
            is_valid = false;
            printf("La dirección no es válida\n");
        }
            clear_input_buffer();
        printf("Ingrese la fecha de agregado del contacto: ");
        if (fgets(fecha_agregado, sizeof(fecha_agregado), stdin) != NULL) {
            fecha_agregado[strcspn(fecha_agregado, "\n")] = '\0'; // Elimina el carácter de nueva línea
        }
        if (is_valid && validar_fecha(fecha_agregado)) {
            printf("La fecha es válida\n");
        } else {
            is_valid = false;
            printf("La fecha no es válida\n");
        }

        if (is_valid) {
            printf("El contacto es válido\n");
            insertar_contacto(nombre, apellido, telefono, correo, direccion, fecha_agregado);
        }
    }
}