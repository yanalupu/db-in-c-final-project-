#include <stdio.h>  // Для FILE
#include <stdlib.h>
#include "levels.h"
#include "db_structs.h"

void select_levels(FILE *file) {
    if (!file) {
        fprintf(stderr, "File pointer is NULL\n");
        return;
    }
    
    printf("Listing all levels...\n");

    struct Level level;
    size_t record_size = sizeof(struct Level);

    fseek(file, 0, SEEK_SET);  // Устанавливаем указатель на начало файла

    while (fread(&level, record_size, 1, file) == 1) {
        printf("Level Number: %d\n", level.level_number);
        printf("Cell Count: %d\n", level.cell_count);
        printf("Protection Flag: %d\n", level.protection_flag);
        printf("-----------------------\n");
    }

    if (ferror(file)) {
        perror("Error reading file");
    }
}

void update_level(FILE *file, int level_number, struct Level *level) {
    fseek(file, level_number * sizeof(struct Level), SEEK_SET);
    fwrite(level, sizeof(struct Level), 1, file);
}

void delete_level(FILE *file, int level_number) {
    struct Level level;
    fseek(file, level_number * sizeof(struct Level), SEEK_SET);
    fread(&level, sizeof(struct Level), 1, file);
    // No delete_flag in Level structure
    fseek(file, level_number * sizeof(struct Level), SEEK_SET);
    fwrite(&level, sizeof(struct Level), 1, file);
}
