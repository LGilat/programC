#include <stdio.h>
#include <stdlib.h>
#include <crypt.h>
#include <sqlite3.h>
#include <string.h>
#include "db_utils.h"

#define PASSWORD_MAX_LEN 72




int main(int argc, char const *argv[])
{
    /**
     * Declares a SQLite3 database connection handle.
     */
    sqlite3 *db;
    char *err_msg = 0;
    int connect;

    /**
     * Stores the user's password, with a maximum length of 72 characters.
     * The `password` array holds the plaintext password entered by the user.
     * The `hash` array holds the salted and hashed version of the password.
     */
    

    char  *sql_create_table="CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT NOT NULL, password TEXT NOT NULL, mail TEXT NOT NULL);"; 
    

    connect  = sqlite3_open("users.db", &db);
    if (connect != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    connect = sqlite3_exec(db, sql_create_table, NULL, 0, &err_msg);
    if (connect != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        exit(1);
    }

    MainMenu(db);

    sqlite3_close(db);
    return 0;
}
