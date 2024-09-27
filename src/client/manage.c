// //client/manage.c
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>


// // constantes globais
// #define MAX_INPUT 1024
// #define MAX_ARGS 100
// #define MAX_PRODUTOS 100


// typedef struct {
//     int codigo;
//     float preco_custo;
//     float preco_novo;
//     int estoque;
// } Produto;

// Produto* produtos;  
// int total_produtos = 0;

// void manage_products() {
//     int codigo;
//     float preco_custo;
//     float soma_preco_custo = 0.0;
//     float soma_preco_novo = 0.0;
//     int quantidade_produtos = 0;

//     printf("Bem-vindo ao sistema de gerenciamento de produtos:\n");
//     printf("Digite o código e o preço de custo de cada produto (código negativo ou zero para encerrar):\n");

//     while (1) {
//         printf("Código do produto: ");
//         if (scanf("%d", &codigo) != 1 || codigo <= 0) {
//             break;  // Encerrar o loop se o código for zero ou negativo
//         }

//         printf("Preço de custo: ");
//         if (scanf("%f", &preco_custo) != 1) {
//             fprintf(stderr, "Entrada inválida para o preço de custo.\n");
//             while (getchar() != '\n');  // Limpa o buffer de entrada
//             continue;
//         }

//         // Aumentar a alocação se necessário
//         if (total_produtos >= MAX_PRODUTOS) {
//             printf("Número máximo de produtos atingido.\n");
//             break;
//         }

//         // Adicionar o novo produto
//         produtos[total_produtos].codigo = codigo;
//         produtos[total_produtos].preco_custo = preco_custo;
//         produtos[total_produtos].preco_novo = preco_custo * 1.20;  // Calcula o preço novo
//         produtos[total_produtos].estoque = 0;  // Inicializa o estoque como zero
//         soma_preco_custo += preco_custo;
//         soma_preco_novo += produtos[total_produtos].preco_novo;
//         quantidade_produtos++;
//         total_produtos++;

//         printf("Código: %d, Preço novo: %.2f\n", codigo, produtos[total_produtos - 1].preco_novo);
//     }

//     if (quantidade_produtos > 0) {
//         float media_preco_custo = soma_preco_custo / quantidade_produtos;
//         float media_preco_novo = soma_preco_novo / quantidade_produtos;
//         printf("\nA quantidade de produtos com preços alterados foi: %d\n", quantidade_produtos);
//         printf("Média dos preços de custo: %.2f\n", media_preco_custo);
//         printf("Média dos preços novos: %.2f\n", media_preco_novo);
//     } else {
//         printf("Nenhum produto foi inserido.\n");
//     }
// }

// client/manage.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../util/global.h"
#include "../util/command.h"
Produto* produtos = NULL;
int total_produtos = 0;

void manage_products() {
    int codigo;
    float preco_custo;
    int estoque;

    printf("Bem-vindo ao sistema de gerenciamento de produtos:\n");

    while (1) {
        char input[MAX_INPUT];
        printf("\nDigite um dos comandos (-i, -rm, -ls, -lz, sair): ");
        fgets(input, MAX_INPUT, stdin);
        input[strcspn(input, "\n")] = '\0'; 

        if (strcmp(input, "-ls") == 0) {
            command_get();
        } else if (strcmp(input, "-lz") == 0) {
            command_Zero();
        } else if (strcmp(input, "sair") == 0) {
            break;  // Sair do gerenciamento
        } else if (strcmp(input, "-i") == 0) {
            printf("Código do produto: ");
            scanf("%d", &codigo);
            printf("Preço de custo: ");
            scanf("%f", &preco_custo);
            printf("Estoque: ");
            scanf("%d", &estoque);
            command_Insert(codigo, preco_custo, estoque);
            getchar();  // Limpa o buffer
        } else if (strcmp(input, "-rm") == 0) {
            printf("Código do produto: ");
            scanf("%d", &codigo);
            printf("Quantidade a remover: ");
            scanf("%d", &estoque);
            command_Remove(codigo, estoque);
            getchar();  // Limpa o buffer
        } else {
            printf("Comando não reconhecido.\n");
        }
    }
}
