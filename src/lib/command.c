// lib/command.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "../util/global.h"
#include "../util/command.h"
#include "../util/db.h"
#include "../util/print.h"

void command_Insert(sqlite3 *db, int codigo, double preco_custo, int estoque)
{
    Produto *novo_produto = malloc(sizeof(Produto));

    if (codigo <= 0 && preco_custo <= 0.0 && estoque < 0)
    {
        printf(YELLOW "Erro: Todos os campos devem ser preenchidos. Código: %d, Preço Custo: %.2f, Estoque: %d\n" RESET, codigo, preco_custo, estoque);
        return;
    }

    if (novo_produto == NULL)
    {
        error("Erro: Falha na alocação de memória para novo produto.\n");
        return;
    }

    float percentage = user->value;
    novo_produto->codigo = codigo;
    novo_produto->preco_custo = preco_custo;
    novo_produto->preco_novo = preco_custo * (1 + (percentage / 100));
    novo_produto->estoque = estoque;
    novo_produto->next = NULL;

    // Se a lista estiver vazia, insira o novo produto como o primeiro
    if (produtos == NULL)
    {
        produtos = novo_produto;
    }
    else
    {
        // Caso contrário, insira no final da lista
        Produto *current = produtos;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = novo_produto;
    }

    post_product(db, novo_produto, user->id);
    printf(GREEN "Produto %d inserido com sucesso.\n" RESET, codigo);
    free(novo_produto);
}

// Função para listar produtos
void command_get(sqlite3 *db) {
    // Verifica se a lista de produtos está vazia
    if (produtos == NULL) {
        info("Nenhum produto cadastrado.\n");
        return;
    }

    printf("Listando todos os produtos:\n");
    
    // Chama a função que deve listar produtos do banco de dados
    get_products(db, user->id);

    // A lista de produtos em memória (se necessário)
    Produto *current = produtos;
    while (current != NULL) {
        if(current->preco_custo > 0.0 && current->estoque > 0){
            printf(BLUE "Código: %d, Preço de Custo: %.2f, Preço Novo: %.2f, Estoque: %d\n" RESET,
            current->codigo, current->preco_custo, current->preco_novo, current->estoque);
        } 
        current = current->next;
    }
}

void command_Remove(sqlite3 *db, int codigo, int quantidade)
{

    if (quantidade < 0)
    {
        warning("Erro: A quantidade a ser removida deve ser maior que zero.\n");
        return;
    }
    else
    {

        update_stock(db, codigo, quantidade);
    }
}


void command_update(sqlite3 *db, int codigo, double preco_custo, int estoque) {

    
    Produto *novo_produto = malloc(sizeof(Produto));


    if (codigo <= 0 && preco_custo <= 0.0 && estoque < 0)
    {
        printf(YELLOW "Erro: Todos os campos devem ser preenchidos. Código: %d, Preço Custo: %.2f, Estoque: %d\n" RESET, codigo, preco_custo, estoque);
        return;
    }

    if (novo_produto == NULL)
    {
        error("Erro: Falha na alocação de memória para novo produto.\n");
        return;
    }

    float percentage = user->value;
    novo_produto->codigo = codigo;
    novo_produto->preco_custo = preco_custo;
    novo_produto->preco_novo = preco_custo * (1 + (percentage / 100));
    novo_produto->estoque = estoque;
    novo_produto->next = NULL;

    // Se a lista estiver vazia, insira o novo produto como o primeiro
    if (produtos == NULL)
    {
        produtos = novo_produto;
    }
    else
    {
        // Caso contrário, insira no final da lista
        Produto *current = produtos;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = novo_produto;
    }

    update_product(db, novo_produto, codigo);
    printf(GREEN "Produto %d atualizado com sucesso.\n" RESET, codigo);
    free(novo_produto);
}


void command_Zero(sqlite3 *db){
  
    get_stock_zero(db, user->id);
}

void command_Delete(sqlite3 *db, int codigo) {
    // Verifica se o produto existe antes de tentar deletá-lo
    if (product_exists(db, codigo)) {
        delete_product(db, codigo); 
        printf(GREEN "Produto %d deletado.\n" RESET, codigo);
    } else {
        info("Produto não encontrado.\n");
    }
}
