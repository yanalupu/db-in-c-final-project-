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
} ROW;

void output(const char *path);
void sort(const char *path);
void add_record(const char *path);
void read_row(FILE *file, long int row, ROW *row_data);
void print_row(const ROW *row_data);
long int get_file_size(const char *path);
int compare_rows(const void *a, const void *b);
#endif