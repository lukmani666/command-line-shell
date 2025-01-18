CC = gcc
CFLAGS = -Wall
TARGET = shell
OBJ_DIR = obj
SRC_DIR = src

SRC = $(SRC_DIR)/main.c $(SRC_DIR)/shell.c $(SRC_DIR)/builtins.c $(SRC_DIR)/utils.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)

