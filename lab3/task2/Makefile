CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -lm
SRC_DIR = src
OBJ_DIR = obj

TARGET = main.out

double: $(OBJ_DIR)/demo_double.o
	$(CC) $(CFLAGS) $^ -o $(TARGET) $(LDFLAGS)

int: $(OBJ_DIR)/demo_int.o
	$(CC) $(CFLAGS) $^ -o $(TARGET) $(LDFLAGS)

string: $(OBJ_DIR)/demo_string.o
	$(CC) $(CFLAGS) $^ -o $(TARGET) $(LDFLAGS)

float: $(OBJ_DIR)/demo_float.o
	$(CC) $(CFLAGS) $^ -o $(TARGET) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: clean double int string float
