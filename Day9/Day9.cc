#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

void parseInput(std::vector<uint64_t> &numbers)
{
	std::string line;
	
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
		while(getline(input,line))
		{
			numbers.push_back(std::stoll(line));
		}
  }
  input.close();
}

std::pair<uint64_t,uint64_t> findWrongNumber(const std::vector<uint64_t> &numbers)
{
	std::pair<uint64_t,uint64_t> result;
	
	for(unsigned number=25;number<numbers.size();number++)
	{
		bool followsRule = false;
		
		for(unsigned i=number-25;i<number-1;i++)
		{
			for(unsigned j=i+1;j<number;j++)
			{
				if(numbers[i]+numbers[j] == numbers[number])
				{
					followsRule = true;
					break;
				}
			}
			if(followsRule)
			{
				break;
			}
		}
		if(!followsRule)
		{
			result.first = numbers[number];
			break;
		}
	}
	
	unsigned min = 0;
	unsigned max = 1;
	uint64_t sum = numbers[0]+numbers[1];
	while(max < numbers.size()-1)
	{
		if(sum > result.first)
		{
			sum -= numbers[min];
			min++;
		}
		else if(sum < result.first)
		{
			sum += numbers[max+1];
			max++;
		}
		else
		{
			result.second = (*(std::min_element(numbers.begin()+min,numbers.begin()+max+1))) + (*(std::max_element(numbers.begin()+min,numbers.begin()+max+1)));
			break;
		}
	}
	
	return result;
}

int main()
{
	std::pair<uint64_t,uint64_t> result;
	
	std::vector<uint64_t> numbers;
   
  parseInput(numbers);

 	result = findWrongNumber(numbers);
	
  std::cout << "resultA: " << result.first << '\n';
  std::cout << "resultB: " << result.second << std::endl;
 	
  return 0;
}
