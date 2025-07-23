#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef enum MODE {
    DEC,
    INC,
} MODE;

// int compare(const int a, const int b) {
//     return a-b;
// }

MODE getmode(int result) {
    if(result < 0) return DEC;
    else return INC;
}

void rem(int* new, const int* report, int count, int skip) {
    for(int i = 0, j = 0;  j < count-1; i++) {
        if (i != skip) {
            new[j] = report[i];
            j++;
        }
    }
}

// if true report was safe
bool is_safe(int* new, const int* report, int count, bool recurs) {
    bool status = true;
    int unsafe = 0;
    MODE mode;
    int diff = report[1]-report[0];
    int abs_diff = abs(diff);
    if (abs_diff != 1 && abs_diff != 2 && abs_diff != 3) {
        status = false;
        if (recurs) {
            rem(new, report, count, 0);
            if (is_safe(new, new, count-1, false) == true) {
                status = true;
            }
            if (!true) {
                rem(new, report, count, 1);
                if (is_safe(new, new, count-1, false) == true) {
                    status = true;
                }
            }
        }
        goto eval;
        
    }
    mode = getmode(diff);
    for(int i = 2; (i < count && unsafe < 2); i++) {
        diff = report[i] - report[i-1];
        if (getmode(diff) != mode) {
            status = false;
            if (recurs) {
                rem(new, report, count, i);
                if (is_safe(new, new, count-1, false) == true) {
                    status = true;
                }
                goto eval;
            }
        } else {
            int abs_diff = abs(diff);
            if (abs_diff != 1 && abs_diff != 2 && abs_diff != 3) {
                status = false;
                if (recurs) {
                rem(new, report, count, i);
                if (is_safe(new, new, count-1, false) == true) {
                    status = true;
                }
                goto eval;
            }
            }
        }
    }
    eval:
        if (status) return true;
        else return false;
        
}

int main(void) {

    const int MAX_NUMS = 8; // max number of numbers in a row
    char buff[64];
    int report[MAX_NUMS];
    char *token;

    FILE *f = fopen("new.txt", "r");
    if (!f) return 1;

    int safe = 0;
    while(fgets(buff, sizeof(buff), f)) {
        token = strtok(buff, " ");
        report[0] = atoi(token);
        int count = 1;
        while (token!=NULL)
        {
            token = strtok(NULL, " ");
            if (token[1] == '\n') {
                token[1] = '\0';
                report[count] = atoi(token);
                count++;
                break;
            }
            else if (token[2] == '\n') {
                token[2] = '\0';
                report[count] = atoi(token);
                count++;
                break;
            }
            int n = atoi(token);
            report[count] = n;
            count++;
        }

        int new[count];
        if (is_safe(new, report, count, true) == true) {
            safe++;
        }

        // printing each input line
        // for(int i = 0; i < count; i++) {
        //     printf("%d ", report[i]);
        // }
        // printf("\n");
        
    }
    fclose(f);
    printf("%d", safe);

    
    return 0;
}