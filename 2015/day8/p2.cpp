#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

vector<char> encode_string(vector<char> string) {
    vector<char> enc_str;
    for (size_t i = 0; i < string.size(); i++) {
        if (string[i] == '\"' ) {
            if (i == 0) {
                enc_str.push_back(string[i]);
                enc_str.push_back('\\');
                enc_str.push_back('\"');
            } else if (i == string.size()-1) {
                enc_str.push_back('\\');
                enc_str.push_back('\"');
                enc_str.push_back(string[i]);
            } else {
                enc_str.push_back('\\');
                enc_str.push_back(string[i]);
            }
        } else if (string[i] == '\\') {
            enc_str.push_back('\\');
            enc_str.push_back(string[i]);
        } else {
            enc_str.push_back(string[i]);
        }
        
    }
    return enc_str;
}
int main(void) {
    ifstream in("input.txt");
    string line;
    unsigned long code, encode;
    code = encode = 0;
    while (getline(in, line)) {
        // cout << line << '\n';
        vector<char> vec;
        char c;
        for (auto& c : line) {
            vec.push_back(c);
        }

        for (auto& c : vec) {
            printf("%c", c);
        }
        printf("| %d\n", vec.size());
        vector<char> enc_str = encode_string(vec);

        for (auto& c : enc_str) {
            printf("%c", c);
        }
        printf("| %d\n", enc_str.size());

        code += vec.size();
        encode += enc_str.size();
    }
    in.close();
    cout << encode << " - " << code << " = " << encode-code;
    return 0;
}