#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "merge_binary_insertion_sort.h"

//! Initial capacity for the array
#define INITIAL_CAPACITY 2

void insert_element(ArrayToBeSorted* array_to_be_sorted, void* element) {
  array_to_be_sorted->array[array_to_be_sorted->nitems++] = element;
}

//! element is a record and array_to_be_sorted is initialized with compar function and other fields
void array_to_be_sorted_add(ArrayToBeSorted* array_to_be_sorted, void* element) {
  if (array_to_be_sorted == NULL) {
    fprintf(stderr, "add_array_to_be_sorted_element: array_to_be_sorted parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if (element == NULL) {
    fprintf(stderr, "add_array_to_be_sorted_element: element parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  //! if number of elements are higher or equal to capacity of the array then increase the void pointed array's size
  if (array_to_be_sorted->nitems >= array_to_be_sorted->array_capacity) {
    array_to_be_sorted->array = (void**)realloc(array_to_be_sorted->array, 2*array_to_be_sorted->array_capacity*sizeof(void*));
    if (array_to_be_sorted->array == NULL) {
      fprintf(stderr, "array_to_be_sorted_add: unable to reallocate memory to host the new element");
      exit(EXIT_FAILURE);
    }
    array_to_be_sorted->array_capacity = 2*array_to_be_sorted->array_capacity;
  }
  insert_element(array_to_be_sorted, element);
}

ArrayToBeSorted* array_to_be_sorted_create(int (*compar)(const void*,const void*)) {
  if (compar == NULL) {
    fprintf(stderr, "array_to_be_sorted_create: compar parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  ArrayToBeSorted* array_to_be_sorted = (ArrayToBeSorted*)malloc(sizeof(ArrayToBeSorted));
  if (array_to_be_sorted == NULL) {
    fprintf(stderr, "array_to_be_sorted_create: unable to allocate memory for the array_to_be_sorted array");
    exit(EXIT_FAILURE);
  }
  //! vector of void pointers
  array_to_be_sorted->array = (void**)malloc(INITIAL_CAPACITY*sizeof(void*));
  if (array_to_be_sorted->array == NULL) {
    fprintf(stderr, "array_to_be_sorted_create: unable to allocate memory for the internal array");
    exit(EXIT_FAILURE);
  }

  array_to_be_sorted->nitems = 0;
  array_to_be_sorted->array_capacity = INITIAL_CAPACITY;
  array_to_be_sorted->compar = compar;
  return array_to_be_sorted;
}

int array_is_empty(ArrayToBeSorted* array_to_be_sorted) {
  if (array_to_be_sorted == NULL) {
    fprintf(stderr, "array_to_be_sorted_is_empty: array_to_be_sorted parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  return array_to_be_sorted->nitems == 0;
}

size_t array_size(ArrayToBeSorted* array_to_be_sorted) {
  if (array_to_be_sorted == NULL) {
    fprintf(stderr, "array_to_be_sorted_size: array_to_be_sorted parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  return array_to_be_sorted->nitems;
}

void* array_to_be_sorted_get(ArrayToBeSorted* array_to_be_sorted, unsigned long i) {
  if (array_to_be_sorted == NULL) {
    fprintf(stderr, "array_to_be_sorted_get: array_to_be_sorted parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if (i >= array_to_be_sorted->nitems) {
    fprintf(stderr, "array_to_be_sorted_get: Index %lu is out of the array bounds", i);
    exit(EXIT_FAILURE);
  }
  return array_to_be_sorted->array[i];
}

void array_to_be_sorted_free_memory(ArrayToBeSorted* array_to_be_sorted) {
  if (array_to_be_sorted == NULL) {
    fprintf(stderr, "array_to_be_sorted_free_memory: array_to_be_sorted parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  free(array_to_be_sorted->array);
  free(array_to_be_sorted);
}

void binary_insertion_sort(void** base, size_t nitems, int (*compar)(const void *, const void*)) {
  int pos;
  int j;
  size_t i;
  void** arr = base;
  void *temp;
  for(i = 1; i < nitems; i++) {
    j = (int)i-1;
    temp = arr[i];
    pos = binary_search(base, arr[i], 0, j, compar);
    while(j >= pos) {
      arr[j + 1] = arr[j];
      j = j - 1;
    }
    arr[j + 1] = temp; 
  }
}

// insert your code here
int binary_search(void** base, void* elem, int low, int high, int (*compar)(const void *, const void*))
{
    if(high <= low)
      return(compar(elem, base[low]) > 0) ? (low + 1) : low;

    int mid = low + (high - low) / 2;
    int c = compar(elem, base[mid]);
    if (!c)
      return mid + 1;

    if (c > 0)
      return binary_search(base, elem, mid + 1, high, compar);
    else
      return binary_search(base, elem, low, mid - 1, compar);
}

void merge_binary_insertion_sort(void** base, size_t nitems, size_t k, int (*compar)(const void *, const void*)) 
{
    if (nitems <= k) {
        binary_insertion_sort(base, nitems, compar);
    } else {
        if(nitems != 1)
        {//! (base) is the left side of the array with nitems/2 elements
        merge_binary_insertion_sort(base, nitems/2, k, compar);
        //! (base + nitems/2) is the right side of the array with nitems - nitems/2 elements
        merge_binary_insertion_sort(base + nitems/2, nitems - nitems/2, k, compar);
        //! left, left_items, right, right_items
        merge(base, nitems/2, base + nitems/2, nitems - nitems/2, compar);
        }
    }
}

void merge(void** left_base, size_t left_size, void** right_base, size_t right_size, int (*compar)(const void *, const void*)) {
    size_t i = 0, j = 0, k = 0;
    //! temp will hold merged array
    void** temp = malloc((left_size + right_size) * sizeof(void*));
    while (i < left_size && j < right_size) {
        //! left_base[i] <= right_base[j]
        if (compar(left_base[i], right_base[j]) <= 0) {
            temp[k++] = left_base[i++];
        } else {
            temp[k++] = right_base[j++];
        }
    }
    //! if there are some left-over elements either right or left side then copy it to temp
    //!@ {
    while (i < left_size) {
        temp[k++] = left_base[i++];
    }
    while (j < right_size) {
        temp[k++] = right_base[j++];
    }
    //!@ }
    memcpy(left_base, temp, (left_size + right_size) * sizeof(void*));
    free(temp);
}
