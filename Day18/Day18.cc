#include <iostream>
#include <fstream>
#include <vector>
#include <array>

void parseInput(std::vector<std::string> &equations)
{
	std::string line;
	
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
		while(getline(input,line))
		{
			equations.push_back(line);
		}
  }
  input.close();
}

uint64_t calculateEquation(const std::string &equation)
{
	uint64_t result = 0;
	
	size_t pos = 0;
	size_t endpos = 0;
	char operation = 0;
	
	while(pos < equation.size())
	{
		if(equation[pos] == '+' || equation[pos] == '*')
		{
			operation = equation[pos];
		}
		else if(equation[pos] == '(')
		{
			unsigned depth = 1;
			
			endpos = pos;
			while(depth > 0)
			{
				endpos = equation.find_first_of("()",endpos+1);
				if(equation[endpos] == '(')
				{
					depth++;
				}
				else
				{
					depth--;
				}
			}
			
			uint64_t partResult = calculateEquation(equation.substr(pos+1,endpos-pos-1));
			if(operation == '+')
			{
				result += partResult;
			}
			else if(operation == '*')
			{
				result *= partResult;
			}
			else
			{
				result = partResult;
			}
			pos = endpos;
		}
		else
		{
			if(operation == '+')
			{
				result += equation[pos] - '0';
			}
			else if(operation == '*')
			{
				result *= equation[pos] - '0';
			}
			else
			{
				result = equation[pos] - '0';
			}
		}
		pos += 2;
	}

	return result;
}

uint64_t advancedCalculation(const std::string &equation)
{
	uint64_t result = 0;
	
	size_t pos = 0;
	size_t endpos = 0;
	
	while(pos < equation.size())
	{
		if(equation[pos] == '+')
		{
			;
		}
		else if(equation[pos] == '*')
		{
			int depth = 0;
			endpos = pos+1;
			
			while(endpos != std::string::npos && (equation[endpos] != '*' || depth > 0))
			{
				endpos = equation.find_first_of("()*",endpos+1);
				if(equation[endpos] == '(')
				{
					depth++;
				}
				else if(equation[endpos] == ')')
				{
					depth--;
				}
			}
			pos += 2;
			if(endpos != std::string::npos)
			{
				//-1 because of I want the substr to be exclusive the ' ' and not the '*' that comes after
				result *= advancedCalculation(equation.substr(pos, endpos-pos-1));
				pos = endpos-2;
			}
			else
			{
				result *= advancedCalculation(equation.substr(pos));
				pos = equation.size();
			}
		}
		else if(equation[pos] == '(')
		{
			unsigned depth = 1;
			
			endpos = pos;
			while(depth > 0)
			{
				endpos = equation.find_first_of("()",endpos+1);
				if(equation[endpos] == '(')
				{
					depth++;
				}
				else
				{
					depth--;
				}
			}
			
			uint64_t partResult = advancedCalculation(equation.substr(pos+1,endpos-pos-1));
			if(result > 0)
			{
				result += partResult;
			}
			else
			{
				result = partResult;
			}
			pos = endpos;
		}
		else
		{
			if(result > 0)
			{
				result += equation[pos] - '0';
			}

			else
			{
				result = equation[pos] - '0';
			}
		}
		pos += 2;
	}
	
	return result;
}

uint64_t calculate(const std::vector<std::string> &equations)
{
	uint64_t result = 0;
	
	for(auto& equation:equations)
	{
		result += calculateEquation(equation);
	}
	
	return result;
}

uint64_t advancedMath(const std::vector<std::string> &equations)
{
	uint64_t result = 0;
	
	for(auto& equation:equations)
	{
		result += advancedCalculation(equation);
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	
	std::vector<std::string> equations;
   
  parseInput(equations);

 	resultA = calculate(equations);
	resultB = advancedMath(equations);
 	
  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
 	
  return 0;
}
