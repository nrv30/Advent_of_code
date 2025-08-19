#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

bool is_valid_hex_digit(char c) {
    c = (char) (tolower(c));
    return (isdigit(c) != 0 || (c >= 'a' && c <= 'f'));
}

int main(void) {
    ifstream in("input.txt");
    string line;
    size_t code, mem, encode;
    code = mem = 0;
    while (getline(in, line)) {
        vector<char> vec;
        char c;
        for (auto& c : line) {
            vec.push_back(c);
        }

        for (auto& c : vec) {
            printf("%c", c);
        }
        printf("| %d| ", vec.size());
        code += vec.size();
        size_t temp_mem = 0;

        for (size_t i = 0; i < vec.size(); i++) {
            if (vec[i] == '\\'){
                if (vec[i+1] == '\\' || vec[i+1] == '\"') {
                   temp_mem++;
                   i++;
                } else if (vec[i+1] == 'x') {
                    string s;
                    if (is_valid_hex_digit(vec[i+2]) && is_valid_hex_digit(vec[i+3])) {
                        temp_mem++;
                        i+=3;
                    }
                }
            } else if (!(vec[i] == '\"')) {
                temp_mem++;
            }
        }
        mem += temp_mem; printf("%d\n", temp_mem);
    }
    in.close();
    printf("%zu - %zu:  %zu\n", code, mem, code - mem);
    return 0;
}