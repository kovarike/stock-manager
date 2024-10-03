#ifndef DB_H
#define DB_H


#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

#include <string.h>
#include "../util/global.h"




int callback(void *NotUsed, int argc, char **argv, char **azColName);
int create_tables(sqlite3 *db);


int check_user_exists(sqlite3 *db);
int get_user_data(sqlite3 *db);


void post_user(sqlite3 *db);

void post_product(sqlite3 *db, Produto *produto, const char *user_id);

void get_products(sqlite3 *db, const char *user_id);
void get_stock_zero(sqlite3 *db, const char *user_id);

void update_product(sqlite3 *db, Produto *produto, int code);

void update_stock(sqlite3 *db, int codigo, int quantidade);
int product_exists(sqlite3 *db, int codigo);

// Função para deletar um produto
void delete_product(sqlite3 *db, int codigo);

int count_products(sqlite3 *db);

#endif