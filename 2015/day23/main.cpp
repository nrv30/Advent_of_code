#include <iostream>
#include <fstream>
#include <sstream> 
#include <vector>

using namespace std;

struct instruction {
	string op;
	int* regis;
	int offset;
};

int a, b; // there are only 2 registers
vector<instruction> instructions;

int* which_register(string reg) {
	if (reg == "a" || reg == "a,") return &a;
	else return &b;
}

int parse_offset_to_int(string offset) {
	int offset_int = stoi(offset.substr(1), nullptr, 10);
	if (offset[0] == '-') offset_int*=-1;
	return offset_int;
}

int inbounds(instruction* instr, int i) {
	int address = i + instr->offset;
	if (address < 0 || address > instructions.size())
		return -1;
	return address; 
}

int main(void) {
	a = 1;
	b = 0;
	ifstream in("input.txt");
	string line;
	while(getline(in, line)) {
		vector<string> tokens;
		stringstream s(line);
		string tok;
		instruction instr = {};
		while (s >> tok) {
			if (tok == "a" || tok == "b" || tok == "a," || tok == "b,")
				instr.regis = which_register(tok);
			else if (tok[0] == '+' || tok[0] == '-')
				instr.offset = parse_offset_to_int(tok);
			else 
				instr.op = tok; 
		}
		instructions.push_back(instr);
	}

	int i = 0;
	while (i < instructions.size()) {
		instruction* instr = &(instructions[i]);
		if (instr->op == "hlf") {
			*instr->regis/=2;
		}

		else if (instr->op == "tpl") {
			*instr->regis*=3;
		}	

		else if (instr->op == "inc") {
			*instr->regis+=1;
		}

		else if (instr->op == "jmp") {
			jmp:
			int address = inbounds(instr, i);
			if (address < 0) {
				break;
			}
			else {
				i = address;
				continue;
			}
		}	

		else if (instr->op == "jie") {
			if (*instr->regis % 2 == 0)
				goto jmp;
		}

		else if (instr->op == "jio") {
			if (*instr->regis == 1) 
				goto jmp; 
		}
		++i;
	}

	cout << "The value of register b is " << b << '\n';
	cout << "The value of register a is " << a << '\n';
	
	return 0;
}
