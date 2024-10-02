#ifndef SH_H
#define Sh_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>




void read_command(char* input);
void parse_command(char* input, char** args);
void execute_command(char** args, sqlite3*db);


#endif