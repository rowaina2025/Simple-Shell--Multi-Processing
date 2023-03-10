//
// Created by rowiana on 3/10/23.
//

#ifndef LAB1_BUILTIN_SHELL_H
#define LAB1_BUILTIN_SHELL_H

void cd(char* path, int word_count);

void export(char *command, char *input_cmd);

void echo(char *command_list[], int word_count);

#endif //LAB1_BUILTIN_SHELL_H
