
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "util/sh.h"
#include "util/command.h"

// constantes globais
#define MAX_INPUT 1024
#define MAX_ARGS 100
#define MAX_PRODUTOS 5000

// typedef struct {
//     int codigo;
//     float preco_custo;
//     float preco_novo;
//     int estoque;
// } Produto;

// Produto* produtos  = NULL;  
// int total_produtos = 0;

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    char input[MAX_INPUT];
    char* args[MAX_ARGS];

    produtos = (Produto*)malloc(MAX_PRODUTOS * sizeof(Produto));
    if (produtos == NULL) {
        fprintf(stderr, "Erro ao alocar memória.\n");
        return 1;
    }

    while (1) {
        read_command(input);
        parse_command(input, args);
        execute_command(args);
    }

    free(produtos);
    return 0;
}
