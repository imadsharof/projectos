#include "student.h"

void student_to_str(char* buffer, Student s){
    int day = s.birthdate.tm_mday;
    int month = s.birthdate.tm_mon;
    int year = s.birthdate.tm_year;
    sprintf(buffer, "%u: %s %s in section %s, born on the %d/%d/%d", s.id, s.fname, s.lname, s.section, day, month + 1, year + 1900);
}