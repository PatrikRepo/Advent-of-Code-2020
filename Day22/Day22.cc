#include <iostream>
#include <fstream>
#include <deque>
#include <unordered_map>

void parseInput(std::deque<unsigned> &player1, std::deque<unsigned> &player2)
{
	std::string line;
	
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
  	getline(input,line);
  	getline(input,line);
  	
		while(line != "")
		{
			player1.push_back(std::stoi(line));
			getline(input,line);
		}
		
  	getline(input,line);
  	getline(input,line);
  	
		while(line != "")
		{
			player2.push_back(std::stoi(line));
			getline(input,line);
		}
  }
  input.close();

}

uint64_t combat(std::deque<unsigned> player1, std::deque<unsigned> player2)
{
	uint64_t result = 0;
	
	while(!player1.empty() && !player2.empty())
	{
		unsigned p1 = player1.front();
		player1.pop_front();
		unsigned p2 = player2.front();
		player2.pop_front();
		
		if(p1 > p2)
		{
			player1.push_back(p1);
			player1.push_back(p2);
		}
		else
		{
			player2.push_back(p2);
			player2.push_back(p1);
		}
	}
	
	while(!player1.empty())
	{
		result += (player1.front()*player1.size());
		player1.pop_front();
	}
	while(!player2.empty())
	{
		result += (player2.front()*player2.size());
		player2.pop_front();
	}
	
	
	return result;
}

bool subgame(std::deque<unsigned> &player1, std::deque<unsigned> &player2)
{
	bool result = false;
	
	std::unordered_map<std::string,unsigned> cache1;
	std::unordered_map<std::string,unsigned> cache2;
	
	while(!player1.empty() && !player2.empty())
	{
		std::string key1;
		std::string key2;
		
		for(auto it=player1.begin(); it!= player1.end(); it++)
		{
			key1 += (*it);
			key1 += ",";
		}
		for(auto it=player2.begin(); it!= player2.end(); it++)
		{
			key2 += (*it);
			key2 += ",";
		}
		
		if(cache1.count(key1) == 1)
		{
			break;
		}
		else
		{
			cache1[key1] = 1;
		}
		if(cache2.count(key2) == 1)
		{
			break;
		}
		else
		{
			cache2[key1] = 1;
		}
				
		unsigned p1 = player1.front();
		player1.pop_front();
		unsigned p2 = player2.front();
		player2.pop_front();
		
		if(p1 <= player1.size() && p2 <= player2.size())
		{
			auto newPlayer1 = player1;
			auto newPlayer2 = player2;
			while(newPlayer1.size() > p1)
			{
				newPlayer1.pop_back();
			}
			while(newPlayer2.size() > p2)
			{
				newPlayer2.pop_back();
			}
			if(subgame(newPlayer1,newPlayer2))
			{
				player1.push_back(p1);
				player1.push_back(p2);
			}
			else
			{
				player2.push_back(p2);
				player2.push_back(p1);
			}
		}
		else
		{
			if(p1 > p2)
			{
				player1.push_back(p1);
				player1.push_back(p2);
			}
			else
			{
				player2.push_back(p2);
				player2.push_back(p1);
			}
		}
	}
	
	if(!player1.empty())
	{
		result = true;
	}
	
	return result;
}

uint64_t recursiveCombat(std::deque<unsigned> &player1, std::deque<unsigned> &player2)
{
	uint64_t result = 0;
	
	while(!player1.empty() && !player2.empty())
	{
		unsigned p1 = player1.front();
		player1.pop_front();
		unsigned p2 = player2.front();
		player2.pop_front();
		
		if(p1 <= player1.size() && p2 <= player2.size())
		{
			auto newPlayer1 = player1;
			auto newPlayer2 = player2;
			while(newPlayer1.size() > p1)
			{
				newPlayer1.pop_back();
			}
			while(newPlayer2.size() > p2)
			{
				newPlayer2.pop_back();
			}
			if(subgame(newPlayer1,newPlayer2))
			{
				player1.push_back(p1);
				player1.push_back(p2);
			}
			else
			{
				player2.push_back(p2);
				player2.push_back(p1);
			}
		}
		else
		{
			if(p1 > p2)
			{
				player1.push_back(p1);
				player1.push_back(p2);
			}
			else
			{
				player2.push_back(p2);
				player2.push_back(p1);
			}
		}
	}
	
	while(!player1.empty())
	{
		result += (player1.front()*player1.size());
		player1.pop_front();
	}
	while(!player2.empty())
	{
		result += (player2.front()*player2.size());
		player2.pop_front();
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	
	std::deque<unsigned> player1;
	std::deque<unsigned> player2;
  
  parseInput(player1, player2);

 	resultA = combat(player1, player2);
	resultB = recursiveCombat(player1, player2);
	
  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
 	
  return 0;
}
