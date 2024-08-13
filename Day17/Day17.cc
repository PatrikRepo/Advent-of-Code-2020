#include <iostream>
#include <fstream>
#include <vector>
#include <array>

void parseInput(std::array<std::array<char,22>,22> &startLayer)
{
	std::string line;
	
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
  	unsigned offset = 7;
  	unsigned y = 7;
		while(getline(input,line))
		{
			for(unsigned i=0; i<line.size(); i++)
			{
				startLayer[y][i+offset] = line[i];
			}
			y++;
		}

		for(unsigned i=0; i<startLayer.size(); i++)
		{
			for(unsigned j=0; j<startLayer[0].size(); j++)
			{
				if(startLayer[i][j] == 0)
				{
					startLayer[i][j] = '.';
				}
			}
		}
  }
  input.close();
}

unsigned countActiveNeighbors(size_t y, size_t x, const std::array<std::array<char,22>,22> &layer, const std::array<std::array<char,22>,22> &layerAbove,const std::array<std::array<char,22>,22> &layerBelow)
{
	unsigned result = 0;
	
	result += layerBelow[y-1][x-1] == '#' ? 1 : 0;
	result += layer[y-1][x-1] == '#' ? 1 : 0;
	result += layerAbove[y-1][x-1] == '#' ? 1 : 0;

	result += layerBelow[y-1][x] == '#' ? 1 : 0;
	result += layer[y-1][x] == '#' ? 1 : 0;
	result += layerAbove[y-1][x] == '#' ? 1 : 0;

	result += layerBelow[y-1][x+1] == '#' ? 1 : 0;
	result += layer[y-1][x+1] == '#' ? 1 : 0;
	result += layerAbove[y-1][x+1] == '#' ? 1 : 0;

	result += layerBelow[y][x-1] == '#' ? 1 : 0;
	result += layer[y][x-1] == '#' ? 1 : 0;
	result += layerAbove[y][x-1] == '#' ? 1 : 0;

	result += layerBelow[y][x] == '#' ? 1 : 0;
	result += layerAbove[y][x] == '#' ? 1 : 0;

	result += layerBelow[y][x+1] == '#' ? 1 : 0;
	result += layer[y][x+1] == '#' ? 1 : 0;
	result += layerAbove[y][x+1] == '#' ? 1 : 0;

	result += layerBelow[y+1][x-1] == '#' ? 1 : 0;
	result += layer[y+1][x-1] == '#' ? 1 : 0;
	result += layerAbove[y+1][x-1] == '#' ? 1 : 0;

	result += layerBelow[y+1][x] == '#' ? 1 : 0;
	result += layer[y+1][x] == '#' ? 1 : 0;
	result += layerAbove[y+1][x] == '#' ? 1 : 0;

	result += layerBelow[y+1][x+1] == '#' ? 1 : 0;
	result += layer[y+1][x+1] == '#' ? 1 : 0;
	result += layerAbove[y+1][x+1] == '#' ? 1 : 0;

	
	return result;
}

uint64_t sixCycles(std::array<std::array<char,22>,22> &startLayer)
{
	uint64_t result = 0;
	
	auto emptyLayer = startLayer;
	
	for(auto& line:emptyLayer)
	{
		for(auto& element:line)
		{
			element = '.';
		}
	}
	
	std::vector<std::array<std::array<char,22>,22>> layers;
	
	layers.push_back(emptyLayer);
	layers.push_back(startLayer);
	layers.push_back(emptyLayer);
	
	for(unsigned count=0; count<6; count++)
	{
		bool newTop = false;
		bool newBottom = false;
		
		auto newLayers = layers;
		
		for(unsigned i=0; i<layers.size(); i++)
		{
			std::array<std::array<char,22>,22> layerAbove;
			std::array<std::array<char,22>,22> layerBelow;
			
			if(i==0)
			{
				layerAbove = emptyLayer;
				layerBelow = layers[1];
			}
			else if(i==layers.size()-1)
			{
				layerAbove = layers[i-1];
				layerBelow = emptyLayer;
			}
			else
			{
				layerAbove = layers[i-1];
				layerBelow = layers[i+1];
			}
			
			
			for(unsigned j=1; j<layers[i].size()-1; j++)
			{
				for(unsigned k=1; k<layers[i][0].size()-1; k++)
				{
					unsigned neighbors = countActiveNeighbors(j,k,layers[i],layerAbove,layerBelow);
					if(layers[i][j][k] == '#' && (neighbors < 2 || neighbors > 3))
					{
						newLayers[i][j][k] = '.';
					}
					else if(layers[i][j][k] == '.' && neighbors == 3)
					{
						newLayers[i][j][k] = '#';	
						if(i == 0 && !newTop)
						{
							newTop = true;
						}
						else if(i == layers.size()-1 && !newBottom)
						{
							newBottom = true;
						}
					}
				}
			}
		}
		
		layers = newLayers;
		if(newTop)
		{
			layers.insert(layers.begin(), emptyLayer);
		}
		if(newBottom)
		{
			layers.push_back(emptyLayer);
		}
	}

	
	for(auto& layer:layers)
	{
		for(auto& line:layer)
		{
			for(auto& element:line)
			{
				if(element == '#')
				{
					result++;
				}
			}	
		}
	}
	
	return result;
}

unsigned countHyperNeighbors(size_t x, size_t y, size_t z, size_t w, const std::array<std::array<std::array<std::array<char,22>,22>,15>,15> hyperBlock)
{
	unsigned result = 0;
	
	for(unsigned i=w-1; i<=w+1; i++)
	{
		for(unsigned j=z-1; j<=z+1; j++)
		{
			for(unsigned k=y-1; k<=y+1; k++)
			{
				for(unsigned l=x-1; l<=x+1; l++)
				{
					if(!(x==l && y==k && z==j && w==i) && hyperBlock[i][j][k][l] == '#')
					{
						result++;
					}
				}
			}
		}
	}
	
	return result;
}
uint64_t hyperCubes(const std::array<std::array<char,22>,22> &startLayer)
{
	uint64_t result = 0;
	
	auto emptyLayer = startLayer;
	
	for(auto& line:emptyLayer)
	{
		for(auto& element:line)
		{
			element = '.';
		}
	}
	
	std::array<std::array<std::array<char,22>,22>,15> emptyBlock;
	for(unsigned i=0; i<15; i++)
	{
		emptyBlock[i] = emptyLayer;
	}

	std::array<std::array<std::array<char,22>,22>,15> startBlock;
	
	for(unsigned i=0; i<15; i++)
	{
		if(i!=7)
		{
			startBlock[i] = emptyLayer;
		}
	}
	startBlock[7] = startLayer;
	
	std::array<std::array<std::array<std::array<char,22>,22>,15>,15> hyperBlock;
	
	for(unsigned i=0; i<15; i++)
	{
		if(i!=7)
		{
			hyperBlock[i] = emptyBlock;
		}
	}
	hyperBlock[7] = startBlock;
	
	unsigned start = 6;
	unsigned end = 8;
	
	for(unsigned count=0; count<6; count++)
	{
		auto newHyperBlock = hyperBlock;
		bool newTop = false;
		bool newBottom = false;
		
		for(unsigned i=start; i<=end; i++)
		{
			for(unsigned j=start; j<=end; j++)
			{
				for(unsigned k=start; k<=end+7; k++)
				{
					for(unsigned l=start; l<=end+7; l++)
					{
						unsigned neighbors = countHyperNeighbors(l,k,j,i,hyperBlock);
						if(hyperBlock[i][j][k][l] == '#' && (neighbors < 2 || neighbors > 3))
						{
							newHyperBlock[i][j][k][l] = '.';
						}
						else if(hyperBlock[i][j][k][l] == '.' && neighbors == 3)
						{
							newHyperBlock[i][j][k][l] = '#';	
							if(!newTop && (i == start || j == start || k == start || l == start))
							{
								newTop = true;
							}
							else if(!newBottom && (i == end || j == end || k == end || l == end))
							{
								newBottom = true;
							}
						}
					}
				}
			}
		}
		
		hyperBlock = newHyperBlock;
		if(newTop)
		{
			start--;
		}
		if(newBottom)
		{
			end++;
		}
	}
	
	for(auto& block:hyperBlock)
	{
		for(auto& layer:block)
		{
			for(auto& line:layer)
			{
				for(auto& element:line)
				{
					if(element == '#')
					{
						result++;
					}
				}
			}
		}
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	
	std::array<std::array<char,22>,22> startLayer{0};
   
  parseInput(startLayer);

 	resultA = sixCycles(startLayer);
	resultB = hyperCubes(startLayer);
 	
  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
 	
  return 0;
}
