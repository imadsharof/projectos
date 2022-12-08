#ifndef _PARSING_H
#define _PARSING_H

#include "student.h"

/** 
 * Parse the arguments of an update query.
 * Example:
 * ```
 * char* input = "update id=474979 set fname=Haythem";
 * parse_command(input, command, query);
 * parse_update(query, field_filter, value_filter, field_to_update, update_value);
 * ```
 * @return: true if the parsing was successful, false otherwise
 **/
bool parse_update(char* query, char* field_filter, char* value_filter, char* field_to_update, char* update_value);

/**
 * Parse the arguments of an insert query.
 * Example:
 * ```
 * char* input = "insert Haythem Boughardain polytech 28/04/2001";
 * parse_command(input, command, query);
 * parse_insert(query, fname, lname, &id, section, &birthdate);
 * ```
 * @return: true if the parsing was successful, false otherwise
 **/
bool parse_insert(char* query_arguments, char* fname, char* lname, unsigned* id, char* section, struct tm* birthdate);

/** 
 * Parse field=value selectors.
 * Example:
 * ```
 * char* query = "fname=Haythem";
 * parse_selectors(query, field, value);
 * ```
 * @return: true if the parsing was successful, false otherwise
 **/
bool parse_selectors(char* query, char* field, char* value);

/** 
 * Parse the command from the unaltered input.
 * Example:
 * ```
 * char* input = "update id=474979 set fname=Haythem";
 * parse_command(input, command, query);
 * ```
 * @return: true if the parsing was successful, false otherwise
 **/
bool parse_command(char* input, char* command, char* query);

#endif