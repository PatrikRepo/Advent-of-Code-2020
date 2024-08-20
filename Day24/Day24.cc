#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <array>

void parseInput(std::vector<std::string> &instructions)
{
	std::string line;
	
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
  	while(getline(input,line))
  	{
  		instructions.push_back(line);
  	}
  }
  input.close();

}

std::pair<uint64_t,uint64_t> flipTiles(const std::vector<std::string> &instructions)
{
	std::pair<uint64_t,uint64_t> result;
	
	std::array<std::array<size_t,230>,230> tiles{0};
	
	for(auto& instruction:instructions)
	{
		size_t pos = 0;
		size_t x = 115;
		size_t y = 115;
		bool halfStep = false;
		
		while(pos < instruction.size())
		{
			if(instruction[pos] == 'e')
			{
				x++;
			}
			else if(instruction[pos] == 'w')
			{
				x--;
			}
			else if(instruction[pos] == 'n')
			{
				y--;
				pos++;
				if(instruction[pos] == 'e')
				{
					if(halfStep)
					{	
						x++;
						halfStep = false;
					}
					else
					{
						halfStep = true;
					}
				}
				else
				{
					if(halfStep)
					{	
						halfStep = false;
					}
					else
					{
						halfStep = true;
						x--;
					}
				}
			}
			else
			{
				y++;
				pos++;
				if(instruction[pos] == 'e')
				{
					if(halfStep)
					{	
						x++;
						halfStep = false;
					}
					else
					{
						halfStep = true;
					}
				}
				else
				{
					if(halfStep)
					{	
						halfStep = false;
					}
					else
					{
						halfStep = true;
						x--;
					}
				}
			}
			pos++;
		}
		
		tiles[y][x] = (tiles[y][x]+1)%2;
	}
	
	for(auto& line:tiles)
	{
		for(auto element:line)
		{
			if(element == 1)
			{
				result.first++;
			}
		}
	}

	for(unsigned count=0; count<100; count++)
	{
		auto newTiles = tiles;
		
		for(unsigned i=1; i<tiles.size()-1; i++)
		{
			for(unsigned j=1; j<tiles[0].size()-1; j++)
			{
				unsigned neighbors = 0;
				
				neighbors += (tiles[i][j-1] == 1) ? 1 : 0;
				neighbors += (tiles[i][j+1] == 1) ? 1 : 0;
				if(i%2 == 1)
				{
					neighbors += (tiles[i-1][j-1] == 1) ? 1 : 0;
					neighbors += (tiles[i-1][j] == 1) ? 1 : 0;
					neighbors += (tiles[i+1][j-1] == 1) ? 1 : 0;
					neighbors += (tiles[i+1][j] == 1) ? 1 : 0;
				}
				else
				{
					neighbors += (tiles[i-1][j+1] == 1) ? 1 : 0;
					neighbors += (tiles[i-1][j] == 1) ? 1 : 0;
					neighbors += (tiles[i+1][j+1] == 1) ? 1 : 0;
					neighbors += (tiles[i+1][j] == 1) ? 1 : 0;
				}
				
				if(tiles[i][j] == 1 && (neighbors == 0 || neighbors > 2))
				{
					newTiles[i][j] = 0;
				}
				else if(tiles[i][j] == 0 && neighbors == 2)
				{
					newTiles[i][j] = 1;
				}
			}
		}
		
		tiles = newTiles;
	}

	for(auto& line:tiles)
	{
		for(auto element:line)
		{
			if(element == 1)
			{
				result.second++;
			}
		}
	}

	return result;
}

int main()
{
	std::pair<uint64_t,uint64_t> result;
	
	std::vector<std::string> instructions;
  
  parseInput(instructions);

 	result = flipTiles(instructions);
	
  std::cout << "resultA: " << result.first << '\n';
  std::cout << "resultB: " << result.second << std::endl;
 	
  return 0;
}
