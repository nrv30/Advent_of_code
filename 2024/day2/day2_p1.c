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
bool is_safe(const int* report, int count) {
    MODE mode;
    int diff = abs(report[0]-report[1]);
    if (diff != 1 && diff != 2 && diff != 3) {
        return false;
    } else {
        mode = getmode(diff);
        for (int i = 2; i < count-1; i++) {
            int diff = abs(report[0]-report[1]);
            MODE temp = getmode(diff);
            if (temp!=mode) {
                return false;
            }
            else if (diff != 1 && diff != 2 && diff != 3) {
                return false; 
            }
        }
    } return true;
        
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
            report[count] = atoi(token);
            count++;
        }
        
        if (is_safe(report, count)) {
            safe++;
        } else {
            int new[count];
            for (int i = 0; i < count; i++) {
                rem(new, report, count, i);
                bool nestsafe = false;
                for (int j = 0; j < count-1; j++) {
                    if (is_safe(new, count)) {
                        nestsafe = true;
                    }
                }
                if (nestsafe) {safe++; break;}
            }   
        }
        // if (is_safe(report, count) == true) {
        //     safe++;
        // }

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