// referenced: https://aoc-puzzle-solver.streamlit.app/

#include <iostream>
#include <fstream>
#include <sstream> 
#include <vector>
#include <map>
#include <numeric>


size_t get_cycle_length(std::string &starting_node, std::string &instructions, 
						std::map<std::string, std::pair<std::string, 
						std::string>>& network)
{
	int instructions_size = static_cast<int>(instructions.size());
	size_t count = 1;
	size_t index = 0;
	std::string head = starting_node;
	while (true) {
		char instr = instructions[index];
		std::cout << head <<'\n';
		if (instr == 'L')
			head = network[head].first;
		else
			head = network[head].second;
		if (head[2] == 'Z')
			break;
		index++;
		count++;
		if (index == instructions_size)
			index = 0;
	}

	return count;
}

void part_2(std::string &instructions, std::map<std::string, std::pair<std::string, 
			std::string>>& network, std::vector<std::string> &starting_nodes) 
{
	bool started = false;
	size_t answer = 0;
	for (auto& node : starting_nodes) {
		if (!started) {
			answer = get_cycle_length(node, instructions, network);
			started = true;
		} else 
			answer = std::lcm(get_cycle_length(node, instructions, network), answer);
	}

	std::cout << "answer " << answer << '\n';
}

int main(int argc, char* argv[]) {
	if (argc <= 1) {
		std::cout << "not enough args" << '\n';
		return 69;
	}
	std::string filepath = argv[1];
	std::ifstream in(filepath);
	if (!in) {
		std::cout << "File not found" << '\n';
		return 69;
	}
	std::string line;
	std::string instructions = "";
	std::vector<std::string> data;
	bool read_instructions = false;
	std::map<std::string, std::pair<std::string, std::string>> network;
	std::vector<std::string> starting_nodes; 
	while(getline(in, line)) {
		if (line.empty())
			read_instructions = true;
		else if (!read_instructions) {
			instructions += line;
		} else {
			int equals = line.find('=');
			std::string lvalue, rvalue, l, r;
			lvalue = line.substr(0, equals-1);
			rvalue = line.substr(equals+3);
			int comma = rvalue.find(',');
			l = rvalue.substr(0, comma);
			r = rvalue.substr(comma+2, 3);

			if (lvalue[2] == 'A') {
				starting_nodes.push_back(lvalue);
			}
			network[lvalue] = std::make_pair(l,r);	
		}	
	}

	part_2(instructions, network, starting_nodes);
}