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

ShellResult list_stu(Student *head){
    Student *current = head;
    if(current == NULL){
        printf("No students found.\n");
        return SHELL_OK;
    }
    while(current!=NULL){
        printf("%d  %s  %d\n",current->id,current->name,current->score);
        current = current->next;
    }
    return SHELL_OK;
} 

ShellResult find_stu(Student *head,int id){
    Student *current = head;

    while(current!=NULL){
        if(current->id == id){
            printf("ID: %d\n", current->id);
            printf("Name: %s\n", current->name);
            printf("Score: %d\n", current->score);
            return SHELL_OK;
        }
        current = current->next;
    }
    return SHELL_ERR_STUDENT_NOT_FOUND;
}

ShellResult delete_stu(Student **head_p, int id){
    Student *current = *head_p;
    Student *prev = NULL;

    while(current!=NULL){
        if(current->id == id){
            if(prev == NULL){
                *head_p = current->next;
            }else{
                prev->next = current->next;
            }
            free(current);
            return SHELL_OK;
        }
        prev = current;
        current = current->next;
    }
    return SHELL_ERR_STUDENT_NOT_FOUND;
}

ShellResult update_stu(Student *head, int id, const char *name, int score){
    if(score<0||score>100){
        return SHELL_ERR_INVALID_SCORE;
    }
    Student *current = head;

    while(current!=NULL){
        if(current->id == id){
            strncpy(current->name,name,sizeof(current->name)-1);
            current->name[sizeof(current->name)-1] = '\0';
            current->score = score;
            return SHELL_OK;
        }
        current = current->next;
    }
    return SHELL_ERR_STUDENT_NOT_FOUND;
}

    


