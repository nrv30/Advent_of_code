#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 100
bool grid[SIZE][SIZE];


void print(bool (*temp)[SIZE]);

size_t check_neighbors(size_t i, size_t j) {
    size_t count = 0;
    if (j > 0 && grid[i][j-1]) count++;
    if (i < SIZE-1 && j > 0 && grid[i+1][j-1]) count++;
    if (i < SIZE-1 && grid[i+1][j]) count++;
    if (i < SIZE-1 && j < SIZE-1 && grid[i+1][j+1]) count++;
    if (j < SIZE-1 && grid[i][j+1]) count++;
    if (i > 0 && j < SIZE-1 && grid[i-1][j+1]) count++;
    if (i > 0 && grid[i-1][j]) count++;
    if (i > 0 && j > 0 && grid[i-1][j-1]) count++;

    return count;
}

void update(bool (*temp)[SIZE]) {
    for (size_t i = 0; i < SIZE; ++i) {
        for (size_t j = 0; j < SIZE; ++j) {
            if (!((i == 0 && j == 0) ||
            (i == 0 && j == SIZE - 1) ||
            (i == SIZE - 1 && j == 0) ||
            (i == SIZE - 1 && j == SIZE - 1))) 
            {
                size_t neighbors_on = check_neighbors(i, j);
                if (grid[i][j]) {
                    if (neighbors_on != 2 && neighbors_on != 3) temp[i][j] = false;
                } else {
                    if (neighbors_on == 3) temp[i][j] = true;
                }
            }
        }
    }
}

void print(bool (*temp)[SIZE]) {
    for (size_t i = 0; i < SIZE; ++i) {
        for (size_t j = 0; j < SIZE; ++j) {
            if (temp[i][j]) printf("ON, ");
            else printf("OFF, ");
        }
        printf("\n");
    }
    printf("\n");
}

size_t count_on() {
    size_t count = 0;
    for (size_t i = 0; i < SIZE; ++i) {
        for (size_t j = 0; j < SIZE; ++j) {
            if (grid[i][j]) count++;
        }
    }
    return count;
}

int main(void) {
    FILE* f = fopen("input.txt", "r");
    if (!f) return 1;
    int c;
    int row, col;
    row = col = 0;
    while ((c = getc(f)) != EOF) {
        if (c == '#') {
            grid[row][col] = true;
            col++;
        } else if (c == '.') {
            grid[row][col] = false;
            col++;
        } else if (c == '\n') {
            row++;
            col = 0;
        }
    }
    fclose(f);

    // print(grid);
    bool temp[SIZE][SIZE];
    memcpy(temp, grid, sizeof(grid));

    for (size_t i = 0; i < 100; ++i) {
        update(temp);
        memcpy(grid, temp, sizeof(temp));
        // print(grid);
    }

    printf("%zu\n", count_on());
    
}