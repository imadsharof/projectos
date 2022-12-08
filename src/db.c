#include "db.h"

void db_add(Database *database, Student *student){
    db_size_extend(database); /// checks if logical size is bigger than physical size
    database->data[database->logical_size] = *student;
    database->logical_size++;
}

void db_delete(Database *database, int index){
    database->logical_size--;
    for (int i = index; i < database->logical_size; i++){
        database->data[i] = database->data[i+1]; /// overwrites student i with student i+1
    }
}

void db_save(Database *database, const char *path){
    FILE *file = fopen(path, "wb");
    if (!file){
        printf("Error opening file.\n");
        return;
    }
    fwrite(database->data, sizeof(Student), database->logical_size, file);
    fclose(file);
}

void db_load(Database *database, const char *path){
    FILE *file = fopen(path, "rb");
    if (!file){
        printf("Error opening file.\n");
        return;
    }
    Student* student = NULL; student = malloc(sizeof(Student));
    while (fread(student, sizeof(Student), 1, file)){ /// keeps reading file until nothing left to read
        db_add(database, student); /// adds every student read to database
    }
    fclose(file);
}

void db_init(Database *database){
    database->physical_size = 64;
    database->logical_size = 0;
    database->data = malloc(sizeof(Student) * database->physical_size);
}

void db_size_extend(Database *database){
    if (database->logical_size >= database->physical_size){ /// compares logical and physical sizes
        database->physical_size *= 2;
        database->data = realloc(database->data, sizeof(Student) * database->physical_size);
        if (!database->data) {
            perror("malloc error!\n");
            exit(1);
        }
    }
}

bool db_check(Database *database, int index, char* field, char* value){
    /// different comparisons depending on the specified field
    if (!strcmp(field, "id")){
        char *ptr;
        int id = strtol(value, &ptr, 10);
        if (database->data[index].id == id){
            return true;
        }
    } else if (!strcmp(field, "fname")){
        value[strcspn(value, "\n")] = 0;
        if (!strcmp(database->data[index].fname, value)){
            return true;
        }
    } else if (!strcmp(field, "lname")){
        value[strcspn(value, "\n")] = 0;
        if (!strcmp(database->data[index].lname, value)){
            return true;
        }
    } else if (!strcmp(field, "section")){
        value[strcspn(value, "\n")] = 0;
        if (!strcmp(database->data[index].section, value)){
            return true;
        }
    } else if (!strcmp(field, "birthdate")){
        value[strcspn(value, "\n")] = 0;
        struct tm birthdate;
        if (strptime(value, "%d/%m/%Y", &birthdate) != NULL){  
            if (database->data[index].birthdate.tm_mday == birthdate.tm_mday){
                if (database->data[index].birthdate.tm_mon == birthdate.tm_mon){
                    if (database->data[index].birthdate.tm_year == birthdate.tm_year){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void db_update(Database *database, int index, char* field_to_update, char* update_value){
    if (!strcmp(field_to_update, "id")){
        char *ptr;
        int id = strtol(update_value, &ptr, 10);
        database->data[index].id = id;
    } else if (!strcmp(field_to_update, "fname")){
        update_value[strcspn(update_value, "\n")] = 0; /// removes "\n" from update_value end
        strcpy(database->data[index].fname, update_value);
    } else if (!strcmp(field_to_update, "lname")){
        update_value[strcspn(update_value, "\n")] = 0;
        strcpy(database->data[index].lname, update_value);
    } else if (!strcmp(field_to_update, "section")){
        update_value[strcspn(update_value, "\n")] = 0;
        strcpy(database->data[index].section, update_value);
    } else if (!strcmp(field_to_update, "birthdate")){
        update_value[strcspn(update_value, "\n")] = 0;
        struct tm birthdate;
        if (strptime(update_value, "%d/%m/%Y", &birthdate) != NULL){
            database->data[index].birthdate = birthdate;
        }
    }
}