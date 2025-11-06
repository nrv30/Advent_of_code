#include <string.h>
#include <stdlib.h>

#define DEFAULT_LINE_SIZE 256

typedef struct StringArray {
    char** items;
    size_t capacity;
    size_t count;
} StringArray;

int indexof(char* str, char c);
char* substr(char* src, int start, int end);
void split(StringArray* tokens, char* src, char* delimiter);
void read_file_to_lines(StringArray* lines, FILE* f, size_t* line_size);
void free_string_arr(StringArray* strings);


#ifdef UTILS_IMPLEMENTATION

// https://gist.github.com/rexim/b5b0c38f53157037923e7cdd77ce685d
// Must remeber to free all memory allocated by this macro
#define da_append(xs, x)                                                             \
    do {                                                                             \
        if ((xs)->count >= (xs)->capacity) {                                         \
            if ((xs)->capacity == 0) (xs)->capacity = 256;                           \
            else (xs)->capacity *= 2;                                                \
            (xs)->items = realloc((xs)->items, (xs)->capacity*sizeof(*(xs)->items)); \
        }                                                                            \
                                                                                     \
        (xs)->items[(xs)->count++] = (x);                                            \
    } while (0)

#define da_pop(xs)             \
    do {                       \
        if ((xs)->count > 0) { \
            ((xs)->count)--;   \
        }                      \
    } while (0)

// returns the index of the first occurrence of a character in a string
// returns -1 if it wasn't found
int indexof(char* src, char c) {
    for (int i = 0; i < strlen(src); ++i) {
        if (src[i] == c) 
            return i;
    }
    return -1;
}

// frees each string in a StringArray
// Note: This does not free the memory allocated by da_append()
void free_strings(StringArray* strings) {
    for (size_t i = 0; i < strings->count; i++) {
        free(strings->items[i]);
    }
}

// allocates a new string from start to index plus size
// returns NULL on error
// Note: Remeber to call free on this string
char* substr(char* src, int start, int size) {
    int len = (int)strlen(src);
    if (start + size > len) {
        fprintf(stderr, "Out of bounds access\n");
        return NULL;
    }
    printf("len: %d\n", len);
    char* sub = malloc(sizeof(char)*(size+1));
    if (!sub) {
        fprintf(stderr, "malloc failed\n");
        return NULL;
    }
    for (int new_count = 0; new_count < size; new_count++, start++) {
        sub[new_count] = src[start];
    }
    sub[size] = '\0';
    return sub;
}

// provide pointer to a StringArray
// fill it with all the tokens seperated by a delimiter
// Note: You don't need to free each token if you allocated src on the stack
void split(StringArray* tokens, char* src, char* delimiter) {
    printf("%d\n", tokens->count);
    char* token = strtok(src, delimiter);
    da_append(tokens, token);
    for (;;) {
        token = strtok(NULL, delimiter);
        if (!token)
            break;
        da_append(tokens, token);
    } 
}

// reads a whole file into an array of strings
// and strips the newline at the end of the line
// provide a StringArray to read the lines into
// user calls fopen, and passes the pointer
// provide the size of the line buffer as a pointer to size_t
// or pass NULL and it will default to DEFAULT_LINE_SIZE
// Note: remeber to call free_strings because each line is allocated with strndup
// Note: File must have an empty newline at the bottom 
void read_file_to_lines(StringArray* lines, FILE* f, size_t* line_size) {
    if (!f) {
        fprintf(stderr, "invalid file\n");
        return;
    }
    size_t local_line_size; 
    if (!line_size)
        local_line_size = DEFAULT_LINE_SIZE; 
    else 
        local_line_size = *line_size;

    char line[local_line_size];
    while (fgets(line, sizeof(line), f)) {
        line[strlen(line)-1] = '\0';
        da_append(lines, strdup(line));
    }
}

#endif