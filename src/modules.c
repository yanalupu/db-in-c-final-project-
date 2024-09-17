#include <stdio.h>  // Для FILE
#include <stdlib.h>
#include "modules.h"
#include "db_structs.h"

void select_all_modules(FILE *file) {
    if (!file) {
        fprintf(stderr, "File pointer is NULL\n");
        return;
    }
    
    printf("Listing all modules...\n");

    struct Module module;
    size_t record_size = sizeof(struct Module);

    fseek(file, 0, SEEK_SET);  // Устанавливаем указатель на начало файла

    while (fread(&module, record_size, 1, file) == 1) {
        printf("Module ID: %d\n", module.id);
        printf("Name: %s\n", module.name);
        printf("Level Number: %d\n", module.level_number);
        printf("Cell Number: %d\n", module.cell_number);
        printf("Delete Flag: %d\n", module.delete_flag);
        printf("-----------------------\n");
    }

    if (ferror(file)) {
        perror("Error reading file");
    }
}

void update_module(FILE *file, int id, struct Module *module) {
    fseek(file, id * sizeof(struct Module), SEEK_SET);
    fwrite(module, sizeof(struct Module), 1, file);
}

void delete_module(FILE *file, int id){
    struct Module module;
    fseek(file, id * sizeof(struct Module), SEEK_SET);
    fread(&module, sizeof(struct Module), 1, file);
    module.delete_flag = 1;
    fseek(file, id * sizeof(struct Module), SEEK_SET);
    fwrite(&module, sizeof(struct Module), 1, file);
}
