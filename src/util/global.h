#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_INPUT 1024
#define MAX_ARGS 100
#define MAX_PRODUTOS 5000
#define SQL_BUFFER_SIZE 1024

// typedef struct {
//     int codigo;
//     double preco_custo;
//     double preco_novo;
//     int estoque;
// } Produto;
typedef struct Produto {
    int codigo;
    double preco_custo;
    double preco_novo;
    int estoque;
    struct Produto* next; // ponteiro para o próximo produto
} Produto;




extern Produto* produtos;  
extern int total_produtos;

typedef struct {
    char id[37];
    char name[251];
    char email[251];
    int value;  
} Data;

extern Data *user; 



int login(sqlite3 *db);
void manage_products(sqlite3 *db);




#endif










