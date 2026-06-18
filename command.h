#ifndef COMMAND_H
#define COMMAND_H

#include "student.h"

typedef enum {
    SHELL_OK = 0,
    SHELL_EXIT,
    SHELL_ERR_UNKNOWN_COMMAND,
    SHELL_ERR_INVALID_ARGUMENT,
    SHELL_ERR_FILE_OPEN,
    SHELL_ERR_FILE_WRITE,
    SHELL_ERR_STUDENT_NOT_FOUND,
    SHELL_ERR_DUPLICATE_STUDENT,
    SHELL_ERR_INVALID_SCORE
}ShellResult;

ShellResult add_stu(Student **head_p,int id, const char *name, int score);
ShellResult list_stu(Student *head);
ShellResult find_stu(Student *head, int id);
ShellResult delete_stu(Student **head_p, int id);
ShellResult update_stu(Student *head, int id, int score);
ShellResult save_list(Student *head, const char *filename);
ShellResult stats(Student *head);
ShellResult clear(void);
ShellResult reload(Student **head_p);
ShellResult help(void);
ShellResult exit_p(Student *head);
#endif
