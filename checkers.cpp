#include <iostream>
#include <string>
#include <assert.h>


enum Field{
	Empty,
	White,
	Black,
};

class Step {
public:
	Step(){};
	Step(int f, int t)
		: from(f)
		, to(t)
	{}
public:
	bool isValid() const
	{
		return (from != -1) && (to != -1) && (from!= to);
	}
	int from = -1;
	int to = -1;
};

class Move {
public:
	Move(Step step) {
		steps_[0] = step;
	}
	bool addStep(Step step)
	{
		if(stepCount_ == maxSteps_)
		{
			return false;
		}
		steps_[stepCount_] = step;
		stepCount_++;
		return true;
	}
	const Step getStep(int ind) const
	{
		if(ind >= maxSteps_)
		{
			return Step();
		}
		return steps_[ind];
	}
private:
	static constexpr int maxSteps_ = 6;
	int stepCount_ = 0;
	Step steps_[maxSteps_];
};

// all checkers set on black
// 1A is black
class Board {

public:	

	Board()
	{
		reset();
	}

	void reset() {
		for(int i = 0; i < 12; ++i)
		{
			fields[i] = White;
  		fields[size_-i-1] = Black;
		}
		for(int i = 12; i < 20; ++i)
		{
			fields[i] = Empty;
		}
	}

	int size() const { return size_; }
	
	Field get(int i) const { return fields[i]; }

	void doMove(const Move & move)
	{
		int ind = 0;
		while(move.getStep(ind).isValid())
		{
			Step step = move.getStep(ind);
			fields[step.to] = fields[step.from];
			fields[step.from] = Empty;
			ind++;
		}
	}
	void remove(int i)
	{
	
	}

private:
	static constexpr int size_ = 32;
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

class CheckersAI {

public:	
	bool checkMove(const Board & b, const Move & m) 
	{
		return true;
	}

	void applyMove(const Board & b, const Move & m)
	{
	}

	Move findMyMove(const Board & b)
	{
		return Move(Step(1,2));
	}

};

class Game {
public:
	void reset() 
	{}

	bool applyTheirMove()
	{
		return true;
	}

	bool doMyMove()
	{
		return true;
	}

private:
	bool myMove_ = false;
	Board b;
};

int main()
{
/*
  ======= Test zone =======
*/
	{
		Board b;
		assert((b.get(0) == White) && "Board init error: first isn't white");
		assert((b.get(1) == White) && "Board init error: isn't white");
		assert((b.get(2) == White) && "Board init error: isn't white");
		assert((b.get(3) == White) && "Board init error: isn't white");
		assert((b.get(4) == White) && "Board init error: isn't white");
		assert((b.get(5) == White) && "Board init error: isn't white");
		assert((b.get(6) == White) && "Board init error: isn't white");
		assert((b.get(7) == White) && "Board init error: isn't white");
		assert((b.get(8) == White) && "Board init error: isn't white");
		assert((b.get(9) == White) && "Board init error: isn't white");
		assert((b.get(10) == White) && "Board init error: isn't white");
		assert((b.get(11) == White) && "Board init error: isn't white");
		
		assert((b.get(12) == Empty) && "Board init error: empty");
		assert((b.get(13) == Empty) && "Board init error: empty");
		assert((b.get(14) == Empty) && "Board init error: empty");
		assert((b.get(15) == Empty) && "Board init error: empty");
		assert((b.get(16) == Empty) && "Board init error: empty");
		assert((b.get(17) == Empty) && "Board init error: empty");
		assert((b.get(18) == Empty) && "Board init error: empty");
		assert((b.get(19) == Empty) && "Board init error: empty");

		assert((b.get(20) == Black) && "Board init error: isn't black");
		assert((b.get(21) == Black) && "Board init error: isn't black");
		assert((b.get(22) == Black) && "Board init error: isn't black");
		assert((b.get(23) == Black) && "Board init error: isn't black");
		assert((b.get(24) == Black) && "Board init error: isn't black");
		assert((b.get(25) == Black) && "Board init error: isn't black");
		assert((b.get(26) == Black) && "Board init error: isn't black");
		assert((b.get(27) == Black) && "Board init error: isn't black");
		assert((b.get(28) == Black) && "Board init error: isn't black");
		assert((b.get(29) == Black) && "Board init error: isn't black");
		assert((b.get(30) == Black) && "Board init error: isn't black");
		assert((b.get(31) == Black) && "Board init error: isn't black");
	}
	{
		Board b;
		Step step(8,12);
		Move move(step);
		b.doMove(move);
		assert(b.get(8) == Empty && b.get(12) == White && "Check board move white");

		b.reset();
		
		printBoard(b);
		Move move1(Step(8,12));
		Step step2(12,16);
		move1.addStep(step2);
		b.doMove(move1);
		printBoard(b);
		
		assert(b.get(8) == Empty);
		assert(b.get(12) == Empty);
		assert(b.get(16) == White);
	}
	return 0;
/*
	====== Game zone =======
*/
	std::string in;
	
	Board b;
	
	printBoard(b);

	std::cout << "Your turn: ";

	while( getline(std::cin, in) ) {
		std::cout << "you enter:" << in << std::endl;
	}
	return 0;
}
