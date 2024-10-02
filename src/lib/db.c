// lib/db.c
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include "../util/db.h"
#include "../util/global.h"
#include "../util/print.h"

// Prototipação da função callback
int callback(void *NotUsed, int argc, char **argv, char **azColName);

// Função para criar tabelas
int create_tables(sqlite3 *db) {
    char *errMsg = 0;

    const char *sql_user = "CREATE TABLE IF NOT EXISTS Data ("
                           "ID TEXT PRIMARY KEY, "
                           "NAME TEXT NOT NULL, "
                           "EMAIL TEXT NOT NULL, "
                           "VALUE INTEGER NOT NULL);";

    const char *sql_product = "CREATE TABLE IF NOT EXISTS Produto ("
                              "CODIGO INTEGER PRIMARY KEY, "
                              "PRECO_CUSTO REAL NOT NULL, "
                              "PRECO_NOVO REAL NOT NULL, "
                              "ESTOQUE INTEGER NOT NULL, "
                              "USER_ID TEXT NOT NULL, "
                              "FOREIGN KEY(USER_ID) REFERENCES Data(ID));";

    int rc = sqlite3_exec(db, sql_user, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, RED "Erro ao criar tabela de usuários: %s\n" RESET, errMsg);
        sqlite3_free(errMsg);
        exit(EXIT_FAILURE);
    }

    rc = sqlite3_exec(db, sql_product, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, RED "Erro ao criar tabela de produtos: %s\n" RESET, errMsg);
        sqlite3_free(errMsg);
        exit(EXIT_FAILURE);
    }
    return 0;
}

// Função para verificar se o usuário já existe
int check_user_exists(sqlite3 *db) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT ID FROM Data LIMIT 1;"; 
    // Preparar a consulta SQL
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, RED "Erro ao verificar usuário: %s\n" RESET, sqlite3_errmsg(db));
        return 0;
    }

    // Executar a consulta
    rc = sqlite3_step(stmt);
    
    if (rc == SQLITE_ROW) {
        // Se houver resultado, o ID do usuário já existe
        // Copiar o ID do banco de dados para user->id
        const char *id = (const char *)sqlite3_column_text(stmt, 0);
        if(id){
            strncpy(user->id, id, sizeof(user->id) - 1); // Cópia segura
            user->id[sizeof(user->id) - 1] = '\0'; // Garantir terminação nula
        }
        sqlite3_finalize(stmt);
        return 1;  // Usuário encontrado
    }
    
    // Finalizar a consulta
    sqlite3_finalize(stmt);
    return 0;  // Usuário não encontrado
}


// Função para buscar os dados do usuário no banco de dados
int get_user_data(sqlite3 *db) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT ID, NAME, EMAIL, VALUE FROM Data WHERE ID = ?;";
    
    // Preparar a consulta SQL
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, RED "Erro ao preparar consulta: %s\n" RESET, sqlite3_errmsg(db));
        return rc;
    }

    // Bind do ID do usuário na consulta
    sqlite3_bind_text(stmt, 1, user->id, -1, SQLITE_STATIC);

    // Executar a consulta e verificar se obteve resultado
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // Preencher a estrutura Data com os resultados da consulta
       
        strcpy(user->name, (const char *)sqlite3_column_text(stmt, 1));
        user->name[sizeof(user->name) - 1] = '\0'; 

        strcpy(user->email, (const char *)sqlite3_column_text(stmt, 2));
        user->email[sizeof(user->email) - 1] = '\0';

        user->value = sqlite3_column_int(stmt, 3);
    } else if (rc == SQLITE_DONE) {
        error("Error ao carregar informções.\n");
    } else {
        fprintf(stderr, RED "Erro ao buscar infomações: %s\n" RESET, sqlite3_errmsg(db));
    }

    // Finalizar a consulta
    sqlite3_finalize(stmt);

    return rc == SQLITE_ROW ? 0 : 1;  // Retornar 0 se encontrou o usuário
}


// Função para cadastrar um usuário no banco de dados
void post_user(sqlite3 *db) {

    if (check_user_exists(db)) {
        fprintf(stderr, YELLOW "Usuário já existe com ID: %s\n" RESET, user->id);
        return; // Não insere se o usuário já existe
    }

    char *errMsg = 0;
    char sql[SQL_BUFFER_SIZE];

    snprintf(sql, sizeof(sql),
             "INSERT INTO Data (ID, NAME, EMAIL, VALUE) "
             "VALUES ('%s', '%s', '%s', %d);",
             user->id, user->name, user->email, user->value); 

    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, RED "Erro ao inserir usuário: %s\n" RESET, errMsg);
        sqlite3_free(errMsg);
        exit(EXIT_FAILURE);
    }
}

// Função para cadastrar produtos
void post_product(sqlite3 *db, Produto *produto, const char *user_id) {
    char *errMsg = 0;
    char sql[SQL_BUFFER_SIZE];
    if(produto->codigo == 0 && produto->preco_custo == 0.00 && produto->preco_novo == 0.00 && produto->estoque == 0){return;}

    snprintf(sql, sizeof(sql),
             "INSERT INTO Produto (CODIGO, PRECO_CUSTO, PRECO_NOVO, ESTOQUE, USER_ID) "
             "VALUES (%d, %.2f, %.2f, %d, '%s');",
             produto->codigo, produto->preco_custo, produto->preco_novo, produto->estoque, user_id);
    printf(BLUE "\nCódigo: %d, Preço Custo: %.2f, Preço Novo: %.2f, Estoque: %d.\n" RESET,
    produto->codigo, produto->preco_custo, produto->preco_novo, produto->estoque);

    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, RED "Erro: voçê est´tentando inserir um produto que já existe: %s\n" RESET, errMsg);
        sqlite3_free(errMsg);
        exit(EXIT_FAILURE);
    }
}

// Função para obter todos os produtos de um usuário
void get_products(sqlite3 *db, const char *user_id) {
    char *errMsg = 0;
    char sql[SQL_BUFFER_SIZE];

    snprintf(sql, sizeof(sql), "SELECT * FROM Produto WHERE USER_ID = '%s';", user_id);

    int rc = sqlite3_exec(db, sql, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, RED "Erro ao obter produtos: %s\n" RESET, errMsg);
        sqlite3_free(errMsg);
    }
}

// Função para obter todos os produtos com estoque zerado de um usuário
void get_stock_zero(sqlite3 *db, const char *user_id) {
    char *errMsg = 0;
    char sql[SQL_BUFFER_SIZE];

    // Consulta para selecionar produtos com estoque zero
    snprintf(sql, sizeof(sql), "SELECT * FROM Produto WHERE USER_ID = '%s' AND ESTOQUE = 0;", user_id);

    printf("Produtos com estoque zerado:\n");

    int rc = sqlite3_exec(db, sql, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, RED "Erro ao obter produtos com estoque zerado: %s\n" RESET, errMsg);
        sqlite3_free(errMsg);
    }
}

// Função de callback para imprimir os produtos
int callback(void *NotUsed, int argc, char **argv, char **azColName) {


    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

// Função para atualizar um produto
void update_product(sqlite3 *db, Produto *produto, int code) {
    char *errMsg = 0;
    char sql[SQL_BUFFER_SIZE];

    snprintf(sql, sizeof(sql),
             "UPDATE Produto SET PRECO_CUSTO = %.2f, PRECO_NOVO = %.2f, ESTOQUE = %d "
             "WHERE CODIGO = %d;",
             produto->preco_custo, produto->preco_novo, produto->estoque, code);

    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, RED "Erro ao atualizar produto: %s\n" RESET, errMsg);
        sqlite3_free(errMsg);
        exit(EXIT_FAILURE);
    }
}



void update_stock(sqlite3 *db, int codigo, int quantidade) {


    // Verifica se o produto existe e obtém o estoque atual
    int estoque_atual = 0;
    sqlite3_stmt *stmt;
    const char *sql_check = "SELECT ESTOQUE FROM Produto WHERE CODIGO = ?;";

    // Preparar a consulta SQL
    int rc = sqlite3_prepare_v2(db, sql_check, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, RED "Erro ao preparar consulta: %s\n" RESET, sqlite3_errmsg(db));
        return;
    }

    // Bind do código do produto
    sqlite3_bind_int(stmt, 1, codigo);

    // Executar a consulta e verificar se obteve resultado
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        estoque_atual = sqlite3_column_int(stmt, 0);
    } else {
        printf(YELLOW "Produto com código %d não encontrado.\n" RESET, codigo);
        sqlite3_finalize(stmt);
        return;
    }

    sqlite3_finalize(stmt);

    // Verifica se há estoque suficiente para remover a quantidade solicitada
    if (estoque_atual < quantidade) {
        printf(YELLOW "Estoque insuficiente para remover %d unidades do produto %d. Estoque atual: %d.\n" RESET, quantidade, codigo, estoque_atual);
        return;
    }

    // Atualiza o estoque do produto
    char *errMsg = 0;
    char sql_update[SQL_BUFFER_SIZE];

    snprintf(sql_update, sizeof(sql_update),
             "UPDATE Produto SET ESTOQUE = ESTOQUE - %d WHERE CODIGO = %d;",
             quantidade, codigo);

    rc = sqlite3_exec(db, sql_update, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, RED "Erro ao atualizar estoque do produto: %s\n" RESET, errMsg);
        sqlite3_free(errMsg);
        exit(EXIT_FAILURE);
    }

    printf(GREEN "Quantidade de %d unidades removida do produto %d. Estoque atual: %d.\n" RESET, quantidade, codigo, estoque_atual - quantidade);
}

// Implementação da função para verificar se o produto existe
int product_exists(sqlite3 *db, int codigo) {
    char sql[SQL_BUFFER_SIZE];
    sqlite3_stmt *stmt;
    
    snprintf(sql, sizeof(sql), "SELECT COUNT(*) FROM Produto WHERE CODIGO = %d;", codigo);

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar a consulta: %s\n", sqlite3_errmsg(db));
        return 0; // Assume que o produto não existe em caso de erro
    }

    rc = sqlite3_step(stmt);
    int exists = 0;
    if (rc == SQLITE_ROW) {
        exists = sqlite3_column_int(stmt, 0) > 0;
    }

    sqlite3_finalize(stmt);
    return exists;
}





// Função para deletar um produto
void delete_product(sqlite3 *db, int codigo) {
    char *errMsg = 0;
    char sql[SQL_BUFFER_SIZE];

    snprintf(sql, sizeof(sql), "DELETE FROM Produto WHERE CODIGO = %d;", codigo);

    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, RED "Erro ao deletar produto: %s\n" RESET, errMsg);
        sqlite3_free(errMsg);
        exit(EXIT_FAILURE);
    }
}

// int count_products(sqlite3 *db) {
//     const char *sql = "SELECT COUNT(*) FROM Produto;";
//     sqlite3_stmt *stmt;
//     int total_produtos = 0;

//     // Prepara a consulta SQL
//     int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
//     if (rc != SQLITE_OK) {
//         fprintf(stderr, "Erro ao preparar consulta: %s\n", sqlite3_errmsg(db));
//         return -1;
//     }

//     // Executa a consulta e captura o resultado
//     rc = sqlite3_step(stmt);
//     if (rc == SQLITE_ROW) {
//         total_produtos = sqlite3_column_int(stmt, 0);
//     } else {
//         fprintf(stderr, "Erro ao contar produtos: %s\n", sqlite3_errmsg(db));
//     }

//     // Finaliza a instrução SQL
//     sqlite3_finalize(stmt);
    
//     return total_produtos;
// }