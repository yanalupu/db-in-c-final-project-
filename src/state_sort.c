#include <stdio.h>
#include <stdlib.h>

// Определение структуры ROW
typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int status;
    int code;
} ROW;

// Прототипы функций
void output(const char *path);
void sort_and_output(const char *path);
void add_record(const char *path);
void read_row(FILE *file, long int row, ROW *row_data);
void print_row(const ROW *row_data);
long int get_file_size(const char *path);
int compare_rows(const void *a, const void *b);

int main(void) {
    char path[300];
    int num_menu = -1;

    // Чтение пути к файлу
    if (scanf("%s", path) != 1) {
        printf("n/a\n");
        return 0;
    }

    // Чтение номера меню
    if (scanf("%d", &num_menu) != 1) {
        printf("n/a\n");
        return 0;
    }

    // Обработка выбранного пункта меню
    switch (num_menu) {
        case 0:
            output(path);  // Вывод содержимого файла
            break;
        case 1:
            sort_and_output(path);  // Сортировка и вывод отсортированных данных
            break;
        case 2:
            add_record(path); // Добавление записи
            sort_and_output(path);  // Сортировка после добавления
            break;
        default:
            printf("n/a\n");   // Если выбран некорректный пункт меню
            break;
    }

    return 0;
}

// Функция для вывода данных из файла
void output(const char *path) {
    FILE *file = fopen(path, "rb");
    if (!file) {
        printf("n/a\n");
        return;
    }

    ROW row_data;
    long int size = get_file_size(path);
    if (size < 0) {
        printf("n/a\n");
        fclose(file);
        return;
    }

    for (long int i = 0; i < size; i++) {
        read_row(file, i, &row_data);
        print_row(&row_data);
        printf("\n");
    }

    fclose(file);
}

// Функция для сортировки данных в памяти и их вывода
void sort_and_output(const char *path) {
    FILE *file = fopen(path, "rb");
    if (!file) {
        printf("n/a\n");
        return;
    }

    long int size = get_file_size(path);
    if (size < 0) {
        printf("n/a\n");
        fclose(file);
        return;
    }

    // Выделение памяти для данных
    ROW *rows = malloc(size * sizeof(ROW));
    if (!rows) {
        printf("n/a\n");
        fclose(file);
        return;
    }

    // Чтение данных из файла в массив
    for (long int i = 0; i < size; i++) {
        read_row(file, i, &rows[i]);
    }
    fclose(file);

    // Сортировка данных
    qsort(rows, size, sizeof(ROW), compare_rows);

    // Вывод отсортированных данных
    for (long int i = 0; i < size; i++) {
        print_row(&rows[i]);
        printf("\n");
    }

    // Освобождение выделенной памяти
    free(rows);
}

// Функция для добавления новой записи в файл
void add_record(const char *path) {
    FILE *file = fopen(path, "ab");
    if (!file) {
        printf("n/a\n");
        return;
    }

    ROW row_data;
    if (scanf("%d %d %d %d %d %d %d %d", 
              &row_data.year, 
              &row_data.month, 
              &row_data.day, 
              &row_data.hour, 
              &row_data.minute, 
              &row_data.second, 
              &row_data.status, 
              &row_data.code) != 8) {
        printf("n/a\n");
        fclose(file);
        return;
    }

    fwrite(&row_data, sizeof(ROW), 1, file);
    fclose(file);
}

// Функция для чтения строки из файла
void read_row(FILE *file, long int row, ROW *row_data) {
    fseek(file, row * sizeof(ROW), SEEK_SET);
    fread(row_data, sizeof(ROW), 1, file);
}

// Функция для вывода строки
void print_row(const ROW *row_data) {
    printf("%d %d %d %d %d %d %d %d",
           row_data->year, row_data->month, row_data->day,
           row_data->hour, row_data->minute, row_data->second,
           row_data->status, row_data->code);
}

// Функция для получения размера файла
long int get_file_size(const char *path) {
    FILE *file = fopen(path, "rb");
    if (!file) {
        return -1;
    }
    
    fseek(file, 0, SEEK_END);
    long int size = ftell(file) / sizeof(ROW);
    fclose(file);
    return size;
}

// Функция для сравнения записей (используется qsort)
int compare_rows(const void *a, const void *b) {
    const ROW *row1 = (const ROW *)a;
    const ROW *row2 = (const ROW *)b;

    if (row1->year != row2->year) return row1->year - row2->year;
    if (row1->month != row2->month) return row1->month - row2->month;
    if (row1->day != row2->day) return row1->day - row2->day;
    if (row1->hour != row2->hour) return row1->hour - row2->hour;
    if (row1->minute != row2->minute) return row1->minute - row2->minute;
    return row1->second - row2->second;
}
