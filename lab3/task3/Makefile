CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -lm
SRC_DIR = src
OBJ_DIR = obj

SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/demonstration.c $(SRC_DIR)/liver_ops.c $(SRC_DIR)/liver_read.c $(SRC_DIR)/modlog.c $(SRC_DIR)/statusManager.c $(SRC_DIR)/liver.c
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TARGET = main.out

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: clean