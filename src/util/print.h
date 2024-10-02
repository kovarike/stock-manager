#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>

#define RESET        "\x1b[0m"
#define RED          "\x1b[31m"
#define GREEN        "\x1b[32m"
#define YELLOW       "\x1b[33m"
#define BLUE         "\x1b[34m"
#define MAGENTA      "\x1b[35m"
#define CYAN         "\x1b[36m"
#define WHITE        "\x1b[37m"

#define BRIGHT_RED   "\x1b[91m"
#define BRIGHT_GREEN "\x1b[92m"
#define BRIGHT_YELLOW "\x1b[93m"
#define BRIGHT_BLUE  "\x1b[94m"
#define BRIGHT_MAGENTA "\x1b[95m"
#define BRIGHT_CYAN  "\x1b[96m"
#define BRIGHT_WHITE "\x1b[97m"

void error(const char* message);

void success(const char* message);

void warning(const char* message);

void info(const char* message);

void print_error(const char* message);

void print_success(const char* message);

void print_warning(const char* message);

void print_info(const char* message);
#endif
