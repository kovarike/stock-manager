// //service/sh.c
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define MAX_INPUT 1024


// void read_command(char* input) {
//     printf("app> ");
//     fgets(input, MAX_INPUT, stdin);
//     input[strcspn(input, "\n")] = '\0';  
// }



// void pipe(char* input, char** args) {
//     int i = 0;
//     args[i] = strtok(input, " ");
//     while (args[i] != NULL) {
//         i++;
//         args[i] = strtok(NULL, " ");
//     }
// }


// void execute(char** args) {
//     if (strcmp(args[0], "manage") == 0) {
//         manage_products();
//     } else if (strcmp(args[0], "-i") == 0) {
//         if (args[1] != NULL && args[2] != NULL) {
//             int codigo = atoi(args[1]);
//             int estoque = atoi(args[2]);
//             insertProduto(codigo, estoque);
//         } else {
//             printf("Uso: -i <codigo> <estoque>\n");
//         }
//     } else if (strcmp(args[0], "-get") == 0) {
//         listProdutos();
//     } else if (strcmp(args[0], "-r") == 0) {
//         if (args[1] != NULL) {
//             int codigo = atoi(args[1]);
//             removeProduto(codigo);
//         } else {
//             printf("Uso: -r <codigo>\n");
//         }
//     } else if (strcmp(args[0], "-z") == 0) {
//         produtosZerados();
//     } else if (strcmp(args[0], "exit") == 0) {
//         exit(0);
//     } else {
//         printf("Comando não reconhecido: %s\n", args[0]);
//     }
// }


// service/sh.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../util/sh.h"
#include "../util/command.h"  

#define MAX_INPUT 1024

void read_command(char* input) {
    printf("app> ");
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
    if (strcmp(args[0], "manage") == 0) {
        manage_products();
    } else if (strcmp(args[0], "-i") == 0) {
        if (args[1] != NULL && args[2] != NULL) {
            int codigo = atoi(args[1]);
            int estoque = atoi(args[2]);
            command_Insert(codigo, estoque);
        } else {
            printf("Uso: -i <codigo> <estoque>\n");
        }
    } else if (strcmp(args[0], "-get") == 0) {
        command_get();
    } else if (strcmp(args[0], "-r") == 0) {
        if (args[1] != NULL) {
            int codigo = atoi(args[1]);
            command_Remove(codigo, 1);
        } else {
            printf("Uso: -r <codigo>\n");
        }
    } else if (strcmp(args[0], "-z") == 0) {
        command_Zero();
    } else if (strcmp(args[0], "exit") == 0) {
        exit(0);
    } else {
        printf("Comando não reconhecido: %s\n", args[0]);
    }
}
