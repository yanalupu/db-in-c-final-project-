// status_events.h

#ifndef STATUS_EVENTS_H
#define STATUS_EVENTS_H

#include <stdio.h>
#include "db_structs.h"

// Объявления функций для работы с событиями статусов
void select_status_events(FILE *status_event_file, int num_records);

#endif // STATUS_EVENTS_H
