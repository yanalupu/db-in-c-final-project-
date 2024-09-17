#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Структуры данных
struct Module {
    int id;
    char name[30];
    int level_number;
    int cell_number;
    int delete_flag;
};

struct Level {
    int level_number;
    int cell_count;
    int protection_flag;
    int delete_flag;
};

struct StatusEvent {
    int event_id;
    int module_id;
    int new_status;
    char date[11];
    char time[9];
};

// Функции для создания бинарных файлов
void create_modules_bin() {
    FILE *file = fopen("modules.bin", "wb");
    if (!file) {
        perror("Error opening modules.bin");
        return;
    }

    struct Module modules[] = {
        {1, "Module A", 1, 1, 0},
        {2, "Module B", 2, 3, 0},
        {3, "Module C", 1, 2, 1}  // Этот модуль помечен как удаленный
    };

    fwrite(modules, sizeof(struct Module), 3, file);
    fclose(file);
    printf("modules.bin created and populated.\n");
}

void create_levels_bin() {
    FILE *file = fopen("levels.bin", "wb");
    if (!file) {
        perror("Error opening levels.bin");
        return;
    }

    struct Level levels[] = {
        {1, 4, 0, 0},
        {2, 6, 1, 0},
        {3, 5, 0, 1}  // Этот уровень помечен как удаленный
    };

    fwrite(levels, sizeof(struct Level), 3, file);
    fclose(file);
    printf("levels.bin created and populated.\n");
}

void create_status_events_bin() {
    FILE *file = fopen("status_events.bin", "wb");
    if (!file) {
        perror("Error opening status_events.bin");
        return;
    }

    struct StatusEvent events[] = {
        {1, 1, 2, "12.09.2024", "12:00:00"},
        {2, 2, 3, "13.09.2024", "14:30:00"},
        {3, 1, 4, "14.09.2024", "09:15:00"}
    };

    fwrite(events, sizeof(struct StatusEvent), 3, file);
    fclose(file);
    printf("status_events.bin created and populated.\n");
}

// Главная функция
int main() {
    create_modules_bin();
    create_levels_bin();
    create_status_events_bin();

    printf("All binary files created and populated successfully.\n");
    return 0;
}
