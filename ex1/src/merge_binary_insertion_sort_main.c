#include "merge_binary_insertion_sort_main.h"
bool k_record = false;
//! A record to be added in an array
struct record {
  int integer_field;
  char* string_field;
  int int_field;
  double double_field;
};

static int compar_record_int_field(const void* r1_p,const void* r2_p) {
  if (r1_p == NULL) {
    fprintf(stderr, "compar_record_int_field: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL) {
    fprintf(stderr, "compar_record_int_field: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }

  struct record *rec1_p = (struct record*)r1_p;
  struct record *rec2_p = (struct record*)r2_p;
  if (rec1_p->int_field < rec2_p->int_field) 
    return -1;
  else if(rec1_p->int_field > rec2_p->int_field)
    return 1;
  else 
    return 0;
}
static int compar_record_double_field(const void* r1_p,const void* r2_p) {
  if (r1_p == NULL) {
    fprintf(stderr, "compar_record_double_field: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL) {
    fprintf(stderr, "compar_record_double_field: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }

  struct record *rec1_p = (struct record*)r1_p;
  struct record *rec2_p = (struct record*)r2_p;
  if (rec1_p->double_field < rec2_p->double_field) 
    return -1;
  else if(rec1_p->double_field > rec2_p->double_field)
    return 1;
  else 
    return 0;
}

static int compar_record_string_field(const void* r1_p, const void* r2_p) {
  if (r1_p == NULL) {
    fprintf(stderr, "compar_string: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if (r2_p == NULL) {
    fprintf(stderr, "compar_string: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }

  struct record *rec1_p = (struct record*)r1_p;
  struct record *rec2_p = (struct record*)r2_p;
  return strcmp(rec1_p->string_field, rec2_p->string_field);
}
/**
 * Frees the memory occupied by an array, including its elements.
 */
static void free_array(ArrayToBeSorted* array) {
  size_t nitems = array_size(array);
  for (unsigned long i = 0; i < nitems; ++i) {
    struct record* array_element = (struct record*)array_to_be_sorted_get(array, i);
    //free(array_element->string_field);
    free(array_element);
  }
  array_to_be_sorted_free_memory(array);
}

/**
 * Prints the contents of an array.
 */
#ifdef PRINT_ARR
static void print_array(ArrayToBeSorted* array) {
  size_t nitems = array_size(array);
  struct record* array_element;

  for (unsigned long i = 0; i < nitems; ++i) {
    array_element = (struct record*)array_to_be_sorted_get(array, i);
    printf("<%d, %s, %d, %lf>\n", array_element->integer_field, array_element->string_field, array_element->int_field, array_element->double_field);
  }
}
#endif

void read_file(const char* file_name, ArrayToBeSorted* array) {
    FILE *fp;
    char ch;
    unsigned long long int j, x, y, i = 0;
    char *buffer = malloc(sizeof(char) * 100);
    if(buffer == NULL) {
        fprintf(stderr, "Couldn't allocate a memory.");
        exit(EXIT_FAILURE);
    }
    fp = fopen(file_name, "r");
    if(fp == NULL) {
        fprintf(stderr, "Couldn't open the file.");
        exit(EXIT_FAILURE);
    }
    while((ch = (char)fgetc(fp)) != EOF) {
        if(ch != '\n') {
            buffer[i++] = ch;
        }
        if(ch == '\n') {
            unsigned long long int k, l;
            buffer[i] = 0;
            for(x = 0; *(buffer + x) != 0 && *(buffer + x) != ','; x++);
            char *integer_part = malloc(sizeof(char)* (x+1));
            if(integer_part == NULL) {
                fprintf(stderr, "Couldn't allocate a memory.");
                exit(EXIT_FAILURE);
            }
            for(j = x + 1; *(buffer + j) != 0 && *(buffer + j) != ','; j++);
            char* string_part = malloc(sizeof(char) * j - x);
            if(string_part == NULL) {
                fprintf(stderr, "Couldn't allocate a memory.");
                exit(EXIT_FAILURE);
            }
            for(y = j + 1; *(buffer + y) != 0 && *(buffer + y) != ','; y++);
            char *int_part = malloc(sizeof(char)* y - j);
            if(int_part == NULL) {
                fprintf(stderr, "Couldn't allocate a memory.");
                exit(EXIT_FAILURE);
            }
            char* double_part = malloc(sizeof(char)* i - y);
            if(double_part == NULL) {
                fprintf(stderr, "Couldn't allocate a memory.");
                exit(EXIT_FAILURE);
            }
            for(k = 0; k < x; k++) {
                integer_part[k] = buffer[k];
            }
            integer_part[k] = 0;
            for(k = x + 1, l = 0; k < j; k++) {
                string_part[l++] = buffer[k];
            }
            string_part[l] = 0;
            for(k = j + 1, l = 0; k < y; k++) {
                int_part[l++] = buffer[k];
            }
            int_part[l] = 0;
            for(k = y + 1, l = 0; k < i; k++) {
                double_part[l++] = buffer[k];
            }
            double_part[l] = 0;
            i = 0;
            int integer_p = atoi(integer_part);
            int int_p = atoi(int_part);
            double double_p = atof(double_part);
            load_array( integer_p, string_part, int_p, double_p, array);
            
            //!free memory
            free(integer_part);
            free(int_part);
            free(double_part);
        }
    }
    free(buffer);
    fclose(fp);
}

void load_array(int integer_part, char* string_part, int int_part, double double_part, ArrayToBeSorted* array) {
  struct record* record_p = malloc(sizeof(struct record));
  if (record_p == NULL) {
      fprintf(stderr, "main: unable to allocate memory for the read record");
      exit(EXIT_FAILURE);
    }   
    record_p->integer_field = integer_part;
    record_p->string_field = string_part;
    record_p->int_field = int_part;
    record_p->double_field = double_part;
    //! we're sending record pointer as a void pointer
    array_to_be_sorted_add(array, (void*)record_p);
}

/*function to write ordered array in out file*/
void write_to_file(const char* file_name, ArrayToBeSorted* array) {
  unsigned long i;
  FILE *fp = fopen(file_name, "w");
  struct record* array_element;

  if(fp == NULL) {
      fprintf(stderr, "Couldn't open the file.");
      exit(EXIT_FAILURE);
  }
  for(i = 0; i < array->nitems; i++) {
   array_element = (struct record*)array_to_be_sorted_get(array, i);
   fprintf(fp, "%d, %s, %d, %lf\n", array_element->integer_field, array_element->string_field, array_element->int_field, array_element->double_field);
  }
  printf("Write to a file is complete.\n");
  fclose(fp);
}

/*writes k value and program execution time relation to a file*/
void write_k_execution_time(const char *filename, size_t k, double execution_time) {
  FILE *file = fopen(filename, "a"); // Open the file in append mode
  if (file == NULL) {
    printf("Error opening the file.\n");
    return;
  }

  fprintf(file, "%zu, %.3f\n", k, execution_time); // Write the k value and execution time to the file

  fclose(file); // Close the file
}

void sort_records(const char *infile, const char *outfile, size_t k, size_t field) {
  int (*compare)(const void*, const void*);
  if(field == 1) //string compare
    compare = compar_record_string_field;
  else if (field == 2)
    compare = compar_record_int_field; //int compare
  else
    compare = compar_record_double_field; //int compare
  ArrayToBeSorted* array = array_to_be_sorted_create(compare);
  
  read_file(infile, array);
  printf("\nDATA IS LOADED TO MEMORY\n");
  
  #ifdef PRINT_ARR
  print_array(array);
  #endif
  clock_t t1, t2;
  t1 = clock();
  merge_binary_insertion_sort(array->array, array->nitems, k, array->compar);
  t2 = clock();
  double duration = (double)(t2 - t1) / CLOCKS_PER_SEC;
  printf("\nTime of execution in seconds for ordering: %.10f sec\n", duration);
  #ifdef PRINT_ARR
  print_array(array);
  #endif
  if(k_record) {
    write_k_execution_time(outfile, k, (t2-t1)/(double)(CLOCKS_PER_SEC));
  } else {
    write_to_file(outfile, array);
  }
  free_array(array);
}

bool parse_int(char *string, int *integer) {
  if(!string || !integer) {
    fprintf(stderr, "parse_int: cannot have a NULL parameter.\n");
    exit(EXIT_FAILURE);
  }
  int i = 0;
  int integer_chars = 0;
  char int_buffer[BUFFER_SIZE];
  int length = (int)strlen(string);   //! strlen doesn't include null character
  for(i = 0; string[i] == 32; i++);   //! Stops at first character that's not a white-space

  if(length == i) return 0;           //! String is only white-spaces
  if(string[i] == '-') {
    printf("Negative value isn't accepted");
    return 0;
  }
  while(i < length && !isspace(string[i])) {
    if(!isdigit(string[i])) return 0;
    int_buffer[integer_chars++] = string[i++];
  }
  int_buffer[integer_chars] = 0;      //! End the string
  while(isspace(string[i++]));
  if(string[i] != 0) return 0;
  *integer = atoi(int_buffer);
  return 1;
}

void get_input_val(int* val, bool* parsed, char* buffer) {
  do {
    fgets(buffer, BUFFER_SIZE, stdin);
    char *newline = strchr(buffer, '\n');
    if (newline) {
      *newline = '\0';
    }
    *parsed = parse_int(buffer, val);
    if(!(*parsed)) {
      printf("Must be a positive integer value!\n");
    }
  } while(!(*parsed));
}

int main(int argc, char const *argv[])
{
  int k = 0, field = 0, choice = 0;
  bool parsed = false;
  char buffer[BUFFER_SIZE];

  if (argc < 3) {             
    printf("Usage: merge_binary_insertion_sort_main <input_file> <output_file>\n");
    exit(EXIT_FAILURE); 
  }
  printf("Enter k variable:\n");
  get_input_val(&k, &parsed, buffer);
  parsed = 0;
  printf("Enter field variable for ordering:\n "
        "1. Order by String field\n "
        "2. Order by Integer field\n "
        "Any positive number other than 1 or 2 will order by Double field\n");
  get_input_val(&field, &parsed, buffer);
  parsed = 0;
  printf("Would you like to write a relation of k value?\n"
        "1. Yes\n"
        "2. No\n");
  get_input_val(&choice, &parsed, buffer);
  if(choice == 1) {
    k_record = true;
  }
  sort_records(argv[1], argv[2], (size_t)k, (size_t)field);
  
  printf("\nBINARY INSERTION MERGE SORT COMPLETE\n");
  return EXIT_SUCCESS;
}