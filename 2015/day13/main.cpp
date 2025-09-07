#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>
#include <algorithm>

using namespace std;

bool contains(vector<string>& vec, string s) {
    for (size_t i = 0; i < vec.size(); i++) {
        if (s == vec[i]) return true;
    }
    return false;
}

int compute_net_happiness(vector<string>& names, map<pair<string, string>, int>& seating) {
    int net_happiness = 0;
    size_t names_len = names.size();
    for (size_t i = 0; i < names_len; ++i) {
        string l, r;
        l = names[i];
        if (i == names_len-1) {
            r = names[0];
        } else r = names[i+1];

        net_happiness += seating[make_pair(l, r)];
        net_happiness += seating[make_pair(r, l)];
    }
    return net_happiness;
}

int main(void) {
    ifstream in("input.txt");
    string line;
    vector<string> names;
    map<pair<string, string>, int> seating;
    while (getline(in, line)) {
        vector<string>tokens;
        stringstream s(line);
        string token;
        // care about tokens 1 and 3 and 4 and 11
        size_t count = 0;
        while(s >> token) {
            if (count == 0 || count == 2 || count == 3) tokens.push_back(token);
            else if (count == 10) {
                string stripped = token.substr(0, token.size()-1);
                tokens.push_back(stripped);
            }
            count++;
        }
        if (!contains(names, tokens[0])) {
            names.push_back(tokens[0]);
        }
        if (!contains(names, tokens[3])) {
            names.push_back(tokens[3]);
        }
        int happiness = stoi(tokens[2]);
        if (tokens[1] == "lose") happiness *= -1;
        seating.insert({make_pair(tokens[0], tokens[3]), happiness});
    }
    in.close();

    string my_name = "nirvair";
    for (auto& name : names) {
        seating.insert({make_pair(name, my_name), 0});
        seating.insert({make_pair(my_name, name), 0});
    }
    names.push_back(my_name);

    int optimal_happiness = 0;
    size_t count_perms = 0;
    do
    {
        int net_happiness = compute_net_happiness(names, seating);
        cout << net_happiness << '\n';
        if (net_happiness > optimal_happiness) optimal_happiness = net_happiness;
        count_perms++;
    }
    while (next_permutation(names.begin(), names.end()));

    cout << "optimal happiness: " << optimal_happiness << " permutations: " << count_perms << '\n';
}