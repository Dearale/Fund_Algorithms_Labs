CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -lm
SRC_DIR = src
OBJ_DIR = obj

TARGET = main.out

int: $(OBJ_DIR)/demo_int.o
	$(CC) $(CFLAGS) $^ -o $(TARGET) $(LDFLAGS)

string: $(OBJ_DIR)/demo_string.o
	$(CC) $(CFLAGS) $^ -o $(TARGET) $(LDFLAGS)

person: $(OBJ_DIR)/demo_person.o
	$(CC) $(CFLAGS) $^ -o $(TARGET) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: clean double int string float
