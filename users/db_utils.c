// db_utils.c
#include <stdio.h>
#include <ncurses.h>
#include <sqlite3.h>
#include "db_utils.h"



void getUsername(char *username) {
    printf("Enter your username: ");
    scanf("%s", username);
}

void getPassword(char *password) {
    printf("\nEnter your password: ");
    scanf("%s", password);
}

void getMail(char *mail) {
    printf("\nEnter your mail: ");
    scanf("%s", mail);
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
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password_hash, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, mail, -1, SQLITE_STATIC);

    connect = sqlite3_step(stmt);
    if (connect != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        exit(1);
    }
    sqlite3_finalize(stmt);
    printf("User registered successfully\n");
}


void MainMenu(sqlite3 *db) {
    int option;
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &option);
    switch (option) {
        case 1:
            registerUser(db);
            break;
        case 2:
            loginUser(db);
            printf("Login\n");
            break;
        case 3:
            exit(0);
        default:
            printf("Invalid choice\n");
            break;
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
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    connect = sqlite3_step(stmt);
    if (connect == SQLITE_ROW) {
        password_hash = (char *) sqlite3_column_text(stmt, 0);
        if (strcmp(password_hash, password_entered) == 0) {
            printf("Login successful\n");
        }
        else {
            printf("Login failed\n");
        }

    }
    
    sqlite3_finalize(stmt);

}