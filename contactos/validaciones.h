#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool validar_nombre(char *nombre);
bool validar_apellido(char *apellido);
bool validar_telefono(char *telefono);
bool validar_correo(char *correo);
bool validar_direccion(char *direccion);
bool validar_fecha(char *fecha);

#endif