#include <iostream>

#include "gtest/gtest.h"
#include "checkers.h"

//#include "checkersAI.cpp"

/*
  ┏━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┓
h ┃   ┃ 57┃   ┃ 59┃   ┃ 61┃   ┃ 63┃
  ┣━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┫
g ┃ 48┃   ┃ 50┃   ┃ 52┃   ┃ 54┃   ┃
  ┣━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┫
f ┃   ┃ 41┃   ┃ 43┃   ┃ 45┃   ┃ 47┃
  ┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫
e ┃ 32┃   ┃ 34┃   ┃ 36┃   ┃ 38┃   ┃
  ┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫
d ┃   ┃ 25┃   ┃ 27┃   ┃ 29┃   ┃ 31┃
  ┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫
c ┃ 16┃   ┃ 18┃   ┃ 20┃   ┃ 22┃   ┃
  ┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫
b ┃   ┃ 9 ┃   ┃ 11┃   ┃ 13┃   ┃ 15┃
  ┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫
a ┃ O ┃   ┃ 2 ┃   ┃ 4 ┃   ┃ 6 ┃   ┃
  ┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫
    1   2   3   4   5   6   7   8 
 */

TEST(testFindNoTakesEmptyBoard, aiTest)
{
	int pA[12] = {0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int pB[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int kA[12] = {0};
	int kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Move m;
	ai.findAnyTake(b, 11, true, m);
	EXPECT_EQ(m, Move());
}

TEST(testFindOneTakes, aiTest)
{
	int pA[12] = {0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int pB[12] = {20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int kA[12] = {0};
	int kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Move m;
	ai.findAnyTake(b, 11, true, m);
	m.toString();
	EXPECT_EQ(m, Move(Step(29, true)));
}

TEST(testFindTwoTakes, aiTest)
{
	int pA[12] = {0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int pB[12] = {20, 0, 18, 0, 36, 0, 0, 0, 0, 0, 0, 0};
	int kA[12] = {0};
	int kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Move m;
	ai.findAnyTake(b, 11, true, m);
	m.toString();
	Move tm(Step(29, true));
	tm.addStep(Step(43, true));
	EXPECT_EQ(m, tm);
}

TEST(testFindAllTakes, aiTest)
{
	int pA[12] = {0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int pB[12] = {20, 2, 18, 0, 36, 0, 52, 50, 0, 0, 0, 0};
	int kA[12] = {0};
	int kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Moves ms;
	ai.findAllTake(b, 11, true, ms);

	for(int i = 0; i < ms.size(); ++i)
	{
		ms.get(i).toString();
	}
	EXPECT_EQ(ms.size(), 3);
	
	Move m1(Step(43, true));
	m1.addStep(Step(61, true));
	EXPECT_EQ(ms.get(0), m1);
	
	Move m2(Step(29, true));
	m2.addStep(Step(43, true));
	m2.addStep(Step(57, true));
	EXPECT_EQ(ms.get(1).size(), 3);
	EXPECT_EQ(ms.get(1), m2);

	EXPECT_EQ(ms.get(2), Move(Step(25,true)));
}

/*
  ┏━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┓
h ┃   ┃ 57┃   ┃ 59┃   ┃ 61┃   ┃ 63┃
  ┣━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┫
g ┃ 48┃   ┃ 50┃   ┃ 52┃   ┃ 54┃   ┃
  ┣━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┫
f ┃   ┃ 41┃   ┃ 43┃   ┃ 45┃   ┃ 47┃
  ┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫
e ┃ 32┃   ┃ 34┃   ┃ 36┃   ┃ 38┃   ┃
  ┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫
d ┃   ┃ 25┃   ┃ 27┃   ┃ 29┃   ┃ 31┃
  ┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫
c ┃ 16┃   ┃ 18┃   ┃ 20┃   ┃ 22┃   ┃
  ┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫
b ┃   ┃ 9 ┃   ┃ 11┃   ┃ 13┃   ┃ 15┃
  ┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫
a ┃ O ┃   ┃ 2 ┃   ┃ 4 ┃   ┃ 6 ┃   ┃
  ┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫
    1   2   3   4   5   6   7   8 
 */
TEST(testFindAllTakesReturnSamePlace, aiTest)
{
	int pA[12] = {0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int pB[12] = {0, 20, 36, 34, 18, 0, 0, 0, 0, 0, 0};
	int kA[12] = {0};
	int kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Moves ms;
	ai.findAllTake(b, 11, true, ms);
	ms.toString();

	EXPECT_EQ(ms.size(), 2);
	
	Move m1(Step(29, true));
	m1.addStep(Step(43, true));
	m1.addStep(Step(25, true));
	m1.addStep(Step(11, true));

	EXPECT_EQ(ms.get(0).size(), 4);
	EXPECT_EQ(ms.get(1).size(), 4);
	EXPECT_EQ(ms.get(0), m1);
}

TEST(testFindAllTakesWithouLoop, aiTest)
{
	int pA[12] = {0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int pB[12] = {0, 11, 29, 45, 43, 27, 0, 0, 0, 0, 0, 0};
	int kA[12] = {0};
	int kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Moves ms;
	ai.findAllTake(b, 2, true, ms);
	ms.toString();

	EXPECT_EQ(ms.size(), 2);
	
	Move m1(Step(20, true));
	m1.addStep(Step(38, true));
	m1.addStep(Step(52, true));
	m1.addStep(Step(34, true));

	EXPECT_EQ(ms.get(0).size(), 4);
	EXPECT_EQ(ms.get(0), m1);
	
	Move m2(Step(20, true));
	m2.addStep(Step(34, true));
	m2.addStep(Step(52, true));
	m2.addStep(Step(38, true));

	EXPECT_EQ(ms.get(1).size(), 4);
	EXPECT_EQ(ms.get(1), m2);
}

TEST(testOffsetForPeise, aiTest)
{
	CheckersAI ai;
	EXPECT_EQ(ai.offset(CheckersAI::Right, true), 9);
	EXPECT_EQ(ai.offset(CheckersAI::Left, true), 7);
	EXPECT_EQ(ai.offset(CheckersAI::RightBack, true), -7);
	EXPECT_EQ(ai.offset(CheckersAI::LeftBack, true), -9);

	EXPECT_EQ(ai.offset(CheckersAI::Right, false), -9);
	EXPECT_EQ(ai.offset(CheckersAI::Left, false), -7);
	EXPECT_EQ(ai.offset(CheckersAI::RightBack, false), 7);
	EXPECT_EQ(ai.offset(CheckersAI::LeftBack, false), 9);
}

TEST(testAIDetectBoardBorders, aiTest)
{
	CheckersAI ai;
	
	EXPECT_TRUE(ai.canGoDirection(CheckersAI::Right, 0, true));
	EXPECT_FALSE(ai.canGoDirection(CheckersAI::Left, 0, true));
	EXPECT_FALSE(ai.canGoDirection(CheckersAI::RightBack, 0, true));
	EXPECT_FALSE(ai.canGoDirection(CheckersAI::LeftBack, 0, true));
	
	EXPECT_TRUE(ai.canGoDirection(CheckersAI::Right, 2, true));
	EXPECT_TRUE(ai.canGoDirection(CheckersAI::Left, 2, true));
	EXPECT_FALSE(ai.canGoDirection(CheckersAI::RightBack, 2, true));
	EXPECT_FALSE(ai.canGoDirection(CheckersAI::LeftBack, 2, true));
	
	EXPECT_TRUE(ai.canGoDirection(CheckersAI::Right, 11, true));
	EXPECT_TRUE(ai.canGoDirection(CheckersAI::Left, 11, true));
	EXPECT_TRUE(ai.canGoDirection(CheckersAI::RightBack, 11, true));
	EXPECT_TRUE(ai.canGoDirection(CheckersAI::LeftBack, 11, true));
	
	EXPECT_FALSE(ai.canGoDirection(CheckersAI::Right, 15, true));
	EXPECT_TRUE(ai.canGoDirection(CheckersAI::Left, 15, true));
	EXPECT_FALSE(ai.canGoDirection(CheckersAI::RightBack, 15, true));
	EXPECT_TRUE(ai.canGoDirection(CheckersAI::LeftBack, 15, true));
	
	EXPECT_TRUE(ai.canGoDirection(CheckersAI::Right, 59, true));
	EXPECT_TRUE(ai.canGoDirection(CheckersAI::Left, 59, true));
	EXPECT_TRUE(ai.canGoDirection(CheckersAI::RightBack, 59, true));
	EXPECT_TRUE(ai.canGoDirection(CheckersAI::LeftBack, 59, true));
	
	EXPECT_FALSE(ai.canGoDirection(CheckersAI::Right, 32, false));
	EXPECT_TRUE(ai.canGoDirection(CheckersAI::Left, 32, false));
	EXPECT_FALSE(ai.canGoDirection(CheckersAI::RightBack, 32, false));
	EXPECT_TRUE(ai.canGoDirection(CheckersAI::LeftBack, 32, false));

	EXPECT_FALSE(ai.onKingSide(0, true));
	EXPECT_TRUE(ai.onKingSide(0, false));
	
	EXPECT_TRUE(ai.onKingSide(57, true));
	EXPECT_FALSE(ai.onKingSide(57, false));
}

TEST(testInitBoardColors, boardTest)
{
	Board b;
	EXPECT_EQ(b.whoIsThere(0),  White);
	EXPECT_EQ(b.whoIsThere(1),  Empty);
	EXPECT_EQ(b.whoIsThere(2),  White);
	EXPECT_EQ(b.whoIsThere(32), Empty);
	EXPECT_EQ(b.whoIsThere(41), Black);
	EXPECT_EQ(b.whoIsThere(63), Black);
}

TEST(testFindBaseMovesForPieceWithoutTake, aiTest)
{
	Board b;
	CheckersAI ai;
	Moves m;

	EXPECT_EQ(ai.findMoves(b, 18, true,  m), 2);
	EXPECT_EQ(m.size(), 2);
	EXPECT_EQ(m.get(0), Move(Step(27, false)));
	EXPECT_EQ(m.get(1), Move(Step(25, false)));

	EXPECT_EQ(ai.findMoves(b, 16, true,  m), 1);
	//m.toString();
	EXPECT_EQ(m.size(), 1);
	EXPECT_EQ(m.get(0), Move(Step(25, false)));

	EXPECT_EQ(ai.findMoves(b, 9,  true,  m), 0);
	EXPECT_EQ(m.size(), 0);

	EXPECT_EQ(ai.findMoves(b, 43, false, m), 2);
	EXPECT_EQ(m.size(), 2);
	EXPECT_EQ(m.get(0), Move(Step(34, false)));
	EXPECT_EQ(m.get(1), Move(Step(36, false)));

	EXPECT_EQ(ai.findMoves(b, 47, false, m), 1);
	EXPECT_EQ(m.size(), 1);
	EXPECT_EQ(m.get(0), Move(Step(38, false)));

	EXPECT_EQ(ai.findMoves(b, 54, false, m), 0);
}

TEST(testFindBaseMovesForPieceWithTake, aiTest)
{
	int pA[12] = {0, 18, 25, 9, 0, 0, 0, 0, 0, 0, 0, 0};
	int pB[12] = {0, 27, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int kA[12] = {0};
	int kB[12] = {0};

	Board b;
	b.initWithData(pA, pB, kA, kB);
	CheckersAI ai;
	Moves m;

	// шашка заблокирована с одной диагонали и должна рубить 1раз по другой
	EXPECT_EQ(ai.findMoves(b, 18, true,  m), 1);
	EXPECT_EQ(m.get(0), Move(Step(36, true)));
	
	// шашка заблокирована с одной диагонали и не рубит за пределы доски влево
	EXPECT_EQ(ai.findMoves(b, 9, true,  m), 0);
}

TEST(testFindMovesPieceCantTakeOutsideBoard, aiTest)
{
	int pA[12] = {0, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int pB[12] = {0, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int kA[12] = {0};
	int kB[12] = {0};

	Board b;
	b.initWithData(pA, pB, kA, kB);
	CheckersAI ai;
	Moves m;

	// шашка не рубит за пределы доски
	EXPECT_EQ(ai.findMoves(b, 22, true,  m), 1);
	EXPECT_EQ(m.get(0), Move(Step(29, false)));
}

TEST(testFindMovesPieceMustTakeMultiply, aiTest)
{
	int pA[12] = {0, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int pB[12] = {0, 27, 45, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int kA[12] = {0};
	int kB[12] = {0};

	Board b;
	b.initWithData(pA, pB, kA, kB);
	CheckersAI ai;
	Moves m;

	// шашка должна срубить дважды
	EXPECT_EQ(ai.findMoves(b, 18, true,  m), 1);
	Move em(Step(36,true));
	em.addStep(Step(54, true));
	EXPECT_EQ(m.get(0), em);
}

