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
#include "util/global.h"
#include "util/sh.h"


int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    char input[MAX_INPUT];
    char* args[MAX_ARGS];
    
    produtos = (Produto*)malloc(MAX_PRODUTOS * sizeof(Produto));
    if (produtos == NULL) {
        fprintf(stderr, "Erro ao alocar memória.\n");
        exit(EXIT_FAILURE);
        return 1;
    }

    printf("\nDigite um dos comandos (manager, exit):\n");

    while (1) {
        read_command(input);
        parse_command(input, args);
        execute_command(args);
    }

    free(produtos);
    return 0;
}
