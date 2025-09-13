#include <iostream>
#include <fstream>
#include <sstream> 
#include <vector>
#include <cstddef>

using namespace std;

typedef struct Sue{
	int children;
	int cats;
	int samoyeds, pomeranians, akitas, vizslas;
	int goldfish;
	int trees;
	int cars;
	int perfumes;
	
} Sue;

void print_sue(Sue* s) {
	cout << "---------------------------------------------\n";
	for (size_t i = 0; i < sizeof(Sue)/sizeof(int); i++) {
		cout << *((int*)s+i) << '\n';
	}
	cout << "---------------------------------------------\n";
}

int main(void) {
	ifstream in("input (1).txt");
	string line;

	Sue target = {
		.children = 3,
		.cats = 7,
		.samoyeds = 2,
		.pomeranians = 3,
		.akitas = 0,
		.vizslas = 0,
		.goldfish = 5,
		.trees = 3, 
		.cars = 2,
		.perfumes = 1, 
	};

	size_t count = 0;
	while(getline(in, line)) {
		stringstream linestream(line);
		vector<string> tokens;
		string token;
		while (linestream >> token) {
			tokens.push_back(token);
		}

		Sue s = {
			.children = -1,
			.cats = -1,
			.samoyeds = -1,
			.pomeranians = -1,
			.akitas = -1,
			.vizslas = -1,
			.goldfish = -1,
			.trees = -1, 
			.cars = -1,
			.perfumes = -1, 
		};
		
		size_t tokens_len = tokens.size();
		for (size_t i = 2; i < tokens_len-1; i+=2) {
			token = tokens[i];
			token = token.substr(0, token.size()-1);
			
			string next_token = tokens[i+1];
			if (i < tokens_len-2) next_token = next_token.substr(0, next_token.size()-1);
			// cout << next_token << '\n';
			if (token == "children") {
				s.children = stoi(next_token);
			} else if (token == "cats") {
				s.cats = stoi(next_token);
			} else if (token == "samoyeds") {
				s.samoyeds = stoi(next_token);
			}  else if (token == "pomeranians") {
				s.pomeranians = stoi(next_token);
			}  else if (token == "akitas") {
				s.akitas = stoi(next_token);
			}  else if (token == "vizslas") {
				s.vizslas = stoi(next_token);
			}  else if (token == "goldfish") {
				s.goldfish = stoi(next_token);
			}  else if (token == "trees") {
				s.trees = stoi(next_token);
			}  else if (token == "cars") {
				s.cars = stoi(next_token);
			}  else if (token == "perfumes") {
				s.perfumes = stoi(next_token);
			}  
		}
		++count;

		cout << "count: " << count << '\n';
		bool isgood = true;
		bool tried_special = false;
		for (size_t i = 0; i < 10; i++) {
			int s_field = *((int*) &s+i);
			int target_field = *((int*) &target+i);

			// if (count == 103) print_sue(&s);
			if (s_field == -1) continue;
			
			if (i == 1 || i == 7) {
				if (target_field >= s_field) goto wrong;
				else continue;
			} 
			
			if (i == 3 || i == 6)
			 {
				if (target_field <= s_field) goto wrong;
				else continue;
			}

			if (s_field != target_field) {
				wrong:
				isgood = false;
				break;
		 	} 
		} 
		if (isgood) {
			print_sue(&s);
			goto end;
		}
	}
	
	end:
	cout << '\n' << "answer: " << count << '\n';
	in.close();
}
