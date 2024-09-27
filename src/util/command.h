#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define MAX_PRODUTOS 100

typedef struct {
    int codigo;
    float preco_custo;
    float preco_novo;
    int estoque;
} Produto;

extern Produto* produtos;  
extern int total_produtos;


void command_get();
void command_Insert(int codigo, int estoque);
void command_Remove(int codigo, int quantidade);
void command_Zero();

#endif










