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
/* #include "command.h"  */

/* ---------------------------------------------------------------
 * TODO: Implement the interactive shell loop.
 *   - Print a prompt and read a line from stdin.
 *   - Parse the line into a command and arguments.
 *   - Dispatch to the appropriate handler function.
 *   - Loop until the user types "exit" or EOF.
 * --------------------------------------------------------------- */
void run_shell(const char *csv_path) {
    /* TODO */
    char line[256];
    while(1){
#ifdef ADMIN_MODE
        printf("admin> ");
#else
        printf("client> ");
#endif
        if(fgets(line, sizeof(line), stdin) == NULL) {
            printf("Bye!\n");
            break;
        }
        char *cmd = strtok(line, " \n");

        if(cmd == 0) {
            continue;
        }
        if(strcmp(cmd, "exit")==0){
            printf("Bye!\n");
            break;
        }
    }
    (void)csv_path;
}

/* ---------------------------------------------------------------
 * TODO: Implement batch mode – read commands from a file.
 *   - Open cmd_file for reading.
 *   - Execute each line as a command (same logic as run_shell).
 *   - Close the file when done.
 * --------------------------------------------------------------- */
void run_command_file(const char *cmd_file, const char *csv_path) {
    /* TODO */
    FILE *fp = fopen(cmd_file, "r");
    if(fp == NULL){
        perror("파일을 열 수 없습니다");
        return;
    }
    char buffer[256];
    while(fgets(buffer, sizeof(buffer), fp) != NULL){
        char *cmd = strtok(buffer, " \n");
        if (cmd == 0) {
            continue;
        }
        if(strcmp(cmd, "exit")==0){
            printf("Bye!\n");
            break;
        }
    }

    fclose(fp); 
    (void)cmd_file;
    (void)csv_path;
}

int main(int argc, char *argv[]) {
    const char *csv_path  = "students.csv"; /* default CSV file */
    const char *cmd_file  = NULL;           /* -f <file> argument */

    /* TODO: Parse command-line arguments.
     *   Supported flags:
     *     -f <file>   run commands from <file> instead of stdin
     *   Remaining positional argument (if any): path to students CSV.
     *
     *   Example parsing skeleton:
     *
     *   for (int i = 1; i < argc; i++) {
     *       if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
     *           cmd_file = argv[++i];
     *       } else {
     *           csv_path = argv[i];
     *       }
     *   }
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
            printf("Usage: ./admin_shell <csv_file>[-f command_file]\n");
        #else
            printf("Usage: ./client_shell <csv_file> [-f command_file]\n");
        #endif
            return 1;
     }
    (void)argc;
    (void)argv;

    Student *student_list = load(csv_path);

    if (student_list != NULL) {
        printf("테스트 성공 ,첫 번째 학생: %s (점수: %d)\n", student_list->name, student_list->score);
    } else {
        printf("엑셀 파일이 비어있네요\n");
    }

#ifdef ADMIN_MODE
    /* Admin shell: supports add, delete, update, save, load, sort, list, find, help, exit */
    if(cmd_file) {
        run_command_file(cmd_file, csv_path);
    } else {
        run_shell(csv_path);
    }

#elif defined(CLIENT_MODE)
    /* Client shell: supports find, list, help, exit  (read-only) */
    i(cmd_file) {
        run_command_file(cmd_file, csv_path);
    } else {
        run_shell(csv_path);
    }

#else
#error "Define either -DADMIN_MODE or -DCLIENT_MODE when compiling."
#endif

    return 0;
}
