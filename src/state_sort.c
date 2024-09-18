#include <stdio.h>
#include <stdlib.h>
#include "state_sort.h"

int main(void) {
    char path[300];
    int num_menu = -1;

    if (scanf("%s", path) != 1) {
        printf("n/a\n");
        return 0;
    }

    if (scanf("%d", &num_menu) != 1) {
        printf("n/a\n");
        return 0;
    }

    switch (num_menu) {
        case 0:
            output(path); 
            break;
        case 1:
            sort(path);  
            break;
        case 2:
            add_record(path); 
            sort(path);  
            break;
        default:
            printf("n/a\n");   
            break;
    }

    return 0;
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


void sort(const char *path) {
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

    ROW *rows = malloc(size * sizeof(ROW));
    if (!rows) {
        printf("n/a\n");
        fclose(file);
        return;
    }

    for (long int i = 0; i < size; i++) {
        read_row(file, i, &rows[i]);
    }
    fclose(file);

    qsort(rows, size, sizeof(ROW), compare_rows);

    for (long int i = 0; i < size; i++) {
        print_row(&rows[i]);
        printf("\n");
    }

    free(rows);
}

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

void read_row(FILE *file, long int row, ROW *row_data) {
    fseek(file, row * sizeof(ROW), SEEK_SET);
    fread(row_data, sizeof(ROW), 1, file);
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
    long int size = ftell(file) / sizeof(ROW);
    fclose(file);
    return size;
}

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