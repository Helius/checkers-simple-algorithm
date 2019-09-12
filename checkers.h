#pragma once

//TODO: for desktop only!!
#include <vector>
#include <algorithm>


enum Fld {
	Empty,
	White,
	Black,
	WhiteKing,
	BlackKing
};

class Step {
public:
	Step(){};
	Step(int t, bool tk = false)
		: to(t)
		, take(tk)
	{}
public:
	inline bool isValid() const
	{
		return (to != -1);
	}

  bool operator < (const Step & s) const
  {
		return (to < s.to);
  }

	bool operator== (const Step & s) const
	{
		return (to == s.to) && (take == s.take);
	}

public:
	int to = -1;
	int take = 0;
};


class Move {

public:
	
	Move() = default;
	Move(Step step) {
		steps_[0] = step;
		hasTakes_ = step.take;
		stepCount_ = 1;
	}

	void toString()
	{
		std::cout << "******* Move [count][takes] " << stepCount_ << "| " << hasTakes_ << ": ";
		for(int j = 0; j < stepCount_; ++j)
		{
			std::cout << steps_[j].to << ",";
		}
		std::cout << std::endl;
	}

	bool addStep(Step step)
	{
		if(stepCount_ == maxSteps_ - 1)
		{
			return false;
		}
		steps_[stepCount_] = step;
		hasTakes_ |= step.take;
		stepCount_++;
		return true;
	}

	bool addStepBack(Step step)
	{
		if(stepCount_ == maxSteps_ - 1)
		{
			return false;
		}
		for(int i = stepCount_; i > 0; --i)
		{
			steps_[i] = steps_[i-1];
		}
		steps_[0] = step;
		hasTakes_ |= step.take;
		stepCount_++;
		return true;
	}

	int size() const {
		return stepCount_;
	}
	
	const Step getStep(int ind) const
	{
		if(ind >= maxSteps_)
		{
			return Step();
		}
		return steps_[ind];
	}

	bool hasTakes() const { return hasTakes_; }

	bool operator== (const Move & m) const
	{	
		std::vector<Step> va;
		std::vector<Step> vb;

		if(m.size() != size()) return false;

		for(int i = 0; i < stepCount_; ++i) {
				va.push_back(steps_[i]);
			if(m.getStep(i).isValid()) {
				vb.push_back(m.getStep(i));
			}
		}

		std::sort(va.begin(), va.end());
		std::sort(vb.begin(), vb.end());

		if(va.size() != vb.size())
		{
			return false;
		}
		
		for(int i = 0; i < va.size(); ++i)
		{
			if(!(va[i] == vb[i]))
			{
				return false;
			}
		}
		return true;
	}

public:
	static constexpr int maxSteps_ = 5;
private:
	// max number of take
	int stepCount_ = 0;
	Step steps_[maxSteps_];
	bool hasTakes_ = false;
};


#include <cstring>

// all checkers set on black
// 1A is black
// the whites start from 1a
class Board {

public:	
	static constexpr int rowSize_ = 12;

	int pA[rowSize_] = {0, 2, 4, 6, 9, 11, 13, 15, 16, 18, 20, 22};
	int pB[rowSize_] = {63, 61, 59, 57, 54, 52, 50, 48, 47, 45, 43, 41};
	int kA[rowSize_] = {0};
	int kB[rowSize_] = {0};

	void initWithData (int * pa, int * pb, int * ka, int * kb)
	{
		memcpy(pA, pa, sizeof(pA));
		memcpy(pB, pb, sizeof(pB));
		memcpy(kA, ka, sizeof(kA));
		memcpy(kB, kb, sizeof(kB));
	}
	
	Fld whoIsThere(int ind) const
	{
		for(int i = 0; i < 12; ++i) {
			if(pA[i] == ind) {
				if(kA[i] == 1)
					return WhiteKing;
				else
					return White;
			}
		}
		for(int i = 0; i < 12; ++i) {
			if(pB[i] == ind) {
				if(kB[i] == 1)
					return BlackKing;
				else
					return Black;
			}
		}
		return Empty;
	}

private:
};
	
class Moves
{
	public:

		void addNew(Step s) 
		{ 
			if(count < size_) 
			{
				Move m(s);
				moves[count++] = m;
			}
		}

		int addToLast(Step s) 
		{ 
			if(count) 
			{ 
				moves[count-1].addStepBack(s); 
			}
		}

		void toString() {
			for(int i = 0; i < size(); ++i)
			{
				get(i).toString();
			}
		}

		Move get(int i) const { return moves[i]; } 

		void clear() { count = 0; }
		int size() const { return count; }

	private:
		static constexpr int size_ = 5;
		Move moves[size_];
		int count = 0;
};


class CheckersAI {

public:

	enum Direction {
		Right = 0,
		Left = 1,
		RightBack = 2,
		LeftBack = 3,
	};


	int offset(int d, bool white)
	{
		switch(d)
		{
			case Right:
				return white ? 9 : -9;
			case Left:
				return white ? 7 : -7;
			case RightBack:
				return white ? -7 : 7;
			case LeftBack:
				return white ? -9 : 9;
		}
	}

	class Enimy
	{
		public:
			Enimy() = delete;
			Enimy(int original)
				: orig(original)
			{}
			void add(int taken) { e[ind++] = taken; }
			bool hasTaken(int taken)
			{
				for(int i = 0; i < Move::maxSteps_; ++i)
				{
					if(e[i] == taken) return true;
				}
				return false;
			}
			void toString()
			{
				std::cout << "Enimy: ";
				for(int i = 0; i < Move::maxSteps_; ++i)
				{
					std::cout << e[i] << ", ";
				}
				std::cout << std::endl;
			}
		public:
			int orig = -1;
		private:
			int ind = 0;
			int e[Move::maxSteps_] = {-1};
	};

	//TODO: there is bug or feature: "fuck we are still here!"
	// we can't detect all takes in loop when check clockwise direction
	// because we've checked already ccw direction and detect it correctly
	// think how to remove this branch of unnecessary work
	int canTake(const Board & b, int dir, int ind, bool white, Enimy & enimy, int from = -1)
	{
		if(canGoDirection(dir, ind, white) && (dir != from))
		{
			int offs = offset(dir, white);
			if(!enimy.hasTaken(offs+ind) 
					&& (b.whoIsThere(ind + offs) == (white ? Black : White)) 
					&& canGoDirection(dir, ind + offs, white))
			{
				int newInd = ind + offs + offset(dir, white);
				if((b.whoIsThere(newInd) == Empty) || newInd == enimy.orig)
				{
					enimy.add(ind+offs);
					return newInd;
				}
			}
		}
		return -1;
	}

	void findAllTake(const Board & b, int ind, bool white, Moves & m)
	{
		Enimy enimy(ind);
		findAllTake(b, ind, white, m, enimy, -1);
	}

	// recurcive find less than size moves with takes
	void findAllTake(const Board & b, int ind, bool white, Moves & m, Enimy enimy, int from = -1)
	{
		bool takesFound = false;

		for(int i = 0; i < 4; ++i)
		{
			int newInd = canTake(b, i, ind, white, enimy, from);
			if(newInd != -1)
			{
				//std::cout << "we " << ind << " check " << newInd << std::endl;
				takesFound |= true;

				// go dipper
				int newFrom = -1;
				if(i == Right)
					newFrom = LeftBack;
				if(i == Left)
					newFrom = RightBack;
				if(i == RightBack)
					newFrom = Left;
				if(i == LeftBack)
					newFrom = Right;

				findAllTake(b, newInd, white, m, enimy, newFrom);
				if(from != -1) {
					m.addToLast(Step(ind, true));
				}
			}
		}
		if(!takesFound && (from != -1))
		{
			//std::cout << "reached end, add new for " << ind << std::endl;
			m.addNew(Step(ind, true));
		}
	}
						

	// find only one move with takes, according to the rules, we have to take, but can choose
	// what to take, so we just take something
	bool findAnyTake(const Board & b, int ind, bool white, Move & m, int from = -1)
	{
		for(int i = 0; i < 4; ++i)
		{
			if(canGoDirection(i, ind, white) && (i != from))
			{
				int offs = offset(i, white);
				if((b.whoIsThere(ind + offs) == (white ? Black : White)) && canGoDirection(i, ind + offs, white))
				{
					int newInd = ind+offs + offset(i, white);
					if((b.whoIsThere(newInd) == Empty))
					{
						// we can take
						if(m.addStep(Step(newInd, true)))
						{
							int newFrom = -1;
							if(i == Right)
								newFrom = LeftBack;
							if(i == Left)
								newFrom = RightBack;
							if(i == RightBack)
								newFrom = Left;
							if(i == LeftBack)
								newFrom = Right;
							findAnyTake(b, newInd, white, m, newFrom);
							return true;
						}
					}
				}
			}
		}
		return false;
	}

	int findMoves(const Board & b, int ind, bool white, Moves & m)
	{
		int count = 0;
		m.clear();

		// first we have to check can we take?
		findAllTake(b, ind, white, m);
		if(int size = m.size())
		{
			return size;
		}

		for(int i = 0; i < 2; ++i)
		{
			int newInd = offset(i, white) + ind;
			if(canGoDirection(i, ind, white))
			{
				if(b.whoIsThere(newInd) == Empty)
				{
					m.addNew(Step(newInd, false));
				}
			}	
		}
		return m.size();
	}

	bool canGoDirection(int dir, int ind, bool white) 
	{
		switch(dir)
		{
			case RightBack:
				if(white ? ind < 9 : ind > 54) return false;
				return white ? (ind+1)%16 != 0 : ind%16 != 0;
			case Right:
				if(white ? ind > 63 : ind < 0) return false;
				return white ? (ind+1)%16 != 0 : ind%16 != 0;
			case LeftBack:
				if(white ? ind < 9 : ind > 54) return false;
				return white ? ind%16 != 0 : (ind+1)%16 != 0;
			case Left:
				if(white ? ind > 63 : ind < 0) return false;
				return white ? ind%16 != 0 : (ind+1)%16 != 0;
		}
	}

	bool onKingSide(int ind, bool white) { return white ? ind > 54 : ind < 9; }

		
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

