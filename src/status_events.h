#ifndef STATUS_EVENTS_H
#define STATUS_EVENTS_H

#include <stdio.h>   // Добавляем <stdio.h> для использования типа FILE
#include "db_structs.h"

// Функции для работы с событиями статусов
void select_all_status_events(FILE *file);
void insert_status_event(FILE *file, struct StatusEvent *event);
void update_status_event(FILE *file, int event_id, struct StatusEvent *event);
void delete_status_event(FILE *file, int event_id);

#endif // STATUS_EVENTS_H
