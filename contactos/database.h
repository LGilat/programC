#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


sqlite3* open_database();
int create_table();
int insertar_contacto(char *nombre, char *apellido, char *telefono, char *correo, char *direccion, char *fecha_agregado);
void throw_error(char *err_msg, sqlite3 *db);


#endif