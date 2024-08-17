#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_map>

struct orderRules
{
	bool operator()(std::pair<unsigned,std::vector<std::string>> a, std::pair<unsigned,std::vector<std::string>> b) {return a.first < b.first; }
};

void parseInput(std::vector<std::pair<unsigned,std::vector<std::string>>> &rules, std::vector<std::string> &messages)
{
	std::string line;
	
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
  	getline(input,line);
		while(line != "")
		{
			size_t pos = 0;
			size_t endpos = line.find_first_of(":");
			unsigned id = std::stoi(line.substr(0,endpos));
			std::vector<std::string> paths;
			pos = endpos + 2;
			while(endpos < line.size())
			{
				endpos = line.find_first_of("|",pos);
				endpos = (endpos != std::string::npos) ? endpos : line.size()+1;
				paths.push_back(line.substr(pos,endpos-pos-1));
				pos = endpos + 2;
			}
			rules.push_back(std::make_pair(id,paths));
			
			getline(input,line);
		}
		while(getline(input,line))
		{
			messages.push_back(line);
		}
  }
  input.close();
  
  for(auto& rule:rules)
  {
  	if(rule.second.size() == 1 && rule.second[0] == "\"a\"")
  	{
  		rule.second[0] = "a";
  	}
  	else if(rule.second.size() == 1 && rule.second[0] == "\"b\"")
  	{
  		rule.second[0] = "b";
  	}
  }
}

void findValidMessages(const std::vector<std::pair<unsigned,std::vector<std::string>>> &rules, const std::string &line, std::unordered_map<std::string,unsigned> &validMessages, size_t pos, std::unordered_map<std::string,unsigned> &cache)
{
	size_t endpos = line.find_first_of(" ",pos);
	endpos = (endpos != std::string::npos) ? endpos : line.size();
	unsigned rule = std::stoi(line.substr(pos,endpos-pos));
	
	for(auto& path:rules[rule].second)
	{
		auto newLine = line.substr(0,pos) + path;
		if(endpos != line.size())
		{
			newLine += line.substr(endpos);
		}
		if(cache.count(newLine) == 0)
		{
			cache[newLine] = 1;
			size_t newPos = pos;
			if(newLine[pos] == 'a' || newLine[pos] == 'b')
			{
				newPos += 2;
				if(newPos > newLine.size())
				{
					unsigned index = 0;
					while(index < newLine.size())
					{
						if(newLine[index] == ' ')
						{
							newLine.erase(newLine.begin() + index);
						}
						else
						{
							index++;
						}
					}

					validMessages[newLine] = 1;
				}
			}
			if(newPos < newLine.size())
			{
				findValidMessages(rules, newLine, validMessages, newPos, cache);
			}
		}
	}
}

uint64_t validateMessages(const std::vector<std::pair<unsigned,std::vector<std::string>>> &rules, const std::vector<std::string> &messages)
{
	uint64_t result = 0;
	
	std::unordered_map<std::string,unsigned> cache;
	std::unordered_map<std::string,unsigned> validFirst;
	std::string line = "42";
	
	findValidMessages(rules, line, validFirst, 0, cache);
	
	for(auto& message:messages)
	{
		if(message.size() == 24 && validFirst.count(message.substr(0,8)) == 1 && validFirst.count(message.substr(8,8)) == 1 && validFirst.count(message.substr(16)) == 0)
		{
			result++;
		}
	}	
	
	return result;
}

uint64_t newRules(const std::vector<std::pair<unsigned,std::vector<std::string>>> &rules, const std::vector<std::string> &messages)
{
	uint64_t result = 0;
	
	std::unordered_map<std::string,unsigned> cache;
	std::unordered_map<std::string,unsigned> validFirst;
	std::string line = "42";
	
	findValidMessages(rules, line, validFirst, 0, cache);

	for(auto& message:messages)
	{
		if(message.size()%8 == 0)
		{
			unsigned first = 0;
			unsigned second = 0;
			bool valid = true;
			bool secondPart = false;
			unsigned index = 0;
			
			while(index < message.size())
			{
				if(validFirst.count(message.substr(index,8)) == 1)
				{
					if(!secondPart)
					{
						first++;
					}
					else
					{
						valid = false;
						break;
					}
				}
				else
				{
					if(!secondPart)
					{
						secondPart = true;
					}
					second++;
				}
				index += 8;
			}
			if(valid && first > second && second > 0)
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
	
	std::vector<std::pair<unsigned,std::vector<std::string>>> rules;
	std::vector<std::string> messages;
   
  parseInput(rules, messages);


	std::sort(rules.begin(),rules.end(),orderRules());
	
 	resultA = validateMessages(rules,messages);
	resultB = newRules(rules,messages);
 	
  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
 	
  return 0;
}
