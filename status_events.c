#include <stdio.h>  // Для FILE
#include <stdlib.h>
#include "status_events.h"
#include "shared.h"
#include "db_structs.h"

void select_all_status_events(FILE *file) {
    if (!file) {
        fprintf(stderr, "File pointer is NULL\n");
        return;
    }
    
    printf("Listing all status events...\n");

    struct StatusEvent event;
    size_t record_size = sizeof(struct StatusEvent);

    fseek(file, 0, SEEK_SET);  // Устанавливаем указатель на начало файла

    while (fread(&event, record_size, 1, file) == 1) {
        printf("Event ID: %d\n", event.event_id);
        printf("Module ID: %d\n", event.module_id);
        printf("New Status: %d\n", event.new_status);
        printf("Date: %s\n", event.date);
        printf("Time: %s\n", event.time);
        printf("-----------------------\n");
    }

    if (ferror(file)) {
        perror("Error reading file");
    }
}

void insert_status_event(FILE *file, void *event) {
    printf("Inserting status event...\n");
    insert_into_table(file, event, sizeof(struct StatusEvent));
}

void update_status_event(FILE *file, int event_id, struct StatusEvent *event) {
    fseek(file, event_id * sizeof(struct StatusEvent), SEEK_SET);
    fwrite(event, sizeof(struct StatusEvent), 1, file);
}

void delete_status_event(FILE *file, int event_id) {
    struct StatusEvent event;
    fseek(file, event_id * sizeof(struct StatusEvent), SEEK_SET);
    fread(&event, sizeof(struct StatusEvent), 1, file);
    // No delete_flag in StatusEvent structure
    fseek(file, event_id * sizeof(struct StatusEvent), SEEK_SET);
    fwrite(&event, sizeof(struct StatusEvent), 1, file);
}
