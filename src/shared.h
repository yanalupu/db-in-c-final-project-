#ifndef SHARED_H
#define SHARED_H

#include <stdio.h>
#include <stdlib.h>
#include "db_structs.h"

int select_from_table(FILE *file, void *buffer, size_t size, int count);
void insert_into_table(FILE *file, void *record, size_t size);
void update_record_in_table(FILE *file, int id, void *record, size_t size);
void delete_from_table(FILE *file, int id, size_t size);

#endif // SHARED_H
