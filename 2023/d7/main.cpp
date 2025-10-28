	
#include <iostream>
#include <fstream>
#include <sstream> 
#include <vector>
#include <tuple>
#include <unordered_map>
#include <algorithm>
#include <set>

using namespace std;

enum HAND_TYPE {
	FIVE_OF_A_KIND = 7,
	FOUR_OF_A_KIND = 6,
	FULL_HOUSE = 5,
	THREE_OF_A_KIND = 4,
	TWO_PAIR = 3,
	ONE_PAIR = 2,
	HIGH_CARD = 1,
};

unordered_map<char, int> CARD_RANKINGS = 
	{
		{'A', 13}, {'K',12}, {'Q', 11}, 
		{'T', 9}, {'9', 8}, {'8', 7},
		{'7', 6}, {'6', 5}, {'5', 4}, 
		{'4', 3}, {'3', 2}, {'2', 1},
		{'J', 10}
	}; 

unordered_map<string, HAND_TYPE> HAND_TYPE_MAP = 
{
	{"5", FIVE_OF_A_KIND}, {"4-1", FOUR_OF_A_KIND},
	{"3-2", FULL_HOUSE}, {"3-1-1", THREE_OF_A_KIND},
	{"2-2-1", TWO_PAIR}, {"2-1-1-1", ONE_PAIR},
	{"1-1-1-1-1", HIGH_CARD}
};

struct Ranked_Hand {
	string handstr;
	HAND_TYPE type;
	size_t bid;
};

// return a map of every unique card in the hand 
// and how many times it was occurred
unordered_map<char, int> count_unique(string &hand) {
	unordered_map<char, int> cards;
	for (char c : hand) {
		if (cards.find(c) != cards.end())
			cards[c]++;
		else 
			cards.insert({c, 1});
	}
	return cards;
}

// returns a string representing the type
string get_type_key(unordered_map<char, int> &hand) {
	vector<int> card_counts;
	for (const auto& c : hand)
		card_counts.push_back(c.second);
	sort(card_counts.begin(), card_counts.end(), 
		 [](int a, int b) {return a > b;});
	string key = to_string(card_counts[0]);
	for (size_t i = 1; i < card_counts.size(); i++)
		key += "-" + to_string(card_counts[i]);
	return key;
}

// compares the hands character by character 
int literal_compare(string &a, string &b) {
	for (size_t i = 0; i < 5; ++i) {
		int diff = CARD_RANKINGS[a[i]] - CARD_RANKINGS[b[i]];
		if (diff > 0)
			return false;
		else if (diff < 0)
			return true;
	}
	return false;
}

bool comparator(Ranked_Hand &a, Ranked_Hand &b) {
	int diff = a.type - b.type; // subtracting the enums
	if (diff > 0) 
		return false;
	else if (diff < 0) 
		return true;
	else {
		// cout << a.handstr << " " << b.handstr << '\n';
		return literal_compare(a.handstr, b.handstr);
	}
}

// returns a list of Ranked_Hands type
vector<Ranked_Hand> rank_hands(vector<tuple<string, size_t>> &hands) {
	vector<Ranked_Hand> ranked_hands;
	for (auto& hand : hands) {
		string handstr;
		size_t bid;
		tie(handstr, bid) = hand;

		string dup_handstr = handstr;
		bool has_joker = false;
		int count = std::count(handstr.begin(), handstr.end(), 'J');
		if (count != 0) {
			cout << handstr << '\n';
			dup_handstr.erase(remove(dup_handstr.begin(), 
			dup_handstr.end(), 'J'), dup_handstr.end());
			unordered_map<char, int> hand_map = count_unique(dup_handstr);
			HAND_TYPE type = HIGH_CARD;
			for (auto& [key, value] : hand_map) {
				value+=count;
				string type_key = get_type_key(hand_map);
				HAND_TYPE temp_type = HAND_TYPE_MAP[type_key];
				// cout << type_key << " " << temp_type << '\n';
				if (temp_type > type)
					type = temp_type;
				value-=count;
			}
			// cout << handstr << ' '  << ' ' << type << '\n';
			ranked_hands.push_back({handstr, type, bid});
		} else {
			unordered_map<char, int> hand_map = count_unique(dup_handstr);
			string type_key = get_type_key(hand_map);
			HAND_TYPE type = HAND_TYPE_MAP[type_key];
			ranked_hands.push_back({handstr, type, bid});
		}
	}
	return ranked_hands;
} 

int main(void) {
	ifstream in("input.txt");
	if (!in.is_open())
		cout << "file not found\n";

	vector<tuple<string, size_t>> hands;
	string line;
	while(getline(in, line)) {
		size_t space_index = line.find(' ');
		// make a tuple of hand and bid
		hands.push_back({line.substr(0, space_index), 
		static_cast<size_t>(stoi(line.substr(space_index+1)))});
	}
	
	vector<Ranked_Hand> ranked_hands = rank_hands(hands);
	sort(ranked_hands.begin(), ranked_hands.end(), comparator);
	unsigned long long sum = 0;
	for (size_t i = 0; i < ranked_hands.size(); i++) {
		sum += ranked_hands[i].bid * (i+1); 
	}

	cout << sum << '\n';
}



/*
let J be a wildcard...
K = number of J
New cards < K
ABCJJ
AAABC
AABBC
AABCC
ABBBC
ABBCC
ABCCC
ABCXY
ABCXX
ABCYY
*/