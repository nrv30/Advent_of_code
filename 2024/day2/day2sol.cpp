#include <iostream>
#include <vector>

int main(void) {
    int answer = 0;
    for (int i = 0; i < 1000; i++) {
        std::vector<int> a;
        while(true) {
            int x;
            scanf("%d", &x); // reads num
            a.push_back(x); 
            char c;
            scanf("%c", &c); // reads space or newline
            if (c== '\n') {
                break;
            }
        }
        int k = (int)a.size();
        bool ok = true;
        bool only_inc = true; 
        bool only_dec = true;
        for (int j = 0; j <k-1; j++) {
            int diff = a[j+1] - a[j];
            if (diff > 0) {
                only_dec = false;
            }
            if (diff < 0) {
                only_inc = false;
            }
            if (!(1<= abs(diff) && abs(diff <=3))) {
                ok = false;
                break;
            }
        }
        if (ok && (only_inc || only_dec)) {
            answer++;
        }
    }
    printf("%d\n", answer);
    return 0;
}