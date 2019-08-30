#include <iostream>
#include <string>


enum Field{
	Empty,
	White,
	Black,
};

// all checkers set on black
// 1A is black
class Board {

public:	

	Board(bool imWhite = false)
		: imWhite_(imWhite)
	{
		for(int i = 0; i < 12; ++i)
		{
			fields[i] = imWhite ? White : Black;
  		fields[size_-i-1] = imWhite ? Black : White;
		}
	}

	int size() const { return size_; }
	Field get(int i) const { return fields[i]; }

private:
	static constexpr int size_ = 32;
	bool imWhite_ = false;
	Field fields[size_] = {Empty};
};

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

	for(int i = 0; i < 8; ++i)
	{
		std::cout << (char)('h'-i) << " ";
		printLine(i, b);	
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
	
	Board b(false);
	
	printBoard(b);

	std::cout << "Your turn: ";

	while( getline(std::cin, in) ) {
		std::cout << "you enter:" << in << std::endl;
	}
	return 0;
}
