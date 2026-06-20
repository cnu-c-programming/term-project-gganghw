/*
 * main.c  –  Mini Student Shell
 *
 * TODO: Implement admin_shell and client_shell.
 *
 * Build:
 *   make admin   →  admin_shell  (compiled with -DADMIN_MODE)
 *   make client  →  client_shell (compiled with -DCLIENT_MODE)
 *
 * Usage:
 *   ./admin_shell [students.csv]
 *   ./admin_shell -f commands.txt [students.csv]
 *   ./client_shell [students.csv]
 *   ./client_shell -f commands.txt [students.csv]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* TODO: Add your own header includes here */
#include "student.h"
#include "file_io.h"
#include "command.h"

const char *current_csv_path = NULL;
/* ---------------------------------------------------------------
* TODO: Implement the interactive shell loop.
 *   - Print a prompt and read a line from stdin.
 *   - Parse the line into a command and arguments.
 *   - Dispatch to the appropriate handler function.
 *   - Loop until the user types "exit" or EOF.
 * --------------------------------------------------------------- */
void run_shell(Student **head) {
    /* TODO */
    char line[256];
    while(1){
#ifdef ADMIN_MODE
        printf("admin> ");
#else
        printf("client> ");
#endif
        if(fgets(line, sizeof(line), stdin) == NULL) {
            exit_p(*head);
            break;
        }
        char *cmd = strtok(line, " \n");

        if(cmd == 0) {
            continue;
        }

        if(strcmp(cmd, "exit")==0){
            exit_p(*head);
            break;
        }else if(strcmp(cmd, "help")==0){
            help();
        }else if(strcmp(cmd, "clear")==0){
            clear();
        }else if(strcmp(cmd, "list")==0){
            list_stu(*head);
        }else if(strcmp(cmd, "stats")==0){
            stats(*head);
        }else if(strcmp(cmd, "reload")==0){
            reload(head);
        }else if(strcmp(cmd, "find")==0){
            char *id_str = strtok(NULL, " \n");
            if(id_str == NULL) {
                printf("Error: missing arguments.\n");
            }else{
                ShellResult res = find_stu(*head, atoi(id_str));
                if(res == SHELL_ERR_STUDENT_NOT_FOUND){
                    printf("Error: student not found.\n");
                }
            }
        }
#ifdef ADMIN_MODE
        else if(strcmp(cmd, "save") == 0) {
                save_list(*head, current_csv_path);
        }else if(strcmp(cmd, "delete") == 0){
            char *id_str = strtok(NULL, " \n");
            if(id_str == NULL){
                printf("Error: missing arguments.\n");
            }else{
                ShellResult res = delete_stu(head, atoi(id_str));
                if(res == SHELL_OK){
                    printf("Student deleted.\n");
                }else if(res == SHELL_ERR_STUDENT_NOT_FOUND){
                    printf("Error: student not found.\n");
                }
            }
        }else if(strcmp(cmd, "update") == 0){
            char *id_str = strtok(NULL, " \n");
            char *score_str = strtok(NULL, " \n");
            if(id_str == NULL || score_str == NULL) {
                printf("Error: missing arguments.\n");
            }else{
                ShellResult res = update_stu(*head, atoi(id_str), atoi(score_str));
                if(res == SHELL_OK){
                    printf("Student updated.\n");
                }else if(res == SHELL_ERR_STUDENT_NOT_FOUND){
                    printf("Error: student not found.\n");
                }else if(res == SHELL_ERR_INVALID_SCORE){
                    printf("Error: invalid score.\n");
                }
            }
        }else if(strcmp(cmd, "add") == 0){
            char *id_str = strtok(NULL, " \n");
            char *name = strtok(NULL, " \n");
            char *score_str = strtok(NULL, " \n");

            if(id_str == NULL || name == NULL || score_str == NULL) {
                printf("Error: missing arguments.\n");
            }else{
                ShellResult res = add_stu(head, atoi(id_str), name, atoi(score_str));
                if(res == SHELL_OK){
                    printf("Student added.\n");
                }else if(res == SHELL_ERR_DUPLICATE_STUDENT){
                    printf("Error: duplicate ID.\n");
                }else if(res == SHELL_ERR_INVALID_SCORE){
                    printf("Error: invalid score.\n");
                }
            }
        }
#endif
        else {
        printf("Unknown command or permission denied.\n");
        }
    }
}

/* ---------------------------------------------------------------
 * TODO: Implement batch mode – read commands from a file.
 *   - Open cmd_file for reading.
 *   - Execute each line as a command (same logic as run_shell).
 *   - Close the file when done.
 * --------------------------------------------------------------- */
void run_command_file(const char *cmd_file, Student **head) {
    /* TODO */
    FILE *fp = fopen(cmd_file, "r");
    if(fp == NULL){
        perror("파일을 열 수 없습니다");
        return;
    }
    char buffer[256];
    int line_num = 0;

    while(fgets(buffer, sizeof(buffer), fp) != NULL){
        int len = strlen(buffer);//수정
        if(len > 0 && buffer[len - 1] == '\n'){
            buffer[len - 1] = '\0';
        }
        if(strlen(buffer) == 0 || buffer[0] == '#'){
            continue;
        }
       int i = 0;
        while(buffer[i] == ' ' || buffer[i] == '\t') {
            i++;
        }
        if(buffer[i] == '\0' || buffer[i] == '#'){
            continue;
        }
        line_num++;
        printf("[command file:%d] %s\n", line_num, buffer);

       char *cmd = strtok(buffer, " \n");
        if (cmd == NULL) continue;

        if(strcmp(cmd, "exit") == 0){
            exit_p(*head);
            break;
        }else if(strcmp(cmd, "help") == 0){
            help();
        }else if(strcmp(cmd, "clear") == 0){
            clear();
        }else if(strcmp(cmd, "list") == 0){
            list_stu(*head);
        }else if(strcmp(cmd, "stats") == 0){
            stats(*head);
        }else if(strcmp(cmd, "reload") == 0){
            reload(head);
        }else if(strcmp(cmd, "find") == 0){
            char *id_str = strtok(NULL, " \n");
             if(id_str == NULL) {
                printf("Error: missing arguments. Skipped line %d.\n", line_num);
            }else{
                ShellResult res = find_stu(*head, atoi(id_str));
                if(res == SHELL_ERR_STUDENT_NOT_FOUND){
                    printf("Error: student not found. Skipped line %d.\n", line_num);
                }
            }
        }
#ifdef ADMIN_MODE
        else if(strcmp(cmd, "save") == 0){
                save_list(*head, current_csv_path);
        }else if(strcmp(cmd, "delete") == 0){
            char *id_str = strtok(NULL, " \n");
            if(id_str == NULL){
                printf("Error: missing arguments. Skipped line %d.\n", line_num);
            }else{
                ShellResult res = delete_stu(head, atoi(id_str));
                if(res == SHELL_ERR_STUDENT_NOT_FOUND){
                    printf("Error: student not found. Skipped line %d.\n", line_num);
                }else if(res == SHELL_OK){
                    printf("Student deleted.\n");
                }
            }
        }else if(strcmp(cmd, "update") == 0){
            char *id_str = strtok(NULL, " \n");
            char *score_str = strtok(NULL, " \n");
            if(id_str == NULL || score_str == NULL){
                printf("Error: missing arguments. Skipped line %d.\n", line_num);
            }else{
                ShellResult res = update_stu(*head, atoi(id_str), atoi(score_str));
                if(res == SHELL_ERR_STUDENT_NOT_FOUND){
                    printf("Error: student not found. Skipped line %d.\n", line_num);
                }else if(res == SHELL_ERR_INVALID_SCORE){
                    printf("Error: invalid score. Skipped line %d.\n", line_num);
                }else if(res == SHELL_OK){
                    printf("Student updated.\n");
                }
            }
        }else if(strcmp(cmd, "add") == 0){
            char *id_str = strtok(NULL, " \n");
            char *name = strtok(NULL, " \n");
            char *score_str = strtok(NULL, " \n");

            if(id_str == NULL || name == NULL || score_str == NULL){
                    printf("Error: missing arguments. Skipped line %d.\n", line_num);
            }else{
                ShellResult res = add_stu(head, atoi(id_str), name, atoi(score_str));
                if(res == SHELL_ERR_DUPLICATE_STUDENT   ){
                    printf("Error: duplicate ID. Skipped line %d.\n", line_num);
                }else if(res == SHELL_ERR_INVALID_SCORE){
                    printf("Error: invalid score. Skipped line %d.\n", line_num);
                }else if(res == SHELL_OK){
                    printf("Student added.\n"); 
                }
            }
        }
#endif
        else{
            printf("Unknown command or permission denied. Skipped line %d.\n", line_num);
        }
    }
    fclose(fp);
}

int main(int argc, char *argv[]) {
    const char *csv_path  = NULL; /* default CSV file */
    const char *cmd_file  = NULL;           /* -f <file> argument */

    /* TODO: Parse command-line arguments.
     *   Supported flags:
     *     -f <file>   run commands from <file> instead of stdin
     *   Remaining positional argument (if any): path to students CSV.
     */
     for(int i = 1; i<argc;i++){
        if(strcmp(argv[i], "-f")== 0 && i + 1 < argc){
            cmd_file = argv[++i];
        }else{
            csv_path = argv[i];
        }
     }
     if(csv_path == NULL){
        #ifdef ADMIN_MODE
            printf("Usage: ./admin_shell <csv_file> [-f command_file]\n");
        #else
            printf("Usage: ./client_shell <csv_file> [-f command_file]\n");
        #endif
            return 1;
     }
    (void)argc;
    (void)argv;

    Student *head = load(csv_path);
    current_csv_path = csv_path;

    int count = 0;
    Student *curr = head;
    while(curr != NULL) {
        count++;
        curr = curr->next;
    } 
#ifdef ADMIN_MODE
    printf("[Admin Program]\n");
#else
    printf("[Client Program]\n");
#endif
    printf("Loaded %d students from %s.\n", count, csv_path);  

#ifdef ADMIN_MODE
    /* Admin shell: supports add, delete, update, save, load, sort, list, find, help, exit */
    if(cmd_file) {
        run_command_file(cmd_file, &head);
    } else {
        run_shell(&head);
    }

#elif defined(CLIENT_MODE)
    /* Client shell: supports find, list, help, exit  (read-only) */
    if(cmd_file) {
        run_command_file(cmd_file, &head);
    } else {
        run_shell(&head);
    }

#else
#error "Define either -DADMIN_MODE or -DCLIENT_MODE when compiling."
#endif

    return 0;
}
