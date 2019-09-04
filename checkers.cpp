#include "checkers.h"

#include <iostream>
#include <string>
#include <assert.h>

void printLine(int ind, const Board & b)
{
	std::cout << "\u2503";

	if(!(ind % 2)) 
	{
		std::cout << "   ";
		std::cout << "\u2503";
	}

	for(int i = 0; i < 4; ++i)
	{
		switch(b.get(ind*4+i))
		{
			case Empty:
				std::cout << "   ";
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
	if((ind % 2)) 
	{
		std::cout << "   ";
		std::cout << "\u2503";
	}
	
	std::cout << std::endl;
}

void printBoard(const Board & b)
{
	std::cout << std::endl;

	std::cout << "  \u250F";
	for(int i = 0; i < 15; ++i)
	{
		std::cout << (!(i%2) ? "\u2501\u2501\u2501" : "\u2533");
	}
	std::cout << "\u2513";
	std::cout << std::endl;

	for(int i = 8; i > 0; --i)
	{
		std::cout << (char)('h'- i + 1) << " ";
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
int main()
{
	std::string in;
	
	Board b;
	
	printBoard(b);

	std::cout << "Your turn: ";

	while( getline(std::cin, in) ) {
		std::cout << "you enter:" << in << std::endl;
	}
	return 0;
}
