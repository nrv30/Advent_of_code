#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

const int NUMSIZE = 5;
const int MAX_FILE = 1000;

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

    int sum = 0;

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

    int temp;
    for (int i = 0; i < MAX_FILE; i++) {
        
    }
    return 0;
}
