#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <unordered_map>

void parseInput(std::vector<std::pair<std::string,int>> &instructions)
{
	std::string line;
	
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
		while(getline(input,line))
		{
			size_t pos = 0;
			size_t endpos = 0;
			
			endpos = line.find_first_of(" ");
			std::string inst = line.substr(0,endpos);
			
			pos = line.find_first_of("-1234567890",endpos);
			instructions.push_back(std::make_pair(inst,std::stoi(line.substr(pos))));
		}
  }
  input.close();
}

uint64_t findLoop(const std::vector<std::pair<std::string,int>> &instructions)
{
	uint64_t result = 0;
	
	int acc = 0;
	int pointer = 0;
	std::unordered_map<int,int> cache;
	
	while(pointer >=0 && (unsigned)pointer < instructions.size())
	{
		if(cache.count(pointer) == 0)
		{
			cache[pointer] = 1;
		}
		else
		{
			result = acc;
			break;
		}
		if(instructions[pointer].first == "acc")
		{
			acc += instructions[pointer].second;
		}
		else if(instructions[pointer].first == "jmp")
		{
			pointer += instructions[pointer].second-1;
		}
		pointer++;
	}
	
	return result;
}

uint64_t fixCode(std::vector<std::pair<std::string,int>> &baseInstructions)
{
	uint64_t result = 0;
	
	int acc = 0;
	int pointer = 0;
	
	for(unsigned i=0; i<baseInstructions.size(); i++)
	{
		bool done = true;
		std::unordered_map<int,int> cache;
		auto instructions = baseInstructions;
		if(instructions[i].first == "acc")
		{
			continue;
		}
		else if(instructions[i].first == "nop")
		{
			instructions[i].first = "jmp";
		}
		else
		{
			instructions[i].first = "nop";
		}
		while(pointer >=0 && (unsigned)pointer < instructions.size())
		{
			if(cache.count(pointer) == 0)
			{
				cache[pointer] = 1;
			}
			else
			{
				acc = 0;
				pointer = 0;
				done = false;
				break;
			}
			if(instructions[pointer].first == "acc")
			{
				acc += instructions[pointer].second;
			}
			else if(instructions[pointer].first == "jmp")
			{
				pointer += instructions[pointer].second-1;
			}
			pointer++;
		}
		if(done)
		{
			result = acc;
			break;
		}
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	
	std::vector<std::pair<std::string,int>> instructions;
   
  parseInput(instructions);

 	resultA = findLoop(instructions);
	resultB = fixCode(instructions);
	
  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
 	
  return 0;
}
