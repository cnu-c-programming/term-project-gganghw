#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

Student* create(int id, const char* name, int score) {
    Student* new_stu = (Student*)malloc(sizeof(Student));
    if (new_stu == NULL) {
        return NULL;
}

new_stu->id = id;
new_stu->score = score;
strcpy(new_stu->name, name);

new_stu->next = NULL;
return new_stu;
}