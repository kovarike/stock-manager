
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "util/global.h"
#include "util/sh.h"


int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    char input[MAX_INPUT];
    char* args[MAX_ARGS];
    
    produtos = (Produto*)malloc(MAX_PRODUTOS * sizeof(Produto));
    if (produtos == NULL) {
        fprintf(stderr, "Erro ao alocar memória.\n");
        exit(EXIT_FAILURE);
        return 1;
    }

    printf("\nDigite um dos comandos (manager, exit):\n");

    while (1) {
        read_command(input);
        parse_command(input, args);
        execute_command(args);
    }

    free(produtos);
    return 0;
}
