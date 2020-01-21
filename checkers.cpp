
#include <iostream>
#include <string>
#include <assert.h>

#include "checkers.h"


void printLine(int ind, const Board & b)
{
	std::cout << "\u2503";

	if((ind % 2)) 
	{
		std::cout << "   ";
		std::cout << "\u2503";
	}

	for(int i = 0; i < 4; ++i)
	{
		switch(b.whoIsThere(ind*8 + i*2 + ind%2))
		{
			case Empty:
				std::cout << "   ";
				std::cout << "\u2503";
				break;
			case WhiteKing:
				std::cout << " @ ";
				std::cout << "\u2503";
				break;
			case BlackKing:
				std::cout << " H ";
				std::cout << "\u2503";
				break;
			case White:
				std::cout << " O ";
				std::cout << "\u2503";
				break;
			case Black:
				std::cout << " # ";
				std::cout << "\u2503";
				break;
		}
		
		if(i < 3) {
			std::cout << "   ";
			std::cout << "\u2503";
		}
	}
	if(!(ind % 2)) 
	{
		std::cout << "   ";
		std::cout << "\u2503";
	}
	
	std::cout << std::endl;
}

void printBoard(const Board & b)
{
	std::cout << std::endl << "\033[90m";

	std::cout << "  \u250F";
	for(int i = 0; i < 15; ++i)
	{
		std::cout << (!(i%2) ? "\u2501\u2501\u2501" : "\u2533");
	}
	std::cout << "\u2513";
	std::cout << std::endl;

	for(int i = 8; i > 0; --i)
	{
		std::cout << (char)('a'+ i - 1) << " ";
		printLine(i-1, b);	
		std::cout << "  ";
		std::cout << "\u2523";
		if(i < 7) {
			for(int i = 0; i < 15; ++i)
			{
				std::cout << (!(i%2) ? "\u2501\u2501\u2501" : "\u254b");
			}
			std::cout << "\u252B";
			std::cout << std::endl;
		}
		else
		{
			for(int i = 0; i < 15; ++i)
			{
				std::cout << (!(i%2) ? "\u2501\u2501\u2501" : "\u253B");
			}
			std::cout << "\u252B";
			std::cout << std::endl;

		}
	}
	std::cout << "  ";
	for(int i = 0; i < 8; ++i)
	{
		std::cout << "  " << i+1 << " ";
	}
	std::cout << std::endl;
}

#include <vector>
#include <sstream>


int main()
{
	Game game;
	//b.initWithData(pA, pB, kA, kB);
	printBoard(game.b);

	while(1) { 
		std::cout << std::endl << "Your turn: ";
		std::string input;
		std::string tmp;
		std::vector<int> nums;
		nums.clear();
		while(std::getline(std::cin, tmp)) {
			std::stringstream ss(tmp);
			int ti;
			while(ss >> ti) 
				nums.push_back(ti);
			break;
		}
		game.b.move(nums[0], nums[1]);
		for(int i = 2; i < nums.size(); ++i) {
			game.b.take(nums[i]);
		}
		printBoard(game.b);
		Move2 m = game.getMyMove();
		game.b = game.b.clone(m);
		printBoard(game.b);
	}

	return 0;
}
