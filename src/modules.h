#ifndef MODULES_H
#define MODULES_H

#include <stdio.h>
#include "db_structs.h"

// Функции для работы с модулями
void select_all_modules(FILE *file);
void update_module(FILE *file, int id, struct Module *module);
void delete_module(FILE *file, int id);

#endif // MODULES_H
