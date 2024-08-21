#include <iostream>
#include <fstream>
#include <array>

void parseInput(std::array<uint64_t,2> &keys)
{
	std::string line;
	
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
  	getline(input,line);
  	keys[0] = std::stoll(line);
  	
  	getline(input,line);
  	keys[1] = std::stoll(line);
  }
  input.close();

}

uint64_t crack(const std::array<uint64_t,2> &keys)
{
	uint64_t result = 0;
	
	unsigned index = 0;
	unsigned num = 7;
	uint64_t value = 1;
	bool done = false;
	unsigned loopSize = 0;
	
	while(!done)
	{
		value *= num;
		value %= 20201227;
		loopSize++;
		
		if(value == keys[0])
		{
			done = true;
			index = 1;
		}
		else if(value == keys[1])
		{
			done = true;
			index = 0;
		}
	}
	
	value = 1;
	num = keys[index];
	
	for(unsigned i=0; i<loopSize; i++)
	{
		value *= num;
		value %= 20201227;
	}
	
	result = value;
	
	return result;
}

int main()
{
	uint64_t result = 0;
	
	std::array<uint64_t,2> keys;
  
  parseInput(keys);

 	result = crack(keys);
	
  std::cout << "resultA: " << result << '\n';
 	
  return 0;
}
