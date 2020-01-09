#pragma once

//TODO: for desktop only!!
//#include <iostream>
//#include <vector>
//#include <algorithm>


enum Fld {
	Empty,
	White,
	Black,
	WhiteKing,
	BlackKing
};

class Step {
	public:
		Step() = default;
		Step(int toInd, int takeInd = -1)
		: to(toInd)
		, take(takeInd)
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
		inline bool hasTake() {return  take != -1;}

	public:
		int to = -1;
		int take = -1;
};


class Move2 {

	public:

		Move2() = default;

		Move2(int fromInd)
			: from(fromInd)
		{}

		bool addStep(Step step)
		{
			if(stepCount_ == maxSteps_ - 1)
			{
				return false;
			}
			steps_[stepCount_] = step;
			hasTakes_ |= step.hasTake();
			stepCount_++;
			return true;
		}

		inline int currentInd() const {
			if(stepCount_ == 0) {
				return from;
			} else {
				return steps_[stepCount_ - 1].to;
			}

		}

		inline int size() const {
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

		bool alreadyTaken(int ind) const {
			for(int i = 0; i < stepCount_; ++i) {
				if(steps_[i].take == ind) {
					return true;
				}
			}
			return false;
		} 

		bool operator() (const Move2 & m) const{
			return m.size() > 0;
		}

		int getFrom() const { return from; }

	public:
		static constexpr int maxSteps_ = 5;
	private:
		int stepCount_ = 0;
		Step steps_[maxSteps_];
		bool hasTakes_ = false;
	private:
		int from = -1;
};

#ifndef __AVR__
#include <cstring>
#endif
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
		for (int i = 0; i < 12; ++i) {
			if (pA[i] == ind)
			{
				return White;
			}
			else if (pB[i] == ind)
			{
				return Black;
			}
		}
		return Empty;
	}

	bool isItKing(int ind) const
	{
		for (int i = 0; i < 12; ++i) {
			if ((pA[i] == ind) && kA[i])
			{
				return true;
			}
			else if ((pB[i] == ind) && kB[i])
			{
				return true;
			}
		}
		return false;
	}

private:
};

/*

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
		hasTakes_ |= step.hasTake();
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
		hasTakes_ |= step.hasTake();
		stepCount_++;
		return true;
	}

	inline int size() const {
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

	bool operator() (const Move & m) const{
		return m.size();
	}

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

class Moves
{
	public:

		Move & clone(Move & m, Step s)
		{
			if(count < size_) {
				moves[count++] = m;
				moves[count-1].addStep(s);
				return moves[count-1];
			}
			return invalidMove;
		}

		Move & addNew(Step s)
		{
			if(count < size_)
			{
				Move m(s);
				moves[count++] = m;
				return moves[count-1];
			}
			return invalidMove;
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
		static constexpr int size_ = 8;
		Move moves[size_];
		Move invalidMove = Move();
		int count = 0;
};

*/

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

	int calcNewFrom(int i)
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
		return newFrom;
	}

	Step eatEnemy(const Board & b, const int dir, int ind, const bool white, const Move2 & m)
	{
		while(canGoDirection(dir, ind, white))
		{
			int offs = offset(dir, white);
			
			if (b.whoIsThere(ind + offs) == (white ? Black : White) && !m.alreadyTaken(ind + offs))
			{
				int indAfterEnemy = ind + offs + offset(dir, white);

				if(canGoDirection(dir, ind+offs, white) && (
						(b.whoIsThere(indAfterEnemy) == Empty) 
						|| indAfterEnemy == m.getFrom() 
						|| m.alreadyTaken(indAfterEnemy)))
					{
					return Step(indAfterEnemy, ind+offs);
				} else {
					return Step();
				}
			}
			else if ((b.whoIsThere(ind + offs) == Empty) || m.alreadyTaken(ind + offs))
			{
				ind += offs;
			}
			else
			{
				return Step();
			}
		}
		return Step();
	}

	
	Move2 findLongestTake(const Board & b, const Move2 m, const bool white, const int from = -1)
	{
		Move2 resultMove;

		int ind = m.currentInd();

		// check all directions
		for(int dir = 0; dir < 4; ++dir)
		{
			if(dir != from)
			{
				Step step = eatEnemy(b, dir, ind, white, m);
				
				if(step.isValid()) 
				{
					Move2 nextMove = m;
					nextMove.addStep(step);
					// update if longer
					if(nextMove.size() > resultMove.size()) {
						resultMove = nextMove;
					}

					Move2 move = findLongestTake(b, nextMove, white, calcNewFrom(dir));
					// update if longer
					if(move.size() > resultMove.size()) {
						resultMove = move;
					}
					// check other empty spaces after enemy we can land
					while(canGoDirection(dir, step.to, white) && (b.whoIsThere(step.to + offset(dir, white) == Empty))) {
						Move2 additionalMove = m;
						step.to = step.to + offset(dir, white);
						additionalMove.addStep(step);
						/*
						if(additionalMove.size() > resultMove.size()) {
							resultMove = additionalMove;
						}*/
						Move2 additionalResult = findLongestTake(b, additionalMove, white, calcNewFrom(dir));
						if(additionalResult.size() > resultMove.size()) {
							resultMove = additionalResult;
						}
					}
				}
			}
		}

		// finally return longest if it exist or empty move
		return resultMove;
	}

	Move2 findLongestTake(const Board & b, const bool white, const int startInd = -1)
	{
		// so we have start index and 4 direction to search
		Move2 m(startInd);

		return findLongestTake(b, m, white); 
	}
/*

	class Enimy
	{
		public:
			Enimy() = delete;
			Enimy(int original)
				: orig(original)
			{}
			void add(int taken) { e[ind++] = taken; }
			int lastTaken() { return e[ind-1]; }
			bool hasTaken(int taken)
			{
				for(int i = 0; i < Move::maxSteps_; ++i)
				{
					if(e[i] == taken) return true;
				}
				return false;
			}
			bool isOriginal(int ind) {return orig == ind; }
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

	// walk forward until find an animy and an empty place after it, return ind of this place
	int takeFirstEnimy(const Board & b, int dir, int ind, bool white, Enimy & enimy, std::string nest = std::string())
	{
		while(canGoDirection(dir, ind, white))
		{
			int offs = offset(dir, white);
			std::cout << nest << "check from " 
				<< ind << ", dir: " 
				<< dir << " to " 
				<< ind + offs << std::endl;

			enimy.toString();

			if (b.whoIsThere(ind + offs) == (white ? Black : White) && !enimy.hasTaken(ind + offs))
			{
				int indAfterEnimy = ind + offs + offset(dir, white);

				std::cout << nest << "detected! dest " << indAfterEnimy << ", empty? " << ((b.whoIsThere(indAfterEnimy) == Empty || enimy.isOriginal(indAfterEnimy)) ? "yes" : "no") << std::endl;

				if(canGoDirection(dir, ind+offs, white) && ((b.whoIsThere(indAfterEnimy) == Empty) || enimy.isOriginal(indAfterEnimy)) && !enimy.hasTaken(ind+offs)) {

					enimy.add(ind + offs);
					return indAfterEnimy;
				}
				else
				{
					return -1; // can't walk further
				}
			}
			ind += offs;
		}
		return -1;
	}

	std::string prefix(int nest) {
		std::string result;
		for(int i = 0; i < nest; ++i) {
			result += "\t";
		}
		return result;
	}

	void findAllKingTakes(const Board & b, int ind, bool white, Moves & m, Enimy enimy, int from = -1, int nest = 0)
	{
		nest++;

		bool takesFound = false;
		std::cout << prefix(nest) << "=========== start from " << ind << ", dir" << from << std::endl;

		for(int i = 0; i < 4; ++i)
		{
			int newInd = takeFirstEnimy(b, i, ind, white, enimy, prefix(nest));
			std::cout <<  prefix(nest) <<"and we now at " << newInd << std::endl;
			if(newInd != -1)
			{
				takesFound |= 1;

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

				findAllKingTakes(b, newInd, white, m, enimy, newFrom, nest);
				if(from != -1) {
					m.addToLast(Step(ind, true));
				}
			}
		}
		if(!takesFound && (from != -1))
		{
			std::cout << prefix(nest) << "reached end, add new for " << ind << std::endl;
			m.addNew(Step(ind, true));
		}
	}


	//TODO: there is a bug or a feature: "fuck we are still here!"
	// we can't detect all takes in loop when check clockwise direction
	// because we've checked already ccw direction and detect it correctly
	// Thinking how to remove this branch of unnecessary work
	//
	// return ind after taking peice at ind with dir or -1
	int canTake(const Board & b, int dir, int ind, bool white, Enimy & enimy, int from = -1)
	{
		if((dir != from) && canGoDirection(dir, ind, white))
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

	// recurcive find less than size moves with takes for piece
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
*/
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

