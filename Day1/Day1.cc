#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

void parseInput(std::vector<unsigned> &numbers)
{
	std::string line;
	
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
  	while(getline(input, line))
  	{
  		numbers.push_back(std::stoi(line));
  	}
  }
  input.close();
}

uint64_t multiplyNumbers(const std::vector<unsigned> &numbers)
{
	uint64_t result = 0;
	
	bool done = false;
	for(unsigned i=0; i<numbers.size()-1; i++)
	{
		for(unsigned j=i+1; j<numbers.size(); j++)
		{
			if(numbers[i]+numbers[j] == 2020)
			{
				result = numbers[i]*numbers[j];
				done = true;
				break;
			}
		}
		if(done)
		{
			break;
		}
	}
	
	return result;
}

uint64_t threeNumbers(const std::vector<unsigned> &numbers)
{
	uint64_t result = 0;
	
	bool done = false;
	for(unsigned i=0; i<numbers.size()-2; i++)
	{
		for(unsigned j=i+1; j<numbers.size()-1; j++)
		{
			for(unsigned k=j+1; k<numbers.size(); k++)
			{
				if(numbers[i]+numbers[j]+numbers[k] == 2020)
				{
					result = numbers[i]*numbers[j]*numbers[k];
					done = true;
					break;
				}
			}
			if(done)
			{
				break;
			}
		}
		if(done)
		{
			break;
		}
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	
	std::vector<unsigned> numbers;
   
  parseInput(numbers);
	
 	resultA = multiplyNumbers(numbers);
	resultB = threeNumbers(numbers);
	
  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
 	
  return 0;
}
