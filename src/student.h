#ifndef _STUDENT_H
#define _STUDENT_H

#define __USE_XOPEN
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <ctype.h>
#include <pthread.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

typedef struct Student {
    unsigned id;
    char fname[64];
    char lname[64];
    char section[64];
    struct tm birthdate;
} Student;

/** 
 * Convert information contained in Student variable to character array.
 * Example:
 * ```
 * char buffer[100];
 * Student student;
 * student_to_str(buffer, student);
 * ```
 * @return: void
 **/
void student_to_str(char* buffer, Student student);

#endif