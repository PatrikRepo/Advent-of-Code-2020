#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <array>
#include <unordered_map>
#include <deque>
#include <algorithm>

void parseInput(std::vector<std::pair<unsigned,std::vector<std::string>>> &tiles)
{
	std::string line;
	
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
		while(getline(input,line))
		{
			size_t pos = line.find_first_of("1234567890");
			size_t endpos = line.size()-1;
			unsigned id = std::stoi(line.substr(pos,endpos-pos));
			
			getline(input,line);
			std::vector<std::string> tile;
			
			while(line != "")
			{
				tile.push_back(line);
				getline(input,line);
			}
			tiles.push_back(std::make_pair(id,tile));
		}
  }
  input.close();

}

void flipTileHorizontal(std::vector<std::string> &tile)
{
	auto newTile = tile;
	for(unsigned i=0; i<tile.size(); i++)
	{
		for(unsigned j=0; j<tile[0].size(); j++)
		{
			newTile[i][j] = tile[i][tile[0].size()-1-j];
		}
	}
	tile = newTile;
}

void flipTileVertical(std::vector<std::string> &tile)
{
	auto newTile = tile;
	for(unsigned i=0; i<tile.size(); i++)
	{
		for(unsigned j=0; j<tile[0].size(); j++)
		{
			newTile[i][j] = tile[tile[0].size()-1-i][j];
		}
	}
	tile = newTile;
}

void rotateTileRight(std::vector<std::string> &tile)
{
	auto newTile = tile;
	for(unsigned i=0; i<tile.size(); i++)
	{
		for(unsigned j=0; j<tile[0].size(); j++)
		{
			newTile[j][tile[0].size()-1-i] = tile[i][j];
		}
	}
	tile = newTile;
}

void rotateTileHalf(std::vector<std::string> &tile)
{
	auto newTile = tile;
	for(unsigned i=0; i<tile.size(); i++)
	{
		for(unsigned j=0; j<tile[0].size(); j++)
		{
			newTile[tile.size()-1-i][tile.size()-1-j] = tile[i][j];
		}
	}
	tile = newTile;
}

void rotateTileLeft(std::vector<std::string> &tile)
{
	auto newTile = tile;
	for(unsigned i=0; i<tile.size(); i++)
	{
		for(unsigned j=0; j<tile[0].size(); j++)
		{
			newTile[tile.size()-1-j][i] = tile[i][j];
		}
	}
	tile = newTile;
}

uint64_t puzzleTiles(std::vector<std::pair<unsigned,std::vector<std::string>>> &tiles, std::vector<std::string> &map)
{
	uint64_t result = 1;
	
	std::unordered_map<unsigned,std::array<unsigned,4>> tileMap;
	
	unsigned leftUpperCorner = 0;
		
	std::deque<unsigned> openList;
	std::vector<unsigned> closedList;
	
	openList.push_back(0);
	
	while(!openList.empty())
	{
		unsigned index = openList.front();
		openList.pop_front();
		closedList.push_back(index);
		
		unsigned North = 0;
		unsigned East = 0;
		unsigned South = 0;
		unsigned West = 0;

		std::string tileNorth = tiles[index].second[0];
		std::string tileSouth = tiles[index].second.back();
		std::string tileEast;
		std::string tileWest;
		for(unsigned i=0; i<tiles[index].second.size(); i++)
		{
			tileWest += tiles[index].second[i][0];
			tileEast += tiles[index].second[i].back();
		}
		
		std::array<unsigned,4> tileNeighbors{0};
		
		for(unsigned i=0; i<tiles.size(); i++)
		{
			if(index != i)
			{
			
				std::string nNorth = tiles[i].second[0];
				std::string nSouth = tiles[i].second.back();
				std::string nEast;
				std::string nWest;
				for(unsigned j=0; j<tiles[i].second.size(); j++)
				{
					nWest += tiles[i].second[j][0];
					nEast += tiles[i].second[j].back();
				}
				std::string reverseNorth = nNorth;
				std::string reverseEast = nEast;
				std::string reverseSouth = nSouth;
				std::string reverseWest = nWest;
				
				for(unsigned j=0; j<reverseNorth.size(); j++)
				{
					reverseNorth[j] = nNorth[reverseNorth.size()-1-j];
					reverseEast[j] = nEast[reverseEast.size()-1-j];
					reverseSouth[j] = nSouth[reverseSouth.size()-1-j];
					reverseWest[j] = nWest[reverseWest.size()-1-j];
				}
				
				bool foundNorth = false;

				if(tileNorth == nNorth)
				{
					foundNorth = true;
					rotateTileHalf(tiles[i].second);
					flipTileHorizontal(tiles[i].second);
				}
				else if(tileNorth == reverseNorth)
				{
					foundNorth = true;
					rotateTileHalf(tiles[i].second);
				}
				else if(tileNorth == nEast)
				{
					foundNorth = true;
					rotateTileRight(tiles[i].second);
					flipTileHorizontal(tiles[i].second);
				}
				else if(tileNorth == reverseEast)
				{
					foundNorth = true;
					rotateTileRight(tiles[i].second);
				}
				else if(tileNorth == nSouth)
				{
					foundNorth = true;
				}
				else if(tileNorth == reverseSouth)
				{
					foundNorth = true;
					flipTileHorizontal(tiles[i].second);
				}
				else if(tileNorth == nWest)
				{
					foundNorth = true;
					rotateTileLeft(tiles[i].second);
				}
				else if(tileNorth == reverseWest)
				{
					foundNorth = true;
					rotateTileLeft(tiles[i].second);
					flipTileHorizontal(tiles[i].second);
				}
				if(foundNorth)
				{
					tileNeighbors[0] = i+1;
					North++;
					if(std::find_if(openList.begin(),openList.end(),[i](unsigned oIndex) { return i == oIndex; }) == std::end(openList) && 
						std::find_if(closedList.begin(),closedList.end(),[i](unsigned cIndex) { return i == cIndex; }) == std::end(closedList))
					{
						openList.push_back(i);
					}
					continue;
				}
				
				bool foundEast = false;
				
				if(tileEast == nNorth)
				{
					foundEast = true;
					rotateTileLeft(tiles[i].second);
					flipTileVertical(tiles[i].second);
				}
				else if(tileEast == reverseNorth)
				{
					foundEast = true;
					rotateTileLeft(tiles[i].second);
				}
				else if(tileEast == nEast)
				{
					foundEast = true;
					rotateTileHalf(tiles[i].second);
					flipTileVertical(tiles[i].second);
				}
				else if(tileEast == reverseEast)
				{
					foundEast = true;
					rotateTileHalf(tiles[i].second);
				}
				else if(tileEast == nSouth)
				{
					foundEast = true;
					rotateTileRight(tiles[i].second);
				}
				else if(tileEast == reverseSouth)
				{
					foundEast = true;
					rotateTileRight(tiles[i].second);
					flipTileVertical(tiles[i].second);
				}
				else if(tileEast == nWest)
				{
					foundEast = true;
				}
				else if(tileEast == reverseWest)
				{
					foundEast = true;
					flipTileVertical(tiles[i].second);
				}
				if(foundEast)
				{
					tileNeighbors[1] = i+1;
					East++;
					if(std::find_if(openList.begin(),openList.end(),[i](unsigned oIndex) { return i == oIndex; }) == std::end(openList) && 
						std::find_if(closedList.begin(),closedList.end(),[i](unsigned cIndex) { return i == cIndex; }) == std::end(closedList))
					{
						openList.push_back(i);
					}
					continue;
				}
				
				bool foundSouth = false;
				
				if(tileSouth == nNorth)
				{
					foundSouth = true;
				}
				else if(tileSouth == reverseNorth)
				{
					foundSouth = true;
					flipTileHorizontal(tiles[i].second);
				}
				else if(tileSouth == nEast)
				{
					foundSouth = true;
					rotateTileLeft(tiles[i].second);
				}
				else if(tileSouth == reverseEast)
				{
					foundSouth = true;
					rotateTileLeft(tiles[i].second);
					flipTileHorizontal(tiles[i].second);
				}
				else if(tileSouth == nSouth)
				{
					foundSouth = true;
					rotateTileHalf(tiles[i].second);
					flipTileHorizontal(tiles[i].second);
				}
				else if(tileSouth == reverseSouth)
				{
					foundSouth = true;
					rotateTileHalf(tiles[i].second);
				}
				else if(tileSouth == nWest)
				{
					foundSouth = true;
					rotateTileRight(tiles[i].second);
					flipTileHorizontal(tiles[i].second);
				}
				else if(tileSouth == reverseWest)
				{
					foundSouth = true;
					rotateTileRight(tiles[i].second);
				}
				if(foundSouth)
				{
					tileNeighbors[2] = i+1;
					South++;
					if(std::find_if(openList.begin(),openList.end(),[i](unsigned oIndex) { return i == oIndex; }) == std::end(openList) && 
						std::find_if(closedList.begin(),closedList.end(),[i](unsigned cIndex) { return i == cIndex; }) == std::end(closedList))
					{
						openList.push_back(i);
					}
					continue;
				}
				
				bool foundWest = false;
				
				if(tileWest == nNorth)
				{
					foundWest = true;
					rotateTileRight(tiles[i].second);
				}
				else if(tileWest == reverseNorth)
				{
					foundWest = true;
					rotateTileRight(tiles[i].second);
					flipTileVertical(tiles[i].second);
				}
				else if(tileWest == nEast)
				{
					foundWest = true;
				}
				else if(tileWest == reverseEast)
				{
					foundWest = true;
					flipTileVertical(tiles[i].second);
				}
				else if(tileWest == nSouth)
				{
					foundWest = true;
					rotateTileLeft(tiles[i].second);
					flipTileVertical(tiles[i].second);
				}
				else if(tileWest == reverseSouth)
				{
					foundWest = true;
					rotateTileLeft(tiles[i].second);
				}
				else if(tileWest == nWest)
				{
					foundWest = true;
					rotateTileHalf(tiles[i].second);
					flipTileVertical(tiles[i].second);
				}
				else if(tileWest == reverseWest)
				{
					foundWest = true;
					rotateTileHalf(tiles[i].second);
				}
				if(foundWest)
				{
					tileNeighbors[3] = i+1;
					West++;
					if(std::find_if(openList.begin(),openList.end(),[i](unsigned oIndex) { return i == oIndex; }) == std::end(openList) && 
						std::find_if(closedList.begin(),closedList.end(),[i](unsigned cIndex) { return i == cIndex; }) == std::end(closedList))
					{
						openList.push_back(i);
					}
				}
			}
		}
		
		tileMap[index] = tileNeighbors;
		
		if(North+East+South+West == 2)
		{
			result *= tiles[index].first;
			if(North == 0 && West == 0)
			{
				leftUpperCorner = index;
			}
		}
	}

	bool done = false;
	unsigned currentRow = leftUpperCorner;
	unsigned currentTile = currentRow;
	
	while(!done)
	{
		std::string lineOne;
		std::string lineTwo;
		std::string lineThree;
		std::string lineFour;
		std::string lineFive;
		std::string lineSix;
		std::string lineSeven;
		std::string lineEight;
		
		bool rowDone = false;

		while(!rowDone)
		{
			lineOne += tiles[currentTile].second[1].substr(1,8);
			lineTwo += tiles[currentTile].second[2].substr(1,8);
			lineThree += tiles[currentTile].second[3].substr(1,8);
			lineFour += tiles[currentTile].second[4].substr(1,8);
			lineFive += tiles[currentTile].second[5].substr(1,8);
			lineSix += tiles[currentTile].second[6].substr(1,8);
			lineSeven += tiles[currentTile].second[7].substr(1,8);
			lineEight += tiles[currentTile].second[8].substr(1,8);
			
			if(tileMap[currentTile][1] != 0)
			{
				currentTile = tileMap[currentTile][1]-1;
			}
			else
			{
				rowDone = true;
			}
		}
		map.push_back(lineOne);
		map.push_back(lineTwo);
		map.push_back(lineThree);
		map.push_back(lineFour);
		map.push_back(lineFive);
		map.push_back(lineSix);
		map.push_back(lineSeven);
		map.push_back(lineEight);
		if(tileMap[currentRow][2] != 0)
		{
			currentRow = tileMap[currentRow][2]-1;
			currentTile = currentRow;
		}
		else
		{
			done = true;
		}
	}
	
	return result;
}

uint64_t findMonsters(std::vector<std::string> &map)
{
	uint64_t result = 0;
	
	unsigned monsters = 0;
	const unsigned  symsInMonster = 15;
	unsigned count = 0;
	
	while(monsters == 0)
	{
		if(count == 4)
		{
			flipTileHorizontal(map);
		}
		else if(count == 8)
		{
			flipTileVertical(map);
		}
		else if(count == 12)
		{
			flipTileHorizontal(map);
		}
		
		std::array<std::string,3> monster;
		monster[0] = "                  # ";
		monster[1] = "#    ##    ##    ###";
		monster[2] = " #  #  #  #  #  #   ";
		
		for(unsigned i=2; i<map.size(); i++)
		{
			for(unsigned j=0; j<map[0].size()-20; j++)
			{
				bool foundMonster = true;
				for(unsigned k=0; k<20; k++)
				{
					if((monster[0][k] == '#' && map[i-2][j+k] != '#') || (monster[1][k] == '#' && map[i-1][j+k] != '#') || (monster[2][k] == '#' && map[i][j+k] != '#'))
					{
						foundMonster = false;
						break;
					}
				}
				if(foundMonster)
				{
					monsters++;
				}
			}
		}
		rotateTileRight(map);
		count++;
	}
	
	for(auto& line:map)
	{
		for(auto& element:line)
		{
			if(element == '#')
			{
				result++;
			}
		}
	}
	
	result -= (monsters*symsInMonster);
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	
	std::vector<std::pair<unsigned,std::vector<std::string>>> tiles;
  std::vector<std::string> map;
  
  parseInput(tiles);
	
	//For convenience sake the first question results is calculated and the map for the second question is done in the same function
 	resultA = puzzleTiles(tiles, map);
	resultB = findMonsters(map);

  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
 	
  return 0;
}
