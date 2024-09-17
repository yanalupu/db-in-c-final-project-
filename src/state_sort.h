#ifndef STATE_SORT_H
#define STATE_SORT_H
#define PATH "door_state_1"
#include <stdio.h>
typedef struct Rows {
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int second;
  int status;
  int code;
} ROWS;
void input_path(char *path, int *err);
void input_number(int *num_menu, int *err);
void get_size_of_binary_file(char *path, long int *size, int *err);
void output(ROWS *row, FILE *file, int *ptr, char *path, long int size,
            int count_struct);
void print_row(int *ptr, int count_struct);
void read_row(FILE *file, long int row, int *ptr, int count_struct);
void write_row(FILE *file, long int row, int *ptr, int count_struct);
void fast_sort(FILE *file, int **ptr, long int left, long int right,
               int count_struct);
void swap_rows(FILE *file, long int row0, long int row1, int **ptr,
               int count_struct);
#endif
