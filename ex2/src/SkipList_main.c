#include "SkipList.h"

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
  return strcasecmp(string_1, string_2);
}

void free_string_arr(char** str_arr) {
    if(!str_arr) {
        return;
    }
    int i;
    for(i = 0; str_arr[i]; i++) {
        free(str_arr[i]);
    }
    free(str_arr);
}

void print_missing_words(char** str_arr) {
    if(!str_arr) {
        return;
    }
    int i;
    printf("List of missing words:\n");
    for(i = 0; str_arr[i]; i++) {
        printf("|%-20s|\n", str_arr[i]);
    }
}

void read_dictionary(const char* file_name, struct SkipList* list) {
    FILE *fp;
    char ch;
    char *buffer = malloc(sizeof(char) * BUFFER_SIZE);
    if(!buffer) {
        fprintf(stderr, "Couldn't allocate memory for buffer in read_dictionary\n");
        exit(EXIT_FAILURE);
    }
    int i = 0;
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
        } else {
            buffer[i] = 0;
            char* str = malloc(strlen(buffer) + 1);
            if(!str) {
                fprintf(stderr, "Couldn't allocate memory for str in read_dictionary\n");
                exit(EXIT_FAILURE);
            }
            strcpy(str, buffer);
            insert_skiplist(list, (void*)str);
            i = 0;
        }
    }
    printf("Dictionary is loaded.\n");
    free(buffer);
    fclose(fp);
}

void write_height_execution_time(const char *filename, size_t k, double execution_time) {
  FILE *file = fopen(filename, "a"); // Open the file in append mode
  if (file == NULL) {
    printf("Error opening the file.\n");
    return;
  }

  fprintf(file, "%zu, %.3f\n", k, execution_time); 

  fclose(file); // Close the file
}

void search_in_list(const char *textfile, struct SkipList* list) {
    FILE *fp;
    char ch;
    char *buffer = malloc(sizeof(char) * BUFFER_SIZE);
    if(!buffer) {
        fprintf(stderr, "Couldn't allocate memory for buffer in search_in_list\n");
        exit(EXIT_FAILURE);
    }
    long long unsigned int strings_size = 0;
    char **strings = NULL;
    const void* test = NULL;
    int i = 0;
    if(buffer == NULL) {
        fprintf(stderr, "Couldn't allocate a memory.");
        exit(EXIT_FAILURE);
    }
    fp = fopen(textfile, "r");
    if(fp == NULL) {
        fprintf(stderr, "Couldn't open the file.");
        exit(EXIT_FAILURE);
    }
    while((ch = (char)fgetc(fp)) != EOF) {
        if(ch != 32 && ch != '\n') 
        {
            buffer[i++] = ch;
        } 
        else 
        {
            buffer[i] = 0;
            size_t size_str = strlen(buffer) + 1;
            char* str = malloc(size_str);
            if(!str) {
                fprintf(stderr, "Couldn't allocate memory for str in search_in_list\n");
                exit(EXIT_FAILURE);
            }
            strcpy(str, buffer);
            str = strtok(str, ",.");
            //remove additional symbols and uppercases such as , . A 
            test = search_skiplist(list, (void*)str);
            if(test == NULL) {
                strings = realloc(strings, (++strings_size) * sizeof(char*));
                if(!strings) {
                    fprintf(stderr, "Couldn't allocate memory for strings in search_in_list\n");
                    exit(EXIT_FAILURE);
                }
                strings[strings_size - 1] = malloc(strlen(str) + 1);
                if(!strings[strings_size - 1]) {
                    fprintf(stderr, "Couldn't allocate memory for strings[i] in search_in_list\n");
                    exit(EXIT_FAILURE);
                }
                strcpy(strings[strings_size - 1], str);
            }
            i = 0;
        }
    }
    strings = realloc(strings, (++strings_size) * sizeof(char*));
    if(!strings) {
        fprintf(stderr, "Couldn't allocate memory for strings in search_in_list\n");
        exit(EXIT_FAILURE);
    }
    strings[strings_size - 1] = NULL;
    print_missing_words(strings);
    free_string_arr(strings);
    free(buffer);
    fclose(fp);
}

//ispunct for removing , .
//Albero, , .
/*char* remove_extra_from_str(char* str) {
    int i;
    for(i = 0; *(str + i); i++) {
        tolower((str + i));
    }
}
*/
void find_errors(const char *dictfile, const char *textfile, size_t max_height) {
    struct SkipList* list = NULL;
    int (*compare)(const void*, const void*) = compar_string;
    new_skiplist(&list, max_height, compare);
    clock_t t1, t2;
    t1 = clock();
    read_dictionary(dictfile, list);
    //print_skiplist(list);
    printf("\nRicerca errori iniziata\n");
    search_in_list(textfile,list);
    t2 = clock();
    double duration = (double)(t2 - t1) / CLOCKS_PER_SEC;
    printf("\nRicerca errori finita: %.10f sec\n", duration);
    write_height_execution_time("max_height_ex.csv", max_height, duration);
    clear_skiplist(&list);
}

int parse_int(char *string, int *integer) {
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
  if(string[i] == '-' || string[i] == 48) {
    printf("Must be greater than zero.\n");
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

void get_input_val(int* val, int* parsed, char* buffer) {
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

int main(int argc, char const *argv[]) {
  size_t max_height;
  int k = 0;
  int parsed = 0;
  char buffer[BUFFER_SIZE];

  srand((unsigned int)time(NULL)); // seed the random number generator
  if (argc < 3) {             
   printf("Usage: SkipList <dict_file> <text_file>\n");
   exit(EXIT_FAILURE); 
  }
  
  printf("Enter max_height:\n");
  get_input_val(&k, &parsed, buffer);

  max_height = (size_t) k;
  find_errors(argv[1],argv[2],max_height);

  return EXIT_SUCCESS;
}

