#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <variant>
#include <unordered_map>
#include <bitset>

void parseInput(std::vector<std::variant<std::string,std::pair<uint64_t,uint64_t>>> &instructions)
{
	std::string line;
	
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
		while(getline(input,line))
		{
			if(line[1] == 'a')
			{
				instructions.push_back(line.substr(line.find_first_of("X01")));
			}
			else
			{
				size_t pos = line.find_first_of("0123456789");
				size_t endpos = line.find_first_of("]",pos);
				uint64_t address = std::stoi(line.substr(pos,endpos-pos));
				
				pos = line.find_first_of("0123456789", endpos);
				uint64_t value = std::stoll(line.substr(pos));
				
				instructions.push_back(std::make_pair(address,value));
			}
		}
  }
  input.close();
}

uint64_t initialize(const std::vector<std::variant<std::string,std::pair<uint64_t,uint64_t>>> &instructions)
{
	uint64_t result = 0;
	
	std::unordered_map<uint64_t,uint64_t> cache;
	std::string mask = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
	
	for(auto& instruction:instructions)
	{
		if(instruction.index() == 0)
		{
			mask = std::get<std::string>(instruction);
		}
		else
		{
			uint64_t address = std::get<std::pair<uint64_t,uint64_t>>(instruction).first;
			std::bitset<64> value(std::get<std::pair<uint64_t,uint64_t>>(instruction).second);
			
			for(unsigned i=0; i<mask.size(); i++)
			{
				if(mask[mask.size()-1-i] != 'X')
				{
					value[i] = mask[mask.size()-1-i]-'0';
				}
			}
			
			cache[address] = value.to_ullong();
		}
	}
	
	for(auto mem:cache)
	{
		result += mem.second;
	}
	
	return result;
}

uint64_t versionTwo(const std::vector<std::variant<std::string,std::pair<uint64_t,uint64_t>>> &instructions)
{
	uint64_t result = 0;
	
	std::unordered_map<uint64_t,uint64_t> cache;
	std::string mask = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
	
	for(auto& instruction:instructions)
	{
		if(instruction.index() == 0)
		{
			mask = std::get<std::string>(instruction);
		}
		else
		{
			std::bitset<64> address(std::get<std::pair<uint64_t,uint64_t>>(instruction).first);
			uint64_t value = std::get<std::pair<uint64_t,uint64_t>>(instruction).second;
			
			for(unsigned i=0; i<mask.size(); i++)
			{
				if(mask[mask.size()-1-i] == '1')
				{
					address[i] = 1;
				}
			}
			
			std::vector<std::bitset<64>> addresses;
			addresses.push_back(address);
			
			for(unsigned i=0; i<mask.size(); i++)
			{
				if(mask[mask.size()-1-i] == 'X')
				{
					auto newAddresses = addresses;
					for(auto add:addresses)
					{
						if(add[i] == 1)
						{
							add[i] = 0;
						}
						else
						{
							add[i] = 1;
						}
						newAddresses.push_back(add);
					}
					addresses = newAddresses;
				}
			}
			
			for(auto& add:addresses)
			{
				cache[add.to_ullong()] = value;
			}
		}
	}
	
	for(auto mem:cache)
	{
		result += mem.second;
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	
	std::vector<std::variant<std::string,std::pair<uint64_t,uint64_t>>> instructions;
   
  parseInput(instructions);

 	resultA = initialize(instructions);
	resultB = versionTwo(instructions);
 	
  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
 	
  return 0;
}
