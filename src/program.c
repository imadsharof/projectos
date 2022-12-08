#include "program.h"

/** 
 * Function executed by threads created in the "manage_*_query" functions.
 * Copies the content of the temporary results file to the effective log file.
 * ```
 * @return: void
 **/
void *copy_thread(void *data){
    int *retour = (int *) malloc (sizeof (int));
    char* filename = data;
    char copy_token;
    FILE* file = fopen(filename, "a+"); /// opens the file in "a+" to append instead of overwriting
    FILE* tmp_file = fopen("tmp_log.txt", "r");
    while ((copy_token = fgetc(tmp_file)) != EOF){ /// copying character by character until end of file
        fputc(copy_token, file);
    }
    fclose(file);
    fclose(tmp_file);
    *retour = 1;
    pthread_exit(retour);
}

void manage_select_query(Database *database, char* query, char* field, char* value){
    struct timespec start, end, now;
    clock_gettime(CLOCK_REALTIME, &start); /// starting the timer to know the execution time
    int counter = 0, i;
    char path[256];
    FILE *tmp_file = fopen("tmp_log.txt", "a+");
    if (parse_selectors(query, field, value)){
        for (i = 0; i < database->logical_size; i++){
            if (db_check(database, i, field, value)){
                counter++;
                char buffer[100];
                student_to_str(buffer, database->data[i]);
                fprintf(tmp_file, "%s\n", buffer);
            }
        }
    }
    fclose(tmp_file);
    clock_gettime(CLOCK_REALTIME, &now);
    long now_ns = now.tv_nsec + 1e9 * now.tv_sec;
    sprintf(path, "logs/%li-select.txt", now_ns); /// creating the corresponding log file with the timestamp
    FILE *file = fopen(path, "a+");
    clock_gettime(CLOCK_REALTIME, &end); /// ending the timer to know the execution time
    double time_spent = (end.tv_sec - start.tv_sec) * 1e3 + (end.tv_nsec - start.tv_nsec) / 1e6;
    fprintf(file, "Query \"%s %s=%s\" completed in %fms with %i results.\n", "select", field, value, time_spent, counter);
    fclose(file);
    int *thread_return;
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, copy_thread, path); /// creating the thread to copy the text saved in the temp file
    pthread_join(thread_id, (void **) &thread_return);
    free(thread_return);
    remove("tmp_log.txt"); /// removing the temporary log file
}

void manage_delete_query(Database *database, char* query, char* field, char* value){
    struct timespec start, end, now;
    clock_gettime(CLOCK_REALTIME, &start); /// starting the timer to know the execution time
    int counter = 0, i;
    char copy_token, path[256];
    FILE *tmp_file = fopen("tmp_log.txt", "a+");
    if (parse_selectors(query, field, value)){
        for (i = 0; i < database->logical_size; i++){
            if (db_check(database, i, field, value)){
                counter++;
                char buffer[100];
                student_to_str(buffer, database->data[i]);
                fprintf(tmp_file, "%s\n", buffer);
                db_delete(database, i); i--; /// decrement i to avoid missing adjacent students to delete
            }
        }
    }
    fclose(tmp_file);
    clock_gettime(CLOCK_REALTIME, &now);
    long now_ns = now.tv_nsec + 1e9 * now.tv_sec;
    sprintf(path, "logs/%li-delete.txt", now_ns); /// creating the corresponding log file with the timestamp
    FILE *file = fopen(path, "a+");
    clock_gettime(CLOCK_REALTIME, &end);  /// ending the timer to know the execution time
    double time_spent = (end.tv_sec - start.tv_sec) * 1e3 + (end.tv_nsec - start.tv_nsec) / 1e6;
    fprintf(file, "Query \"%s %s=%s\" completed in %fms with %i results.\n", "delete", field, value, time_spent, counter);
    fclose(file);
    int *thread_return;
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, copy_thread, path); /// creating the thread to copy the text saved in the temp file
    pthread_join(thread_id, (void **) &thread_return);
    free(thread_return);
    remove("tmp_log.txt"); /// removing the temporary log file
}

void manage_insert_query(Database *database, char* query, char* fname, char* lname, unsigned* id, char* section, struct tm* birthdate){
    struct timespec start, end, now;
    clock_gettime(CLOCK_REALTIME, &start); /// starting the timer to know the execution time
    int counter = 0;
    char copy_token, path[256];
    FILE *tmp_file = fopen("tmp_log.txt", "a+");
    char request[256]; strcpy(request, query); request[strlen(request)-1] = 0;
    if (parse_insert(query, fname, lname, id, section, birthdate)){
        Student* new_student = NULL; new_student = malloc(sizeof(Student));
        new_student->id = *id;
        strncpy(new_student->fname, fname, 64);
        strncpy(new_student->lname, lname, 64);
        strncpy(new_student->section, section, 64);
        new_student->birthdate.tm_mday = birthdate->tm_mday;
        new_student->birthdate.tm_mon = birthdate->tm_mon;
        new_student->birthdate.tm_year = birthdate->tm_year;
        db_add(database, new_student);
        char buffer[100];
        student_to_str(buffer, *new_student);
        fprintf(tmp_file, "%s\n", buffer);
        counter++;
    }
    fclose(tmp_file);
    clock_gettime(CLOCK_REALTIME, &now);
    long now_ns = now.tv_nsec + 1e9 * now.tv_sec;
    sprintf(path, "logs/%li-insert.txt", now_ns); /// creating the corresponding log file with the timestamp
    FILE *file = fopen(path, "a+");
    clock_gettime(CLOCK_REALTIME, &end);
    double time_spent = (end.tv_sec - start.tv_sec) * 1e3 + (end.tv_nsec - start.tv_nsec) / 1e6;
    fprintf(file, "Query \"%s %s\" completed in %fms with %i results.\n", "insert", request, time_spent, counter);
    fclose(file);
    int *thread_return;
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, copy_thread, path); /// creating the thread to copy the text saved in the temp file
    pthread_join(thread_id, (void **) &thread_return);
    free(thread_return);
    remove("tmp_log.txt"); /// removing the temporary log file
}

void manage_update_query(Database *database, char* query, char* field_filter, char* value_filter, char* field_to_update, char* update_value){
    struct timespec start, end, now;
    clock_gettime(CLOCK_REALTIME, &start); /// starting the timer to know the execution time
    int counter = 0, i;
    char copy_token, path[256];
    FILE *tmp_file = fopen("tmp_log.txt", "a+");
    char request[256]; strcpy(request, query); request[strlen(request)-1] = 0;
    if (parse_update(query, field_filter, value_filter, field_to_update, update_value)){
        for (i = 0; i < database->logical_size; i++){
            if (db_check(database, i, field_filter, value_filter)){
                counter++;
                db_update(database, i, field_to_update, update_value);
                char buffer[100];
                student_to_str(buffer, database->data[i]);
                fprintf(tmp_file, "%s\n", buffer);
            }
        }
    }
    fclose(tmp_file);
    clock_gettime(CLOCK_REALTIME, &now);
    long now_ns = now.tv_nsec + 1e9 * now.tv_sec;
    sprintf(path, "logs/%li-update.txt", now_ns); /// creating the corresponding log file with the timestamp
    FILE *file = fopen(path, "a+");
    clock_gettime(CLOCK_REALTIME, &end);
    double time_spent = (end.tv_sec - start.tv_sec) * 1e3 + (end.tv_nsec - start.tv_nsec) / 1e6;
    fprintf(file, "Query \"%s %s\" completed in %fms with %i results.\n", "update", request, time_spent, counter);
    fclose(file);
    int *thread_return;
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, copy_thread, path); /// creating the thread to copy the text saved in the temp file
    pthread_join(thread_id, (void **) &thread_return);
    free(thread_return);
    remove("tmp_log.txt"); /// removing the temporary log file
}