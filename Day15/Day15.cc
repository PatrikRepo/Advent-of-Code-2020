#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <unordered_map>

void parseInput(std::vector<unsigned> &numbers)
{
	std::string line;
	
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
		getline(input,line);
		size_t pos = 0;
		size_t endpos = line.find_first_of(",");
		
		while(endpos != std::string::npos)
		{
			numbers.push_back(std::stoi(line.substr(pos,endpos-pos)));
			pos = endpos+1;
			endpos = line.find_first_of(",",pos);
		}
		numbers.push_back(std::stoi(line.substr(pos)));
  }
  input.close();
}

uint64_t playGame(const std::vector<unsigned> &numbers)
{
	uint64_t result = 0;
	
	std::unordered_map<unsigned,unsigned> cache;
	unsigned number = numbers[0];
	unsigned counter = 1;
	
	for(unsigned i=1; i<numbers.size(); i++)
	{
		cache[number] = counter;
		number = numbers[i];
		counter++;
	}
	
	while(counter < 2020)
	{
		if(cache.count(number) == 0)
		{
			cache[number] = counter;
			number = 0;
		}
		else
		{
			unsigned turn = cache[number];
			cache[number] = counter;
			number = counter - turn;
		}
		counter++;
	}
	
	result = number;
	
	return result;
}

//If this didn't execute in 6s I would improve it. My initial guess is that I can find and cache a loop and then just find the number I'm looking for.
//But 6 seconds... I don't really care about 6 seconds.
uint64_t longGame(const std::vector<unsigned> &numbers)
{
	uint64_t result = 0;
	
	std::unordered_map<unsigned,unsigned> cache;
	unsigned number = numbers[0];
	unsigned counter = 1;
	
	for(unsigned i=1; i<numbers.size(); i++)
	{
		cache[number] = counter;
		number = numbers[i];
		counter++;
	}
	
	while(counter < 30000000)
	{
		if(cache.count(number) == 0)
		{
			cache[number] = counter;
			number = 0;
		}
		else
		{
			unsigned turn = cache[number];
			cache[number] = counter;
			number = counter - turn;
		}
		counter++;
	}
	
	result = number;
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	
	std::vector<unsigned> numbers;
   
  parseInput(numbers);

 	resultA = playGame(numbers);
	resultB = longGame(numbers);
 	
  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
 	
  return 0;
}
