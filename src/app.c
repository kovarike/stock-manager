/*
 * This file is part of the Stockmanager system.
 *
 * Copyright (C) 2024 Danilo Da Silva Batista.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an "AS IS"
 * BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 * implied. See the License for the specific language governing permissions
 * and limitations under the License.
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <sqlite3.h>
#include "util/db.h"
#include "util/global.h"
#include "util/sh.h"
Produto *produtos = NULL;
Data *user = NULL;


int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    //banco de dados
    sqlite3 *db;
    int rc = sqlite3_open("db/data.db", &db);
    if (rc) {
        fprintf(stderr, "Não foi possível abrir o banco de dados: %s\n", sqlite3_errmsg(db));
        exit(EXIT_FAILURE);
    }

    if (db == NULL) {
        fprintf(stderr, "Database pointer is NULL.\n");
        return -1; 
    }

    

    // Data user
    user = malloc(sizeof(Data));
    if (user == NULL) {
        fprintf(stderr, "Erro ao alocar memória para usuário.\n");
        free(user);
        return -1; 
    }


    if (create_tables(db) != 0) {
        fprintf(stderr, "Erro ao criar tabelas no bamco de dados.\n");
        sqlite3_close(db);
        return EXIT_FAILURE;
    }


    if (login(db) != 0) {
        fprintf(stderr, "Falha no login.\n");
        sqlite3_close(db);
        return EXIT_FAILURE;
    }
    
    get_user_data(db);
    
    
    produtos = (Produto*)malloc(MAX_PRODUTOS * sizeof(Produto));
    if (produtos == NULL) {
        fprintf(stderr, "Erro ao alocar memória.\n");
        free(produtos);
        exit(EXIT_FAILURE);
        return 1;
    }
    char input[MAX_INPUT];
    char* args[MAX_ARGS];

    printf("\nDigite um dos comandos (manager, exit):\n");

    while (1) {
        memset(input, 0, sizeof(input));
        read_command(input);

        if (strlen(input) == 0) {
            continue;  
        }
        
        parse_command(input, args);
        if (args[0] == NULL) {
            fprintf(stderr, "Comando inválido.\n");
            continue;  
        }
        
        execute_command(args, db);
    }

    free(user);
    free(produtos);
    sqlite3_close(db);
    return EXIT_SUCCESS;
}


