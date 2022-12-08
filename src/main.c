#include "program.h"

/** 
 * Haythem Boughardain (matricule : 474979).
 * INFO-F201 - Systèmes d'exploitation : Programmation système en C
 * This project aims to create an efficient database management program which
 * allows users to create, load, save and modify databases easily.
 **/

bool active_program = 1; /// bool which specifies if program should be active or not

void stop_program(int signo){ /// signal handler to catch Ctrl+C from user
    if (signo == SIGINT){
        active_program = 0; /// sets active_program to false to leave "while" loop in main()
        fclose(stdin); /// closes stdin in case user presses Ctrl+C during fgets()
    }
}

int main(int argc, char** argv){
    signal(SIGINT, stop_program); /// specifies to signal handler which signal to catch
    printf("Welcome to the Tiny Database!\n");
    if (argc > 2){
        printf("Too many arguments!\nExiting the program...\n");
        return 1;
    }
    Database *database; database = malloc(sizeof(Database));
    db_init(database);
    char* db_path = "output_db.bin"; /// sets default output path in case there is no specified database
    if (argc == 2){
        printf("Loading the database...\n");
        if (access(argv[1], F_OK) != -1){ /// checks if specified database is accessible
            db_path = argv[1];
            db_load(database, argv[1]);
            printf("Done!\n");
        } else {
            printf("The specified file is inaccessible.\nInitiating an empty database...\n");
        }
    }
    if (access("logs", F_OK) == -1){ /// checks if logs folder does not exist, in which case it is created
        mkdir("logs", 0777);
    }
    char input[100], command[64], query[64], field[64], value[64], field_to_update[64], update_value[64], fname[64], lname[64], section[64];
    unsigned id; struct tm birthdate;
    printf("Please enter your requests.\n");
    while ((active_program) && (printf("> ")) && (fgets(input, 100, stdin) != NULL)){
        /// main "while" loop which will act as terminal when program is executed
        if (parse_command(input, command, query)){
            if (!strcmp(command, "select")){
                manage_select_query(database, query, field, value);
            } else if (!strcmp(command, "delete")){
                manage_delete_query(database, query, field, value);
            } else if (!strcmp(command, "insert")){
                manage_insert_query(database, query, fname, lname, &id, section, &birthdate);
            } else if (!strcmp(command, "update")){
                manage_update_query(database, query, field, value, field_to_update, update_value);
            }
        }
    }
    printf("Comitting database changes to the disk...\n");
    db_save(database, db_path); /// saves the database after the "while" loop is finished (when pressing Ctrl+C for example)
    printf("Done.\n");
    free(database);
    return 0;
}