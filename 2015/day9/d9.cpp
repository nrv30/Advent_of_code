#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

unsigned long sum_vec(vector<string>* vec_pt, map<pair<string, string>, size_t>* m) {
    vector<string> vec = *vec_pt;
    unsigned long sum = 0;
    for(size_t i = 1; i < vec.size(); i++) {
        size_t n =  (*m)[{vec[i-1], vec[i]}];
        if (n == 0) {
            n = (*m)[{vec[i], vec[i-1]}];
        }
        sum+=n;

    }
    return sum;
}

int main(void) {

    map<pair<string, string>, size_t> m;
    set<string> cities;
    ifstream in("input.txt");
    string line;
    while (getline(in, line)) {
        vector<string> tokens;
        stringstream s(line);
        string token;
        pair<string,string> p;
        size_t d;
        while (s >> token) {
            if (token != "=" && token != "to") tokens.push_back(token);
        }
       
        cities.insert(tokens[0]); cities.insert(tokens[1]);
        p.first = tokens[0]; 
        p.second = tokens[1]; 
        d = stoi(tokens[2]);
        m.insert({p, d});
    }
    in.close();

    vector<string> vec;
    for (auto& c : cities) {
        vec.push_back(c);
    }

    unsigned long count = 0;
    unsigned long sum = 0;
    do {
       unsigned long n = sum_vec(&vec, &m);
       cout << n << '\n';
       if (n > sum) sum = n;
       count++; 
    } while (next_permutation(vec.begin(), vec.end()));
    cout << sum << '\n';

    return 0;
}