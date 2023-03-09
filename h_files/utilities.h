//
// Created by rowiana on 3/7/23.
//
#include <stdbool.h>
#include "commands.h"
#ifndef LAB1_UTILITIES_H
#define LAB1_UTILITIES_H

char *input_command();

int parse_command(char* command, char **command_list, char* separator);

bool is_built_in(enum Commands command);

void setEnum(char* command, enum Commands *prog_command, int words_count);

void lg(char *command, int pid);

void extract_export_name(char *expression, char *name);

void extract_export_value(char *expression, char *extracted_export);

#endif //LAB1_UTILITIES_H
