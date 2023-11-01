#ifndef MERGE_BINARY_INSERTION_SORT_H
#define MERGE_BINARY_INSERTION_SORT_H

/**
 * An array of any number of elements of any kind, not ordered in any specific way
 */
//! The internal structure of this implementation of arrays
struct ArrayToBeSorted{
  void** array;
  size_t nitems;                    //! keeps track of actual number of elements in the array
  unsigned long array_capacity;     //! keeps track of allocated memory for this array
  int (*compar)(const void*,const void*);
};
typedef struct ArrayToBeSorted ArrayToBeSorted;
/**
 * This function creates an empty array without ordering it and returns the created array.
 * It takes as input a pointer to a function that implements the precedence relation between
 *  the array elements, which will be used for sorting later.
 * Such a function must accept two pointers to elements as input and return 0 if the first 
 * element does not precede the second one, and a number different from zero otherwise.
 * The input parameter cannot be NULL.
 */
ArrayToBeSorted* array_to_be_sorted_create(int (*compar)(const void*,const void*));

/**
 * It accepts as input a pointer to an array_to_be_sorted and a pointer to an element.
 * It adds the element to the array.
 * The input parameters cannot be NULL.
 */
void array_to_be_sorted_add(ArrayToBeSorted* array_to_be_sorted, void* element);
void insert_element(ArrayToBeSorted* array_to_be_sorted, void* element);

/**
 * It accepts as input a pointer to an array_to_be_sorted and it returns 1 iff
 * the array_to_be_sorted is empty (0 otherwise).
 * The input parameter cannot be NULL.
 */
int array_is_empty(ArrayToBeSorted* array_to_be_sorted);

/**
 * It accepts as input a pointer to an array_to_be_sorted and it
 * returns the number of elements currently stored into the array.
 * The input parameter cannot be NULL.
 */
size_t array_size(ArrayToBeSorted* array_to_be_sorted);

/**
 * It accepts as input a pointer to an array_to_be_sorted and an integer "i" and
 * it returns the pointer to the i-th element of the array_to_be_sorted.
 * The first parameter cannot be NULL; the second parameter must be a valid
 * position within the array_to_be_sorted.
 */
void* array_to_be_sorted_get(ArrayToBeSorted* array_to_be_sorted, unsigned long i);

/**
 * It accepts as input a pointer to an array_to_be_sorted and
 * it frees the memory allocated to store the array_to_be_sorted. 
 * It does not free the memory allocated to store the array elements,
 * since freing that memory is responsibility of the function where
 * the array_to_be_sorted was created.
 * The input parameter cannot be NULL.
 */
void array_to_be_sorted_free_memory(ArrayToBeSorted* array_to_be_sorted);

/**
 * We divide the array into two subarrays - sorted and unsorted. 
 * The first element of the array is in the sorted subarray and all other elements are in the unsorted subarray.
 * Then we iterate from the second element to the last. 
 * In the i-th iteration, we first use a binary search on the sorted subarray to find the position of an element larger than our key. 
 * Let's call this position "pos".
 * We then shift all the elements from pos to the right by one and set Array[pos] = key.
 */
void binary_insertion_sort(void** base, size_t nitems, int (*compar)(const void *, const void*));

/**
 * find the index where the element should be inserted
 */
int binary_search(void** base, void* elem, int low, int high, int (*compar)(const void *, const void*));

/**
 * We start merging the elements again based on the comparison of the size of the elements.
 * First, we compare the elements from each list and then combine them into another list in a sorted manner.
 */
void merge(void** left_base, size_t left_size, void** right_base, size_t right_size, int (*compar)(const void *, const void*));

/**
 * This function performs a hybrid merge and binary insertion sort on an array of elements.
 * It takes four parameters:
 * - base: a pointer to the first element of the array to be sorted
 * - nitems: the number of elements in the array
 * - k: a parameter that determines when to switch from merge sort to binary insertion sort
 * - compar: a function that compares two elements and returns a value indicating their order
 *
 * The function sorts the array in place using a combination of merge sort and binary insertion sort.
 * When the size of a subarray being sorted is less than or equal to k, the function switches from merge sort to binary insertion sort.
 */
void merge_binary_insertion_sort(void** base, size_t nitems, size_t k, int (*compar)(const void *, const void*));

#endif /* MERGE_BINARY_INSERTION_SORT_H */
