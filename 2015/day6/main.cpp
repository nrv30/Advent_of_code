#include <iostream>
#include <fstream>
#include <vector>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <tuple>
#include <cstdlib>

using namespace std;

#define grid_size 1000

void init(int** grid) {
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            grid[i][j] = 0;
        }
    }
}

void turn(int** grid, bool direction, vector<pair<int, int>> corners) {
    int delta;
    if (direction) {
        delta = 1;
    } else {
        delta = -1;
    }

    for (int i = corners[0].first; i <= corners[1].first; i++) {
        for (int j = corners[0].second; j <= corners[1].second; j++) {
            int temp = grid[i][j];
            temp += delta;
            if (temp < 0) temp = 0;
            grid[i][j] = temp;
        }
    }
}

void toggle(int** grid, vector<pair<int, int>> corners) {
    for (int i = corners[0].first; i <= corners[1].first; i++) {
        for (int j = corners[0].second; j <= corners[1].second; j++) {
            grid[i][j] += 2;
        }
    }
}

long count_lights(int** grid) {
    unsigned long total;
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            total+= grid[i][j];
        }
    }
    return total;
}

tuple<string, vector<pair<int, int>>> get_corners(string line) {
    vector<pair<int, int>> corners;
    char line_cstr[256];
    string cmd;
    strcpy(line_cstr, line.c_str());
    char* tok = strtok(line_cstr, " ");
    printf("tok:%s\n", tok);
    if (strcmp(tok, "turn") == 0) {
        cmd = "turn";
        if (line.find("on") != string::npos) {
            cmd += " on";
        } else {
            cmd += " off";
        }
    } else {
        cmd = "toggle";
    }
    // cout << "CMD: " << cmd << '\n';
    // exit(1);
    // printf("tok:%s\n", tok);
    for (int i = 0; tok != NULL; i++) {
        tok = strtok(NULL, " ");
        string tok_str;
        if (tok) tok_str = tok;
        if (tok_str.contains(',')) {
            pair<int, int> corner;
            int comma_index = tok_str.find(',');
            corner.first = stoi(tok_str.substr(0, comma_index));
            corner.second = stoi(tok_str.substr(comma_index+1));
            corners.push_back(corner);
        }
    }
    auto data = make_tuple(cmd, corners);
    return data;
}

int main(void) {
    int** grid = (int**)malloc(sizeof(int*)*grid_size);
    for (int i = 0; i < grid_size; i++) {
        grid[i] = (int*)malloc(sizeof(int) * grid_size);
    }

    init(grid);

    ifstream in("input.txt");
    string line;
    while(getline(in, line)) {
        cout << line << '\n';
        vector<pair<int, int>> corners;;
        string cmd;
        
        tie(cmd, corners) = get_corners(line);
        
        if (cmd == "turn on") {
            printf("turn on\n");
            turn(grid, true, corners);
        } else if (cmd == "turn off") {
            turn(grid, false, corners);
            printf("turn off\n");
        }else {
            toggle(grid, corners);
            printf("toggle\n");
        }
        // lcorner.first = line.substr(space_indes, comma_indexes[0]);
        // cout << "LEFT -- " << corners[0].first <<  " " << corners[0].second << '\n';
        // cout << "RIGHT -- " << corners[1].first <<  " " << corners[1].second << '\n';
    }
    in.close();
    long total = count_lights(grid);
    printf("total: %ld\n", total);
    free(grid);
    return 0;
}