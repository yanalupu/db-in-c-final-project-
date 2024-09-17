#ifndef LEVELS_H
#define LEVELS_H

#include <stdio.h>   // Добавляем <stdio.h> для использования типа FILE
#include "db_structs.h"

void select_levels(FILE *file);
void update_level(FILE *file, int level_number, struct Level *level);
void delete_level(FILE *file, int level_number);

#endif // LEVELS_H
