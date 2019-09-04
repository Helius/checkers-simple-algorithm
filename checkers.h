#pragma once


enum Field{
	Empty,
	White,
	Black,
	WhiteKing,
	BlackKing
};

class Step {
public:
	Step(){};
	Step(int f, int t)
		: from(f)
		, to(t)
	{}
public:
	inline bool isValid() const
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
		stepCount_ = 1;
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

	Board(Field * f)
	{
		for(int i = 0; i < size_; ++i)
		{
			fields[i] = f[i];
		}
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

	static int size() { return size_; }
	
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
		if(i < size_)
		{
			fields[i] = Empty;	
		}
	}

private:
	static constexpr int size_ = 32;
	Field fields[size_] = {Empty};
};

class CheckersAI {

public:	
	bool checkMove(const Board & b, const Move & m) 
	{
		int i = 0;
		while(m.getStep(i).isValid())
		{
			Step s = m.getStep(i);
			if(findAvailableFields(b, s.from) && destReachable(s.to))
			{
				// ok
				return true;
			}
			else
			{
				return false;
				//sorry, did you do wrong move?
			}
			i++;
		}
		return false;
	}

	int findAvailableFields(const Board & b, int ind)
	{
		for(int i = 0; i < maxAvailableFields; ++i)
		{
			availableFields[i] = -1;
		}
		if(onLeftSide(ind))
		{
		}
		else if(onRightSide(ind))
		{
		}
		else
		{
			availableFields[0] = ind + 4;
			availableFields[1] = ind + 5;
			return 2;
		}
		
	}

	const int * getAvailable() const { return availableFields; }

	void applyMove(const Board & b, const Move & m)
	{
	}

	Move findMyMove(const Board & b)
	{
		return Move(Step(1,2));
	}
private:
	static constexpr int maxAvailableFields = 12;
	int availableFields[maxAvailableFields];

	bool destReachable(int ind)
	{
		for(int i = 0; i < maxAvailableFields; ++i)
		{
			if(availableFields[i] == ind) return true;
			return false;
		}
	}
	bool oddLine(int ind) {return !(ind % 2); }
	bool onLeftSide(int ind) { return !(ind % 8); }
	bool onRightSide(int ind) { return !(ind+1 % 8); }

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

