// db_utils.h
#ifndef DB_UTILS_H
#define DB_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <crypt.h>
#include <sqlite3.h>
#include <string.h>

// Declaración de la función display_users
void display_users(sqlite3 *db);
void MainMenu(sqlite3 *db);
void registerUser(sqlite3 *db);
void loginUser(sqlite3 *db);
void getUsername(char *username);
void getPassword(char *password);
void getMail(char *mail);


#endif // DB_UTILS_H
