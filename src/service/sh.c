// service/sh.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../util/global.h"
#include "../util/sh.h"
#include "../util/command.h"  



void read_command(char* input) {
    printf("StockManager> ");
    fgets(input, MAX_INPUT, stdin);
    input[strcspn(input, "\n")] = '\0';  
}

void parse_command(char* input, char** args) {
    int i = 0;
    args[i] = strtok(input, " ");
    while (args[i] != NULL) {
        i++;
        args[i] = strtok(NULL, " ");
    }
}

void execute_command(char** args) {
    if (strcmp(args[0], "manager") == 0) {
        manage_products();
    } else if (strcmp(args[0], "exit") == 0) {
        exit(0);
    } else {
        printf("Comando não reconhecido: %s\n", args[0]);
        printf("Digite um dos comandos (manager, exit):\n");
    }
}
