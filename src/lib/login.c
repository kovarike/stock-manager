#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char id[100];
    char name[1024];
    char codeId[10];
    char value[100];  // Corrected typo from "valeu" to "value"
} Data;

void get() {
    // Lendo os dados de volta
    Data readData[3];
    FILE *file = fopen("data.bin", "rb");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);  // Use exit to terminate on error
    }

    size_t itemsRead = fread(readData, sizeof(Data), 3, file);
    fclose(file);

    // Verifica se leu menos itens que o esperado
    if (itemsRead < 3) {
        printf("Leitura incompleta, apenas %zu itens foram lidos.\n", itemsRead);
    }

    // Exibindo os dados lidos
    for (size_t i = 0; i < itemsRead; i++) {
        printf("ID: %s, Value: %s\n", readData[i].id, readData[i].value); // Corrected formatting
    }
}

void post() {
    // Criando alguns dados para armazenar
    Data data[] = {
        {"danilo@danilo.com", "danilo", "654546", "4.99"}
    };

    // Abrindo o arquivo para escrita em binário
    FILE *file = fopen("data.bin", "wb");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);  // Use exit to terminate on error
    }

    // Gravando os dados no arquivo
    fwrite(data, sizeof(Data), sizeof(data) / sizeof(Data), file);
    
    // Fechando o arquivo
    fclose(file);
}

int login() {
    
    post();  
    get();   
    return EXIT_SUCCESS;
}


// // client/manage.c
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "command.h"

// void manage_products() {
//     int codigo;
//     float preco_custo;
//     int estoque;

//     printf("Bem-vindo ao sistema de gerenciamento de produtos:\n");

//     while (1) {
//         char input[MAX_INPUT];
//         printf("\nDigite um comando (inserir, remover, listar, zerados, sair): ");
//         fgets(input, MAX_INPUT, stdin);
//         input[strcspn(input, "\n")] = '\0';  // Remove a nova linha

//         if (strcmp(input, "listar") == 0) {
//             command_get();
//         } else if (strcmp(input, "zerados") == 0) {
//             command_Zero();
//         } else if (strcmp(input, "sair") == 0) {
//             break;  // Sair do gerenciamento
//         } else if (strcmp(input, "inserir") == 0) {
//             printf("Código do produto: ");
//             scanf("%d", &codigo);
//             printf("Preço de custo: ");
//             scanf("%f", &preco_custo);
//             printf("Estoque: ");
//             scanf("%d", &estoque);
//             command_Insert(codigo, estoque);
//             getchar();  // Limpa o buffer
//         } else if (strcmp(input, "remover") == 0) {
//             printf("Código do produto: ");
//             scanf("%d", &codigo);
//             printf("Quantidade a remover: ");
//             scanf("%d", &estoque);
//             command_Remove(codigo, estoque);
//             getchar();  // Limpa o buffer
//         } else {
//             printf("Comando não reconhecido.\n");
//         }
//     }
// }

//


// void manage_products() {
//     int codigo;
//     float preco_custo;
//     int estoque;

//     printf("Bem-vindo ao sistema de gerenciamento de produtos:\n");

//     while (1) {
//         char input[MAX_INPUT];
//         printf("\nDigite um comando (inserir, remover, listar, zerados, sair): ");
//         fgets(input, MAX_INPUT, stdin);
//         input[strcspn(input, "\n")] = '\0';  // Remove a nova linha

//         // Debug: imprime a entrada recebida
//         printf("Entrada recebida: '%s'\n", input);

//         // Verifica e processa os comandos
//         if (strcmp(input, "listar") == 0) {
//             command_get();
//         } else if (strcmp(input, "zerados") == 0) {
//             command_Zero();
//         } else if (strcmp(input, "sair") == 0) {
//             printf("Saindo do gerenciamento...\n");
//             break;  // Sair do gerenciamento
//         } else if (strcmp(input, "inserir") == 0) {
//             printf("Código do produto: ");
//             scanf("%d", &codigo);
//             printf("Preço de custo: ");
//             scanf("%f", &preco_custo);
//             printf("Estoque: ");
//             scanf("%d", &estoque);
//             command_Insert(codigo, estoque);
//             getchar();  // Limpa o buffer
//         } else if (strcmp(input, "remover") == 0) {
//             printf("Código do produto: ");
//             scanf("%d", &codigo);
//             printf("Quantidade a remover: ");
//             scanf("%d", &estoque);
//             command_Remove(codigo, estoque);
//             getchar();  // Limpa o buffer
//         } else {
//             printf("Comando não reconhecido: %s\n", input);
//         }
//     }
// }





//Criar e Gravar JSON em um Arquivo Binário
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void write_json_to_bin(const char *filename, const char *json_string) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Não foi possível abrir o arquivo");
        return;
    }
    
    size_t length = strlen(json_string);
    fwrite(&length, sizeof(size_t), 1, file); // Armazena o comprimento do JSON
    fwrite(json_string, sizeof(char), length, file); // Armazena o JSON
    fclose(file);
}

int main() {
    const char *json_data = "{\"nome\":\"Produto\", \"preco\":99.99}";
    write_json_to_bin("data.bin", json_data);
    return 0;
}

//Ler JSON de um Arquivo Binário
#include <stdio.h>
#include <stdlib.h>

char *read_json_from_bin(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Não foi possível abrir o arquivo");
        return NULL;
    }
    
    size_t length;
    fread(&length, sizeof(size_t), 1, file); // Lê o comprimento do JSON
    char *json_string = malloc(length + 1); // Aloca espaço para a string
    if (!json_string) {
        fclose(file);
        perror("Não foi possível alocar memória");
        return NULL;
    }
    
    fread(json_string, sizeof(char), length, file); // Lê o JSON
    json_string[length] = '\0'; // Adiciona o terminador nulo
    fclose(file);
    
    return json_string;
}

int main() {
    char *json_data = read_json_from_bin("data.bin");
    if (json_data) {
        printf("JSON lido: %s\n", json_data);
        free(json_data);
    }
    return 0;
}
