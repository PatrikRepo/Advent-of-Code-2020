#include <iostream>
#include <fstream>
#include <vector>
#include <array>

void parseInput(std::vector<std::array<unsigned,27>> &groups)
{
	std::string line;
	
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
  	std::array<unsigned, 27> group;
  	unsigned count = 0;
  	while(getline(input, line))
  	{
  		if(line == "")
  		{
  			group[26] = count;
  			if(count > 0)
  			{
  			  groups.push_back(group);
  			}
  			group.fill(0);
  			count = 0;
  		}
  		else
  		{
  			count++;
  			for(auto element:line)
  			{
  				group[element-'a']++;
  			}
  		}
  	}
  	group[26] = count;
		groups.push_back(group);
  }
  input.close();
}

uint64_t numberOfQuestions(const std::vector<std::array<unsigned,27>> &groups)
{
	uint64_t result = 0;
	
	for(auto& group:groups)
	{
		for(unsigned i=0; i<group.size()-1; i++)
		{
			if(group[i] != 0)
			{
				result++;
			}
		}
	}
	
	return result;
}

uint64_t numberOfAllYes(const std::vector<std::array<unsigned,27>> &groups)
{
	uint64_t result = 0;
	
	for(auto& group:groups)
	{
		for(unsigned i=0; i<group.size()-1; i++)
		{
			if(group[i] == group[26])
			{
				result++;
			}
		}
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	
	std::vector<std::array<unsigned,27>> groups;
   
  parseInput(groups);


 	resultA = numberOfQuestions(groups);
	resultB = numberOfAllYes(groups);
	
  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
 	
  return 0;
}
