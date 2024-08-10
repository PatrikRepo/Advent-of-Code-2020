#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <numeric>

void parseInput(uint64_t &time, std::vector<std::pair<unsigned, unsigned>> &busses)
{
	std::string line;
	
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
		getline(input,line);
		time = std::stoll(line);
		
		getline(input,line);
		size_t pos = 0;
		size_t endpos = line.find_first_of(",");
		
		unsigned counter = 0;
		
		while(endpos != std::string::npos)
		{

			if(endpos == std::string::npos)
			{
				endpos = line.size();
			}
			if(line.substr(pos,endpos-pos) != "x")
			{
				busses.push_back(std::make_pair(std::stoi(line.substr(pos,endpos-pos)),counter));
			}
			counter++;
			pos = endpos+1;
			endpos = line.find_first_of(",", pos);
		}
		if(line.substr(pos,endpos-pos) != "x")
		{
			busses.push_back(std::make_pair(std::stoi(line.substr(pos)),counter));
		}
  }
  input.close();
}

uint64_t findBus(uint64_t time, const std::vector<std::pair<unsigned, unsigned>> &busses)
{
	uint64_t result = 0;
	
	uint64_t earliest = UINT64_MAX;
	
	for(auto& bus: busses)
	{
		if(earliest > bus.first - time%bus.first)
		{
			earliest = bus.first - time%bus.first;
			result = bus.first*(bus.first - time%bus.first);
		}
	}
	
	return result;
}

uint64_t winContest(const std::vector<std::pair<unsigned, unsigned>> &busses)
{
	uint64_t result = 0;
	
	uint64_t add = busses[0].first;
	
	for(unsigned i=1; i<busses.size(); i++)
	{
		while(result%busses[i].first != busses[i].first - (busses[i].second%busses[i].first))
		{
			result += add;
		}
		add *= busses[i].first;
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	
	uint64_t time = 0;
	std::vector<std::pair<unsigned, unsigned>> busses;
   
  parseInput(time, busses);

 	resultA = findBus(time, busses);
	resultB = winContest(busses);
 	
  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
 	
  return 0;
}
