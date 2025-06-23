#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

const int MAX_SIZE = 5;

int compare(const void* a, const void* b) {
    int result = *(int*)a-*(int*)b;
        if(result < 0) return -1;
        else if(result == 0) return 0;
        else return 1;
    }

int main(void) {


    FILE *file;
    file = fopen("input.txt", "r");

    if (file == NULL) {
    fprintf(stderr, "ERROR: file can't be opened\n");
    return 1;
    }

    char buff[24];
    char r_list_buff[24];
    char l_list_buff[24];

    int r_list_ints[MAX_SIZE];
    int l_list_ints[MAX_SIZE];

    int sum = 0;
    while((fgets(buff, 24, file) != NULL)) {

        strncpy(r_list_buff, buff, MAX_SIZE);
        strncpy(l_list_buff, buff+8, MAX_SIZE);

        for(int i = 0; i < MAX_SIZE; i++) {
            r_list_ints[i] = r_list_buff[i]-'0';
            l_list_ints[i] = l_list_buff[i]-'0';
        }

        
        qsort(r_list_ints, MAX_SIZE, sizeof(int), compare);
        qsort(l_list_ints, MAX_SIZE, sizeof(int), compare);

        // for(int i = 0; i < 5; i++) {
        //     printf("%d ", r_list_ints[i]);
        // }

        // printf("\n");

        // for(int i = 0; i < 5; i++) {
        //     printf("%d ", l_list_ints[i]);
        // }

        // printf("\n");

        int lnsum = 0;
        for (int i = 0; i < MAX_SIZE; i++) {
            int ans = r_list_ints[i] - l_list_ints[i];
            if (ans < 0) ans *= -1;
            sum += ans;
        }
        // printf("lnsum is: %d\n", lnsum);
        // printf("sum is: %d\n", sum);

    }

    printf("%d\n", sum);
    // printf("%d", lncount);

    return 0;
}