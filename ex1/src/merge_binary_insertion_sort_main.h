#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include "merge_binary_insertion_sort.h"
#define BUFFER_SIZE 4096
/**
 * These functions take as input two void pointers to one of the fields in a struct record.
 * Depending on which field is chosen to be sorted (int, double, or string),
 * each of these functions will return 0 if the two elements are equal to each other.
 * If the first element is less than the second element, it will return -1. Otherwise, it will return 1.
 */
static int compar_record_int_field(const void* r1_p,const void* r2_p);
static int compar_record_double_field(const void* r1_p,const void* r2_p);
static int compar_record_string_field(const void* r1_p, const void* r2_p);


//! frees memory for each and every element in the ArrayToBeSorted, including the array itself
static void free_array(ArrayToBeSorted* array);
#ifdef PRINT_ARR
//! prints out the sorted array or about to be sorted
static void print_array(ArrayToBeSorted* array);
#endif

/**
 * This function takes a const char* file_name as the first parameter and an ArrayToBeSorted*
 *  array as the second parameter.The first parameter indicates the name of the file from which 
 * we read the data and load it into memory as an array in ArrayToBeSorted* array.
 */
void read_file(const char* file_name, ArrayToBeSorted* array);

/**
 * This function takes five parameters. The first four parameters are for initializing 
 * the field values of a struct record*, which will later be added to the array.
 * The fifth parameter is for adding the struct record* element to the actual array.
 */
void load_array(int integer_part, char* string_part, int int_part, double double_part, ArrayToBeSorted* array);

/**
 * This function takes a const char* file_name as the first parameter and an ArrayToBeSorted* array as the second parameter.
 * The first parameter indicates the name of the file to which we write the data, more specifically, 
 * the sorted array that is sorted by the precedence of the element.
 */
void write_to_file(const char* file_name, ArrayToBeSorted* array);

/**
 * This function takes four parameters. The first parameter, infile, is the path to the CSV file containing the records to sort.
 * The second parameter, outfile, is a path in which to save the sorted records (which must be different from infile).
 * The third parameter, k, is a parameter of the algorithm.
 * The fourth parameter, field, can be 1, 2 or 3 and indicates which of the three fields should be used to sort the records.
 */
void sort_records(const char *infile, const char *outfile, size_t k, size_t field);

/**
 * This function accepts a character array and an integer pointer as input.
 * The input cannot be NULL. It checks the array of characters and verifies if it contains correctly formulated positive integers.
 * If so, it returns 1. Otherwise, it returns 0 to indicate that there are characters other than integers or that the value is negative.
 * White spaces before and after the correct positive integer value are accepted.
 */
bool parse_int(char *string, int *integer);