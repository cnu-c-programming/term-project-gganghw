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

ShellResult stu_list(Student *head){
    Student *current = head;
    if(current == NULL){
        printf("No students found.\n");
        return SHELL_OK;
    }
    printf("%-5s %-15s %s\n", "ID", "Name", "Score");
    while(current!=NULL){
        printf("%-5d %-15s %d\n", current->id, current->name, current->score);
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

ShellResult update_stu(Student *head, int id, int score){
    if(score<0||score>100){
        return SHELL_ERR_INVALID_SCORE;
    }
    Student *current = head;

    while(current!=NULL){
        if(current->id == id){
            current->score = score;
            return SHELL_OK;
        }
        current = current->next;
    }
    return SHELL_ERR_STUDENT_NOT_FOUND;
}
ShellResult stats(Student *head){
    if(head==NULL){
        printf("No student data available.\n");
        return SHELL_OK;
    }
    int count = 0;
    int sum = 0;
    int max =-1;
    int min =101;
    Student *current = head;
    while(current!=NULL){
        count++;
        sum+=current->score;
        if(current->score>max){
            max = current->score;
        }
        if(current->score<min){
            min = current->score;
        }
        current = current->next;
    }
    printf("Count: %d\n", count);
    printf("Average: %.1f\n", (float)sum/count);
    printf("Max: %d\n", max);
    printf("Min: %d\n", min);
    return SHELL_OK;
}
ShellResult clear(void){
    printf("\033[2J\033[H");
    return SHELL_OK;
}
ShellResult save_list(Student *head){
    int count = 0;
    Student *current = head;
    while(current!=NULL){
        count++;
        current = current->next;
    }
    save(head,"students.csv");
    printf("Saved %d students to students.csv.\n", count);
    return SHELL_OK;
}
ShellResult reload(Student **head_p){
    Student *current = *head_p;
    Student *next;
    while(current!=NULL){
        next = current->next;
        free(current);
        current = next;
    }
    *head_p = NULL;
    int count = load("students.csv", head_p);
    printf("Reloaded %d students from students.csv.\n", count);
    return SHELL_OK;
}
ShellResult help(void){
    printf("Commands:\n");
    printf("save                    Save students to CSV\n");
    printf("reload                  Reload students from CSV\n");
    printf("add <id> <name> <score> Add a student\n");
    printf("delete <id>             Delete a student\n");
    printf("update <id> <score>     Update student score\n");
    printf("find <id>               Find student by ID\n");
    printf("list                    List all students\n");
    printf("stats                   Show statistics\n");
    printf("clear                   Clear screen\n");
    printf("exit                    Exit program\n");
    return SHELL_OK;
}
ShellResult exit(Student *head){
    Student *current = head;
    Student *next;
    while(current!=NULL){
        next = current->next;
        free(current);
        current = next;
    }
    printf("Goodbye.\n");
    return SHELL_EXIT;
}
    


