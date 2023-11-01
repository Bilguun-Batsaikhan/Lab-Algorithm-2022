#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SkipList.h"
//#include "unity.h"

//!Function for compare string
int compar_string(const void* str_1,const void* str_2) {
  if (str_1 == NULL) {
    fprintf(stderr, "compar_string: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if (str_2 == NULL) {
    fprintf(stderr, "compar_string: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  const char * string_1 = (const char *) str_1;
  const char * string_2 = (const char *) str_2;
  return strcmp(string_1, string_2);
}

static char* i1;
static char* i2;
static char* i3;
static size_t MAX_HEIGHT;
static struct SkipList* list;

void setUp() 
{
  i1 = "balck";
  i2 = "blame";
  i3 = "block";
  MAX_HEIGHT = 4;
  new_skiplist(&list, MAX_HEIGHT, compar_string);
  
}

//! Deallocates the data needed for testing
void tearDown() {
  clear_skiplist(&list);
}

//! Checks if skip list not null
static void test_skiplist_not_null() 
{
  if(list == NULL)
  {
    printf("\nSkipList is null");
    exit(EXIT_FAILURE);
  }
  printf("\nSkiplist is not NULL\n");
}

//! Checks if initial max heigth of the skiplist isn't zero
static void test_ini_max_height_not_zero() 
{
  if(list->max_height == 0)
  {
    printf("\nErrror value max_height %zu", list->max_height);
     exit(EXIT_FAILURE);
  }
  printf("\nMax_height have the correct value\n");
}

static void test_is_el_inserted_same_value() 
{
  const void* test = NULL;
  insert_skiplist(list, (void*)i3);
  test = search_skiplist(list, (void*)i3);
  if(test != i3)
  {
    printf("\nErrrore nell'inserimento ");
     exit(EXIT_FAILURE);
  }
  printf("\nInsert e search works correctly\n");
}

static void test_is_el_inserted_different_value() 
{
  const void* test = NULL;
  insert_skiplist(list, (void*)i3);
  test = search_skiplist(list, (void*)i2);
  if(test == i3)
  {
    printf("\nErrrore nell'inserimento ");
    exit(EXIT_FAILURE);
  }
  printf("\nInsert e search works correctly\n");
}
//da aggiungere insert e search test
int main() 
{
  printf("\nStart testing part\n");
  setUp();
  test_skiplist_not_null();
  test_ini_max_height_not_zero();
  test_is_el_inserted_same_value();
  test_is_el_inserted_different_value();
  printf("\nTest complite");
  
}