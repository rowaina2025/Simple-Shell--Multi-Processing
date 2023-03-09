//
// Created by rowiana on 3/7/23.
//
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "../h_files/utilities.h"
#include <libgen.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MAX_SIZE 200

//Some Global Variables
char *command_list[MAX_SIZE];
char input_cmd[MAX_SIZE];
enum Commands command;
int word_count = 0;

/**
 * Setup shell environment by changing the working directory into
 * the current directory
 *
 * @param argv the 2d array of program arguments
 * @return void.
 */
void setup_environment(char *prog_dir) {
    //argv[0] contains the name of the program so change directory to it
    char *current_directory = dirname(prog_dir);
    if (chdir(current_directory) != 0) {
        //Print the error message in console showing the reason for this error
        printf("chdir() failed");
    }
    else
        // The setup message indicating no error occurred in changing directory into the current directory so user can continue
        printf("Current working directory: %s\n", getcwd(NULL, 0));
}

/**
 * Assigns signal to children on child termination to be killed
 */
void on_child_exit() {
    int wstat;
    pid_t	pid;
    while ((pid = waitpid(-1, &wstat, WNOHANG)) > 0) {
        printf("Child process %d exited with status %d\n", pid, WEXITSTATUS(wstat));
        lg(input_cmd, pid);
    }
}

/**
 * execute system command with system call execvp()
 */
void execute_command() {
    pid_t pid = fork();
    int status;
    if(pid == 0) {
        if(command == BACKGROUND) command_list[word_count - 1] = NULL;
        execvp(command_list[0], command_list);
        if (execvp(command_list[0], command_list) == -1) {
            perror("no such system call");
            exit(1);
        }
        printf("%s\n", command_list[0]);
        exit(1);
    } else if(pid > 0 && command) {
        if(command != BACKGROUND) {
            // wait for the child process to terminate
            if (waitpid(pid, &status, 0) == -1) {
                printf("waitpid"); // handle error
                exit(1);
            }
        }
    } else {
        printf("process not generated successfully"); // handle error
        return;
    }
}


/**
 * change directory built-in function
 */
void cd() {
    pid_t pid = fork();
    char path[100];
    int status;
    if(pid == 0) {
        if(word_count == 1 || strcmp(command_list[1], "~") == 0) {
            chdir("/home");
            printf("%s\n", getcwd(NULL, 0));
        }
        if(strcmp(command_list[1], ".") == 0 || strcmp(command_list[1], "..") == 0) {
            chdir(command_list[1]);
            printf("%s\n", getcwd(NULL, 0));
        } else {
            chdir(command_list[1]);
            printf("%s\n", getcwd(path, sizeof(path)));
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
void export() {
    //extract value name to be stored
    char name[MAX_SIZE], value[MAX_SIZE];
    extract_export_name(command_list[1], name);
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
void echo() {
    //prints the words input by the user
    for(int i = 1; i < word_count; i++) {
        printf("%s ", command_list[i]);
    }
    printf("\n");
}

/**
 * remove dollar signs and double quotes for command to be ready for execution
 */
void evaluate_expression() {
    if(command == ECHO) {
        //Remove the double quotes
        memmove(command_list[1], command_list[1] + 1, strlen(command_list[1]));
        for(int i = 0; i < MAX_SIZE; i++) {
            if(command_list[word_count - 1][i] == '\"') {
                command_list[word_count - 1][i] = '\0';
                break;
            }
        }
    }
    bool has_dollar = false;
    // evaluate $ sign
    for(int i = 0; i < word_count; i++) {
        if(command_list[i][0] == '$') {
            memmove(command_list[1], command_list[1] + 1, strlen(command_list[1]));
            strcpy(command_list[i], getenv(command_list[i]));
            has_dollar = true;
            break;
        }
    }
    if(command != ECHO && has_dollar) {
        char temp[MAX_SIZE], *_temp[MAX_SIZE];
        strcpy(temp, command_list[1]);
        int num = parse_command(command_list[1], _temp, " ");
        word_count = num + 1;
        for(int i = 0; i < num; i++) {
            command_list[i + 1] = _temp[i];
        }
        word_count = num + 1;
    }
}

void execute_shell_bultin() {
    switch (command) {
        case CD:
            cd();
            break;
        case EXPORT:
            export();
            break;
        case ECHO:
            echo();
            break;
        case BACKGROUND:
            execute_command();
            break;
        case EXIT:
            exit(1);
        default:
            return;
    }
}

/**
 * Contains the main loop that repeats itself in each command
 */
void shell() {
    do {
        // take input form user
        char *temp_input_cmd = input_command();
        //Save the state of the whole input line
        strcpy(input_cmd, temp_input_cmd);
        // parse it and count its words
        word_count = parse_command(temp_input_cmd, command_list, " ");
        // assign enum values
        if(word_count > 1 && strcmp(command_list[word_count - 1], "&") == 0)
            setEnum(command_list[word_count - 1], &command, word_count);
        else
            setEnum(command_list[0], &command, word_count);
        // Remove $ and "" in echo
        evaluate_expression();
        // Built-in or command ??
        if(is_built_in(command) == true)
            execute_shell_bultin();
        else
            execute_command();
        // reset variables to be ready for the next input from the user
        memset(command_list, '\0', sizeof(command_list));
    } while(command != EXIT);
}

int main(int argc, char *argv[]) {
    // set up the signal handler for 'SIGCHLD' signal generated by the child process 'SIGCHLD' signal sent from chile to parent when child terminates avoiding zombie processes
    signal(SIGCHLD, on_child_exit);
    setup_environment(argv[0]);
    shell();
}