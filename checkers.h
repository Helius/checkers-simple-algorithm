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
	//Move() = delete;
	Move() = default;
	Move(Step step) {
		steps_[0] = step;
		hasTakes_ = step.take;
		stepCount_ = 1;
		count_++;
	}
	~Move() { count_--; }

	void toString()
	{
		std::cout << "******* Move [count][takes] " << stepCount_ << "| " << hasTakes_ << ": ";
		for(int i = 0; i < stepCount_; ++i)
		{
			std::cout << steps_[i].to << ",";
		}
		std::cout << std::endl;
	}

	bool addStep(Step step)
	{
		if(stepCount_ == maxSteps_)
		{
			return false;
		}
		steps_[stepCount_] = step;
		hasTakes_ |= (step.take);
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

	bool operator<(const Move & move)
	{
		int mySum = 0;
		int otherSum = 0;
		for(int i = 0; i < size(); ++i)
		{
			mySum += getStep(i).to;
		}
		for(int i = 0; i < move.size(); ++i)
		{
			otherSum += move.getStep(i).to;
		}
		return mySum < otherSum;
	}

	static int count_;
private:
	// max number of take
	static constexpr int maxSteps_ = 3;
	int stepCount_ = 0;
	Step steps_[maxSteps_];
	bool hasTakes_ = false;
};

int Move::count_ = 0;

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

	int findMoves(const Board & b, int ind, bool white, Move * m, bool takesOnly = false)
	{
		int count = 0;

		// first we have to check can we take?
		if(findAnyTake(b, ind, white, m[0]))
		{
			return m[0].size();
		}

		if(ind%16 != 0) // not left side
		{
			// just move
			if(!takesOnly && (b.whoIsThere(white ? ind+7 : ind-9) == Empty))
			{
				m[count++] = Move(Step(white ? ind+7 : ind-9));
			} // can we take?
			else if(b.whoIsThere(white ? ind+7 : ind-9) == (white ? Black : White))
			{
				//TODO: if we can take, do recursive(b, ind, white, currentMove, takeOnly = true)
				//
				//
				// check we're not jumping over side and it's empty
				if(((white ? ind+7 : ind-9)%16 != 0) 
						&& (b.whoIsThere(white ? ind+7+7 : ind-9-9) == Empty))
				{
					m[count++] = Move(Step(white ? ind+7+7 : ind-9-9, true));
					takesOnly = true;
				}
			}
		}
		if((ind+1)%16 != 0) // not right side
		{
			if(!takesOnly && (b.whoIsThere(white ? ind+9 : ind-7) == Empty))
			{
				m[count++] = Move(Step(white ? ind+9 : ind-7));
			}
			else if(b.whoIsThere(white ? ind+9 : ind-7) == (white ? Black : White))
			{
				// check we're not jumping over side and it's empty
				if((((white ? ind+9 : ind-7)+1)%16 != 0) 
						&& (b.whoIsThere(white ? ind+9+9 : ind-7-7) == Empty))
				{
					m[count++] = Move(Step(white ? ind+9+9 : ind-7-7, true));
					takesOnly = true;
				}
			}
		}

		int newCount = count;
		if(takesOnly) 
		{
			// get rid of notHasTake moves
			for(int j = 0; j < count; ++j)
			{
				if(!m[j].hasTakes())
				{
					m[j].toString();
					newCount--;
					for(int i = j; i < count; ++i)
					{
							m[i] = m[i+1];
					}
				}
			}
		}
		return newCount;
	}

	int canPieceTake(const Board & b, int direction, int ind, bool white)
	{
			
	}

	bool canGoLeft(int ind, bool white)  { return white ? ind%16 != 0 : (ind+1)%16 != 0; }
	bool canGoRight(int ind, bool white) { return white ? (ind+1)%16 != 0 : ind%16 != 0; }

	bool canGoDirection(int d, int ind, bool white) 
	{
		switch(d)
		{
			case RightBack:
				if(white ? ind < 9 : ind > 54) return false;
				return white ? (ind+1)%16 != 0 : ind%16 != 0;
			case Right:
				if(white ? ind > 48 : ind < 9) return false;
				return white ? (ind+1)%16 != 0 : ind%16 != 0;
			case LeftBack:
				if(white ? ind < 9 : ind > 54) return false;
				return white ? ind%16 != 0 : (ind+1)%16 != 0;
			case Left:
				if(white ? ind > 48 : ind < 15) return false;
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

