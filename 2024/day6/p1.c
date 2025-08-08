
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct Pair {
    int row;
    int col;
} Pair;

typedef struct Grid {
    char** items;
    size_t count;
    size_t capacity;
} Grid;

typedef struct Pair_Vector {
    Pair* items;
    size_t count;
    size_t capacity;
} Pair_Vector;

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


void find_start_pos(Grid* grid, size_t row_size, Pair* loc);
bool update(Grid* grid, Pair *vel, Pair* loc, size_t* pair_index, Pair pairs[4], 
            Pair_Vector* vec, size_t row_size, size_t grid_height);
void add_pairs(Pair* loc, Pair* vel);
bool vec_contains(Pair_Vector* vec, Pair pair);
bool equal(Pair a, Pair b);
bool is_done(size_t grid_height, size_t row_size, Pair* loc);

int main(void) {

    FILE* f = fopen("input.txt", "r");
    Pair pairs[4] = {
        (Pair) {-1, 0},
        (Pair) {0, 1},
        (Pair) {1, 0},
        (Pair) {0, -1},
    };
    size_t pair_index = 0;
    Pair vel = pairs[pair_index];
    Pair loc = {0};
    Grid grid = {0};
    Pair_Vector vec = {0};
    size_t count = 0;

    char buff[1024];
    while (fgets(buff, sizeof(buff), f)) {
        size_t buff_size = strlen(buff);
        buff[buff_size-1] = '\0'; 
        char* row = malloc(sizeof(char) * buff_size);
        memcpy(row, buff, buff_size); 
        da_append(&grid, row);
    }

    for (size_t i = 0; i < grid.count; i++) {
        printf("%s\n", grid.items[i]);
    }

    size_t row_size = strlen(grid.items[0]);
    size_t grid_height = grid.count;

    printf("row: %zu  col: %zu\n", row_size, grid_height);
    find_start_pos(&grid, row_size, &loc);

    printf("start-row: %zu  start-col: %zu\n", loc.row, loc.col);

    da_append(&vec, loc);

    bool should_quit = false;
    do {
        should_quit = update(&grid, &vel, &loc, &pair_index, pairs, 
            &vec, row_size, grid_height);
            printf("row: %zu  col: %zu\n", loc.row, loc.col);
            // exit(1);
    } while (!should_quit);
    
    printf("---------------------\n");
    for (size_t i = 0; i < vec.count; i++) {
        printf("row:%d  col:%d\n",  vec.items[i].row, vec.items[i].col);
    }
    printf("count: %d\n", vec.count);
    // free grid
    for (size_t i = 0; i < grid.count; i++) {
        free(grid.items[i]);
    }

}

void find_start_pos(Grid* grid, size_t row_size, Pair* loc) {
    for (size_t row = 0; row < grid->count; row++) {
        for (size_t col = 0; col < row_size; col++) {
            if (grid->items[row][col] == '^') {
                *loc = (Pair) {row, col};
                break;
            }
        }
    }
}

bool update(Grid* grid, Pair *vel, Pair* loc, size_t* pair_index, Pair pairs[4], 
            Pair_Vector* vec, size_t row_size, size_t grid_height) {
    printf("x:%d  y:%d\n", loc->row, loc->col);
    Pair next = *loc;
    add_pairs(&next, vel);
    if (is_done(grid_height, row_size, &next)) return true;
    else{
            char c = grid->items[next.row][next.col];
            if ( c == '.' || c == '^') {
                if (!vec_contains(vec, next)) {
                    da_append(vec, next);
                }
                *loc = next;
            } else if (c == '#') {
                if (*pair_index == 3) *pair_index = 0;
                else *pair_index+=1;
                *vel = pairs[*pair_index];
            }
        }
        return false;   
    }

void add_pairs(Pair* loc, Pair* vel) {
    loc->row += vel->row;
    loc->col += vel->col;
}

bool vec_contains(Pair_Vector* vec, Pair pair) {
    for (size_t i = 0; i < vec->count; i++) {
        Pair temp = vec->items[i];
        if (equal(temp, pair)) return true;
    }
    return false;
}

bool equal(Pair a, Pair b) {
    return (a.row == b.row && a.col == b.col);
}

bool is_done(size_t grid_height, size_t row_size, Pair* loc) {
    if (loc->row > grid_height-1 || loc->row < 0 || loc->col > row_size-1 || loc->row < 0) return true;
    else return false;
}
