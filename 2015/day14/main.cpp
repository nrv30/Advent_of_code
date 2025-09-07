// reference: https://dmatrix.dev/posts/advent-of-code-year-2015-day-14/

#include <iostream>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

typedef struct reindeer {
    size_t state; // 0 is flying 1 is resting
    size_t fly_time;
    size_t move;
    size_t rest_time; 
    size_t rest_timer;
    size_t fly_timer;
    unsigned long distance_traveled;
    size_t points;
} reindeer;

vector<reindeer> deers;

unsigned long compute_winner(vector<reindeer>&deers) {
    unsigned long winner = 0;
    for (auto& d : deers) {
        if (d.distance_traveled >= winner) winner = d.distance_traveled;
    }
    return winner;
}

void reward_winner(vector<reindeer>&deers) {
    unsigned long winning_distance = compute_winner(deers);
    for (auto& d : deers) {
        if (d.distance_traveled == winning_distance) d.points++;
    }
}

void tick(reindeer& d) {
    if (d.state == 0) {
        d.fly_timer--;
        d.distance_traveled += d.move;
        if (d.fly_timer == 0) {
            d.state = 1;
            d.rest_timer = d.rest_time;
        }
    } else {
        d.rest_timer--;
        if (d.rest_timer == 0) {
            d.state = 0;
            d.fly_timer = d.fly_time;
        }
    }
}

// care about tokens 4 and 7 and 14
int main(void) {
    size_t max_size = (size_t)-1;
    ifstream in("input.txt");
    string line;
    while(getline(in, line)) {
        vector<string> tokens;
        stringstream s(line);
        string token;
        while(s >> token) {
            tokens.push_back(token);
        }
        reindeer r = {.state = 0,
                      .fly_time = static_cast<size_t>(stoi(tokens[6])),
                      .move = static_cast<size_t>(stoi(tokens[3])),
                      .rest_time = static_cast<size_t>(stoi(tokens[13])),
                      .fly_timer = r.fly_time,
                      .distance_traveled = 0,
                      .points = 0,
                    };
        deers.push_back(r);
    }
    for (size_t i = 0; i < 2503; i++) {
        for (auto& d: deers) {
            tick(d);
        }
        reward_winner(deers);
    }
    
    size_t winner = 0;
    for (auto& d : deers) {
        if (d.points > winner) winner = d.points;
    }
    cout << winner << '\n';
 
    return 0;
}