#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

void parseInput(std::vector<std::string> &seats)
{
	std::string line;
	
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
		while(getline(input,line))
		{
			seats.push_back(line);
		}
  }
  input.close();
}

unsigned countNeighbors(const std::vector<std::string> &seats, size_t x, size_t y)
{
	unsigned result = 0;
	
	if(x>0 && y>0 && seats[y-1][x-1] == '#')
	{
		result++;
	}
	if(y>0 && seats[y-1][x] == '#')
	{
		result++;
	}
	if(x+1<seats[0].size() && y>0 && seats[y-1][x+1] == '#')
	{
		result++;
	}
	if(x>0 && seats[y][x-1] == '#')
	{
		result++;
	}
	if(x+1<seats[0].size() && seats[y][x+1] == '#')
	{
		result++;
	}
	if(x>0 && y+1<seats.size() && seats[y+1][x-1] == '#')
	{
		result++;
	}
	if(y+1<seats.size() && seats[y+1][x] == '#')
	{
		result++;
	}
	if(x+1<seats[0].size() && y+1<seats.size() && seats[y+1][x+1] == '#')
	{
		result++;
	}
	
	return result;
}

unsigned see(const std::vector<std::string> &seats, size_t x, size_t y, int xAdd, int yAdd)
{
	unsigned result = 0;

	while(seats[y][x] == '.')
	{
		if((xAdd == 0 || (xAdd == -1 && x>0) || (xAdd == 1 && x+1<seats[0].size())) && (yAdd == 0 || (yAdd == -1 && y>0) || (yAdd == 1 && y+1<seats.size())))
		{
			x += xAdd;
			y += yAdd;
		}
		else
		{
			break;
		}
	}
	
	if(seats[y][x] == '#')
	{
		result = 1;
	}
	
	return result;
}

unsigned seeAndCount(const std::vector<std::string> &seats, size_t x, size_t y)
{
	unsigned result = 0;
	
	if(x>0 && y>0)
	{
		result += see(seats, x-1, y-1, -1, -1);
	}
	if(y>0)
	{
		result += see(seats, x, y-1, 0, -1);
	}
	if(x+1<seats[0].size() && y>0)
	{
		result += see(seats, x+1, y-1, 1, -1);
	}
	if(x>0)
	{
		result += see(seats, x-1, y, -1, 0);
	}
	if(x+1<seats[0].size())
	{
		result += see(seats, x+1, y, 1, 0);
	}
	if(x>0 && y+1<seats.size())
	{
		result += see(seats, x-1, y+1, -1, 1);
	}
	if(y+1<seats.size())
	{
		result += see(seats, x, y+1, 0, 1);
	}
	if(x+1<seats[0].size() && y+1<seats.size())
	{
		result += see(seats, x+1, y+1, 1, 1);
	}
	
	return result;
}

uint64_t fillSeats(std::vector<std::string> seats)
{
	uint64_t result = 0;
	
	bool done = false;
	while(!done)
	{
		done = true;
		
		auto newSeats = seats;
		for(unsigned i=0; i<seats.size(); i++)
		{
			for(unsigned j=0; j<seats[0].size(); j++)
			{
				if(seats[i][j] == 'L' && countNeighbors(seats, j, i) == 0)
				{
					newSeats[i][j] = '#';
					done = false;
				}
				else if(seats[i][j] == '#' && countNeighbors(seats, j, i) >= 4)
				{
					newSeats[i][j] = 'L';
					done = false;
				}
			}	
		}
		seats = newSeats;
	}
	
	for(auto& line:seats)
	{
		for(auto& seat:line)
		{
			if(seat == '#')
			{
				result++;
			}
		}
	}
	
	return result;
}

uint64_t realRules(std::vector<std::string> seats)
{
	uint64_t result = 0;
	
	bool done = false;
	while(!done)
	{
		done = true;
		
		auto newSeats = seats;
		for(unsigned i=0; i<seats.size(); i++)
		{
			for(unsigned j=0; j<seats[0].size(); j++)
			{
				if(seats[i][j] == 'L' && seeAndCount(seats, j, i) == 0)
				{
					newSeats[i][j] = '#';
					done = false;
				}
				else if(seats[i][j] == '#' && seeAndCount(seats, j, i) >= 5)
				{
					newSeats[i][j] = 'L';
					done = false;
				}
			}	
		}
		seats = newSeats;
	}
	
	for(auto& line:seats)
	{
		for(auto& seat:line)
		{
			if(seat == '#')
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
	
	std::vector<std::string> seats;
   
  parseInput(seats);

 	resultA = fillSeats(seats);
	resultB = realRules(seats);
 	
  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
 	
  return 0;
}
