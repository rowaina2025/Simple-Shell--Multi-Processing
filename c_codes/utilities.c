//
// Created by rowiana on 3/7/23.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../h_files/utilities.h"

char *filename = "t.txt";

/**
 * function that takes input from the user
 *
 * @return command the whole line input
 */
char *input_command() {
    char *command;
    size_t size = 100;
    command = malloc(size);
    if (command == NULL) {
        printf("Failed to allocate memory");
        return command;
    }
    fgets(command, size, stdin);
    command[strcspn(command, "\n")] = '\0';  // remove newline character
    return command;
}

/**
 * functions sets the command executed by the program
 *
 * @param command command line input
 * @param command_list array of words
 * @return count number of words of command
 */
int parse_command(char* command, char** command_list, char *separator) {
    char *command_word;
    command_word = strtok(command, " ");
    int i = 0, count = 0;
    while (command_word != NULL) {
        command_list[i++] = command_word;
        command_word = strtok(NULL, separator);
        count++;
    }
    return count;
}

/**
 * functions sets the command executed by the program
 *
 * @param command command line input
 * @param prog_command Command to be changed
 * @param words_count number of words of input instruction
 * @return void function
 */
void setEnum(char *command, enum Commands *prog_command, int words_count) {
    if(strcmp(command, "exit") == 0) {
        *prog_command = EXIT;
    } else if(strcmp(command, "echo") == 0) {
        *prog_command = ECHO;
    } else if(strcmp(command, "export") == 0) {
        *prog_command = EXPORT;
    } else if(strcmp(command, "cd") == 0) {
        *prog_command = CD;
    } else if(strcmp(command, "&") == 0) {
        *prog_command = BACKGROUND;
    } else if(words_count == 1) {
        *prog_command = NO_PARAM_EXE;
    } else if(words_count > 1) {
        *prog_command = PARAM_EXE;
    }
}

/**
 * Checks if the input command is built in by this program or an executable
 * command in the system
 *
 * @param command the 1d array of char the first word entered
 * @return true if builtin and false otherwise.
 */
bool is_built_in(enum Commands command) {
    if(command == CD || command == ECHO || command == EXPORT || command == BACKGROUND || command == EXIT)
        return true;
    else
        return false;
}

/**
 * logs the child termination in text file
 */
void lg(char *command, int pid) {
    FILE *fp = fopen(filename, "a");
    if (fp == NULL)
    {
        printf("Error opening the file %s", filename);
        return;
    }
    fprintf(fp, "Child exit of process id: % d, command: %s\n", pid, command);
    fclose(fp);
}

/**
 * extract value form export expression
*/
void extract_export_value(char *command, char *value) {
    char dummy[100];
    if (sscanf(command, "export %[^=]=\"%[^\n]\"", dummy, value) != 2) {
        printf("Error: Invalid input string format\n");
    }
    int len = strlen(value);
    value[len - 1] = '\0';
}

/**
 * extract name of variable form export expression
*/
void extract_export_name(char *expression, char *name) {
    // Split the string at the '=' character
    char temp_expression[200];
    strcpy(temp_expression, expression);
    char *temp_name = strtok(temp_expression, "=");
    strcpy(name, temp_name);
}
