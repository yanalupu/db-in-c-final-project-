#include <stdio.h>
#include <stdlib.h>
#include "shared.h"
#include "db_structs.h"

int select_from_table(FILE *file, void *buffer, size_t size, int count) {
    return fread(buffer, size, count, file);
}

void insert_into_table(FILE *file, void *record, size_t size) {
    fseek(file, 0, SEEK_END);
    fwrite(record, size, 1, file);
}

void update_record_in_table(FILE *file, int id, void *record, size_t size) {
    fseek(file, id * size, SEEK_SET);
    fwrite(record, size, 1, file);
}

// Функция для удаления записи в таблице
void delete_from_table(FILE *file, int id, size_t size) {
    void *buffer = malloc(size);  // Выделение памяти под запись

    if (!buffer) {
        perror("Memory allocation failed");
        return;
    }

    fseek(file, id * size, SEEK_SET);  // Перемещаемся к нужной записи по ID
    fread(buffer, size, 1, file);      // Читаем запись в буфер

    fseek(file, id * size, SEEK_SET);  // Перемещаемся назад к нужной записи
    fwrite(buffer, size, 1, file);     // Обновляем запись

    free(buffer);  // Освобождаем память
}
