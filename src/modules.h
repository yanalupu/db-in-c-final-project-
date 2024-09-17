// modules.h

#ifndef MODULES_H
#define MODULES_H

#include <stdio.h>
#include "db_structs.h"

// Объявления функций для работы с модулями
void select_modules(FILE *module_file, int num_records);
void delete_modules_by_ids(FILE *module_file, int *ids, int id_count);
void set_protected_mode(FILE *module_file, FILE *level_file, FILE *status_event_file, int module_id);
void move_module_to_memory(FILE *module_file, int module_id, int level, int cell);
void get_active_modules(FILE *module_file);

#endif // MODULES_H
