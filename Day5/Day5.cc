#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

void parseInput(std::vector<std::string> &seats)
{
	std::string line;
	
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
  	while(getline(input, line))
  	{
  		seats.push_back(line);
  	}
  }
  input.close();
}

	
uint64_t highestSeatId(const std::vector<std::string> &seats)
{
	uint64_t result = 0;
	
	for(auto& seat:seats)
	{
		unsigned row = 0;
		unsigned column = 0;
		unsigned half = 64;
		
		for(unsigned i=0; i<7; i++)
		{
			if(seat[i] == 'B')
			{
				row += half;
			}
			half /= 2;
		}
		half = 4;
		for(unsigned i=7; i<10; i++)
		{
			if(seat[i] == 'R')
			{
				column += half;
			}
			half /= 2;
		}
		unsigned id = (row*8) + column;
		if(result < id)
		{
			result = id;
		}
	}

	return result;
}	

uint64_t findSeat(const std::vector<std::string> &seats)
{
	uint64_t result = 0;
	
	std::vector<unsigned> seatIds;
	
	for(auto& seat:seats)
	{
		unsigned row = 0;
		unsigned column = 0;
		unsigned half = 64;
		
		for(unsigned i=0; i<7; i++)
		{
			if(seat[i] == 'B')
			{
				row += half;
			}
			half /= 2;
		}
		half = 4;
		for(unsigned i=7; i<10; i++)
		{
			if(seat[i] == 'R')
			{
				column += half;
			}
			half /= 2;
		}
		unsigned id = (row*8) + column;
		seatIds.push_back(id);
	}
	
	std::sort(seatIds.begin(),seatIds.end());
	
	for(unsigned i=0; i<seatIds.size()-1; i++)
	{
		if(seatIds[i]+1 != seatIds[i+1])
		{
			result = seatIds[i]+1;
			break;
		}
	}

	return result;
}	

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	
	std::vector<std::string> seats;
   
  parseInput(seats);

 	resultA = highestSeatId(seats);
	resultB = findSeat(seats);
	
  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
 	
  return 0;
}
