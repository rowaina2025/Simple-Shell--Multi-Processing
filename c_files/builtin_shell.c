//
// Created by rowiana on 3/10/23.
//
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "../h_files/utilities.h"
#include <sys/wait.h>
#include <stdlib.h>

#define MAX_SIZE 200


/**
 * change directory built-in function
 */
void cd(char* path, int word_count) {
    pid_t pid = fork();
    char _path[MAX_SIZE];
    int status;
    if(pid == 0) {
        if(word_count == 1 || strcmp(path, "~") == 0) {
            chdir("/home");
            printf("%s\n", getcwd(NULL, 0));
        }
        if(strcmp(path, ".") == 0 || strcmp(path, "..") == 0) {
            chdir(path);
            printf("%s\n", getcwd(NULL, 0));
        } else {
            chdir(path);
            printf("%s\n", getcwd(_path, sizeof(_path)));
        }
    } else if(pid > 0) {
        // wait for the child process to terminate
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid"); // handle error
            exit(1);
        }
    } else {
        printf("process not generated successfully"); // handle error
        return;
    }
}

/**
 * export built-in function
 */
void export(char *command, char *input_cmd) {
    //extract value name to be stored
    char name[MAX_SIZE], value[MAX_SIZE];
    extract_export_name(command, name);
    extract_export_value(input_cmd, value);
    if(setenv(name, value, 1) != 0) {
        printf("sentenv Error");
        return;
    }
    printf("Environment variable %s set to %s\n", name, getenv(name));
}

/**
 *  echo built-in function
 */
void echo(char *command_list[], int word_count) {
//    //prints the words input by the user
//    for(int i = 1; i < word_count; i++) {
//        printf("%s ", command_list[i]);
//    }
//    printf("\n");
}