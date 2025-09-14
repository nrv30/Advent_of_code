#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>

// https://gist.github.com/rexim/b5b0c38f53157037923e7cdd77ce685d
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

#define LITERS_OF_EGGNOG 150

typedef struct Nums {
    int* items;
    size_t capacity;
    size_t count;
} Nums;

size_t add(Nums* n) {
    size_t sum = n->items[0];
    for (size_t i = 1; i < n->count; i++) {
        sum += n->items[i];
    }
    return sum;
}

void print(Nums* n) {
    for (size_t i = 0; i < n->count; ++i) {
        printf("[%zu], ", n->items[i]);
    } printf(" SUM: %zu\n", add(n));
}

void combinations(Nums* src, Nums* temp, size_t k, size_t start, size_t* found, size_t* min) {
    if (temp->count == k) {
        if (add(temp) == LITERS_OF_EGGNOG) {
            if (*min > temp->count) {
                *min = temp->count;
                *found = 1;
            } else (*found)++;
        } 
        return;
    }
    
    for (size_t i = start; i < src->count; ++i) {
        da_append(temp, src->items[i]);
        combinations(src, temp, k, i+1, found, min);
        da_pop(temp);
    }
}

int main(void) {
    Nums src = {0}; 
    FILE* f = fopen("input.txt", "r");
    if (!f) return 1;
    int num;
    while (fscanf(f, "%d", &num) == 1) {
        da_append(&src, num);
    }

    size_t found = 0;
    size_t min = SIZE_MAX;
    Nums temp = {0};
    printf("starting: "); print(&src);

    for (size_t k = src.count-1; k >= 2; k--) {
        combinations(&src, &temp, k, 0, &found, &min);
    }
    printf("%zu\n", found);

    return 0;
}