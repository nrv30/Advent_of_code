#include <iostream>

using namespace std;

bool incr_straight(string& inp) {
    for (size_t i = 0; i < inp.size()-2; i++) {
        char c = inp[i];
        if (inp[i+1] == c+1 && inp[i+2] == c+2) return true;
    }
    return false;
}

bool has_bad_letters(string& inp) {
    for (size_t i = 0; i < inp.size(); i++) {
        if (inp[i] == 'o' || inp[i] == 'l' || inp[i] == 'i') return true; 
    }
    return false;
}

bool non_overlapping_pairs(string& inp) {
    size_t count = 0;
    for (size_t i = 0; i < inp.size()-1; i++) {
        if (inp[i]==inp[i+1]) {
            count++;
            i++;
            if (count >= 2) return true;
        }
    }
    return false;
}

bool is_good(string& inp) {
    if (has_bad_letters(inp)) return false;
    if (!incr_straight(inp)) return false;
    if (!non_overlapping_pairs(inp)) return false;
    return true;
}

void increment(std::string& s) {
    for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i) {
        if (s[i] == 'z') {
            s[i] = 'a';
        } else {
            ++s[i];
            return;
        }
    }
}

int main(void) {
    string inp = "hepxxyzz";

    do {
        increment(inp);
        cout << inp << '\n';
    } while (!is_good(inp));

    cout << "last: " << inp << '\n';
    
}