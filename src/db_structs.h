#ifndef DB_STRUCTS_H
#define DB_STRUCTS_H

// Структура для таблицы MODULES
struct Module {
    int id;                // ID модуля
    char name[30];         // Название модуля
    int level_number;      // Номер уровня памяти
    int cell_number;       // Номер ячейки на уровне
    int delete_flag;       // Флаг удаления
};

// Структура для таблицы LEVELS
struct Level {
    int level_number;      // Номер уровня памяти
    int cell_count;        // Количество ячеек
    int protection_flag;   // Флаг защищенности
    int delete_flag;       // Флаг удаления
};

// Структура для таблицы STATUS_EVENTS
struct StatusEvent {
    int event_id;          // ID события
    int module_id;         // ID модуля
    int new_status;        // Новый статус модуля
    char date[11];         // Дата в формате "dd.mm.yyyy"
    char time[9];          // Время в формате "hh:mm:ss"
};

#endif // DB_STRUCTS_H
