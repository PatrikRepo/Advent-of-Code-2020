#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <deque>
#include <algorithm>

struct Bag
{
	unsigned id = 0;
	std::string colour;
	std::vector<std::pair<unsigned,unsigned>> contains;
	std::vector<unsigned> containedBy;
};

void parseInput(std::vector<Bag> &bags)
{
	std::string line;
	
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
  	std::vector<std::vector<std::pair<std::string,unsigned>>> containing;
  	std::unordered_map<std::string,unsigned> map;
  	unsigned id = 0;
		while(getline(input,line))
		{
			size_t pos = 0;
			size_t endpos = 0;
			endpos = line.find_first_of(" ");
			endpos = line.find_first_of(" ", endpos+1);
			std::string bagColour = line.substr(pos,endpos-pos);
			map[bagColour] = id;
			Bag bag;
			bag.id = id;
			id++;
			bag.colour = bagColour;
			bags.push_back(bag);
			
			pos = line.find_first_of("1234567890",endpos);
			std::vector<std::pair<std::string,unsigned>> bagContains;
			while(pos != std::string::npos)
			{
				unsigned amount = line[pos] - '0';
				pos += 2;
				endpos = line.find_first_of(" ",pos);
				endpos = line.find_first_of(" ",endpos+1);
				std::string newBagColour = line.substr(pos,endpos-pos);
				bagContains.push_back(std::make_pair(newBagColour, amount));
				pos = line.find_first_of("1234567890", endpos);
			}	
			containing.push_back(bagContains);
		}
		for(unsigned i=0; i<containing.size(); i++)
		{
			for(unsigned j=0; j<containing[i].size(); j++)
			{
				bags[i].contains.push_back(std::make_pair(map[containing[i][j].first],containing[i][j].second));
				bags[map[containing[i][j].first]].containedBy.push_back(i);
			}
		}
  }
  input.close();
}

uint64_t findOuterBags(const std::vector<Bag> &bags)
{
	uint64_t result = 0;
	
	std::deque<unsigned> openList;
	std::vector<unsigned> closedList;
	
	for(auto& bag:bags)
	{
		if(bag.colour == "shiny gold")
		{
			openList.push_back(bag.id);
			break;
		}
	}
	
	while(!openList.empty())
	{
		unsigned id = openList.front();
		openList.pop_front();
		closedList.push_back(id);
		
		for(auto& bag:bags[id].containedBy)
		{
			if(std::find_if(closedList.begin(),closedList.end(),[bag](unsigned oId){ return bag == oId; }) == std::end(closedList) &&
					std::find_if(openList.begin(),openList.end(),[bag](unsigned cId){ return bag == cId; }) == std::end(openList))
			{
				openList.push_back(bag);
			}
		}
	}	
	
	result = closedList.size()-1;
	
	return result;
}

uint64_t countBags(unsigned id, const std::vector<Bag> &bags)
{
	uint64_t result = 1;
	
	for(auto& bag:bags[id].contains)
	{
		result += countBags(bag.first, bags)*bag.second;
	}
	
	return result;
}

uint64_t findInnerBags(const std::vector<Bag> &bags)
{
	uint64_t result = 0;
	
	unsigned id = 0;
	for(auto& bag:bags)
	{
		if(bag.colour == "shiny gold")
		{
			id = bag.id;
			break;
		}
	}
	
	result = countBags(id, bags)-1;
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	
	std::vector<Bag> bags;
   
  parseInput(bags);

 	resultA = findOuterBags(bags);
	resultB = findInnerBags(bags);
	
  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
 	
  return 0;
}
