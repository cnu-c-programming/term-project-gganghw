#ifndef FILE_IO_H
#define FILE_IO_H

#include "student.h"

Student* load(const char *filename);
void save(Student *head, const char *filename);
#endif // FILE_IO_H