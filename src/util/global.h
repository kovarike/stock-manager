#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 1024
#define MAX_ARGS 100
#define MAX_PRODUTOS 5000

typedef struct {
    int codigo;
    float preco_custo;
    float preco_novo;
    int estoque;
} Produto;

extern Produto* produtos;  
extern int total_produtos;

typedef struct {
    char id[100];
    char name[1024];
    char codeId[10];
    char value[100];  
} Data;



#endif










