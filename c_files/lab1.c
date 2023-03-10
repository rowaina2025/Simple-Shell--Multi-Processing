//
// Created by rowiana on 3/7/23.
//
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "../h_files/utilities.h"
#include "../h_files/builtin_shell.h"

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

void execute_shell_bultin() {
    switch (command) {
        case CD:
            cd(command_list[1], word_count);
            break;
        case EXPORT:
            export(command_list[1], input_cmd);
            break;
        case ECHO:
            echo(command_list, word_count);
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
        // set command state
        if(word_count > 1 && strcmp(command_list[word_count - 1], "&") == 0)
            set_process(command_list[word_count - 1], &command, word_count);
        else
            set_process(command_list[0], &command, word_count);
        // Remove "" echo
        if(command == ECHO && command_list[1][0] == '"')
            remove_double_quotes(command_list, word_count, MAX_SIZE);
        // remove $
        word_count = evaluate_expression(input_cmd, command_list, word_count, MAX_SIZE);
        //Save the state of the whole input line
        strcpy( temp_input_cmd, input_cmd);
        // reset variables to be ready for the next input from the user
        memset(command_list, '\0', sizeof(command_list));
        // parse it and count its words
        word_count = parse_command(temp_input_cmd, command_list, " ");
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
    // Assign SIGCHLD signal
    signal(SIGCHLD, on_child_exit);
    setup_environment(argv[0]);
    shell();
}