#ifndef _DB_H
#define _DB_H

#include "parsing.h"

typedef struct Database {
    Student *data;
    size_t logical_size;
    size_t physical_size;
} Database;

/** 
 * Add a student to a database.
 * Example:
 * ```
 * Student *student = NULL;
 * student = malloc(sizeof(Student));
 * Database *database = NULL;
 * database = malloc(sizeof(Database));
 * db_init(database);
 * db_add(database, student);
 * ```
 * @return: void
 **/
void db_add(Database *database, Student *student);

/** 
 * Remove a student from a database using their index.
 * Example:
 * ```
 * int index = 420;
 * Database *database = NULL;
 * database = malloc(sizeof(Database));
 * db_init(database);
 * db_delete(database, index);
 * ```
 * @return: void
 **/
void db_delete(Database *database, int index);

/** 
 * Save a database to a specified path.
 * Example:
 * ```
 * char* path = "/home/haythem/Documents/INFO-F201/database.bin";
 * Database *database = NULL;
 * database = malloc(sizeof(Database));
 * db_init(database);
 * db_save(database, path);
 * ```
 * @return: void
 **/
void db_save(Database *database, const char *path);

/** 
 * Load a database from a specified path.
 * Example:
 * ```
 * char* path = "/home/haythem/Documents/INFO-F201/database.bin";
 * Database *database = NULL;
 * database = malloc(sizeof(Database));
 * db_init(database);
 * db_load(database, path);
 * ```
 * @return: void
 **/
void db_load(Database *database, const char *path);

/** 
 * Initiate a database in memory.
 * Example:
 * ```
 * Database *database = NULL;
 * database = malloc(sizeof(Database));
 * db_init(database);
 * ```
 * @return: void
 **/
void db_init(Database *database);

/** 
 * Extend the physical memory allocated to a database if logical memory is full.
 * Example:
 * ```
 * Database *database = NULL;
 * database = malloc(sizeof(Database));
 * db_init(database);
 * db_size_extend(database);
 * ```
 * @return: void
 **/
void db_size_extend(Database *database);

/** 
 * Check if a student corresponds to the specified inputs using their index.
 * Example:
 * ```
 * Database *database = NULL;
 * database = malloc(sizeof(Database));
 * db_init(database);
 * int index = 420;
 * char* field = "fname";
 * char* value = "Haythem";
 * db_check(database, index, field, value);
 * ```
 * @return: true if student corresponds to the specified inputs, false otherwise
 **/
bool db_check(Database *database, int index, char* field, char* value);

/** 
 * Update a student with the specified inputs using their index.
 * Example:
 * ```
 * Database *database = NULL;
 * database = malloc(sizeof(Database));
 * db_init(database);
 * int index = 420;
 * char* field_to_update = "id";
 * char* update_value = "123456";
 * db_update(database, index, field_to_update, update_value);
 * ```
 * @return: void
 **/
void db_update(Database *database, int index, char* field_to_update, char* update_value);

#endif