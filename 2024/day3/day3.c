#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

typedef enum STATE {
    READ,
    PARSE,
} STATE;

bool assert_order(char in, char comp) {
    if (in != comp) return false;
    else return true;
}

void reset(int* index, STATE* state) {
    *index = 0;
    *state = READ;
}


// 123
int makeNum(int* nums, int size) {
    int num = 0;
    for(int i = size, j = 0; i > -1; i--, j++) {
        num += nums[i] * (int)pow(10, j);
    }
    return num;
}

int main(void) {
    size_t buff_cap = 1024;
    char* buff = malloc(sizeof(char) * buff_cap);
    if (buff == NULL) {
        printf("FAILED");
        exit(1);
    }
    FILE* f = fopen("input.txt", "r");
    if (f == NULL) {
        printf("FAILED");
        exit(1);
    }

    char tokens[] = {'m', 'u', 'l', '\0', ',', '\0', ')'}; // mul(2,4)
    int c;
    STATE state = READ;
    bool good = true;
    int index,buff_index, count, nums_count, stack_index, sum;
    index = buff_index = count = nums_count = stack_index = sum =  0;

    int nums[3];
    int stack[2];

    // read the whole file into buff char by char
    while((c=fgetc(f)) != EOF) {
        if (buff_index == (int)buff_cap-1) {
            buff_cap*=2;
            buff = realloc(buff, buff_cap);
            if (buff == NULL) {
                printf("FAILED");
                exit(1);
            }
        }
        buff[buff_index] = c;
        buff_index++;
    }

    for(int i = 0; i < buff_index; i++) {
        c = buff[i];
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
                    } else {
                        index++;
                        break;
                    }
                case 1:
                    if (!assert_order(c, 'l')) {
                        reset(&index, &state);
                    } else {
                        index++;
                        break;
                    }
                case 2:
                    if (!assert_order(c, '(')) {
                        reset(&index, &state);
                    } else {
                        index++;
                        break;
                    }
                case 3:
                case 6:
                    if (isdigit(c) == 0) {
                        reset(&index, &state);
                    } else {
                        nums[nums_count] = atoi(c);
                        nums_count++;
                        index++;
                        break;
                    }
                case 4:
                case 7:
                    if (isdigit(c) == 0) {
                        if (!assert_order(c, ',')) {
                            reset(&index, &state);
                        } else {
                            index++; 
                            break;
                        }
                    }       
                    nums[nums_count] = atoi(c);
                    nums_count++; 

                    char temp = buff[buff_index+1];
                    if (isdigit(c) == 0) {
                        if (!assert_order(temp, ',')) {
                            reset(&index, &state);
                        } else {
                            index+=2; 
                            break;
                        }
                    } 

                    nums[nums_count] = atoi(c);
                    nums_count++;
                    int num_int = makeNum(nums, nums_count);
                    stack[stack_index] = num_int;
                    stack_index++;
                    break;
                case 5:
                case 8: 
                    if (!assert_order(c, ',')) {
                        reset(&index, &state);
                    } else {
                        index++;
                        break;
                    }
                case 9:
                    if (!assert_order(c, ')')) {
                        reset(&index, &state);
                    } else {
                        count++;
                        sum += stack[0] * stack[1];
                        reset(&index, &state);
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
        // } else if (state == NUM) {
        //         if (isdigit(c) == 0 && !assert_order(c, ',') && arg.index > 3) {
        //                 reset(&index, &state);
        //             } else if (isdigit(c) != 0) {
        //                 arg.index++;
        //             }else if(assert_order(c, ',')) {
        //                 state = PARSE;
        //             }
        // }
        }
    }
    return 0;
}



