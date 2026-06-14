#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"
#include "student.h"

ShellResult add_stu(Student **head_p,int id, const char *name, int score) {
    if(score<0||score>100){
        return SHELL_ERR_INVALID_SCORE;
    }
    Student *current =*head_p;
    while(current!=NULL){
        if(current->id==id){
            return SHELL_ERR_DUPLICATE_STUDENT;
        }
        current = current->next;
    }

    Student *new_stu =create_student(id,name,score);
    if(new_stu == NULL){
        return SHELL_ERR_INVALID_ARGUMENT;
    }
    if(*head_p == NULL){
        *head_p = new_stu;
    }else{
        current = *head_p;
        while(current->next!=NULL){
            current = current->next;
        }
        current->next = new_stu;
    }
    return SHELL_OK;
}



    


