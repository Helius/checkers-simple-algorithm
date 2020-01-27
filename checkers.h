#pragma once

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
		Step(int8_t toInd, int8_t takeInd = -1)
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
		inline bool hasTake() const {return  take != -1;}

	public:
		int8_t to = -1;
		int8_t take = -1;
		bool becameKing = false;
};


class Move2 {

	public:

		Move2() = default;

		Move2(int8_t fromInd)
			: from(fromInd)
		{}

		bool addStep(Step step)
		{
			if(stepCount_ == maxSteps_ - 1)
			{
				return false;
			}
			steps_[stepCount_] = step;
			stepCount_++;
			return true;
		}

		inline int8_t currentInd() const {
			if(stepCount_ == 0) {
				return from;
			} else {
				return steps_[stepCount_ - 1].to;
			}

		}

		inline int8_t size() const {
			return stepCount_;
		}

		const Step getStep(int8_t ind) const
		{
			if(ind >= maxSteps_)
			{
				return Step();
			}
			return steps_[ind];
		}

		Step front() const {
			if(size()) {
				return steps_[stepCount_-1];
			} else {
				return Step();
			}
		}

		inline bool becameKing() {
			for(int8_t i = 0; i < stepCount_; ++i) {
				if(steps_[i].becameKing) {
					return true;
				}
			}
			return false;
		}

		bool alreadyTaken(int8_t ind) const {
			for(int8_t i = 0; i < stepCount_; ++i) {
				if(steps_[i].take == ind) {
					return true;
				}
			}
			return false;
		} 

		bool hasTakes() {
			for(int8_t i = 0; i < stepCount_; ++i) {
				if(steps_[i].take != -1) {
					return true;
				}
			}
			return false;
		}

		operator bool() const {
			return size() > 0;
		}

		bool operator==(const Move2 & o) const {
			if(o.size() != size()) return false;
			for(uint8_t i = 0; i < size(); ++i) {
				if(!(o.getStep(i) == getStep(i))) {
					return false;
				}
			}
			return true;
		}

		int8_t getFrom() const { return from; }

	public:
		static constexpr int8_t maxSteps_ = 5;
	private:
		int8_t stepCount_ = 0;
		Step steps_[maxSteps_];
	private:
		int8_t from = -1;
};

class Moves
{
	public:

		bool append(Move2 m)
		{
			if(count < size_)
			{
				moves[count++] = m;
				return true;
			}
			return false;
		}

		bool hasTakes() {
			for(uint8_t i = 0; i < size(); ++i) {
				if(moves[i].hasTakes()) {
					return true;
				}
			}
			return false;
		}

		Move2 get(int i) const { return moves[i]; }

		void clear() { count = 0; }
		int size() const { return count; }

		void updateLonger(Move2 m) {
			if(!m) return;
			// sort longest first
			qsort(moves, count, sizeof(Move2), cmpSize);
			// find first shorter, replace, change size
			for(uint8_t i = 0; i < count; ++i) {
				if(moves[i].size() < m.size()) {
					moves[i] = m;
					if(count < size_-1) {
						count = i+1; // cut all shorter
					}
					return;
				}
			}
			if(!count || (m.size() == moves[0].size())) {
				append(m);
			}
		}

	private:
		static int cmpSize(const void * a, const void * b)
		{
			const Move2 * m1 = static_cast<const Move2*>(a);
			const Move2 * m2 = static_cast<const Move2*>(b);
			return m2->size() - m1->size();
		}

		static constexpr int size_ = 7;
		Move2 moves[size_];
		int count = 0;
};


#ifndef __AVR__
#include <cstring>
#endif
// all checkers set on black
// 1A is black
// the whites start from 1a
class Board {

public:

	void printLine(int8_t line) {
#ifdef __AVR__
		msg << (line%2 ? " " : "");
		for(uint8_t i = 0; i < 4; ++i) {
			int8_t ind = line*8 + i*2 + (line%2 ? 1 : 0);
			int8_t who = whoIsThere(ind);
			if(isItKing(ind)) {
				switch(who) {
					case White:
						msg << "I ";
						break;
					case Black:
						msg << "Z ";
						break;
					case Empty:
						msg << "0 ";
						break;
				}
			} else {
				msg << who;
			}

		}
#else
		std::cout << (const char*)(line%2 ? " " : "");
		for(uint8_t i = 0; i < 4; ++i) {
			std::cout << (int)(whoIsThere(line*8 + i*2 + (line%2 ? 1 : 0))) << " ";
		}
#endif
	}

	void print() {
#ifdef __AVR__
		msg << "  " << value(true) << m::endl;
		for(int8_t i = 0; i < 8; ++i) {
			printLine(7-i);
			msg << m::endl;
		}
		msg << m::endl;
#else
		std::cout << "  " << (int)value(true) << std::endl;
		for(int8_t i = 0; i < 8; ++i) {
			printLine(7-i);
			std::cout << std::endl;
		}
		std::cout << std::endl;

#endif
	}

	int8_t value(bool white) {
		int8_t res = 0;
		for(int i = 0; i < 12; ++i) {
			if(pA[i] != -1) {
				res = res + (white ? 1 : -1) * ((kA[i] ? 3 : 1));
			}
			if(pB[i] != -1) {
				res = res + (white ? -1 : 1) * ((kB[i] ? 3 : 1));
			}
		}
		return res;
	}
	
	void initWithData (int8_t * pa, int8_t * pb, int8_t * ka, int8_t * kb)
	{
		memcpy(pA, pa, sizeof(pA));
		memcpy(pB, pb, sizeof(pB));
		memcpy(kA, ka, sizeof(kA));
		memcpy(kB, kb, sizeof(kB));
	}

	void move(int8_t from, int8_t to, bool becameKing = false) {
		for(uint8_t i = 0; i < 12; ++i) {
			if(pA[i] == from) {
				pA[i] = to;
				kA[i] |= becameKing;
				return;
			}
			if(pB[i] == from) {
				pB[i] = to;
				kB[i] |= becameKing;
				return;
			}
		}
	}

	void take(int8_t ind) {
		for(uint8_t i = 0; i < 12; ++i) {
			if(pA[i] == ind) {
				pA[i] = -1;
				return;
			}
			if(pB[i] == ind) {
				pB[i] = -1;
				return;
			}
		}
	}

	Board clone(Move2 m) const{
		Board b = *this;
		b.move(m.getFrom(), m.front().to, m.becameKing());
		for(uint8_t i = 0; i < m.size(); ++i) {
			Step s = m.getStep(i);
			if(s.take != -1) {
				b.move(s.take, -1);
			}
		}
		return b;
	}

	bool isValid(int8_t ind) const {
		return ind >=0 && ind < 64;
	}

	inline int8_t getPiece(const uint8_t ind, const bool white) const {
		return white ? pA[ind] : pB[ind];
	}
	
	uint8_t peiceCount(bool white) {
		uint8_t cnt = 0;
		for(int i = 0; i < 12; ++i) {
			if(getPiece(i, white) != -1) {
				cnt++;
			}
		}
		return cnt;
	}

	Fld whoIsThere(int8_t ind) const
	{
		for (int8_t i = 0; i < 12; ++i) {
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

	bool isItKing(int8_t ind) const
	{
		for (int8_t i = 0; i < 12; ++i) {
			if (pA[i] == ind)
			{
				return kA[i];
			}
			if (pB[i] == ind)
			{
				return kB[i];
			}
		}
		return false;
	}

private:
	static constexpr int8_t rowSize_ = 12;

	int8_t pA[rowSize_] = {0, 2, 4, 6, 9, 11, 13, 15, 16, 18, 20, 22};
	int8_t pB[rowSize_] = {63, 61, 59, 57, 54, 52, 50, 48, 47, 45, 43, 41};
	int8_t kA[rowSize_] = {0};
	int8_t kB[rowSize_] = {0};
};

class BoardDiff
{
	public:
		void setDown(int8_t dInd) {
			down = dInd;
		}
		
		void setUp(int8_t upInd) {
			if(upCnt < size) {
				up[(upCnt++)%size] = upInd;
			}
		}
		
		Move2 match(const Moves & ms) {
			for(uint8_t j = 0; j < ms.size(); ++j) {
				Move2 m = ms.get(j);
				if((m.front().to == down)) {
					int takeCnt = 0;
					for(int i = 0; i < m.size(); i++) {
						if(m.getStep(i).take != -1) {
							takeCnt++;
						}
					}
					if(upCnt - 1 == takeCnt) {
						return m;
					}
				}
			}
			return Move2();
		}

		operator bool() const {
			return (down != -2) && (upCnt > 0);
		}

		static constexpr uint8_t size = 8;
		int8_t up[size];
		int8_t down = -2;
	private:
		uint8_t upCnt = 0;
};


class CheckersAI {

public:
	
	enum Direction {
		Right = 0,
		Left = 1,
		RightBack = 2,
		LeftBack = 3,
	};

	bool onKingSide(int8_t ind, bool white) { return white ? ind > 54 : ind < 9; }
	
	bool canGoDirection(int8_t dir, int8_t ind, bool white)
	{
#ifdef __AVR__
		static uint16_t savedValue = 500;
		uint16_t mf = memfree();
		if(mf != savedValue) {
			msg << "m:" << mf;
			for(uint8_t i = 0; i < mf/50; ++i) {
				msg << "#";
			}
			msg << m::endl;
			savedValue = mf;
		}
		if(mf < 128)
		{
			msg << "lowr" << m::endl;
			return false;
		}
#endif
		switch(dir)
		{
			case RightBack:
				if(white ? ind < 9 : ind > 54) return false;
				return white ? (ind+1)%16 != 0 : ind%16 != 0;
			case Right:
				if(white ? ind > 54 : ind < 9) return false;
				return white ? (ind+1)%16 != 0 : ind%16 != 0;
			case LeftBack:
				if(white ? ind < 9 : ind > 54) return false;
				return white ? ind%16 != 0 : (ind+1)%16 != 0;
			case Left:
				if(white ? ind > 54 : ind < 9) return false;
				return white ? ind%16 != 0 : (ind+1)%16 != 0;
		}
		return false;
	}
	
	int8_t offset(int8_t d, bool white)
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
		return 0;
	}

	Move2 findBestMove(const Board & b, bool white) {
		Moves ms;
		findTakesAndMoves(b, ms, white);
		int8_t max = -100;
		uint8_t moveInd = 0;

		for(int8_t i = 0; i < ms.size(); ++i) {
			
			Board newB = b.clone(ms.get(i));
			//newB.print();
			Moves newMs;
			findTakesAndMoves(newB, newMs, !white);
			int8_t min = 100;
			for(int8_t j = 0; j < newMs.size(); ++j) {
				Board bb = newB.clone(newMs.get(j));
				//bb.print();
				if(bb.value(white) < min) {
					min = bb.value(white);
				}
			}
			if(min > max) {
				max = min;
				moveInd = i;
			}
		}
		return ms.get(moveInd);
	}

	Move2 findLongestTake(const Board & b, const bool white, const int8_t startInd = -1)
	{
		// so we have start index and 4 direction to search
		Move2 m(startInd);

		return findLongestTake(b, m, white, b.isItKing(startInd));
	}
	
	void findAllTakes(const Board & b, Moves & ms, const bool white, const int8_t startInd = -1)
	{
		// so we have start index and 4 direction to search
		Move2 m(startInd);

		findAllTakes(b, m, ms, white, b.isItKing(startInd));
	}

	void findMoves(const Board & b, Moves & ms, bool white, uint8_t ind)
	{
		if(b.isItKing(ind)) {
			uint8_t originalInd = ind;
			for(uint8_t dir = 0; dir < 4; ++dir) {
				ind = originalInd;
				while(canGoDirection(dir, ind, white) 
					&& (b.whoIsThere(ind + offset(dir, white)) == Empty)) {
					Move2 m(originalInd);
					m.addStep(ind + offset(dir, white));
					if(!ms.append(m)) {
						break;
					}
					ind += offset(dir, white);
				}
			}
		} else {
			for(uint8_t dir = 0; dir < 2; ++dir) {
				if(canGoDirection(dir, ind, white)) {
					uint8_t newOffset = ind + offset(dir, white);
					if(b.whoIsThere(newOffset) == Empty) {
						Move2 m(ind);
						Step step(newOffset);
						step.becameKing |= onKingSide(newOffset, white);
						m.addStep(step);
						if(!ms.append(m)) {
							break;
						}
					}
				}
			}
		}
	}
	void findTheirAllTakes(const Board & b, Moves & ms, bool white) 
	{
		// first find all takes for all pieces
		for(int i = 0; i < 12; ++i) {
			int8_t ind = b.getPiece(i, white);
			if(!b.isValid(ind)) {
				continue;
			}
			findAllTakes(b, ms, white, ind);
		}
		
		if(!ms.size()) {
			for(int i = 0; i < 12; ++i) {
				int8_t ind = b.getPiece(i, white);
				if(!b.isValid(ind)) {
					continue;
				}
				findMoves(b, ms, white, ind);
			}
		}
	}

	void findTakesAndMoves(const Board & b, Moves & ms, bool white) 
	{
		// first find all takes for all pieces
		for(int i = 0; i < 12; ++i) {
			int8_t ind = b.getPiece(i, white);
			if(!b.isValid(ind)) {
				continue;
			}
			if(Move2 m = findLongestTake(b, white, ind)) {
				ms.append(m);
			}
		}
		if(!ms.size()) {
			for(int i = 0; i < 12; ++i) {
				int8_t ind = b.getPiece(i, white);
				if(!b.isValid(ind)) {
					continue;
				}
				findMoves(b, ms, white, ind);
			}
		}
	}

private:

	int8_t calcNewFrom(int8_t i)
	{
		int8_t newFrom = -1;
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

	Step eatEnemy(const Board & b, const int8_t dir, int8_t ind, const bool white, const bool king, const Move2 & m)
	{
		while(canGoDirection(dir, ind, white))
		{
			int8_t offs = offset(dir, white);
			
			if (b.whoIsThere(ind + offs) == (white ? Black : White) && !m.alreadyTaken(ind + offs))
			{
				int8_t indAfterEnemy = ind + offs + offset(dir, white);

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
			else if (king && ((b.whoIsThere(ind + offs) == Empty) || m.alreadyTaken(ind + offs)))
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
	
	void findAllTakes(const Board & b, const Move2 m, Moves & ms, const bool white, bool king, const int8_t from = -1)
	{
		int8_t ind = m.currentInd();

		// check all directions
		for(int8_t dir = 0; dir < 4; ++dir)
		{
			if(dir != from)
			{
				Step step = eatEnemy(b, dir, ind, white, king, m);
				
				if(step.isValid()) 
				{
					Move2 nextMove = m;
					
					if(onKingSide(step.to, white) && !king) {
						king = true;
						step.becameKing = true;
					}
					nextMove.addStep(step);
					// update if longer
					ms.updateLonger(nextMove);
					
					findAllTakes(b, nextMove, ms, white, king, calcNewFrom(dir));
					// update if longer
					//ms.updateLonger(move);
					// check other empty spaces after enemy we can land
					while(king && canGoDirection(dir, step.to, white) && (b.whoIsThere(step.to + offset(dir, white)) == Empty)) {
						Move2 additionalMove = m;
						step.to = step.to + offset(dir, white);
						additionalMove.addStep(step);
						ms.updateLonger(additionalMove);
						/*
						if(additionalMove.size() > resultMove.size()) {
							resultMove = additionalMove;
						}*/
						findAllTakes(b, additionalMove, ms, white, king, calcNewFrom(dir));
						//ms.updateLonger(additionalResult);
					}
				}
			}
		}
	}

	Move2 findLongestTake(const Board & b, const Move2 m, const bool white, bool king, const int8_t from = -1)
	{
		Move2 resultMove;

		int8_t ind = m.currentInd();

		// check all directions
		for(int8_t dir = 0; dir < 4; ++dir)
		{
			if(dir != from)
			{
				Step step = eatEnemy(b, dir, ind, white, king, m);
				
				if(step.isValid()) 
				{
					Move2 nextMove = m;
					
					if(onKingSide(step.to, white) && !king) {
						king = true;
						step.becameKing = true;
					}
					nextMove.addStep(step);
					// update if longer
					if(nextMove.size() > resultMove.size()) {
						resultMove = nextMove;
					}
					Move2 move = findLongestTake(b, nextMove, white, king, calcNewFrom(dir));
					// update if longer
					if(move.size() > resultMove.size()) {
						resultMove = move;
					}
					// check other empty spaces after enemy we can land
					while(king && canGoDirection(dir, step.to, white) && (b.whoIsThere(step.to + offset(dir, white)) == Empty)) {
						Move2 additionalMove = m;
						step.to = step.to + offset(dir, white);
						additionalMove.addStep(step);
						/*
						if(additionalMove.size() > resultMove.size()) {
							resultMove = additionalMove;
						}*/
						Move2 additionalResult = findLongestTake(b, additionalMove, white, king, calcNewFrom(dir));
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
};


class Game {
public:
	enum GameState {
		WaitForBoardInit,
		TheirMove,
		MyMove,
	};

	void startGame() {
		b = Board();
		b.print();
		state = TheirMove;
	}

	void moveFinished() {
		state = MyMove;
	}

	void getTheirMove(Moves & ms) {
		ai.findTheirAllTakes(b, ms, true);
	}

	void applyTheirMove(Move2 m) {
		b = b.clone(m);
		state = MyMove;
		b.print();
	}

	Move2 getMyMove() 
	{
		Move2 m = ai.findBestMove(b, false);
		return m;
	}

	void giveUp()
	{
		reset();
	}

	void myMoveApplyed(Move2 m)
	{
		// check we win or lost
		b = b.clone(m);
		state = TheirMove;
		b.print();
	}

	void reset()
	{
		state = WaitForBoardInit;
	}


	GameState getState() const { return state; }
	
	bool doIWin() {
		return !b.peiceCount(true);
	}

	bool doTheirWin() {
		return !b.peiceCount(false);
	}


public:
	GameState state = WaitForBoardInit;
	Board b;

private:

private:
	CheckersAI ai;
};

