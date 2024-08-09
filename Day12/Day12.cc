#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

enum Heading
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

void parseInput(std::vector<std::pair<char,unsigned>> &directions)
{
	std::string line;
	
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
		while(getline(input,line))
		{
			directions.push_back(std::make_pair(line[0],std::stoi(line.substr(1))));
		}
  }
  input.close();
}

uint64_t followDirections(const std::vector<std::pair<char,unsigned>> &directions)
{
	uint64_t result = 0;
	
	int64_t x = 0;
	int64_t y = 0;
	unsigned heading = Heading::EAST;
	
	for(auto& direction:directions)
	{
		switch(direction.first)
		{
			case 'N':
			{
				y -= direction.second;
				break;
			}
			case 'E':
			{
				x += direction.second;
				break;
			}
			case 'S':
			{
				y += direction.second;
				break;
			}
			case 'W':
			{
				x -= direction.second;
				break;
			}
			case 'R':
			{
				heading = (heading + (direction.second)/90)%4;
				break;
			}
			case 'L':
			{
				heading = (heading + (3*direction.second)/90)%4;
				break;
			}
			case 'F':
			{
				switch(heading)
				{
					case Heading::NORTH:
					{
						y -= direction.second;
						break;
					}
					case Heading::EAST:
					{
						x += direction.second;
						break;
					}
					case Heading::SOUTH:
					{
						y += direction.second;
						break;
					}
					case Heading::WEST:
					{
						x -= direction.second;
						break;
					}
				}
				break;
			}
		}
	}
	
	result = abs(x) + abs(y);
	
	return result;
}

uint64_t followBeacon(const std::vector<std::pair<char,unsigned>> &directions)
{
	uint64_t result = 0;
	
	int64_t x = 0;
	int64_t y = 0;
	int64_t bX = 10;
	int64_t bY = -1;
	
	for(auto& direction:directions)
	{
		switch(direction.first)
		{
			case 'N':
			{
				bY -= direction.second;
				break;
			}
			case 'E':
			{
				bX += direction.second;
				break;
			}
			case 'S':
			{
				bY += direction.second;
				break;
			}
			case 'W':
			{
				bX -= direction.second;
				break;
			}
			case 'R':
			{
				switch((direction.second/90)%4)
				{
					case 1:
					{
						auto temp = bX;
						bX = -bY;
						bY = temp;
						break;
					}
					case 2:
					{
						bX = -bX;
						bY = -bY;
						break;
					}
					case 3:
					{
						auto temp = bX;
						bX = bY;
						bY = -temp;
						break;
					}
				}
				break;
			}
			case 'L':
			{
				switch((direction.second/90)%4)
				{
					case 1:
					{
						auto temp = bX;
						bX = bY;
						bY = -temp;
						break;
					}
					case 2:
					{
						bX = -bX;
						bY = -bY;
						break;
					}
					case 3:
					{
						auto temp = bX;
						bX = -bY;
						bY = temp;
						break;
					}
				}
				break;
			}
			case 'F':
			{
				x += direction.second*bX;
				y += direction.second*bY;
			}
		}
	}
	
	result = abs(x) + abs(y);
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	
	std::vector<std::pair<char,unsigned>> directions;
   
  parseInput(directions);

 	resultA = followDirections(directions);
	resultB = followBeacon(directions);
 	
  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
 	
  return 0;
}
