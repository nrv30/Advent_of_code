#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

typedef enum STATE {
    READ,
    PARSE,
    NUM,
} STATE;

typedef struct ARG {
    int as_int;
    char as_string[4];
    int index;
} ARG;

bool assert_order(char in, char comp) {
    if (in != comp) return false;
    else return true;
}

void reset(int* index, STATE* state) {
    *index = 0;
    *state = READ;
}

// read everything into a buffer first to avoid this nonsense
// then parse

// if after open paren you don't encounter a number reset
    // if the subsequent is a number c
    // if the sub is comma expect int 
    // if the subsequent is a number c
    // if the sub is comma expect comma
    // if !comma reset
    // if comma restart process
// 
int main(void) {
    FILE* f = fopen("input.txt", "r");
    int c; 
    STATE state = READ;
    bool good = true;
    int index = 0;
    ARG arg = {0};
    while((c=fgetc(f)) != EOF && good != false) {
        // putchar(c);
        if (state == READ) {
            switch((char)c) {
                case 'm': 
                state = PARSE;
                default: break;
            }
        } else if (state == PARSE) {

            switch(index) {
                case 0:
                    if (!assert_order(c, 'u')) {
                        reset(&index, &state);
                    } else break;
                case 1:
                    if (!assert_order(c, 'l')) {
                        reset(&index, &state);
                    } else break;
                case 2:
                    if (!assert_order(c, '(')) {
                        reset(&index, &state);
                    } else break;
                case 3:
                    if (isdigit(c) == 0) {
                        reset(&index, &state);
                    } else break;
                case 4:
                    if (isdigit(c) == 0) {
                        reset(&index, &state);
                    } else {
                        state = NUM;
                        arg.index++; 
                        break;
                    }
                default: printf("%c", c); exit(1);
            } 
                               // switch((char)c) {
            //     case : 
            //     default:
            //         good = false;
                    
            // }
        // 1
        // 2
        // 3
        } else if (state == NUM) {
                if (isdigit(c) == 0 && !assert_order(c, ',') && arg.index > 3) {
                        reset(&index, &state);
                    } else if (isdigit(c) != 0) {
                        arg.index++;    
                    }else if(assert_order(c, ',')) {
                        state = PARSE;
                    }
        }
    } 
    return 0;
}