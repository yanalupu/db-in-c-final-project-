#include <stdio.h>
#include <stdlib.h>

#define ROW_SIZE sizeof(ROW)

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

void input_path(char *path, int *err);
void input_number(int *num_menu, int *err);
void output(const char *path);
void sort_file(const char *path);
void add_record(const char *path);
void read_row(FILE *file, long int row, ROW *row_data);
void write_row(FILE *file, long int row, ROW *row_data);
void swap_rows(FILE *file, long int row0, long int row1);
void print_row(const ROW *row_data);
long int get_file_size(const char *path);

int main(void) {
    char path[303];
    int num_menu = -1, err = 0;
    
    input_path(path, &err);
    if (err) {
        printf("n/a\n");
        return 0;
    }

    input_number(&num_menu, &err);
    if (err) {
        printf("n/a\n");
        return 0;
    }

    switch (num_menu) {
        case 0:
            output(path);
            break;
        case 1:
            sort_file(path);
            output(path);
            break;
        case 2:
            add_record(path);
            sort_file(path);
            output(path);
            break;
        default:
            printf("n/a\n");
            break;
    }

    return 0;
}

void input_path(char *path, int *err) {
    if (scanf("%s", path) != 1) {
        *err = 1;
    }
}

void input_number(int *num_menu, int *err) {
    if (scanf("%d", num_menu) != 1) {
        *err = 1;
    }
}

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

void sort_file(const char *path) {
    FILE *file = fopen(path, "r+b");
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

    // Implementing a simple in-place sorting algorithm (e.g., bubble sort)
    // This is a placeholder for the actual external sorting algorithm
    ROW row1, row2;
    for (long int i = 0; i < size - 1; i++) {
        for (long int j = 0; j < size - i - 1; j++) {
            read_row(file, j, &row1);
            read_row(file, j + 1, &row2);

            // Compare based on date and time
            if (row1.year > row2.year ||
                (row1.year == row2.year && row1.month > row2.month) ||
                (row1.year == row2.year && row1.month == row2.month && row1.day > row2.day) ||
                (row1.year == row2.year && row1.month == row2.month && row1.day == row2.day && row1.hour > row2.hour) ||
                (row1.year == row2.year && row1.month == row2.month && row1.day == row2.day && row1.hour == row2.hour && row1.minute > row2.minute) ||
                (row1.year == row2.year && row1.month == row2.month && row1.day == row2.day && row1.hour == row2.hour && row1.minute == row2.minute && row1.second > row2.second)) {
                swap_rows(file, j, j + 1);
            }
        }
    }

    fclose(file);
}

void add_record(const char *path) {
    FILE *file = fopen(path, "ab");
    if (!file) {
        printf("n/a\n");
        return;
    }

    ROW row_data;
    printf("Enter year month day hour minute second status code: ");
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

void read_row(FILE *file, long int row, ROW *row_data) {
    fseek(file, row * ROW_SIZE, SEEK_SET);
    fread(row_data, sizeof(ROW), 1, file);
}

void write_row(FILE *file, long int row, ROW *row_data) {
    fseek(file, row * ROW_SIZE, SEEK_SET);
    fwrite(row_data, sizeof(ROW), 1, file);
}

void swap_rows(FILE *file, long int row0, long int row1) {
    ROW row0_data, row1_data;
    read_row(file, row0, &row0_data);
    read_row(file, row1, &row1_data);
    write_row(file, row0, &row1_data);
    write_row(file, row1, &row0_data);
}

void print_row(const ROW *row_data) {
    printf("%d %d %d %d %d %d %d %d",
           row_data->year, row_data->month, row_data->day,
           row_data->hour, row_data->minute, row_data->second,
           row_data->status, row_data->code);
}

long int get_file_size(const char *path) {
    FILE *file = fopen(path, "rb");
    if (!file) {
        return -1;
    }
    
    fseek(file, 0, SEEK_END);
    long int size = ftell(file) / ROW_SIZE;
    fclose(file);
    return size;
}
