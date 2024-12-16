# CC = gcc
# CFLAGS = -Wall
# TARGET = shell

# all: $(TARGET)

# $(TARGET): main.o shell.o builtins.o utils.o
# 	$(CC) -o $(TARGET) main.o shell.o builtins.o utils.o

# main.o: src/main.c 
# 	$(CC) $(CFLAGS) -c src/main.c

# shell.o: src/shell.c 
# 	$(CC) $(CFLAGS) -c src/shell.c

# builtins.o: src/builtins.c 
# 	$(CC) $(CFLAGS) -c src/builtins.c

# utils.o: src/utils.c 
# 	$(CC) $(CFLAGS) -c src/utils.c

# clean: 
# 	rm -f *.o $(TARGET)



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

