// db_utils.c
#include <stdio.h>
#include <ncurses.h>
#include <sqlite3.h>
#include "db_utils.h"

#define PASSWORD_MAX_LEN 72

void getUsername(char *username) {
    printw("Enter your username: ");
    refresh();
    echo();
    getnstr(username, 49); // Limit the length to prevent buffer overflow
    
}

void getPassword(char *password) {
    printw("\nEnter your password: ");
    refresh();
    noecho();
     getnstr(password, PASSWORD_MAX_LEN - 1);
    echo();
}

void getMail(char *mail) {
    printw("\nEnter your mail: ");
    refresh();
    echo();
    getnstr(mail, 49); // Limit the length to prevent buffer overflow
    
}


void registerUser(sqlite3 *db ) {
    char password[PASSWORD_MAX_LEN];
    char username[50];
    char mail[50];

    char *sql_insert = "INSERT INTO users (username, password, mail) VALUES (?, ?, ?)";
    sqlite3_stmt *stmt;
    int connect;

    getUsername(username);
    getPassword(password);
    getMail(mail);
    
   
    char *password_hash = crypt(password, "salt12");

    connect = sqlite3_prepare_v2(db, sql_insert, -1, &stmt, 0);
    if (connect != SQLITE_OK) {
        printw("SQL error: %s\n", sqlite3_errmsg(db));
         refresh();
        getch();
        return;
    }
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password_hash, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, mail, -1, SQLITE_STATIC);

    connect = sqlite3_step(stmt);
    if (connect != SQLITE_DONE) {
        printw("SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        refresh();
        getch();
        return;
    }
    sqlite3_finalize(stmt);
    printw("User registered successfully\n");
    refresh();
    getch();
}


void MainMenu(sqlite3 *db) {
    int option;
    while (1) {
        clear();
        printw("1. Register\n");
        printw("2. Login\n");
        printw("3. Show users\n");
        printw("4. Exit\n");
        printw("Enter your choice: ");
        refresh();
        scanw("%d", &option);

        switch (option) {
            case 1:
                registerUser(db);
                break;
            case 2:
                loginUser(db);
                break;
            case 3:
                display_users(db);
                break;
            case 4:
                return;
            default:
                printw("Invalid choice\n");
                refresh();
                getch();
                break;
        }
    }
}

void loginUser(sqlite3 *db) {
    char username[50];
    char password[PASSWORD_MAX_LEN];
    char *sql_select = "SELECT password FROM users WHERE username = ?";
    sqlite3_stmt *stmt;
    int connect;

    char *password_hash;
    char *password_entered;
    getUsername(username);
    getPassword(password);
    password_entered = crypt(password, "salt12");

    connect = sqlite3_prepare_v2(db, sql_select, -1, &stmt, 0);
    if (connect != SQLITE_OK) {
         printw("SQL error: %s\n", sqlite3_errmsg(db));
        refresh();
        getch();
        return;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    connect = sqlite3_step(stmt);
    if (connect == SQLITE_ROW) {
        password_hash = (char *) sqlite3_column_text(stmt, 0);
        if (strcmp(password_hash, password_entered) == 0) {
            printw("Login successful\n");
        }
        else {
            printw("Login failed\n");
        }

    }
    else{
        printw("User not found\n");
    }
    
    sqlite3_finalize(stmt);
    refresh();
    getch();

}

void display_users(sqlite3 *db){
   
    sqlite3_stmt *stmt;
    int connect;

    char *sql_query = "SELECT id, username, mail FROM users;";
    connect = sqlite3_prepare_v2(db, sql_query, -1, &stmt, 0);
    if (connect != SQLITE_OK) {
        printw("SQL error: %s\n", sqlite3_errmsg(db));
        refresh();
        getch();
        return;
    }

    clear();
    printw("ID\tUsername\tEmail\n");
    printw("------------------------------------\n");

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        char *username = (char *) sqlite3_column_text(stmt, 1);
        char *email = (char *) sqlite3_column_text(stmt, 2);
        printw("%d\t%s\t%s\n", id, username, email);
        refresh(); 
    }

     // Verificar si ocurrió un error durante la iteración
    if (connect != SQLITE_DONE) {
        printw("SQL step error: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    printw("\nPresione  cualquier tecla para continuar"); 
    refresh();
    getch();
}