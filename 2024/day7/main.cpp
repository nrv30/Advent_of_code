#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

void consider_solutions(vector<size_t> expr, size_t n, bool* good, unsigned long long target) {
    if (expr.size()==0) {
        if (n == target) *good = true;
        return;
    }

    if (n == 0) {
        n = expr.at(0);
        expr.erase(expr.begin());
    } 

    size_t x = expr.at(0);
    expr.erase(expr.begin());

    consider_solutions(expr, n*x, good, target);
    consider_solutions(expr, n+x, good, target);
    string concat_string = to_string(n) + to_string(x);
    consider_solutions(expr, stoll(concat_string), good, target);
}

vector<size_t> parse_expr(string line) {
    vector<size_t> nums;
    basic_stringstream<char> parser(line);
    int num;
    while (parser >> num) {
        nums.push_back(num);
    }
    return nums;
}


int main(void) {
    ifstream in("input.txt");
    string line;
    unsigned long long total = 0;
    while(getline(in, line)) {
        cout << line << '\n';
        if (!(line.size()==0)) {
            bool good = false;
            int colon_index = line.find(':');
            string target_string = line.substr(0, colon_index);
            unsigned long long target = stoll(target_string);
            string expr_string = line.substr(colon_index+1);
            vector<size_t> expr = parse_expr(expr_string);
            consider_solutions(expr, 0, &good, target);
            if (good) total += target;
        }
    }
    in.close();
    cout << total << '\n';
    return 0;
}