#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int part1(int* nums, size_t numsSize) {
        int m1 = 0;
        int m1_index = 0;
        for (size_t i = 0; i < numsSize-1; i++) {
            if (nums[i] > m1) {
                m1 = nums[i];
                m1_index = i;
            }
        }

        int m2 = 0;
        for (size_t i = m1_index+1; i < numsSize; i++) {
            if (nums[i] > m2) {
                m2 = nums[i];
            }
        }

        return m1 * 10 + m2;
    }

long long part2(int* nums, int numsSize) {
    long long maxJoltage = 0;
    int index = -1;

    for (int i = 0; i < 12; i++) {
        index++;
        int max = nums[index];
        for (int j = index+1; i < numsSize-(12-i-1); j++) {
            if (nums[j] > max) {
                max = nums[j];
                index = i;
            }
        }
        maxJoltage = 10 * maxJoltage + max;
    }
    return maxJoltage;
}

int main(int argc, char** argv) {
    FILE* f = fopen(argv[1], "r");
    if (!f)
        return 1;

    long long maxJoltage = 0;
    char buff[256];
    while (fgets(buff, 256, f) != NULL) {
        if (buff[strlen(buff)-1] == '\n')
            buff[strlen(buff)-1] = '\0';
        int buffSize = strlen(buff);
        int nums[buffSize];

        for (int i = 0; i < buffSize; i++) {
            nums[i] = buff[i] - '0';
        }
        if (strcmp(argv[2], "part 1") == 0)
        printf("solving p1\n");
            // maxJoltage += part1(nums, buffSize);
        else 
            printf("solving part 2\n");
            maxJoltage += part2(nums, buffSize);
    }

    printf("answer: %lld\n", maxJoltage);
    
    
}