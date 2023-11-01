#include "SkipList.h"

int node_num = 0;
static int max_h = 0;

void print_skiplist(struct SkipList *list) {
    printf("%-20s | %-6s | %-8s\n", "Item", "Size", "NodeNum");
    printf("---------------------|--------|----------\n");
    struct Node *node = list->head;
    while (node != NULL) {
        printf("%-20s | %-6lld | %-8d\n", (char *)node->item, node->size, node->nodeNum);
        node = node->next[0];
    }
}

void clear_skiplist(struct SkipList** l) {
    struct SkipList* list = *l;
    struct Node *node = list->head->next[0];
    while (node != NULL) {
        struct Node *next = node->next[0];
        free(node->item);
        free(node);
        node = next;
    }
    free(list->head);
    free(list);
    *l = NULL;
}
int randomLevel() {
    int level = 1;
    while ((float)rand() / (float)RAND_MAX < 0.5 && level < max_h) {
        level++;
    }
    return level;
}
/*
int randomLevel() {
    int level = 1;
    while ((float)rand() / (float)RAND_MAX < 0.5 && level < max_h) {
        level++;
    }
    return level;
}
*/
struct Node* createNode(void* item, int level) {
  struct Node* node = malloc(sizeof(struct Node));
  node->size = (size_t)level;
  node->next = malloc(node->size * sizeof(struct Node *));
  for (size_t i = 0; i < node->size; i++) {
      node->next[i] = NULL;
  }
  node->nodeNum = ++node_num;
  if(item != NULL) {
    node->item = item;
  } else {
    fprintf(stderr,"Item cannot be empty\n");
    exit(EXIT_FAILURE);
  }
  return node;
}

void new_skiplist(struct SkipList **list, size_t max_height, int (*compar)(const void *, const void*)) {
    struct SkipList* l = malloc(sizeof(struct SkipList));
    *list = l;
    if (compar == NULL) 
    {
        fprintf(stderr, "new_skiplist: compar parameter cannot be NULL");
        exit(EXIT_FAILURE);
    }
    l->head = malloc(sizeof(struct Node));
    if (l->head == NULL) {
        fprintf(stderr, "new_skiplist: failed to allocate memory for head node");
        exit(EXIT_FAILURE);
    }

    l->head->item = NULL;
    l->max_level = 0;
    l->max_height = max_height;
    l->compare = compar;
    max_h = (int)max_height;

    printf("New SkipList is created\n");
}

void clear_skiplist(struct SkipList **list);

void insert_skiplist(struct SkipList *list, void *item) {
  if(list->head->item == NULL) {
    list->head = createNode(item, max_h);
    if(list->head->size > list->max_level)
    list->max_level = list->head->size;
  }
  else {
    struct Node *new_node = createNode(item, randomLevel());
    if (new_node->size > list->max_level) {
        list->max_level = new_node->size;
    }
    struct Node *x = list->head;
    for (int k = (int)list->max_level - 1; k >= 0; k--) {
        while (x->next[k] != NULL && compar_string(item, x->next[k]->item) >= 0) {
            x = x->next[k];
        }
        if (k < (int)new_node->size) {
            new_node->next[k] = x->next[k];
            x->next[k] = new_node;
        }
    }
  }  
}

const void* search_skiplist(struct SkipList *list, void *item) {
   struct Node *x = list -> head;
   if(compar_string(item, x -> item) == 0)
     return item;
   for (int k = (int)list->max_height - 1; k >= 0; k--) 
   {
        while (x->next[k] != NULL && compar_string(item, x->next[k]->item) > 0) 
        {
            x = x->next[k];
        }
   }
    if(x -> next[0] != NULL)
    {
      x = x -> next[0];
      if (compar_string(item, x->item) == 0)     
         return x->item;
      else
         return NULL;
    }
    return NULL;
}

