// lib/sh.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "../util/global.h"
#include "../util/sh.h"
#include "../util/command.h"  


void read_command(char* input) {
    printf("%s> ", user->name);
    if (fgets(input, MAX_INPUT, stdin) == NULL) {
        fprintf(stderr, "Erro ao ler comando.\n");
        exit(EXIT_FAILURE);
    }
    input[strcspn(input, "\n")] = '\0'; 
}

void parse_command(char* input, char** args) {
    int i = 0;
    args[i] = strtok(input, " ");
    while (args[i] != NULL && i < MAX_ARGS - 1) { 
        i++;
        args[i] = strtok(NULL, " ");
    }
    args[i] = NULL; 
}

typedef struct {
    char* command;
    void (*func)(sqlite3*);
} Command;



void execute_command(char** args, sqlite3* db) {
    Command commands[] = {
        {"manager", manage_products},
        {"exit", NULL} 
    };

    for (int i = 0; i < sizeof(commands) / sizeof(Command); i++) {
        if (strcmp(args[0], commands[i].command) == 0) {
            if (commands[i].func != NULL) {
                commands[i].func(db);
            } else {
                printf("Encerrando o programa...\n");
                exit(0);
            }
            return;
        }
    }

    printf("Comando não reconhecido: %s\n", args[0]);
    printf("Digite um dos comandos (manager, exit):\n");
}
