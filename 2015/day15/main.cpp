#include <iostream>
#include <fstream>
#include <sstream> 
#include <vector>

using namespace std;

typedef struct Cookie {
	string name;
	int capacity, durability, flavor, texture, calories;  
} Cookie;

vector<Cookie> cookies;
long total = 0;

bool adds_to_100(vector<int>& portions) {
	int sum = 0;
	for (auto& i : portions) {
		sum += i;
	}
	if (sum == 100) return true;
	else return false;
}

void compute_recipe_value(vector<int>& portions) {
	long local_total = 1;
	for (int i = 5; i >= 1; i--) {
		long property_value = 0;
		for(size_t j = 0; j < cookies.size(); j++) {
			Cookie cookie = cookies[j];
			if (i == 1) {
				property_value += cookie.capacity * portions[j];
			} else if (i == 2) {
				property_value += cookie.durability * portions[j];
			} else if (i == 3) {
				property_value += cookie.flavor * portions[j];
			} else if (i == 4) {
				property_value += cookie.texture * portions[j];
			} else if (i == 5) {
				property_value += cookie.calories * portions[j];
			}
		}

		if (i == 5 && property_value != 500) return;
		else if (i < 5) {
			if (property_value <= 0) return;
			local_total *= property_value;
		}
	}

	if (local_total > total) {
		total = local_total;
		cout << "local total: " << local_total << '\n';
	}
}

void recurs(vector<int> portions, int max) {
	if (portions.size() == max) {
		if (adds_to_100(portions)) {
			compute_recipe_value(portions);
		}
		return;
	}

	for (int i = 1; i <= 100; i++) {
		portions.push_back(i);
		recurs(portions, max);
		portions.pop_back();
	} 
}

int main(void) {
	ifstream in("input.txt");
	string line;
	while(getline(in, line)) {
		vector<string> tokens;
		stringstream s(line);
		string token;
		while (s >> token) {
			tokens.push_back(token);
		}
		for (size_t i = 2; i < tokens.size()-1; i++) {
			if (i % 2 == 0 && i < 10) 
				tokens[i] = tokens[i].substr(0, tokens[i].size()-1);		
		}

		Cookie cookie = {.name = tokens[0].substr(0, tokens[0].size()-1),
						 .capacity = stoi(tokens[2]),
						 .durability = stoi(tokens[4]),
						 .flavor = stoi(tokens[6]),
						 .texture = stoi(tokens[8]),
						 .calories = stoi(tokens[10]),
						};

		cookies.push_back(cookie);
	}

	vector<int> portions;
	recurs(portions, static_cast<int>(cookies.size()));
	cout << total << '\n';
}
