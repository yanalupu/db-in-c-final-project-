#ifndef STATUS_EVENTS_H
#define STATUS_EVENTS_H

#include <stdio.h>   // Добавляем <stdio.h> для использования типа FILE
#include "db_structs.h"

void select_all_status_events(FILE *file);
void insert_status_event(FILE *file, void *event);
void update_status_event(FILE *file, int event_id, struct StatusEvent *event);
void delete_status_event(FILE *file, int event_id);

#endif // STATUS_EVENTS_H
