#ifndef SH_H
#define Sh_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void read_command(char* input);
void parse_command(char* input, char** args);
void execute_command(char** args);
void manage_products();

#endif