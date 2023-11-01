CC = gcc
CFLAGS = -g -Wall -Wextra -Wpedantic -Wconversion
INCLUDES = src/*.h
COMMON_DEPS = $(INCLUDES) Makefile

all: build/main_ex2 build/main_ex2_test

build/%.o: src/%.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

build/main_ex2: build/SkipList.o build/SkipList_main.o $(COMMON_DEPS)
	$(CC) -o build/SkipList build/SkipList.o build/SkipList_main.o

build/main_ex2_test: build/SkipList_test.o build/SkipList.o $(COMMON_DEPS)
	$(CC) -o build/SkipList_test build/SkipList_test.o build/SkipList.o

clean:
	del build\*