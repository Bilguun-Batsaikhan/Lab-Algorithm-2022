#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "merge_binary_insertion_sort.h"
#include "unity.h"
#include <time.h>

//! Precedence relation used in tests (integer)
static int precedes_int(const void* i1_p,const void* i2_p) {
  int* int1_p = (int*)i1_p;
  int* int2_p = (int*)i2_p;
  if((*int1_p) < (*int2_p)) {
    return -1;
  } else if((*int1_p) > (*int2_p)) {
    return 1;
  } else
  return 0;
}

//! Precedence relation used in tests (double)
static int precedes_double(const void* i1_p,const void* i2_p) {
  double* int1_p = (double*)i1_p;
  double* int2_p = (double*)i2_p;
  if((*int1_p) < (*int2_p)) {
    return -1;
  } else if((*int1_p) > (*int2_p)) {
    return 1;
  } else
  return 0;
}

//! Precedence relation used in tests (string)
static int precedes_string(const void* r1_p, const void* r2_p) {
  char *rec1_p = (char *)r1_p;
  char *rec2_p = (char *)r2_p;
  return strcmp(rec1_p, rec2_p);
}
//! Data elements that are initialized before each test
//! @{
static int i1,i2,i3;
static ArrayToBeSorted* array_int;
static ArrayToBeSorted* array_string;
static ArrayToBeSorted* array_double;
//! @}

//! Sets up the data needed for testing
void setUp() {
  i1 = -26;
  i2 = 20;
  i3 = 22;
  srand((unsigned int)time(NULL));
  array_int = array_to_be_sorted_create(precedes_int);
  array_string = array_to_be_sorted_create(precedes_string);
  array_double = array_to_be_sorted_create(precedes_double);
}

//! Deallocates the data needed for testing
void tearDown() {
  array_to_be_sorted_free_memory(array_int);
}

//! Checks if not NULL pointer is returned upon creating array_to_be_sorted struct
static void test_create_not_null() {
  TEST_ASSERT_NOT_NULL(array_int);
}

//! Checks if initial capacity of the array isn't zero
static void test_ini_cap_not_zero() {
  TEST_ASSERT_NOT_EQUAL(0, array_int->array_capacity);
}

//! Checks if capacity of the array is expanding upon adding more elements
static void test_is_cap_expand() {
  array_to_be_sorted_add(array_int, &i3);
  array_to_be_sorted_add(array_int, &i1);
  array_to_be_sorted_add(array_int, &i2);
  array_to_be_sorted_add(array_int, &i1);
  array_to_be_sorted_add(array_int, &i2);
  TEST_ASSERT_NOT_EQUAL(2, array_int->array_capacity);
}

//! Checks if i'm getting the correct element by its index
static void test_is_getting_correct_el() {
  array_to_be_sorted_add(array_int, &i3);
  array_to_be_sorted_add(array_int, &i1);
  array_to_be_sorted_add(array_int, &i2);
  TEST_ASSERT_EQUAL_INT(-26, *(int*)array_to_be_sorted_get(array_int, 1));
}

//! Checks if an integer element is added to the array
static void test_is_int_el_inserted() {
  array_to_be_sorted_add(array_int, &i3);
  TEST_ASSERT_EQUAL_INT(22, *(int*)array_to_be_sorted_get(array_int, 0));
}

//! Checks if added elements are added by it's inserting order
static void test_is_int_el_inserted_by_order() {
  array_to_be_sorted_add(array_int, &i3);
  array_to_be_sorted_add(array_int, &i1);
  array_to_be_sorted_add(array_int, &i2);
  int arr[3]; unsigned long i;
  for(i = 0; i < 3; i++) {
    arr[i] = *(int*)array_to_be_sorted_get(array_int, i);
  }
  int exp_arr[] = {22, -26, 20};
  TEST_ASSERT_EQUAL_INT_ARRAY(exp_arr, arr, 3);
}

//! Checks if number of elements are increasing after inserting an element
static void test_is_nel_increasing_on_insert() {
  array_to_be_sorted_add(array_int, &i3);
  array_to_be_sorted_add(array_int, &i1);
  array_to_be_sorted_add(array_int, &i2);
  TEST_ASSERT_EQUAL(3, array_size(array_int));
}

//! Checks if array is empty
static void test_zero_el() {
  TEST_ASSERT_TRUE(array_is_empty(array_int));
}

//! Checks that the element from a one-element array is correctly accessed
static void test_array_add_get_one_el() {
  array_to_be_sorted_add(array_int, &i1);
  TEST_ASSERT_EQUAL_INT(-26, *(int*)array_to_be_sorted_get(array_int, 0));
}
/**
 * merge_binary_insertion_sort test for int
*/


//! Checks if an array with 5 positive elements is being sorted correctly by use only merge_sort
static void testi_merge_sort_five_pos_el() 
{
  int exp_arr[] = {13, 25, 32, 59, 89};
  int arr[5];
  unsigned long i;

  array_to_be_sorted_add(array_int, &exp_arr[1]);
  array_to_be_sorted_add(array_int, &exp_arr[3]);
  array_to_be_sorted_add(array_int, &exp_arr[2]);
  array_to_be_sorted_add(array_int, &exp_arr[4]);
  array_to_be_sorted_add(array_int, &exp_arr[0]);
  merge_binary_insertion_sort(array_int->array, array_int->nitems, 0, array_int -> compar);
  for(i = 0; i < 5; i++) {
    arr[i] = *(int*)array_to_be_sorted_get(array_int, i);
  }
  TEST_ASSERT_EQUAL_INT_ARRAY(exp_arr, arr, 5);
}

//! Checks if an array with 5 positive elements is being sorted correctly by use only binary_insertion_sort
static void testi_binary_insertion_sort_five_pos_el() 
{
  int exp_arr[] = {13, 25, 32, 59, 89};
  int arr[5];
  unsigned long i;

  array_to_be_sorted_add(array_int, &exp_arr[1]);
  array_to_be_sorted_add(array_int, &exp_arr[3]);
  array_to_be_sorted_add(array_int, &exp_arr[2]);
  array_to_be_sorted_add(array_int, &exp_arr[4]);
  array_to_be_sorted_add(array_int, &exp_arr[0]);
  merge_binary_insertion_sort(array_int->array, array_int->nitems, 6, array_int -> compar);
  for(i = 0; i < 5; i++) {
    arr[i] = *(int*)array_to_be_sorted_get(array_int, i);
  }
  TEST_ASSERT_EQUAL_INT_ARRAY(exp_arr, arr, 5);
}

//! Checks if an array with 5 positive elements is being sorted correctly by merge_binary_insertion_sort
static void testi_merge_binary_insertion_sort_five_pos_el() 
{
  int exp_arr[] = {13, 25, 32, 59, 89};
  int arr[5];
  unsigned long i;
  size_t k;

  array_to_be_sorted_add(array_int, &exp_arr[1]);
  array_to_be_sorted_add(array_int, &exp_arr[3]);
  array_to_be_sorted_add(array_int, &exp_arr[2]);
  array_to_be_sorted_add(array_int, &exp_arr[4]);
  array_to_be_sorted_add(array_int, &exp_arr[0]);
  k = (size_t)rand() % 5;
  merge_binary_insertion_sort(array_int->array, array_int->nitems, k, array_int -> compar);
  for(i = 0; i < 5; i++) {
    arr[i] = *(int*)array_to_be_sorted_get(array_int, i);
  }
  TEST_ASSERT_EQUAL_INT_ARRAY(exp_arr, arr, 5);
}

//! Checks if an array with 5 negative elements is being sorted correctly by use only merge_sort
static void testi_merge_sort_five_neg_el() {
  int exp_arr[] = {-89, -59, -32, -25, -13};
  int arr[5];
  unsigned long i;

  array_to_be_sorted_add(array_int, &exp_arr[1]);
  array_to_be_sorted_add(array_int, &exp_arr[3]);
  array_to_be_sorted_add(array_int, &exp_arr[2]);
  array_to_be_sorted_add(array_int, &exp_arr[4]);
  array_to_be_sorted_add(array_int, &exp_arr[0]);
  merge_binary_insertion_sort(array_int->array, array_int->nitems, 0, array_int -> compar);
  for(i = 0; i < 5; i++) {
    arr[i] = *(int*)array_to_be_sorted_get(array_int, i);
  }
  TEST_ASSERT_EQUAL_INT_ARRAY(exp_arr, arr, 5);
}

//! Checks if an array with 5 negative elements is being sorted correctly by use only binary_insertion_sort
static void testi_binary_insertion_sort_five_neg_el() {
  int exp_arr[] = {-89, -59, -32, -25, -13};
  int arr[5];
  unsigned long i;

  array_to_be_sorted_add(array_int, &exp_arr[1]);
  array_to_be_sorted_add(array_int, &exp_arr[3]);
  array_to_be_sorted_add(array_int, &exp_arr[2]);
  array_to_be_sorted_add(array_int, &exp_arr[4]);
  array_to_be_sorted_add(array_int, &exp_arr[0]);
  merge_binary_insertion_sort(array_int->array, array_int->nitems, 6, array_int -> compar);
  for(i = 0; i < 5; i++) {
    arr[i] = *(int*)array_to_be_sorted_get(array_int, i);
  }
  TEST_ASSERT_EQUAL_INT_ARRAY(exp_arr, arr, 5);
}

//! Checks if an array with 5 negative elements is being sorted correctly by use only merge_binary_insertion_sort
static void testi_merge_binary_insertion_sort_five_neg_el() {
  int exp_arr[] = {-89, -59, -32, -25, -13};
  int arr[5];
  unsigned long i;
  size_t k;

  array_to_be_sorted_add(array_int, &exp_arr[1]);
  array_to_be_sorted_add(array_int, &exp_arr[3]);
  array_to_be_sorted_add(array_int, &exp_arr[2]);
  array_to_be_sorted_add(array_int, &exp_arr[4]);
  array_to_be_sorted_add(array_int, &exp_arr[0]);
  k = (size_t)rand() % 5;
  merge_binary_insertion_sort(array_int->array, array_int->nitems, k, array_int -> compar);
  for(i = 0; i < 5; i++) {
    arr[i] = *(int*)array_to_be_sorted_get(array_int, i);
  }
  TEST_ASSERT_EQUAL_INT_ARRAY(exp_arr, arr, 5);
}

//! Checks if an array with 5 positive and negative elements is being sorted correctly by only use merge_sort
static void testi_merge_sort_five_pos_neg_el() {
  int exp_arr[] = {-59, -25, 13, 32, 89};
  int arr[5];
  unsigned long i;

  array_to_be_sorted_add(array_int, &exp_arr[1]);
  array_to_be_sorted_add(array_int, &exp_arr[3]);
  array_to_be_sorted_add(array_int, &exp_arr[2]);
  array_to_be_sorted_add(array_int, &exp_arr[4]);
  array_to_be_sorted_add(array_int, &exp_arr[0]);
  merge_binary_insertion_sort(array_int->array, array_int->nitems, 0, array_int -> compar);
  for(i = 0; i < 5; i++) {
    arr[i] = *(int*)array_to_be_sorted_get(array_int, i);
  }
  TEST_ASSERT_EQUAL_INT_ARRAY(exp_arr, arr, 5);
}

//! Checks if an array with 5 positive and negative elements is being sorted correctly by only use binary_insertion_sort
static void testi_binary_insertion_sort_five_pos_neg_el() {
  int exp_arr[] = {-59, -25, 13, 32, 89};
  int arr[5];
  unsigned long i;

  array_to_be_sorted_add(array_int, &exp_arr[1]);
  array_to_be_sorted_add(array_int, &exp_arr[3]);
  array_to_be_sorted_add(array_int, &exp_arr[2]);
  array_to_be_sorted_add(array_int, &exp_arr[4]);
  array_to_be_sorted_add(array_int, &exp_arr[0]);
  merge_binary_insertion_sort(array_int->array, array_int->nitems, 6, array_int -> compar);
  for(i = 0; i < 5; i++) {
    arr[i] = *(int*)array_to_be_sorted_get(array_int, i);
  }
  TEST_ASSERT_EQUAL_INT_ARRAY(exp_arr, arr, 5);
}

//! Checks if an array with 5 positive and negative elements is being sorted correctly by merge_binary_insertion_sort
static void testi_merge_binary_insertion_sort_five_pos_neg_el() {
  int exp_arr[] = {-59, -25, 13, 32, 89};
  int arr[5];
  unsigned long i;
  size_t k;

  array_to_be_sorted_add(array_int, &exp_arr[1]);
  array_to_be_sorted_add(array_int, &exp_arr[3]);
  array_to_be_sorted_add(array_int, &exp_arr[2]);
  array_to_be_sorted_add(array_int, &exp_arr[4]);
  array_to_be_sorted_add(array_int, &exp_arr[0]);
  k = (size_t)rand() % 5;
  merge_binary_insertion_sort(array_int->array, array_int->nitems, k, array_int -> compar);
  for(i = 0; i < 5; i++) {
    arr[i] = *(int*)array_to_be_sorted_get(array_int, i);
  }
  TEST_ASSERT_EQUAL_INT_ARRAY(exp_arr, arr, 5);
}

/**
 * merge_binary_insertion_sort test for double
*/

//! Checks if an array with 5 positive elements is being sorted correctly by use only merge_sort
static void testd_merge_sort_five_pos_el() 
{
  double exp_arr[] = {13.445, 25.242, 32.21310, 59.0011, 89.903};
  double arr[5];
  unsigned long i;

  array_to_be_sorted_add(array_double, &exp_arr[1]);
  array_to_be_sorted_add(array_double, &exp_arr[3]);
  array_to_be_sorted_add(array_double, &exp_arr[2]);
  array_to_be_sorted_add(array_double, &exp_arr[4]);
  array_to_be_sorted_add(array_double, &exp_arr[0]);
  merge_binary_insertion_sort(array_double->array, array_double->nitems, 0, array_double->compar);
  for(i = 0; i < 5; i++) {
    arr[i] = *(double*)array_to_be_sorted_get(array_double, i);
  }
  TEST_ASSERT_EQUAL_FLOAT_ARRAY(exp_arr, arr, 5);
}

//! Checks if an array with 5 positive elements is being sorted correctly by use only binary_insertion_sort
static void testd_binary_insertion_sort_five_pos_el() 
{
  double exp_arr[] = {13.445, 25.242, 32.21310, 59.0011, 89.903};
  double arr[5];
  unsigned long i;

  array_to_be_sorted_add(array_double, &exp_arr[1]);
  array_to_be_sorted_add(array_double, &exp_arr[3]);
  array_to_be_sorted_add(array_double, &exp_arr[2]);
  array_to_be_sorted_add(array_double, &exp_arr[4]);
  array_to_be_sorted_add(array_double, &exp_arr[0]);
  merge_binary_insertion_sort(array_double->array, array_double->nitems, 6, array_double->compar);
  for(i = 0; i < 5; i++) {
    arr[i] = *(double*)array_to_be_sorted_get(array_double, i);
  }
  TEST_ASSERT_EQUAL_FLOAT_ARRAY(exp_arr, arr, 5);
}
//! Checks if an array with 5 positive elements is being sorted correctly by merge_binary_insertion_sort
static void testd_merge_binary_insertion_sort_five_pos_el() 
{
  double exp_arr[] = {13.445, 25.242, 32.21310, 59.0011, 89.903};
  double arr[5];
  unsigned long i;
  size_t k;

  array_to_be_sorted_add(array_double, &exp_arr[1]);
  array_to_be_sorted_add(array_double, &exp_arr[3]);
  array_to_be_sorted_add(array_double, &exp_arr[2]);
  array_to_be_sorted_add(array_double, &exp_arr[4]);
  array_to_be_sorted_add(array_double, &exp_arr[0]);
  k = (size_t)rand() % 5;
  merge_binary_insertion_sort(array_double->array, array_double->nitems, k, array_double->compar);
  for(i = 0; i < 5; i++) {
    arr[i] = *(double*)array_to_be_sorted_get(array_double, i);
  }
  TEST_ASSERT_EQUAL_FLOAT_ARRAY(exp_arr, arr, 5);
}


//! Checks if an array with 5 negative elements is being sorted correctly by use only merge_sort
static void testd_merge_sort_five_neg_el() {
  double exp_arr[] = {-89.903, -59.0011, -32.21310, -25.242, -13.445};
  double arr[5];
  unsigned long i;

  array_to_be_sorted_add(array_double, &exp_arr[1]);
  array_to_be_sorted_add(array_double, &exp_arr[3]);
  array_to_be_sorted_add(array_double, &exp_arr[2]);
  array_to_be_sorted_add(array_double, &exp_arr[4]);
  array_to_be_sorted_add(array_double, &exp_arr[0]);
  merge_binary_insertion_sort(array_double->array, array_double->nitems, 0, array_double->compar);
  for(i = 0; i < 5; i++) {
    arr[i] = *(double*)array_to_be_sorted_get(array_double, i);
  }
  TEST_ASSERT_EQUAL_FLOAT_ARRAY(exp_arr, arr, 5);
}

//! Checks if an array with 5 negative elements is being sorted correctly by use only binary_insertion_sort
static void testd_binary_insertion_sort_five_neg_el() {
  double exp_arr[] = {-89.903, -59.0011, -32.21310, -25.242, -13.445};
  double arr[5];
  unsigned long i;

  array_to_be_sorted_add(array_double, &exp_arr[1]);
  array_to_be_sorted_add(array_double, &exp_arr[3]);
  array_to_be_sorted_add(array_double, &exp_arr[2]);
  array_to_be_sorted_add(array_double, &exp_arr[4]);
  array_to_be_sorted_add(array_double, &exp_arr[0]);
  merge_binary_insertion_sort(array_double->array, array_double->nitems, 6, array_double->compar);
  for(i = 0; i < 5; i++) {
    arr[i] = *(double*)array_to_be_sorted_get(array_double, i);
  }
  TEST_ASSERT_EQUAL_FLOAT_ARRAY(exp_arr, arr, 5);
}

//! Checks if an array with 5 negative elements is being sorted correctly by use only merge_binary_insertion_sort
static void testd_merge_binary_insertion_sort_five_neg_el() {
  double exp_arr[] = {-89.903, -59.0011, -32.21310, -25.242, -13.445};
  double arr[5];
  unsigned long i;
  size_t k;

  array_to_be_sorted_add(array_double, &exp_arr[1]);
  array_to_be_sorted_add(array_double, &exp_arr[3]);
  array_to_be_sorted_add(array_double, &exp_arr[2]);
  array_to_be_sorted_add(array_double, &exp_arr[4]);
  array_to_be_sorted_add(array_double, &exp_arr[0]);
  k = (size_t)rand() % 5;
  merge_binary_insertion_sort(array_double->array, array_double->nitems, k, array_double->compar);
  for(i = 0; i < 5; i++) {
    arr[i] = *(double*)array_to_be_sorted_get(array_double, i);
  }
  TEST_ASSERT_EQUAL_FLOAT_ARRAY(exp_arr, arr, 5);
}


//! Checks if an array with 5 positive and negative elements is being sorted correctly by only use merge_sort
static void testd_merge_sort_five_pos_neg_el() {
  double exp_arr[] = {-59.0011, -25.242, 13.445, 32.21310, 89.903};
  double arr[5];
  unsigned long i;

  array_to_be_sorted_add(array_double, &exp_arr[1]);
  array_to_be_sorted_add(array_double, &exp_arr[3]);
  array_to_be_sorted_add(array_double, &exp_arr[2]);
  array_to_be_sorted_add(array_double, &exp_arr[4]);
  array_to_be_sorted_add(array_double, &exp_arr[0]);
  merge_binary_insertion_sort(array_double->array, array_double->nitems, 0, array_double->compar);
  for(i = 0; i < 5; i++) {
    arr[i] = *(double*)array_to_be_sorted_get(array_double, i);
  }
  TEST_ASSERT_EQUAL_FLOAT_ARRAY(exp_arr, arr, 5);
}

//! Checks if an array with 5 positive and negative elements is being sorted correctly by only use binary_insertion_sort
static void testd_binary_insertion_sort_five_pos_neg_el() {
  double exp_arr[] = {-59.0011, -25.242, 13.445, 32.21310, 89.903};
  double arr[5];
  unsigned long i;

  array_to_be_sorted_add(array_double, &exp_arr[1]);
  array_to_be_sorted_add(array_double, &exp_arr[3]);
  array_to_be_sorted_add(array_double, &exp_arr[2]);
  array_to_be_sorted_add(array_double, &exp_arr[4]);
  array_to_be_sorted_add(array_double, &exp_arr[0]);
  merge_binary_insertion_sort(array_double->array, array_double->nitems, 6, array_double->compar);
  for(i = 0; i < 5; i++) {
    arr[i] = *(double*)array_to_be_sorted_get(array_double, i);
  }
  TEST_ASSERT_EQUAL_FLOAT_ARRAY(exp_arr, arr, 5);
}

//! Checks if an array with 5 positive and negative elements is being sorted correctly by merge_binary_insertion_sort
static void testd_merge_binary_insertion_sort_five_pos_neg_el() {
  double exp_arr[] = {-59.0011, -25.242, 13.445, 32.21310, 89.903};
  double arr[5];
  unsigned long i;
  size_t k;

  array_to_be_sorted_add(array_double, &exp_arr[1]);
  array_to_be_sorted_add(array_double, &exp_arr[3]);
  array_to_be_sorted_add(array_double, &exp_arr[2]);
  array_to_be_sorted_add(array_double, &exp_arr[4]);
  array_to_be_sorted_add(array_double, &exp_arr[0]);
  k = (size_t)rand() % 5;
  merge_binary_insertion_sort(array_double->array, array_double->nitems, k, array_double->compar);
  for(i = 0; i < 5; i++) {
    arr[i] = *(double*)array_to_be_sorted_get(array_double, i);
  }
  TEST_ASSERT_EQUAL_FLOAT_ARRAY(exp_arr, arr, 5);
}

/**
 * merge_binary_insertion_sort test for string(array->array, array->nitems, k, array->compar);
*/

//! Checks if an array with 3 elements is being sorted correctly by merge_sort
static void tests_merge_sort_three_pos_el() 
{
  char exp_arr[3][6] = {"black", "blame", "block"};
  char arr[3][6];
  unsigned long i;

  array_to_be_sorted_add(array_string, &exp_arr[1]);
  array_to_be_sorted_add(array_string, &exp_arr[2]);
  array_to_be_sorted_add(array_string, &exp_arr[0]);
  merge_binary_insertion_sort(array_string->array, array_string->nitems, 0, array_string->compar);
  for(i = 0; i < 3; i++) 
  {
    strcpy(arr[i],((char *)array_to_be_sorted_get(array_string, i)));
  }

  for(i = 0; i < 3; i++)
  {
    if(strcmp(exp_arr[i], arr[i]) != 0)
    { 
      printf("\nError in  tests_merge_sort_three_pos_el because %s,%s are different\n",exp_arr[i], arr[i]);
      exit(EXIT_FAILURE);
    }
  }
}

//! Checks if an array with 3 elements is being sorted correctly by merge_binary_insertion_sort
static void tests_merge_binary_insertion_sort_three_pos_el() 
{
  char exp_arr[3][6] = {"black", "blame", "block"};
  char arr[3][6];
  unsigned long i;
  size_t k;

  array_to_be_sorted_add(array_string, &exp_arr[1]);
  array_to_be_sorted_add(array_string, &exp_arr[2]);
  array_to_be_sorted_add(array_string, &exp_arr[0]);
  k = (size_t)rand() % 5;
  merge_binary_insertion_sort(array_string->array, array_string->nitems, k, array_string->compar);
  for(i = 0; i < 3; i++) 
  {
    strcpy(arr[i],((char *)array_to_be_sorted_get(array_string, i)));
  }
  for(i = 0; i < 3; i++)
  {
    if(strcmp(exp_arr[i], arr[i]) != 0)
    { 
      printf("\nError in tests_merge_binary_insertion_sort_three_pos_el because %s,%s are different\n",exp_arr[i], arr[i]);
      exit(EXIT_FAILURE);
    }
  }
}

//! Checks if an array with 3 elements is being sorted correctly by binary_insertion_sort
static void tests_binary_insertion_sort_three_pos_el() 
{
  char exp_arr[3][6] = {"black", "blame", "block"};
  char arr[3][6];
  unsigned long i;

  array_to_be_sorted_add(array_string, &exp_arr[1]);
  array_to_be_sorted_add(array_string, &exp_arr[2]);
  array_to_be_sorted_add(array_string, &exp_arr[0]);
  merge_binary_insertion_sort(array_string->array, array_string->nitems, 0, array_string->compar);
  for(i = 0; i < 3; i++) 
  {
    strcpy(arr[i],((char *)array_to_be_sorted_get(array_string, i)));
  }

  for(i = 0; i < 3; i++)
  {
    if(strcmp(exp_arr[i], arr[i]) != 0)
    { 
      printf("\nError in  tests_binary_insertion_sort_three_pos_el because %s,%s are different\n",exp_arr[i], arr[i]);
      exit(EXIT_FAILURE);
    }
  }
}


//! Performs all tests
int main() {
  UNITY_BEGIN();

  RUN_TEST(test_create_not_null);
  RUN_TEST(test_ini_cap_not_zero);
  RUN_TEST(test_is_cap_expand);
  RUN_TEST(test_is_getting_correct_el);
  RUN_TEST(test_is_int_el_inserted);
  RUN_TEST(test_is_int_el_inserted_by_order);
  RUN_TEST(test_is_nel_increasing_on_insert);
  RUN_TEST(test_zero_el);
  RUN_TEST(test_array_add_get_one_el);

  printf("\nStart testing for array_int\n");

  RUN_TEST(testi_merge_sort_five_pos_el);
  RUN_TEST(testi_merge_sort_five_neg_el);
  RUN_TEST(testi_merge_sort_five_pos_neg_el);

  RUN_TEST(testi_binary_insertion_sort_five_pos_el);
  RUN_TEST(testi_binary_insertion_sort_five_neg_el);
  RUN_TEST(testi_binary_insertion_sort_five_pos_neg_el);

  RUN_TEST(testi_merge_binary_insertion_sort_five_pos_el);
  RUN_TEST(testi_merge_binary_insertion_sort_five_neg_el);
  RUN_TEST(testi_merge_binary_insertion_sort_five_pos_neg_el);

  printf("\nStart testing for array_double\n");
  
  RUN_TEST(testd_merge_sort_five_pos_el);
  RUN_TEST(testd_merge_sort_five_neg_el);
  RUN_TEST(testd_merge_sort_five_pos_neg_el);

  RUN_TEST(testd_binary_insertion_sort_five_pos_el);
  RUN_TEST(testd_binary_insertion_sort_five_neg_el);
  RUN_TEST(testd_binary_insertion_sort_five_pos_neg_el);

  RUN_TEST(testd_merge_binary_insertion_sort_five_pos_el);
  RUN_TEST(testd_merge_binary_insertion_sort_five_neg_el);
  RUN_TEST(testd_merge_binary_insertion_sort_five_pos_neg_el);
  
  printf("\nStart testing for array_string\n");

  RUN_TEST(tests_binary_insertion_sort_three_pos_el);
  RUN_TEST(tests_merge_binary_insertion_sort_three_pos_el);
  RUN_TEST(tests_merge_sort_three_pos_el);

  return UNITY_END();
  
}
