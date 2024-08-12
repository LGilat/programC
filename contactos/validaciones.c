#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <regex.h>



bool validar_nombre(char *nombre) {
    int longitud = strlen(nombre);
    if (longitud < 4 || longitud > 70) {
        return false;
    }

    return true;
}

bool validar_apellido(char *apellido) {
    int longitud = strlen(apellido);
    if (longitud < 4 || longitud > 70) {
        return false;
    }
    return true;
}

bool validar_telefono(char *telefono) {
    int longitud = strlen(telefono);
    if (longitud != 9 )  {
        return false;
    }
    for (int i = 0; i < longitud; i++) {
        if (!isdigit(telefono[i])) {
            return false;
        }
    }
    return true;
}

bool validar_correo(char *correo) {
    
    if (strchr(correo, '@')) {
        printf("El correo electrónico contiene una arroba.\n");
        return true;
    } 
    return false;
}

bool validar_direccion(char *direccion) {
    int longitud = strlen(direccion);
    if (longitud < 3 || longitud > 70) {
        return false;
    }
    return true;
}

bool validar_fecha(char *fecha){
    regex_t regex;
    int reti;
        // Compilar el patrón de expresión regular usando clases de caracteres POSIX
    reti = regcomp(&regex, "^[0-9]{4}-[0-9]{2}-[0-9]{2}$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "No se pudo compilar el patrón\n");
        exit(1);
    }
    reti = regexec(&regex, fecha, 0, NULL, 0);
    if (!reti) {
        printf("La fecha es válida\n");
        return true;
    } 
    else if (reti == REG_NOMATCH) {
        printf("La fecha no es válida\n");
        return false;
    }
    else {
        char errbuf[100];
        regerror(reti, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Error al ejecutar el patrón: %s\n", errbuf);
        exit(1);
    }
    regfree(&regex);
    return false;
        
}







