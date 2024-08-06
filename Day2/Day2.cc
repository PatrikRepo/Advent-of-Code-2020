#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

struct Password
{
	char letter = 0;
	unsigned min = 0;
	unsigned max = 0;
	std::string password;
};

void parseInput(std::vector<Password> &passwords)
{
	std::string line;
	
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
  	while(getline(input, line))
  	{
  		Password password;
  		size_t pos = 0;
  		size_t endpos = 0;
  		endpos = line.find_first_of("-");
  		password.min = std::stoi(line.substr(0,endpos));
  		
  		pos = endpos+1;
  		endpos = line.find_first_of(" ",pos);
  		password.max = std::stoi(line.substr(pos,endpos));
  		
  		pos = endpos+1;
  		password.letter = line[pos];
  		
  		endpos = line.find_first_of(" ",pos);
  		pos = endpos+1;
  		
  		password.password = line.substr(pos);
			
			passwords.push_back(password);  		
  	}
  }
  input.close();
}

uint64_t validatePassword(const std::vector<Password> &passwords)
{
	uint64_t result = 0;
	
	for(auto& password:passwords)
	{
		unsigned count = 0;
		for(auto& element:password.password)
		{
			if(element == password.letter)
			{
				count++;
			}
		}
		if(count >= password.min && count <= password.max)
		{
			result++;
		}
	}
	
	return result;
}	

uint64_t realValidation(const std::vector<Password> &passwords)
{
	uint64_t result = 0;
	
	for(auto& password:passwords)
	{
		unsigned count = 0;
		if(password.password[password.min-1] == password.letter)
		{
			count++;
		}
		if(password.password[password.max-1] == password.letter)
		{
			count++;
		}
		if(count == 1)
		{
			result++;
		}
	}
	
	return result;
}	

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	
	std::vector<Password> passwords;
   
  parseInput(passwords);
	
 	resultA = validatePassword(passwords);
	resultB = realValidation(passwords);
	
  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
 	
  return 0;
}
