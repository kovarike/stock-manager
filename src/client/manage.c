
// client/manage.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "../util/global.h"
#include "../util/command.h"
#include "../util/print.h"



void manage_products(sqlite3*db) {
    int codigo;
    double preco_custo;
    int estoque;

    printf("Bem-vindo ao sistema de gerenciamento de produtos:\n");

    while (1) {
        char input[MAX_INPUT];
        printf("\nDigite um dos comandos (-i, -rm, -ls, -lz, -up, -dlt, , help, sair): ");
        fgets(input, MAX_INPUT, stdin);
        input[strcspn(input, "\n")] = '\0'; 
        

        if (strcmp(input, "-ls") == 0) {
            command_get(db);
        } else if (strcmp(input, "-lz") == 0) {
            command_Zero(db);
        } else if (strcmp(input, "sair") == 0) {
            break;  // Sair do gerenciamento
        } else if (strcmp(input, "-i") == 0) {
            printf("Código do produto: ");
            while (scanf("%d", &codigo) != 1 || codigo <= 0) {
                printf(YELLOW "Erro: Código inválido. Por favor, insira um número inteiro positivo.\n" RESET);
                while (getchar() != '\n'); // Limpar o buffer de entrada
                printf("Código do produto: ");
            }

            // Validação de entrada para o preço de custo
            printf("Preço de custo: ");
            while (scanf("%lf", &preco_custo) != 1 || preco_custo <= 0.0) {
                printf(YELLOW "Erro: Preço de custo inválido. Por favor, insira um número positivo.\n" RESET);
                while (getchar() != '\n'); // Limpar o buffer de entrada
                printf("Preço de custo: ");
            }

            // Validação de entrada para o estoque
            printf("Estoque: ");
            while (scanf("%d", &estoque) != 1 || estoque < 0) {
                printf(YELLOW "Erro: Estoque inválido. Por favor, insira um número inteiro não negativo.\n" RESET);
                while (getchar() != '\n'); // Limpar o buffer de entrada
                printf("Estoque: ");
            }
            getchar();  
            command_Insert(db, codigo, preco_custo, estoque);
        } else if (strcmp(input, "-rm") == 0) {
              printf("Código do produto: ");
            while (scanf("%d", &codigo) != 1 || codigo <= 0) {
                printf(YELLOW "Erro: Código inválido. Por favor, insira um número inteiro positivo.\n" RESET);
                while (getchar() != '\n'); // Limpar o buffer de entrada
                printf("Código do produto: ");
            }

            printf("Quantidade a remover do estoque: ");
            while (scanf("%d", &estoque) != 1 || estoque < 0) {
                printf(YELLOW "Erro: Estoque inválido. Por favor, insira um número inteiro não negativo.\n" RESET);
                while (getchar() != '\n'); // Limpar o buffer de entrada
                printf("Estoque: ");
            }
            getchar(); 
            command_Remove(db, codigo, estoque);
        } else if(strcmp(input, "-dlt") == 0){

            printf("Código do produto: ");
            while (scanf("%d", &codigo) != 1 || codigo <= 0) {
                printf(YELLOW "Erro: Código inválido. Por favor, insira um número inteiro positivo.\n" RESET);
                while (getchar() != '\n'); // Limpar o buffer de entrada
                printf("Código do produto: ");
            }

            getchar();
            command_Delete(db, codigo);
        } else if(strcmp(input, "-up") == 0){
            printf("Código do produto: ");
            while (scanf("%d", &codigo) != 1 || codigo <= 0) {
                printf(YELLOW "Erro: Código inválido. Por favor, insira um número inteiro positivo.\n" RESET);
                while (getchar() != '\n'); // Limpar o buffer de entrada
                printf("Código do produto: ");
            }

            // Validação de entrada para o preço de custo
            printf("Novo preço de custo: ");
            while (scanf("%lf", &preco_custo) != 1 || preco_custo <= 0.0) {
                printf(YELLOW "Erro: Preço de custo inválido. Por favor, insira um número positivo.\n" RESET);
                while (getchar() != '\n'); // Limpar o buffer de entrada
                printf("Novo preço de custo: ");
            }

            // Validação de entrada para o estoque
            printf("Novo estoque: ");
            while (scanf("%d", &estoque) != 1 || estoque < 0) {
                printf(YELLOW "Erro: Estoque inválido. Por favor, insira um número inteiro não negativo.\n" RESET);
                while (getchar() != '\n'); // Limpar o buffer de entrada
                printf("Novo estoque: ");
            }
            getchar();  
            command_update(db, codigo, preco_custo, estoque);

        } else if(strcmp(input, "help") == 0){
            info("\nComandos disponíveis:\n");
            info("  -i       : Inserir um novo produto.\n");
            info("  -rm      : Remover o estoque de um produto.\n");
            info("  -ls      : Listar todos os produtos.\n");
            info("  -lz      : Listar todos os produtos com estoque zero.\n");
            info("  -up      : Atualizar os dados de um produto.\n");
            info("  -dlt     : Deletar um produto do sistema.\n");
            info("  help     : Exibir esta ajuda.\n");
            info("  sair     : Sair do sistema de gerenciamento.\n");


        } else {
            printf("Comando não reconhecido.\n");
        }
    }
}
