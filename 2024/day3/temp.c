#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int len(int* nums, int size) {
    int len = 0;
    for (int i = 0; i<size; i++) {
        len = i;
    }
    return len;
}

int makeNum(int* nums, int size) {
    int num = 0;
    int numlen = len(nums, size);
    for(int i = numlen, j = 0; i > -1; i--, j++) {
        num += nums[i] * (int)pow(10, j);
    }
    return num;
}

int main(void) {
    int nums[3] = {1,2,3};
    int fin = makeNum(nums, 3);
    printf("%d", fin);
    return 0;
}