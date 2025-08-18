#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <cstdint>
#include <cstdlib>

using namespace std;

typedef enum GATES {
    OR,
    AND,
    LSHIFT,
    RSHIFT,
    NOT,
    INV,
}GATES;

typedef struct WIRE{
    GATES gate;
    string a;
    string b;
    uint16_t signal;
    bool has_signal;
} WIRE;

bool isupper(string s) {
    char first = s[0];
    return (first >= 'A' && first <= 'Z');
}
void tokenize(string line, map<string, WIRE>* signals) {
    stringstream ss(line);
    vector<string> toks;
    string token;
    while (ss >> token) {
        toks.push_back(token);
    }
    string first_token = toks[0];


    if (first_token == "NOT") {
        signals->insert({toks[3], (WIRE) {.gate = NOT, 
                                          .a = toks[1],
                                          .has_signal = false}});
    } else if (isupper(toks[1][0])) {
        GATES temp;
        string gates_token = toks[1];
        if (gates_token == "OR") {
            temp = OR;
        } else if (gates_token == "AND") {
            temp = AND;
        } else if (gates_token == "LSHIFT") {
            temp = LSHIFT;
        } else if (gates_token == "RSHIFT") {
            temp = RSHIFT;
        }
        signals->insert({toks[4], (WIRE) {.gate = temp, 
                                          .a = toks[0], 
                                          .b = toks[2],
                                          .has_signal = false}});
    } else if (isdigit(toks[0][0]) != 0) {
        signals->insert({toks[2], (WIRE){.gate = INV, 
                                        .signal = static_cast<uint16_t>(stoi(toks[0])),
                                        .has_signal = true,
                                        }});
    } else {
        signals->insert({toks[2], (WIRE) {.gate = INV,
                                          .a = toks[0],
                                          .has_signal = false}});
    }

}

uint16_t switch_ops(uint16_t a, uint16_t b, GATES g) {
    switch (g) {
        case AND:
            return a & b;
        case OR:
            return a | b;
        case RSHIFT:
            return a >> b;
        case LSHIFT:
            return a << b;
        default : return 0;
    }
}

uint16_t connect_wires(map<string, WIRE>* signals, string key) {
    WIRE &w = signals->find(key)->second;
    uint16_t signal;
    if (w.has_signal) {
        return w.signal;
    } else if (w.gate == INV) {
        signal = connect_wires(signals, w.a);
        w.signal = signal;
        w.has_signal = true;
        return signal;
    }else if (w.gate == NOT) {
        uint16_t a;
        if ((isdigit(w.a[0])) == 0) {
            a = connect_wires(signals, w.a);
        } else {
            a = static_cast<uint16_t>(stoi(w.a));
        }
        signal = ~ a;
        w.signal = signal;
        w.has_signal = true;
        return signal;
    } else {
        uint16_t a;
        uint16_t b;
        // cout << w.a[0] << '\n';
        // cout << (isdigit(w.a[0])) << '\n';
        if ((isdigit(w.a[0])) == 0) {
            a = connect_wires(signals, w.a);
        } else {
            a = static_cast<uint16_t>(stoi(w.a));
        }
        if ((isdigit(w.b[0])) == 0) { 
            b = connect_wires(signals, w.b);
        } else {
            b = static_cast<uint16_t>(stoi(w.b));
        }
        signal = switch_ops(a, b, w.gate);
        w.signal = signal;
        w.has_signal = true;
        return signal;        
    }
}

int main(void) {
    ifstream in("input.txt");
    string line;
    // map <string, uint16_t> wires;
    map <string, WIRE> signals;

    // Wires: <a, 1234>
    // Signals: <a, struct {OR, a, b}>

    while (getline(in, line)) {
        // cout << line << '\n';
        tokenize(line, &signals);
    }

    in.close();
    // cout << signals.at("c").signal << '\n';
    // exit(1);
    uint16_t result = connect_wires(&signals, "a");
    cout << result << "\n";

    return 0;
}