#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modules.h"
#include "levels.h"
#include "status_events.h"
#include "shared.h"
#include "db_structs.h"

// Функция для отображения меню
void print_menu() {
    printf("\nPlease choose one operation:\n");
    printf("    1. SELECT\n");
    printf("    2. INSERT\n");
    printf("    3. UPDATE\n");
    printf("    4. DELETE\n");
    printf("    5. Get all active additional modules (last module status is 1)\n");
    printf("    6. Delete modules by ids\n");
    printf("    7. Set protected mode for module by id\n");
    printf("    8. Move module by id to specified memory level and cell\n");
    printf("    9. Set protection flag of the specified memory level\n");
    printf("> ");
}

// Функция для выбора данных из базы
void handle_select(FILE *module_file, FILE *level_file, FILE *status_event_file) {
    int table_choice;
    printf("Please choose a table:\n");
    printf("    1. Modules\n");
    printf("    2. Levels\n");
    printf("    3. Status events\n");
    printf("> ");
    scanf("%d", &table_choice);

    int num_records;
    printf("Insert the number of records or leave empty to output all of them: ");
    scanf("%d", &num_records);

    switch (table_choice) {
        case 1:
            select_modules(module_file, num_records);
            break;
        case 2:
            select_levels(level_file, num_records);
            break;
        case 3:
            select_status_events(status_event_file, num_records);
            break;
        default:
            printf("Invalid table choice.\n");
    }
}

// Функция для удаления модулей по ID
void handle_delete(FILE *module_file) {
    char input[100];
    printf("Please input the ids of the deleting modules: ");
    getchar();  // clear newline from buffer
    fgets(input, sizeof(input), stdin);

    int ids[10], id_count = 0;
    char *token = strtok(input, " ");
    while (token != NULL) {
        ids[id_count++] = atoi(token);
        token = strtok(NULL, " ");
    }

    delete_modules_by_ids(module_file, ids, id_count);
}

// Функция для установки защищенного режима для модуля
void handle_protect_mode(FILE *module_file, FILE *level_file, FILE *status_event_file) {
    int module_id;
    printf("Please input the id of the module to set protected mode: ");
    scanf("%d", &module_id);

    set_protected_mode(module_file, level_file, status_event_file, module_id);
}

// Функция для перемещения модуля
void handle_move_module(FILE *module_file) {
    int module_id, level, cell;
    printf("Please input the module id, level, and cell: ");
    scanf("%d %d %d", &module_id, &level, &cell);

    move_module_to_memory(module_file, module_id, level, cell);
}

// Функция для установки флага защиты для уровня памяти
void handle_set_protection_flag(FILE *level_file) {
    int level_id;
    printf("Please input the memory level id to set protection flag: ");
    scanf("%d", &level_id);

    set_memory_protection_flag(level_file, level_id);
}

void select_modules(FILE *module_file, int num_records) {
    struct Module module;
    fseek(module_file, 0, SEEK_SET);
    
    int count = 0;
    while (fread(&module, sizeof(struct Module), 1, module_file) == 1) {
        if (module.delete_flag == 0) {
            printf("%d %s %d %d %d\n", module.id, module.name, module.level_number, module.cell_number, module.delete_flag);
            if (++count == num_records) break;
        }
    }
}
void delete_modules_by_ids(FILE *module_file, int *ids, int id_count) {
    struct Module module;
    fseek(module_file, 0, SEEK_SET);

    while (fread(&module, sizeof(struct Module), 1, module_file) == 1) {
        for (int i = 0; i < id_count; i++) {
            if (module.id == ids[i]) {
                module.delete_flag = 1;  // Mark for deletion
                fseek(module_file, -(long)sizeof(struct Module), SEEK_CUR);
                fwrite(&module, sizeof(struct Module), 1, module_file);
                break;
            }
        }
    }
}


void set_protected_mode(FILE *module_file, FILE *level_file, FILE *status_event_file, int module_id) {
    struct Module module;
    fseek(module_file, 0, SEEK_SET);
    
    while (fread(&module, sizeof(struct Module), 1, module_file) == 1) {
        if (module.id == module_id) {
            module.delete_flag = 0;  // Убираем флаг удаления
            module.level_number = 0; // Перемещение в первый уровень
            module.cell_number = 0;  // Перемещение в первую ячейку

           fseek(module_file, -(long)sizeof(struct Module), SEEK_CUR);

            fwrite(&module, sizeof(struct Module), 1, module_file);
            
            // Добавляем события статусов
            struct StatusEvent event;
            event.module_id = module_id;
            event.new_status = 1; // Переводим в защищенный режим
            snprintf(event.date, sizeof(event.date), "01.01.2024");
            snprintf(event.time, sizeof(event.time), "12:00:00");

            fseek(status_event_file, 0, SEEK_END);
            fwrite(&event, sizeof(struct StatusEvent), 1, status_event_file);
            break;
        }
    }
}
void move_module_to_memory(FILE *module_file, int module_id, int level, int cell) {
    struct Module module;
    fseek(module_file, 0, SEEK_SET);
    
    while (fread(&module, sizeof(struct Module), 1, module_file) == 1) {
        if (module.id == module_id) {
            module.level_number = level;
            module.cell_number = cell;

           fseek(module_file, -(long)sizeof(struct Module), SEEK_CUR);

            fwrite(&module, sizeof(struct Module), 1, module_file);
            break;
        }
    }
}
void get_active_modules(FILE *module_file) {
    struct Module module;
    fseek(module_file, 0, SEEK_SET);
    
    while (fread(&module, sizeof(struct Module), 1, module_file) == 1) {
        if (module.delete_flag == 0) {
            printf("Active module: %d %s\n", module.id, module.name);
        }
    }
}
void set_memory_protection_flag(FILE *level_file, int level_id) {
    struct Level level;
    fseek(level_file, 0, SEEK_SET);

    while (fread(&level, sizeof(struct Level), 1, level_file) == 1) {
        if (level.level_number == level_id) {
            level.protection_flag = 1;  // Set protection flag
            fseek(level_file, -(long)sizeof(struct Level), SEEK_CUR);
            fwrite(&level, sizeof(struct Level), 1, level_file);
            break;
        }
    }
}

void select_levels(FILE *level_file, int num_records) {
    struct Level level;
    fseek(level_file, 0, SEEK_SET);
    
    int count = 0;
    while (fread(&level, sizeof(struct Level), 1, level_file) == 1) {
        printf("Level: %d, Cells: %d, Protection: %d\n", level.level_number, level.cell_count, level.protection_flag);
        if (++count == num_records) break;
    }
}
void select_status_events(FILE *status_event_file, int num_records) {
    struct StatusEvent event;
    fseek(status_event_file, 0, SEEK_SET);
    
    int count = 0;
    while (fread(&event, sizeof(struct StatusEvent), 1, status_event_file) == 1) {
        printf("Event ID: %d, Module ID: %d, Status: %d, Date: %s, Time: %s\n",
               event.event_id, event.module_id, event.new_status, event.date, event.time);
        if (++count == num_records) break;
    }
}


int main() {
    printf("Starting program...\n");

    FILE *module_file = fopen("master_modules.db", "rb+");
    if (!module_file) {
        perror("Error opening modules file");
        return EXIT_FAILURE;
    }

    FILE *level_file = fopen("master_levels.db", "rb+");
    if (!level_file) {
        perror("Error opening levels file");
        fclose(module_file);
        return EXIT_FAILURE;
    }

    FILE *status_event_file = fopen("master_status_events.db", "rb+");
    if (!status_event_file) {
        perror("Error opening status events file");
        fclose(module_file);
        fclose(level_file);
        return EXIT_FAILURE;
    }

    int choice;
    do {
        print_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                handle_select(module_file, level_file, status_event_file);
                break;
            case 2:
                // handle_insert(); (реализовать при необходимости)
                break;
            case 3:
                // handle_update(); (реализовать при необходимости)
                break;
            case 4:
                handle_delete(module_file);
                break;
            case 5:
                get_active_modules(module_file);
                break;
            case 6:
                handle_delete(module_file);
                break;
            case 7:
                handle_protect_mode(module_file, level_file, status_event_file);
                break;
            case 8:
                handle_move_module(module_file);
                break;
            case 9:
                handle_set_protection_flag(level_file);
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);

    fclose(module_file);
    fclose(level_file);
    fclose(status_event_file);

    printf("Program finished successfully.\n");
    return EXIT_SUCCESS;
}
