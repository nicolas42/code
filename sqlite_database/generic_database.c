// gcc sqlite3.o generic_database.c && ./a.out
// compile sqlite by downloading an amalgamated version and doing  "gcc -c sqlite.c" to get the object file.

#include <stdio.h>
#include "sqlite3.h"

// Define maximum length for strings
#define MAX_LENGTH 50

// Callback function to handle results of queries
int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

// Function to open or create a database
sqlite3 *open_database(const char *db_name) {
    sqlite3 *db;
    int rc = sqlite3_open(db_name, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }
    return db;
}

// Function to close a database
void close_database(sqlite3 *db) {
    sqlite3_close(db);
}

// Function to create a table
void create_table(sqlite3 *db) {
    char *sql = "CREATE TABLE IF NOT EXISTS elements("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "name TEXT NOT NULL,"
                "value TEXT NOT NULL);";
    int rc = sqlite3_exec(db, sql, callback, 0, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Table created successfully\n");
    }
}

// Function to insert a row into the table
void insert_row(sqlite3 *db, const char *name, const char *value) {
    char sql[MAX_LENGTH * 2 + 100];
    sprintf(sql, "INSERT INTO elements (name, value) VALUES ('%s', '%s');", name, value);
    int rc = sqlite3_exec(db, sql, callback, 0, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Row inserted successfully\n");
    }
}

// Function to select all rows from the table
void select_rows(sqlite3 *db) {
    char *sql = "SELECT * FROM elements;";
    int rc = sqlite3_exec(db, sql, callback, 0, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }
}

// Function to update a row in the table
void update_row(sqlite3 *db, int id, const char *name, const char *value) {
    char sql[MAX_LENGTH * 2 + 100];
    sprintf(sql, "UPDATE elements SET name = '%s', value = '%s' WHERE id = %d;", name, value, id);
    int rc = sqlite3_exec(db, sql, callback, 0, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Row updated successfully\n");
    }
}

// Function to delete a row from the table
void delete_row(sqlite3 *db, int id) {
    char sql[100];
    sprintf(sql, "DELETE FROM elements WHERE id = %d;", id);
    int rc = sqlite3_exec(db, sql, callback, 0, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Row deleted successfully\n");
    }
}

int main() {
    sqlite3 *db = open_database("example.db");
    if (db == NULL) {
        return 1;
    }

    create_table(db);

    insert_row(db, "Example 1", "Value 1");
    insert_row(db, "Example 2", "Value 2");
    select_rows(db);

    update_row(db, 1, "Updated 1", "Updated Value 1");
    delete_row(db, 2);
    select_rows(db);

    close_database(db);

    return 0;
}
