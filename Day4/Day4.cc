#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

struct Passport
{
	unsigned byr = 0;
	unsigned iyr = 0;
	unsigned eyr = 0;
	unsigned hgt = 0;
	unsigned unit = 0;
	std::string hcl;
	std::string ecl;
	std::string pid;
	std::string cid;
};

void parseInput(std::vector<Passport> &passports)
{
	std::string line;
	
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
  	Passport passport;
  	while(getline(input, line))
  	{
  		size_t pos = 0;
  		size_t endpos = 0;
  		if(line == "")
  		{
  			passports.push_back(passport);
  			passport = Passport();
  		}
  		else
  		{
  			pos = line.find_first_of(":");
  			while(pos != std::string::npos)
  			{
  				endpos = line.find_first_of(" ",pos);
  				if(endpos == std::string::npos)
  				{	
  					endpos = line.size();
  				}
  				std::string field = line.substr(pos-3,3);
  				if(field == "byr")
  				{
  					passport.byr = std::stoi(line.substr(pos+1,endpos-1));
  				}
  				else if(field == "iyr")
  				{
  					passport.iyr = std::stoi(line.substr(pos+1,endpos-1));
  				}
   				else if(field == "eyr")
  				{
  					passport.eyr = std::stoi(line.substr(pos+1,endpos-1));
  				}
  				else if(field == "hgt")
  				{
  					size_t unitPos = line.find_first_not_of("1234567890",pos+1);
  					if(!(unitPos == endpos || unitPos == std::string::npos))
  					{
  						if(line.substr(unitPos, endpos-unitPos) == "cm")
  						{
  							passport.unit = 'c';
  						}
  						else if(line.substr(unitPos, endpos-unitPos) == "in")
  						{
  							passport.unit = 'i';
  						}
  					}
  					else
  					{
  						unitPos = endpos;
  					}
  					passport.hgt = std::stoi(line.substr(pos+1,unitPos-pos-1));
  				}
  				else if(field == "hcl")
  				{
  					passport.hcl = line.substr(pos+1,endpos-pos-1);
  				}
  				else if(field == "ecl")
  				{
  					passport.ecl = line.substr(pos+1,endpos-pos-1);
  				}
  				else if(field == "pid")
  				{
  					passport.pid = line.substr(pos+1,endpos-pos-1);
  				}
  				else if(field == "cid")
  				{
  					passport.cid = line.substr(pos+1,endpos-pos-1);
  				}
  				pos = line.find_first_of(":", endpos-1);
  			}
  		} 		
  	}
  	passports.push_back(passport);
  }
  input.close();
}

uint64_t validatePassports(const std::vector<Passport> &passports)
{
	uint64_t result = 0;
	
	for(auto& passport:passports)
	{
		bool valid = true;
		if(passport.byr == 0 || passport.iyr == 0 || passport.eyr == 0 || passport.hgt == 0 || passport.hcl == "" || passport.ecl == "" || passport.pid == "")
		{
			valid = false;
		}
		if(valid)
		{
			result++;
		}
	}
	
	return result;
}	

bool validateHcl(const std::string &hcl)
{
	bool result = true;
	
	if(hcl[0] != '#' && hcl.size() != 7)
	{
		result = false;
	}
	for(unsigned i=1; i<hcl.size(); i++)
	{
		if(!((hcl[i] >= '0' && hcl[i] <=  '9') || (hcl[i] >= 'a' && hcl[i] <= 'f')))
		{
			result = false;
		}
	}
	
	return result;
}

bool validateEcl(const std::string &ecl)
{
	bool result = false;
	
	if(ecl == "amb" || ecl == "blu" || ecl == "brn" || ecl == "gry" || ecl == "grn" || ecl == "hzl" || ecl == "oth")
	{
		result = true;
	}
	
	return result;
}

bool validatePid(const std::string &pid)
{
	bool result = true;
	
	if(pid.size() != 9)
	{
		result = false;
	}
	for(unsigned i=0; i<pid.size(); i++)
	{
		if(!(pid[i] >= '0' && pid[i] <=  '9'))
		{
			result = false;
		}
	}
	
	return result;
}

uint64_t realValidation(const std::vector<Passport> &passports)
{
	uint64_t result = 0;
	
	for(auto& passport:passports)
	{
		bool valid = true;
		if(passport.byr < 1920 || passport.byr > 2002)
		{
			valid = false;
		}
		if(passport.iyr < 2010 || passport.iyr > 2020)
		{
			valid = false;
		}
		if(passport.eyr < 2020 || passport.eyr > 2030)
		{
			valid = false;
		}
		if(!((passport.unit == 'i' && passport.hgt >= 59 && passport.hgt <= 76)  || (passport.unit == 'c' && passport.hgt >= 150 && passport.hgt <= 193)))
		{
			valid = false;
		}
		if(!validateHcl(passport.hcl))
		{
			valid = false;
		}
		if(!validateEcl(passport.ecl))
		{
			valid = false;
		}
		if(!validatePid(passport.pid))
		{
			valid = false;
		}
		if(valid)
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
	
	std::vector<Passport> passports;
   
  parseInput(passports);

 	resultA = validatePassports(passports);
	resultB = realValidation(passports);
	
  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
 	
  return 0;
}
