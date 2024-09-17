CC = gcc
CFLAGS = -Wall -Wextra -g
SRC = modules_db.c shared.c modules.c levels.c status_events.c
OBJ = $(SRC:.c=.o)
TARGET = modules_db

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /Q *.bin *.exe

.PHONY: all clean
