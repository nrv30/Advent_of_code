#include <iostream>
#include <fstream>
#include <sstream> 
#include <vector>
#include <map>


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
	while(getline(in, line)) {
		if (line.empty())
			read_instructions = true;
		else if (!read_instructions) {
			instructions += line;
		} else {
			int equals = line.find('=');
			std::string l, r;
			std::string rvalue = line.substr(equals+3);
			int comma = rvalue.find(',');
			l = rvalue.substr(0, comma);
			r = rvalue.substr(comma+2, 3);
			network[line.substr(0, equals-1)] = std::make_pair(l,r);	
		}	
	}

	// std::cout << instructions << '\n';
	// for (const auto& [key, value] : network)
    //     std::cout << '[' << key << "] = " << value.first << " " << value.second << "; ";

	int instructions_size = static_cast<int>(instructions.size());
	std::string head = "AAA";
	int count = 1;
	int index = 0;
	while (true) {
		char instr = instructions[index];
		std::cout << head <<'\n';
		// std::cout << instr << '\n';
		if (instr == 'L')
			head = network[head].first;
		else
			head = network[head].second;
		if (head == "ZZZ")
			break;
		index++;
		count++;
		if (index == instructions_size)
			index = 0;
	}

	std::cout << "count: " << count << '\n';
}
