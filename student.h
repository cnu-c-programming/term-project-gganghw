#ifndef STUDENT_H
#define STUDENT_H
typedef struct Student {
    int id;
    char name[32];
    int score;
    struct Student* next;
} Student;

Student* create(int id, const char *name, int score);

#endif