#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

void parseInput(std::vector<uint64_t> &numbers)
{
	std::string line;
	
  std::ifstream input("input.txt");
  numbers.push_back(0);
  if(input.is_open())
  {	
		while(getline(input,line))
		{
			numbers.push_back(std::stoll(line));
		}
  }
  input.close();
  std::sort(numbers.begin(), numbers.end());
  numbers.push_back(numbers.back()+3);
}

uint64_t findPaths(const std::vector<uint64_t> &numbers, unsigned start, unsigned end)
{
	uint64_t result = 0;
	
	for(unsigned i=1; i<=3; i++)
	{
		if(start+i <=end && numbers[start]+3 >= numbers[start+i])
		{
			if(start+i == end)
			{
				result += 1;
			}
			else
			{
				result += findPaths(numbers, start+i, end);
			}
		}
	}
	
	return result;
}

std::pair<uint64_t,uint64_t> calculateDistribution(const std::vector<uint64_t> &numbers)
{
	std::pair<uint64_t,uint64_t> result;
	
	unsigned oneDist = 0;
	unsigned threeDist = 0;
	std::vector<unsigned> threes;
	for(unsigned i=1; i<numbers.size(); i++)
	{
		if(numbers[i]-numbers[i-1] == 1)
		{
			oneDist++;
		}
		else if(numbers[i]-numbers[i-1] == 3)
		{
			threeDist++;
			threes.push_back(i-1);
		}
	}
	
	result.first = oneDist*threeDist;

	result.second = 1;
	unsigned start = 0;
	
	for(auto& end:threes)
	{
		result.second *= findPaths(numbers, start, end);
		start = end;
	}
	
	return result;
}

int main()
{
	std::pair<uint64_t,uint64_t> result;
	
	std::vector<uint64_t> numbers;
   
  parseInput(numbers);

 	result = calculateDistribution(numbers);
	
  std::cout << "resultA: " << result.first << '\n';
  std::cout << "resultB: " << result.second << std::endl;
 	
  return 0;
}
