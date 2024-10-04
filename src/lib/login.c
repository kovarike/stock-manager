// lib/login.c
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
// #include <uuid/uuid.h>
#include "../util/login.h"
#include "../util/global.h"
#include "../util/db.h"

#include <time.h>

void generate_uuid(char *uuid) {
    srand(time(NULL));
    sprintf(uuid, "%08x-%04x-%04x-%04x-%04x%08x",
        rand(), rand() % 0x10000, (rand() % 0x0fff) + 0x4000,
        (rand() % 0x3fff) + 0x8000, rand(), rand());
}


int login(sqlite3 *db) {
    char uuid[37];  // Tamanho do UUID em formato string
    generate_uuid(uuid);
    strcpy(user->id, uuid);
    // uuid_t binuuid;
    // uuid_generate(binuuid);
    // uuid_unparse(binuuid, user->id);

    
    if (check_user_exists(db) != 0 ) {
        printf("Loja já cadastrada: %s\n", user->id);
    } else {
        printf("Cadastro da loja\n");

        printf("Nome da loja: ");
        fgets(user->name, 251, stdin);
        user->name[strcspn(user->name, "\n")] = '\0';

        printf("Email: ");
        fgets(user->email, 251, stdin);
        user->email[strcspn(user->email, "\n")] = '\0';

        printf("Percentual: ");
        scanf("%d", &user->value);
        getchar();
 

        post_user(db);
       
        printf("Loja cadastrada com sucesso. ID: %s\n", user->id);
    }
    
    return 0;
}