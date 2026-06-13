#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "file_io.h"

Student* load(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return NULL; 
    }
    char buffer[256];

    Student *head = NULL;
    Student *tail = NULL;
    while(fgets(buffer, sizeof(buffer), fp) != NULL) {
        char *id_str = strtok(buffer, ",\n");
        char *name = strtok(NULL, ",\n");
        char *score_str = strtok(NULL, ",\n");

        if(id_str == NULL || name == NULL || score_str == NULL) {
            continue;
        }
        int id = atoi(id_str);
        int score = atoi(score_str);
        Student *new_stu = create(id, name, score);
        if(new_stu == NULL) {
            continue;
        }
        if(head == NULL) {
            head = new_stu;
            tail = new_stu;
        }else {
            tail->next = new_stu;
            tail = new_stu;
        }
    }
    fclose(fp);
    return head; 
}