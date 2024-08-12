CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS =

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, build/%.o, $(SRC))
TARGET = build/bank_system

all: build_dir $(TARGET)

build_dir:
	@if not exist build (mkdir build)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@if exist build (rd /s /q build)

.PHONY: clean all build_dir
