#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#include "global.h"



void command_get(sqlite3*db);
void command_Insert(sqlite3*db, int codigo, double preco_custo, int estoque);
void command_Remove(sqlite3*db, int codigo, int quantidade);
void command_update(sqlite3 *db, int codigo, double preco_custo, int estoque);
void command_Zero(sqlite3 * db);
void command_Delete(sqlite3 *db, int codigo);


#endif










