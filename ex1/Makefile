CC = gcc
CFLAGS = -g -Wall -Wextra -Wpedantic -Wconversion
INCLUDES = src/*.h
COMMON_DEPS = $(INCLUDES) Makefile

all: build/main_ex1 build/main_ex1_test

build/%.o: src/%.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

build/main_ex1: build/merge_binary_insertion_sort.o build/merge_binary_insertion_sort_main.o $(COMMON_DEPS)
	$(CC) -o build/merge_binary_insertion_sort build/merge_binary_insertion_sort.o build/merge_binary_insertion_sort_main.o

build/main_ex1_test: build/merge_binary_insertion_sort_tests.o build/merge_binary_insertion_sort.o build/unity.o $(COMMON_DEPS)
	$(CC) -o build/merge_binary_insertion_sort_tests build/merge_binary_insertion_sort_tests.o build/merge_binary_insertion_sort.o build/unity.o 

clean:
	del build\*