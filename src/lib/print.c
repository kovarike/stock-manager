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

void error(const char* message) {
    printf(RED "Erro: %s\n" RESET, message);

    FILE *log_file = fopen("log/logerror.json", "a");
    if (log_file) {
        fprintf(log_file, "Erro: %s\n", message);  
        fclose(log_file);  
    } else {
        printf(RED "Erro ao abrir o arquivo de log.\n" RESET);  
    }
}

void success(const char* message) {
    printf(GREEN "Sucesso: %s\n" RESET, message);
}

void warning(const char* message) {
    printf(YELLOW "Aviso: %s\n" RESET, message);
}

void info(const char* message) {
    printf(CYAN "Info: %s\n" RESET, message);
}

void print_error(const char* message) {
    printf(BRIGHT_RED "Erro Brilhante: %s\n" RESET, message);

    FILE *log_file = fopen("log/logerror.json", "a");
    if (log_file) {
        fprintf(log_file, "Erro: %s\n", message);  
        fclose(log_file);  
    } else {
        printf(BRIGHT_RED "Erro ao abrir o arquivo de log.\n" RESET);  
    }
}

void print_success(const char* message) {
    printf(BRIGHT_GREEN "Sucesso Brilhante: %s\n" RESET, message);
}

void print_warning(const char* message) {
    printf(BRIGHT_YELLOW "Aviso Brilhante: %s\n" RESET, message);
}

void print_info(const char* message) {
    printf(BRIGHT_CYAN "Info Brilhante: %s\n" RESET, message);
}

