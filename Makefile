CC = gcc
# CC = x86_64-w64-mingw32-gcc
# ^^^^ use this on windows, or another compiler

CFLAGS = -Wall -Wextra -Wpedantic
LIB_DIR = lib
OBJ_DIR = build
SRC = $(wildcard $(LIB_DIR)/*.c) main.c
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

TARGET = main

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

$(OBJ_DIR)/%.o: $(LIB_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: main.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -f $(OBJ) $(TARGET)
