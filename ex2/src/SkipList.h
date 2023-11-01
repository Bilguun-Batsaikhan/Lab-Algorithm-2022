#ifndef SKIPLIST_H
#define SKIPLIST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#define BUFFER_SIZE 100

struct SkipList {
  struct Node *head;
  size_t max_level;
  size_t max_height;
  int (*compare)(const void*, const void*);
};

struct Node {
  struct Node **next;
  size_t size;
  void *item;
  int nodeNum;
};

/**
 * compare two string and return strcmp value
 */
int compar_string(const void* str_1,const void* str_2);


/**
 * Create a empty skip list by given the maximum height and comparison function
 *  saving the allocated memory location in *list.
 */
void new_skiplist(struct SkipList **list, size_t max_height, int (*compar)(const void *, const void*));

/** 
 * It free up all memory allocated for the SkipList,
 * including all internal nodes and the data contained in them.
 */ 
void clear_skiplist(struct SkipList **list);

/**
 * Place a certain item in the skiplist list.
 * The item to be inserted is provided as a pointer to a generic data
 */ 
void insert_skiplist(struct SkipList *list, void *item);

/**
 * Determines the number of pointers to be included in the new node
 */ 
int randomLevel();

/**Check if an item with an item value is in the skiplist list.
 * return NULL if no match is found
 * or return the pointer to the item item stored in the skiplist otherwise
 */ 
const void* search_skiplist(struct SkipList *list, void *item);

/**
 * print the skiplist
 */ 
void print_skiplist(struct SkipList *list);
#endif 