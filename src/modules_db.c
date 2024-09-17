#include <stdio.h>
#include <stdlib.h>
#include "modules.h"
#include "levels.h"
#include "status_events.h"
#include "shared.h"
#include "db_structs.h"

// Функция для выключения всех дополнительных модулей и защиты основного модуля
void shutdown_and_protect_module(FILE *module_file, FILE *level_file, FILE *status_event_file) {
    if (!module_file || !level_file || !status_event_file) {
        fprintf(stderr, "One or more file pointers are NULL\n");
        return;
    }

    // Переключение всех дополнительных модулей в статус 0 и удаление записей
    struct Module module;
    fseek(module_file, 0, SEEK_SET);

    // Переход к началу файла и обновление записей
    long pos;
    while ((pos = ftell(module_file)) >= 0 && fread(&module, sizeof(struct Module), 1, module_file) == 1) {
        if (module.id != 0) {  // Пропустить основной модуль
            // Переводим статус в 0 и устанавливаем флаг удаления
            module.delete_flag = 1;
            
            // Записываем обновленные данные обратно в файл
            fseek(module_file, pos, SEEK_SET);
            if (fwrite(&module, sizeof(struct Module), 1, module_file) != 1) {
                perror("Error writing module data");
                return;
            }
            fseek(module_file, pos + sizeof(struct Module), SEEK_SET);
        }
    }

    // Защита основного модуля (с id = 0)
    fseek(module_file, 0, SEEK_SET);
    if (fread(&module, sizeof(struct Module), 1, module_file) != 1) {
        perror("Error reading module data");
        return;
    }

    // Переводим основной модуль в статус 0
    struct StatusEvent status_event;
    status_event.event_id = 0;
    status_event.module_id = 0;
    status_event.new_status = 0;
    snprintf(status_event.date, sizeof(status_event.date), "01.01.2024");
    snprintf(status_event.time, sizeof(status_event.time), "00:00:00");

    insert_status_event(status_event_file, &status_event);

    // Переводим основной модуль в статус 1
    status_event.new_status = 1;
    insert_status_event(status_event_file, &status_event);

    // Переводим основной модуль в статус -20
    status_event.new_status = -20;
    insert_status_event(status_event_file, &status_event);

    // Перемещение основного модуля в первую ячейку первого уровня памяти
    fseek(level_file, 0, SEEK_SET);
    struct Level level;
    if (fread(&level, sizeof(struct Level), 1, level_file) != 1) {
        perror("Error reading level data");
        return;
    }
    level.protection_flag = 1;
    fseek(level_file, 0, SEEK_SET);
    if (fwrite(&level, sizeof(struct Level), 1, level_file) != 1) {
        perror("Error writing level data");
        return;
    }

    module.level_number = 0;  // Перемещение в первый уровень
    module.cell_number = 0;   // Перемещение в первую ячейку
    fseek(module_file, 0, SEEK_SET);
    if (fwrite(&module, sizeof(struct Module), 1, module_file) != 1) {
        perror("Error writing module data");
        return;
    }

    // Устанавливаем флаг защиты для уровня памяти
    fseek(level_file, 0, SEEK_SET);
    if (fwrite(&level, sizeof(struct Level), 1, level_file) != 1) {
        perror("Error writing level data");
        return;
    }

    printf("Module shutdown and protection complete.\n");
}

int main() {
    printf("Starting program...\n");

    FILE *module_file = fopen("modules.bin", "rb+");
    if (!module_file) {
        perror("Error opening modules file");
        return EXIT_FAILURE;
    }

    FILE *level_file = fopen("levels.bin", "rb+");
    if (!level_file) {
        perror("Error opening levels file");
        fclose(module_file);
        return EXIT_FAILURE;
    }

    FILE *status_event_file = fopen("status_events.bin", "rb+");
    if (!status_event_file) {
        perror("Error opening status events file");
        fclose(module_file);
        fclose(level_file);
        return EXIT_FAILURE;
    }
   shutdown_and_protect_module(module_file, level_file, status_event_file);
select_all_modules(module_file);
select_all_levels(level_file);
select_all_status_events(status_event_file);
    printf("Files opened successfully.\n");



    fclose(module_file);
    fclose(level_file);
    fclose(status_event_file);

    printf("Program finished successfully.\n");
    return EXIT_SUCCESS;
}
