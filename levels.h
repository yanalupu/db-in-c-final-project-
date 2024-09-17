#ifndef LEVELS_H
#define LEVELS_H

#include <stdio.h>
#include "db_structs.h"

// Функции для работы с уровнями
void select_all_levels(FILE *file);
void update_level(FILE *file, int level_number, struct Level *level);
void delete_level(FILE *file, int level_number);

#endif // LEVELS_H
