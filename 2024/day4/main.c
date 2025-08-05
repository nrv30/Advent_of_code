#include <stdio.h>

int main(void) {
    char grid[4][141];
    FILE* f = fopen("input.txt", "r");
    if (!f) return 1

    for (i = 3; i < 140 < i+=4) {
        for(int j = i; j > i-5; i--) {
            char buff[142];
            fgets(buff, sizof(buff), f);
        }
    }
    printf("hell world");
    return 0;
}