#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>

int main(void) {
    
    uint64_t target = 33100000;
    uint64_t count = 1;
    uint64_t sum = 0;
    uint64_t limit = 50;
    while (true) {
        // uint64_t iters = 0;
        sum = 0;
        for (uint64_t i = 1; i*i <= count; i++) {
            // if (iters >= limit) 
            //     break;
            if (count % i == 0) {
                // iters++;
                if (count/i <= 50)
                    sum += i;
                if (i != count/i && i <= 50) {
                    sum += count/i;
                    // iters++;
                }
            }
        }
        sum *= 11;

        if (sum >= target) 
            break;
        else {
            printf("SUM: %" PRIu64 "\n", sum);
            count++;
        }
    }
    
    printf("COUNT: %" PRIu64 "\n", count);

    return 0;
}

