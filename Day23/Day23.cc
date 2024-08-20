#include <iostream>
#include <fstream>
#include <utility>
#include <array>

void parseInput(std::array<unsigned,9> &cups)
{
	std::string line;
	
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
  	getline(input,line);
		
		for(unsigned i=0; i<cups.size(); i++)
		{
			cups[i] = line[i] - '0';
		}
  }
  input.close();

}

std::string cupGame(std::array<unsigned,9> cups)
{
	std::string result;
	
	unsigned index = 0;
	for(unsigned count=0; count<100; count++)
	{
		unsigned first = cups[(index+1 < cups.size()) ? index+1 : index+1-cups.size()];
		unsigned second = cups[(index+2 < cups.size()) ? index+2 : index+2-cups.size()];
		unsigned third = cups[(index+3 < cups.size()) ? index+3 : index+3-cups.size()];
		
		unsigned dest = cups[index]-1;
		dest = (dest == 0) ? cups.size() : dest;
		while(dest == first || dest == second || dest == third)
		{
			dest = (dest+cups.size()-1 < cups.size() || dest == 1) ? dest+cups.size()-1 : dest-1;
		}

		unsigned i = index;
		while(cups[i] != dest)
		{
			i = (i+1 < cups.size()) ? i+1 : i+1-cups.size();
			cups[i] = cups[(i+3 < cups.size()) ? i+3 : i+3-cups.size()];
		}
		
		cups[(i+1 < cups.size()) ? i+1 : i+1-cups.size()] = first;
		cups[(i+2 < cups.size()) ? i+2 : i+2-cups.size()] = second;
		cups[(i+3 < cups.size()) ? i+3 : i+3-cups.size()] = third;
		
		index = index+1 < cups.size() ? index+1 : index+1-cups.size();
	}

	for(unsigned i=0; i<cups.size(); i++)
	{
		if(cups[i] == 1)
		{
			index = (i+1)%cups.size();
			break;
		}
	}
	
	for(unsigned i=0; i<cups.size()-1; i++)
	{
		result += std::to_string(cups[(index+i)%cups.size()]);
	}
	
	return result;
}

uint64_t realGame(std::array<unsigned,9> cupsBase)
{
	uint64_t result = 0;
	
	std::array<std::pair<uint32_t,uint32_t>,1000000> cups;
	
	for(uint32_t i=0; i<cupsBase.size(); i++)
	{
		cups[i].first = cupsBase[i];
		cups[i].second = i+1;
	}
	for(uint32_t i=9; i<1000000; i++)
	{
		cups[i].first = i+1;
		cups[i].second = i+1;
	}
	cups[cups.size()-1].second = 0;
	
	uint32_t index = 0;
	
	for(uint32_t count=0; count<10000000; count++)
	{
		uint32_t first = cups[cups[index].second].first;
		uint32_t second = cups[cups[cups[index].second].second].first;
		uint32_t third = cups[cups[cups[cups[index].second].second].second].first;
		uint32_t next = cups[index].second;
		cups[index].second = cups[cups[cups[cups[index].second].second].second].second;
		
		uint32_t dest = cups[index].first;
		if(dest <= 1)
		{
			dest += cups.size();
		}
		dest--;

		while(dest == first || dest == second || dest == third)
		{
			if(dest <= 1)
			{
				dest += cups.size();
			}
			dest--;
		}
		
		bool found = false;
		uint32_t destIndex = 0;
		for(unsigned i=index+25; i>=1; i--)
		{
			if(cups[i-1].first == dest)
			{
				found = true;
				destIndex = i-1;
				break;
			}
		}
		
		if(!found)
		{
			for(unsigned i=index+25; i<cups.size(); i++)
			{
				if(cups[i].first == dest)
				{
					destIndex = i;
					break;
				}
			}
		}
		
		uint32_t destNext = cups[destIndex].second;
		cups[destIndex].second = next;
		cups[cups[cups[next].second].second].second = destNext;
		
		index = cups[index].second;

	}
	
	for(unsigned i=0; i<cups.size(); i++)
	{
		if(cups[i].first == 1)
		{
			index = cups[i].second;
			break;
		}
	}
	
	result = cups[index].first;
	index = cups[index].second;
	result *= cups[index].first;

	return result;
}

int main()
{
	std::string resultA;
	uint64_t resultB = 0;
	
	std::array<unsigned,9> cups;
  
  parseInput(cups);

 	resultA = cupGame(cups);
	resultB = realGame(cups);
	
  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
 	
  return 0;
}
