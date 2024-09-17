// levels.h

#ifndef LEVELS_H
#define LEVELS_H

#include <stdio.h>
#include "db_structs.h"

// Объявления функций для работы с уровнями памяти
void select_levels(FILE *level_file, int num_records);
void set_memory_protection_flag(FILE *level_file, int level_id);

#endif // LEVELS_H
