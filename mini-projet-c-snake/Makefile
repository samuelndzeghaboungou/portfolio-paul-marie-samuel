CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -O2 -g
SANITIZE_FLAGS = -fsanitize=address -fno-omit-frame-pointer
INCLUDES = -Iinclude
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

SRC = src/main.c src/game.c
TARGET = snake.exe

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC) -o $(TARGET) $(LIBS)

asan: $(SRC)
	$(CC) $(CFLAGS) $(SANITIZE_FLAGS) $(INCLUDES) $(SRC) -o $(TARGET) $(LIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	del /Q $(TARGET) 2>nul || exit 0

.PHONY: all asan run clean
