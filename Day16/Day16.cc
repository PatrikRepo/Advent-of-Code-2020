#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <unordered_map>

//The fields and ranges of values from the input rules are stored in an array where every fourth value starts a new field, and all groups of four determine the two intervals of accepted values according to start - end, start - end
//The first six fields are the departure fields required for the answer
//Strategy is to use a hash map to map value on ticket to field
void parseInput(std::array<unsigned,80> &rules, std::array<unsigned,20> &myTicket, std::vector<std::array<unsigned,20>> &tickets)
{
	std::string line;
	
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
  	getline(input,line);
  	unsigned index = 0;
		while(line != "")
		{
			size_t pos = line.find_first_of("1234567890");
			size_t endpos = line.find_first_of("-",pos);
			rules[index] = std::stoi(line.substr(pos,endpos-pos));
			index++;
			
			pos = endpos+1;
			endpos = line.find_first_of(" ",pos);
			rules[index] = std::stoi(line.substr(pos,endpos-pos));
			index++;
			
			pos = line.find_first_of("1234567890", endpos);
			endpos = line.find_first_of("-",pos);
			rules[index] = std::stoi(line.substr(pos,endpos-pos));
			index++;
			
			pos = endpos+1;
			rules[index] = std::stoi(line.substr(pos));
			index++;
			getline(input,line);
		}

	 	getline(input,line);
  	getline(input,line);
  	
		size_t pos = 0;
		size_t endpos = line.find_first_of(",");
		unsigned counter = 0;
		while(endpos != std::string::npos)
		{
			myTicket[counter] = std::stoi(line.substr(pos,endpos-pos));
			counter++;
			pos = endpos+1;
			endpos = line.find_first_of(",",pos);
		}
		myTicket[counter] = std::stoi(line.substr(pos));
		
		getline(input,line);
		getline(input,line);
		
		while(getline(input,line))
		{
			counter = 0;
			std::array<unsigned, 20> ticket;
			pos = 0;
			endpos = line.find_first_of(",");
			
			while(endpos != std::string::npos)
			{
				ticket[counter] = std::stoi(line.substr(pos,endpos-pos));
				counter++;
				pos = endpos+1;
				endpos = line.find_first_of(",",pos);
			}
			ticket[counter] = std::stoi(line.substr(pos));
			tickets.push_back(ticket);
		}
  }
  
  input.close();
}

uint64_t findInvalidTickets(const std::array<unsigned,80> &rules, std::vector<std::array<unsigned,20>> &tickets)
{
	uint64_t result = 0;
	
	unsigned ticketIndex = 0;
	std::vector<unsigned> invalidTickets;
	
	for(auto &ticket:tickets)
	{
		for(auto value:ticket)
		{
			bool valid = false;
			for(unsigned i=0; i<rules.size(); i+=4)
			{
				if((value >= rules[i] && value <= rules[i+1]) || (value >= rules[i+2] && value <= rules[i+3]))
				{
					valid = true;
					break;
				}
			}
			if(!valid)
			{
				result += value;
				if(invalidTickets.empty() || invalidTickets.back() != ticketIndex)
				{
					invalidTickets.push_back(ticketIndex);
				}
			}
		}
		ticketIndex++;
	}
	
	for(int i=invalidTickets.size()-1; i>=0; i--)
	{
		tickets.erase(tickets.begin()+invalidTickets[i]);
	}
	
	return result;
}

uint64_t identifyFields(const std::array<unsigned,80> &rules, const std::array<unsigned,20> &myTicket, const std::vector<std::array<unsigned,20>> &tickets)
{
	uint64_t result = 0;
	
	std::array<std::array<unsigned,20>,20> matrix{0};
	
	for(auto &ticket:tickets)
	{
		for(unsigned i=0; i<ticket.size(); i++)
		{
			for(unsigned j=0; j<rules.size(); j+=4)
			{
				if((ticket[i] >= rules[j] && ticket[i] <= rules[j+1]) || (ticket[i] >= rules[j+2] && ticket[i] <= rules[j+3]))
				{
					matrix[i][j/4] += 1;
				}
			}
		}	
	}
	
	
	for(unsigned i=0; i<matrix[0].size(); i++)
	{
		unsigned max = 0;
		for(unsigned j=0; j<matrix.size(); j++)
		{
			if(matrix[j][i] > max)
			{
				max = matrix[j][i];
			}
		}
		for(unsigned j=0; j<matrix.size(); j++)
		{
			if(matrix[j][i] == max)
			{
				matrix[j][i] = 1;
			}
			else
			{
				matrix[j][i] = 0;
			}
		}
	}

	std::unordered_map<unsigned,unsigned> map;
	std::vector<unsigned> fieldsLeft;
	for(unsigned i=0; i<matrix[0].size(); i++)
	{
		fieldsLeft.push_back(i);
	}
	while(!fieldsLeft.empty())
	{
		std::vector<unsigned> fieldsToRemove;
		
		for(unsigned i=0; i<fieldsLeft.size(); i++)
		{
			unsigned count = 0;
			unsigned index = 0;
			for(unsigned j=0; j<matrix.size(); j++)
			{
				if(matrix[j][fieldsLeft[i]] != 0)
				{
					count++;
					if(count > 1)
					{
						break;
					}
					index = j;
				}
			}
			if(count == 1)
			{
				for(unsigned k=0; k<matrix[0].size(); k++)
				{
					if(k != fieldsLeft[i])
					{
						matrix[index][k] = 0;
					}
				}
				map[fieldsLeft[i]] = index;
				fieldsToRemove.push_back(fieldsLeft[i]);
			}
		}
		
		for(int i=fieldsToRemove.size()-1; i>=0; i--)
		{
			for(int j=fieldsLeft.size()-1; j>=0; j--)
			{
				if(fieldsLeft[j] == fieldsToRemove[i])
				{
					fieldsLeft.erase(fieldsLeft.begin()+j);
					fieldsToRemove.erase(fieldsToRemove.begin()+i);
				}
			}
		}
	}
	
	result = myTicket[map[0]]*myTicket[map[1]];
	result *= myTicket[map[2]];
	result *= myTicket[map[3]];
	result *= myTicket[map[4]];
	result *= myTicket[map[5]];
	
	return result;
}


int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	
	std::array<unsigned,80> rules;
	std::array<unsigned,20> myTicket;
	std::vector<std::array<unsigned,20>> tickets;
   
  parseInput(rules, myTicket, tickets);

 	resultA = findInvalidTickets(rules, tickets);
	resultB = identifyFields(rules, myTicket, tickets);
 	
  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
 	
  return 0;
}
