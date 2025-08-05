#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

const int NUMSIZE = 5;
const int MAX_FILE = 1000;

int intpow(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

int main(void) {

    FILE *file;
    file = fopen("input.txt", "r");

    if (file == NULL) {
    fprintf(stderr, "ERROR: file can't be opened\n");
    return 1;
    }

    int index = 0;

    char buff[24];
    char r_list_buff[24];
    char l_list_buff[24];

    int r_list_ints[MAX_FILE];
    int l_list_ints[MAX_FILE];


    while((fgets(buff, sizeof(buff), file) != NULL)) {

        strncpy(r_list_buff, buff, NUMSIZE);
        strncpy(l_list_buff, buff+8, NUMSIZE);

        int lnum, rnum;
        lnum = rnum = 0;
        for(int i = NUMSIZE-1, j = 0; i > -1; i--, j++) {
            
            lnum+= ((l_list_buff[j]-'0') * intpow(10, i));
            rnum+= ((r_list_buff[j]-'0') * intpow(10, i));
        }

        r_list_ints[index] = rnum;
        l_list_ints[index] = lnum;
        index++;
    }

    int temp, count, comp_score; comp_score = temp = count = 0;
    for (int i = 0; i < MAX_FILE; i++) {
        temp = l_list_ints[i];
        for(int i = 0; i < MAX_FILE; i++) {
            if (temp == r_list_ints[i]) count++;
        }
        comp_score += temp*count;
        count = 0;
    }

    printf("%d", comp_score);
    return 0;
}
