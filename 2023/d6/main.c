//referenced: https://www.youtube.com/watch?v=Od0aBz4WDls

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define UTILS_IMPLEMENTATION
#include "../../utils.h"

long long parse_num(char* line) {
    int colon_index = indexof(line, ':');
    char* data = substr(line, colon_index+1, strlen(line)-(colon_index+1));
    char* token = strtok(data, " ");
    char big_num[128] = "";
    memset(big_num, 0, sizeof(big_num));
    while (token) {
        puts(token);
        strcat(big_num, token);
        token = strtok(NULL, " ");
    }
    free(data);
    big_num[strlen(big_num)-1] = '\0';
    return atoll(big_num);
}

int main(void) {
    FILE* f = fopen("input.txt", "r");
    if (!f) 
        printf("couldn't find the file\n");

    char line1 [256];
    char line2[256];
    fgets(line1, 256, f);
    fgets(line2, 256, f);
    long long time = parse_num(line1);
    long long distance = parse_num(line2);
    printf("time: %lld, distance: %lld\n", time, distance);

    double x_float = (time-sqrt(((time*time) - 4*distance))) / 2;
    long long x_int = (long)x_float + 1;
    long long answer = time + 1 - 2*x_int;
    printf("%lld", answer);

    fclose(f);
    return 0;
}