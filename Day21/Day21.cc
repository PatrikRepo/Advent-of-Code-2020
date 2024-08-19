#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <algorithm>

struct SortAllergens
{
	bool operator() (std::pair<std::string,std::string> pair1, std::pair<std::string,std::string> pair2) { return pair1.second < pair2.second; }
};

void parseInput(std::vector<std::pair<std::vector<std::string>,std::vector<std::string>>> &foodList, std::unordered_map<std::string,unsigned> &ingredientMap, std::unordered_map<std::string,unsigned> &allergenMap)
{
	std::string line;
	
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
  	unsigned ingredientIndex = 0;
  	unsigned allergenIndex = 0;
  	
		while(getline(input,line))
		{
			std::vector<std::string> ingredientList;
			std::vector<std::string> allergenList;
			size_t pos = 0;
			size_t endpos = 0;
			
			while(line[pos] != '(')
			{
				endpos = line.find_first_of(" ",pos);
				std::string ingredient = line.substr(pos,endpos-pos);
				if(ingredientMap.count(ingredient) == 0)
				{
					ingredientMap[ingredient] = ingredientIndex;
					ingredientIndex++;
				}
				
				ingredientList.push_back(ingredient);
				pos = endpos+1;
			}
			
			pos = line.find_first_of(" ",pos)+1;
			
			while(line[endpos] != ')')
			{
				endpos = line.find_first_of(",)",pos);
				
				std::string allergen = line.substr(pos,endpos-pos);
				if(allergenMap.count(allergen) == 0)
				{
					allergenMap[allergen] = allergenIndex;
					allergenIndex++;
				}
				
				allergenList.push_back(allergen);
				
				pos = endpos+2;
			}
			
			foodList.push_back(std::make_pair(ingredientList,allergenList));
		}
  }
  input.close();

}

std::pair<uint64_t,std::string> findSafeFood(const std::vector<std::pair<std::vector<std::string>,std::vector<std::string>>> &foodList, 
	std::unordered_map<std::string,unsigned> &ingredientMap, std::unordered_map<std::string,unsigned> &allergenMap)
{
	std::pair<uint64_t,std::string> result;
	result.first = 0;
	
	std::vector<std::vector<unsigned>> matrix;
	std::vector<unsigned> allergens;
	for(unsigned i=0; i<allergenMap.size(); i++)
	{
		allergens.push_back(0);
	}

	for(unsigned i=0; i<ingredientMap.size(); i++)
	{
		matrix.push_back(allergens);
	}
	
	for(auto& food:foodList)
	{
		for(unsigned i=0; i<food.second.size(); i++)
		{
			for(unsigned j=0; j<food.first.size(); j++)
			{
				matrix[ingredientMap[food.first[j]]][allergenMap[food.second[i]]] += 1;
			}
		}
	}
	
	for(unsigned i=0; i<matrix[0].size(); i++)
	{
		unsigned max = 0;
		for(unsigned j=0; j<matrix.size(); j++)
		{
			if(max < matrix[j][i])
			{
				max = matrix[j][i];
			}
		}
		for(unsigned j=0; j<matrix.size(); j++)
		{
			if(matrix[j][i] < max)
			{
				matrix[j][i] = 0;
			}
		}
	}
	
	std::vector<unsigned> safeIngredientsIndex;
	for(unsigned i=0; i<matrix.size(); i++)
	{
		bool safe = true;
		for(unsigned j=0; j<matrix[0].size(); j++)
		{
			if(matrix[i][j] > 0)
			{
				safe = false;
				break;
			}
		}
		if(safe)
		{
			safeIngredientsIndex.push_back(i);
		}
	}
	
	std::vector<std::string> safeIngredients;
	for(auto ingredientIndex:safeIngredientsIndex)
	{
		for(auto it=ingredientMap.begin(); it!=ingredientMap.end(); it++)
		{
			if(it->second == ingredientIndex)
			{
				safeIngredients.push_back(it->first);
			}
		}	
	}
	
	for(auto& safeIngredient:safeIngredients)
	{
		for(auto& food:foodList)
		{
			for(auto& ingredient:food.first)
			{
				if(safeIngredient == ingredient)
				{
					result.first++;
				}
			}
		}
	}
	
	for(auto ingredientIndex:safeIngredientsIndex)
	{
		for(auto it=ingredientMap.begin(); it!=ingredientMap.end(); it++)
		{
			if(it->second == ingredientIndex)
			{
				safeIngredients.push_back(it->first);
			}
		}	
	}
	
	unsigned count = 0;
	
	std::vector<std::pair<unsigned,unsigned>> unsafeIngredientsIndices;
	
	while(count<allergenMap.size())
	{
		for(unsigned i=0; i<matrix[0].size(); i++)
		{
			unsigned index = 0;
			bool found = false;
			
			for(unsigned j=0; j<matrix.size(); j++)
			{
				if(matrix[j][i] > 0)
				{
					if(!found)
					{
						found = true;
						index = j;
					}
					else
					{
						found = false;
						break;
					}
				}
			}
			if(found)
			{
				count++;
				for(unsigned j=0;j<matrix[0].size(); j++)
				{
					matrix[index][j] = 0;
				}
				unsafeIngredientsIndices.push_back(std::make_pair(index,i));
			}
		}
	}	
	
	std::vector<std::pair<std::string,std::string>> unsafeIngredients;
	
	for(auto& unsafeIngredient:unsafeIngredientsIndices)
	{
		std::string ingredient;
		std::string allergen;
		
		for(auto it=ingredientMap.begin(); it!=ingredientMap.end(); it++)
		{
			if(it->second == unsafeIngredient.first)
			{
				ingredient = it->first;
				break;
			}
		}	
		for(auto it=allergenMap.begin(); it!=allergenMap.end(); it++)
		{
			if(it->second == unsafeIngredient.second)
			{
				allergen = it->first;
				break;
			}
		}	
		unsafeIngredients.push_back(std::make_pair(ingredient,allergen));
	}

	std::sort(unsafeIngredients.begin(), unsafeIngredients.end(), SortAllergens());
	result.second = unsafeIngredients[0].first;
	
	for(unsigned i=1; i<unsafeIngredients.size(); i++)
	{
		result.second += "," + unsafeIngredients[i].first;
	}
	
	return result;
}

int main()
{
	std::pair<uint64_t,std::string> result;
	
	std::vector<std::pair<std::vector<std::string>,std::vector<std::string>>> foodList;
	std::unordered_map<std::string,unsigned> ingredientMap;
	std::unordered_map<std::string,unsigned> allergenMap;
  
  parseInput(foodList, ingredientMap, allergenMap);

 	result = findSafeFood(foodList, ingredientMap, allergenMap);

  std::cout << "resultA: " << result.first << '\n';
  std::cout << "resultB: " << result.second << std::endl;
 	
  return 0;
}
