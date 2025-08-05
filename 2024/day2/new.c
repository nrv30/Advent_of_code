#include <stdio.h>


// skip needs to be 0 indexed
void rem(int* new, const int* report, int count, int skip) {
    for(int i = 0, j = 0;  j < count-1; i++) {
        if (i != skip) {
            new[j] = report[i];
            j++;
        }
    }
}

int main(void) {

    int n[5] = {1,2,3,4,5};
    for (int i = 0; i < 5; i++) {
        printf("%d ", n[i]);
    }
    printf("\n");
    int new[4];
    rem(new, n, 5, 1);

    for (int i = 0; i < 4; i++) {
        printf("%d ", new[i]);
    }
    
    return 0;
}