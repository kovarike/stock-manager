// //service/command.c
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// typedef struct {
//     int codigo;
//     float preco_custo;
//     float preco_novo;
//     int estoque;
// } Produto;

// Produto* produtos;  



// void command_get(int *total_produtos) {
//     if (*total_produtos == 0) {
//         printf("Nenhum produto cadastrado.\n");
//         return;
//     }

//     printf("Listando todos os produtos:\n");
//     for (int i = 0; i < *total_produtos; i++) {
//         printf("Código: %d, Estoque: %d, Preço de Custo: %.2f, Preço Novo: %.2f\n", 
//         produtos[i].codigo, produtos[i].estoque, produtos[i].preco_custo, produtos[i].preco_novo);
//     }
// }


// void command_Insert(int codigo, int estoque, int *total_produtos) {
//     for (int i = 0; i < *total_produtos; i++) {
//         if (produtos[i].codigo == codigo) {
//             produtos[i].estoque += estoque;
//             printf("Estoque do produto %d atualizado para %d.\n", codigo, produtos[i].estoque);
//             return;
//         }
//     }
//     printf("Produto não encontrado.\n");
// }


// void command_Remove(int codigo, int *total_produtos) {
//     for (int i = 0; i < *total_produtos; i++) {
//         if (produtos[i].codigo == codigo) {
//             if (produtos[i].estoque > 0) {
//                 produtos[i].estoque--;
//                 printf("Produto %d removido do estoque. Estoque restante: %d.\n", codigo, produtos[i].estoque);
//             } else {
//                 printf("Produto %d está com estoque zerado.\n", codigo);
//             }
//             return;
//         }
//     }
//     printf("Produto não encontrado.\n");
// }


// void command_Zero(int *total_produtos) {
//     printf("Produtos com estoque zerado:\n");
//     for (int i = 0; i < *total_produtos; i++) {
//         if (produtos[i].estoque == 0) {
//             printf("Código: %d\n", produtos[i].codigo);
//         }
//     }
// }


// service/command.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../util/sh.h"
#include "../util/command.h"


#define MAX_PRODUTOS 100

// typedef struct {
//     int codigo;
//     float preco_custo;
//     float preco_novo;
//     int estoque;
// } Produto;

Produto* produtos  = NULL;  
int total_produtos = 0;

void command_get() {
    if (total_produtos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("Listando todos os produtos:\n");
    for (int i = 0; i < total_produtos; i++) {
        printf("Código: %d, Estoque: %d, Preço de Custo: %.2f, Preço Novo: %.2f\n", 
        produtos[i].codigo, produtos[i].estoque, produtos[i].preco_custo, produtos[i].preco_novo);
    }
}

void command_Insert(int codigo, int estoque) {
    for (int i = 0; i < total_produtos; i++) {
        if (produtos[i].codigo == codigo) {
            produtos[i].estoque += estoque;
            printf("Estoque do produto %d atualizado para %d.\n", codigo, produtos[i].estoque);
            return;
        }
    }

    if (total_produtos < MAX_PRODUTOS) {
        produtos[total_produtos].codigo = codigo;
        produtos[total_produtos].preco_custo = 0.0;  // Preço de custo deve ser fornecido
        produtos[total_produtos].preco_novo = 0.0;   // Preço novo deve ser calculado
        produtos[total_produtos].estoque = estoque;
        total_produtos++;
        printf("Produto %d inserido com estoque %d.\n", codigo, estoque);
    } else {
        printf("Número máximo de produtos atingido.\n");
    }
}

void command_Remove(int codigo, int quantidade) {
    for (int i = 0; i < total_produtos; i++) {
        if (produtos[i].codigo == codigo) {
            if (produtos[i].estoque >= quantidade) {
                produtos[i].estoque -= quantidade;
                printf("Produto %d removido do estoque. Estoque restante: %d.\n", codigo, produtos[i].estoque);
            } else {
                printf("Estoque insuficiente para o produto %d.\n", codigo);
            }
            return;
        }
    }
    printf("Produto não encontrado.\n");
}

void command_Zero() {
    printf("Produtos com estoque zerado:\n");
    for (int i = 0; i < total_produtos; i++) {
        if (produtos[i].estoque == 0) {
            printf("Código: %d\n", produtos[i].codigo);
        }
    }
}
