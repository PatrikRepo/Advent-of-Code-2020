#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

void parseInput(std::vector<std::string> &slope)
{
	std::string line;
	
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
  	while(getline(input, line))
  	{
  		slope.push_back(line); 		
  	}
  }
  input.close();
}

uint64_t countTrees(const std::vector<std::string> &slope)
{
	uint64_t result = 0;
	
	unsigned x = 3;
	
	for(unsigned i=1; i<slope.size(); i++)
	{
		if(slope[i][x] == '#')
		{
			result++;
		}
		x = (x+3)%slope[0].size();
	}
	
	return result;
}

uint64_t allSlopes(const std::vector<std::string> &slope)
{
	uint64_t result = 0;
	
	unsigned x = 1;
	unsigned treeCount = 0;
	
	for(unsigned i=1; i<slope.size(); i++)
	{
		if(slope[i][x] == '#')
		{
			treeCount++;
		}
		x = (x+1)%slope[0].size();
	}
	result = treeCount;
	treeCount = 0;
	
	x = 3;
	for(unsigned i=1; i<slope.size(); i++)
	{
		if(slope[i][x] == '#')
		{
			treeCount++;
		}
		x = (x+3)%slope[0].size();
	}
	result *= treeCount;
	treeCount = 0;
	
	x = 5;
	for(unsigned i=1; i<slope.size(); i++)
	{
		if(slope[i][x] == '#')
		{
			treeCount++;
		}
		x = (x+5)%slope[0].size();
	}
	result *= treeCount;
	treeCount = 0;
	
	x = 7;
	for(unsigned i=1; i<slope.size(); i++)
	{
		if(slope[i][x] == '#')
		{
			treeCount++;
		}
		x = (x+7)%slope[0].size();
	}
	result *= treeCount;
	treeCount = 0;
	
	x = 1;
	for(unsigned i=2; i<slope.size(); i+=2)
	{
		if(slope[i][x] == '#')
		{
			treeCount++;
		}
		x = (x+1)%slope[0].size();
	}
	result *= treeCount;

	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	
	std::vector<std::string> slope;
   
  parseInput(slope);
	
 	resultA = countTrees(slope);
	resultB = allSlopes(slope);
	
  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
 	
  return 0;
}
