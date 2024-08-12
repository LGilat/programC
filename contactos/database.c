#include <sqlite3.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "database.h"

sqlite3* open_database() {
    sqlite3 *db = NULL;
    int connect;

    connect = sqlite3_open("contactos.db", &db);
    if (connect != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return NULL; // Devolver el código de error de SQLite
    }

    return db;
}

void throw_error(char *err_msg, sqlite3 *db) {
    fprintf(stderr, "%s: %s\n", err_msg, sqlite3_errmsg(db));
    sqlite3_close(db);
}

int create_table() { // Cambiado el tipo de retorno a int para que coincida con las llamadas de retorno
    sqlite3 *db = open_database();
    if (db == NULL) {
        return 1; // Error al abrir la base de datos
    }

    char *err_msg = 0;
    int return_code = 0;
    char *sql_create_table = "CREATE TABLE IF NOT EXISTS Contactos("
                             "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                             "nombre TEXT,"
                             "apellido TEXT,"
                             "telefono TEXT,"
                             "correo TEXT,"
                             "direccion TEXT,"
                             "fecha_agregado DATE)";

    return_code = sqlite3_exec(db, sql_create_table, NULL, 0, &err_msg);
    if (return_code != SQLITE_OK) {
        throw_error("Error al crear la tabla", db);
        return 2; // Indica error al crear la tabla
    }

    sqlite3_close(db);
    return 0; // Indica éxito
}

int insertar_contacto(char *nombre, char *apellido, char *telefono, char *correo, char *direccion, char *fecha_agregado) {
    sqlite3 *db = open_database();
    if (db == NULL) {
        return 1; // Error al abrir la base de datos
    }

    char *sql_insert = "INSERT INTO Contactos (nombre, apellido, telefono, correo, direccion, fecha_agregado) VALUES (?, ?, ?, ?, ?, ?)";
    sqlite3_stmt *stmt;

    int return_code = sqlite3_prepare_v2(db, sql_insert, -1, &stmt, 0);
    if (return_code != SQLITE_OK) {
        throw_error("Error al preparar la consulta", db);
        return 2;   
    }

    sqlite3_bind_text(stmt, 1, nombre, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, apellido, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, telefono, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, correo, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, direccion, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 6, fecha_agregado, -1, SQLITE_TRANSIENT);

    return_code = sqlite3_step(stmt);
    if (return_code != SQLITE_DONE) {
        throw_error("Error al insertar el contacto", db);
        sqlite3_finalize(stmt);
        return 2;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}