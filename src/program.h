#ifndef _PROGRAM_H
#define _PROGRAM_H

#include "db.h"

/** 
 * Searches a database using specified inputs,
 * and writes a log file in "./logs/" with all the results.
 * Example:
 * ```
 * Database *database = NULL;
 * database = malloc(sizeof(Database));
 * db_init(database);
 * char* query = "fname=Haythem";
 * char field[64], value[64];
 * manage_select_query(database, query, field, value);
 * ```
 * @return: void
 **/
void manage_select_query(Database *database, char* query, char* field, char* value);

/** 
 * Deletes a student from a database using specified inputs,
 * and writes a log file in "./logs/" with all the results.
 * Example:
 * ```
 * Database *database = NULL;
 * database = malloc(sizeof(Database));
 * db_init(database);
 * char* query = "fname=Haythem";
 * char field[64], value[64];
 * manage_delete_query(database, query, field, value);
 * ```
 * @return: void
 **/
void manage_delete_query(Database *database, char* query, char* field, char* value);

/** 
 * Inserts a new student in a database using specified inputs,
 * and writes a log file in "./logs/" with all the results.
 * Example:
 * ```
 * Database *database = NULL;
 * database = malloc(sizeof(Database));
 * db_init(database);
 * char* query = "Haythem Boughardain 474979 polytech 28/04/2001";
 * char fname[64], lname[64], section[64];
 * unsigned id;
 * struct tm birthdate;
 * manage_insert_query(database, query, fname, lname, &id, section, &birthdate);
 * ```
 * @return: void
 **/
void manage_insert_query(Database *database, char* query, char* fname, char* lname, unsigned* id, char* section, struct tm* birthdate);

/** 
 * Updates a student in a database using specified inputs,
 * and writes a log file in "./logs/" with all the results.
 * Example:
 * ```
 * Database *database = NULL;
 * database = malloc(sizeof(Database));
 * db_init(database);
 * char* query = "fname=Haythem set id=123456";
 * char field_filter[64], value_filter[64], field_to_update[64], update_value[64];
 * manage_update_query(database, query, field_filter, value_filter, field_to_update, update_value);
 * ```
 * @return: void
 **/
void manage_update_query(Database *database, char* query, char* field_filter, char* value_filter, char* field_to_update, char* update_value);

#endif