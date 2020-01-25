#include <iostream>

#include "gtest/gtest.h"
#include "checkers.h"

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

TEST(testFindOneLongestTakes, aiTest)
{
	int8_t pA[12] = {27, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	int8_t kA[12] = {0};
	int8_t pB[12] = {18, 20, 36, 34, 54, -1, -1, -1, -1, -1, -1, -1};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Moves ms;
	ai.findAllTakes(b, ms, true, 27);
	EXPECT_EQ(ms.size(), 1);
}

TEST(testFindAllTakes, aiTest)
{
	int8_t pA[12] = {27, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	int8_t kA[12] = {0};
	int8_t pB[12] = {18, 20, 36, 34, -1, -1, -1, -1, -1, -1, -1, -1};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Moves ms;
	ai.findAllTakes(b, ms, true, 27);
	EXPECT_EQ(ms.size(), 4);
}

TEST(testLongestOverrideShortest, movesTest)
{
	Moves ms;
	
	Move2 m1;
	m1.addStep(Step(1,1));
	EXPECT_EQ(m1.size(), 1);
	m1.addStep(Step(1,1));
	EXPECT_EQ(m1.size(), 2);
	
	Move2 m2;
	m2.addStep(Step(1,1));
	m2.addStep(Step(1,1));
	m2.addStep(Step(1,1));
	EXPECT_EQ(m2.size(), 3);

	ms.append(m1);
	EXPECT_EQ(ms.size(), 1);
	ms.append(m2);
	EXPECT_EQ(ms.size(), 2);
	
	Move2 m3;
	m3.addStep(Step(1,1));
	m3.addStep(Step(1,1));
	m3.addStep(Step(1,1));
	m3.addStep(Step(1,1));

	ms.updateLonger(m3);
	EXPECT_EQ(ms.size(), 1);
	EXPECT_EQ(ms.get(0).size(), 4);
	
	ms.updateLonger(m3);
	EXPECT_EQ(ms.size(), 2);
	EXPECT_EQ(ms.get(0).size(), 4);
	EXPECT_EQ(ms.get(1).size(), 4);

	Move2 m4;
	m4.addStep(Step(1,1));
	ms.updateLonger(m4);
	
	EXPECT_EQ(ms.size(), 2);
	EXPECT_EQ(ms.get(0).size(), 4);
	EXPECT_EQ(ms.get(1).size(), 4);
}

TEST(testPieceBecameKing, aiTest)
{
	int8_t pA[12] = {41, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	int8_t kA[12] = {0};
	int8_t pB[12] = {50, 45, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Move2 m = ai.findBestMove(b, true);
	EXPECT_TRUE(m);
	EXPECT_EQ(m.size(), 2);
	EXPECT_EQ(m.getStep(0), Step(59, 50));
	EXPECT_EQ(m.getStep(1), Step(38, 45));
}

TEST(testFindBestTake, aiTest)
{
	int8_t pA[12] = {2, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	int8_t kA[12] = {0};
	int8_t pB[12] = {9, 13, 27, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Move2 m = ai.findBestMove(b, true);
	EXPECT_TRUE(m);
	EXPECT_EQ(m.size(), 2);
	EXPECT_EQ(m.getStep(0), Step(20,13));
	EXPECT_EQ(m.getStep(1), Step(34,27));
}


TEST(testFindBestMoveAvoidTakeUs, aiTest)
{
	int8_t pA[12] = {0, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	int8_t kA[12] = {0};
	int8_t pB[12] = {18, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Move2 m = ai.findBestMove(b, true);
	EXPECT_TRUE(m);
	EXPECT_EQ(m.size(), 1);
	EXPECT_EQ(m.getStep(0), Step(13));
}

TEST(testFindBestMoveBecauseOneTake, aiTest)
{
	int8_t pA[12] = {11, 32, 43, 54, -1, -1, -1, -1, -1, -1, -1, -1};
	int8_t kA[12] = {0};
	int8_t pB[12] = {41, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Move2 m = ai.findBestMove(b, true);
	EXPECT_TRUE(m);
	EXPECT_EQ(m.size(), 1);
	EXPECT_EQ(m.getStep(0), Step(50, 41));
}

TEST(testFindAllMove, aiTest)
{
	int8_t pA[12] = {0, 2, 29, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	int8_t kA[12] = {0};
	int8_t pB[12] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Moves ms;
	ai.findTakesAndMoves(b, ms, true);
	EXPECT_EQ(ms.size(), 5);
	/*
	EXPECT_EQ(ms.get(0).getStep(0).to, 18);
	EXPECT_EQ(ms.get(0).getStep(0).take, 9);
	EXPECT_EQ(ms.get(0).getStep(1).to, 4);
	EXPECT_EQ(ms.get(0).getStep(1).take, 11);
	
	EXPECT_EQ(ms.get(1).getStep(0).to, 20);
	EXPECT_EQ(ms.get(1).getStep(0).take, 11);
	*/
}

TEST(testFindTakes, aiTest)
{
	int8_t pA[12] = {0, 2, 29, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	int8_t kA[12] = {0};
	int8_t pB[12] = {9, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Moves ms;
	ai.findTakesAndMoves(b, ms, true);
	EXPECT_EQ(ms.size(), 2);
	EXPECT_EQ(ms.get(0).getStep(0).to, 18);
	EXPECT_EQ(ms.get(0).getStep(0).take, 9);
	EXPECT_EQ(ms.get(0).getStep(1).to, 4);
	EXPECT_EQ(ms.get(0).getStep(1).take, 11);
	
	EXPECT_EQ(ms.get(1).getStep(0).to, 20);
	EXPECT_EQ(ms.get(1).getStep(0).take, 11);
}

TEST(testKingRestrictedMove, aiTest)
{
	int8_t pA[12] = {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kA[12] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t pB[12] = {16, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Moves ms;
	ai.findMoves(b, ms, true, 2);
	EXPECT_EQ(ms.size(), 2);
	
	EXPECT_EQ(ms.get(0).getStep(0), Step(11));
	EXPECT_EQ(ms.get(1).getStep(0), Step(9));
}


TEST(testKingMove, aiTest)
{
	int8_t pA[12] = {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kA[12] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t pB[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Moves ms;
	ai.findMoves(b, ms, true, 2);
	EXPECT_EQ(ms.size(), 7);
	
	EXPECT_EQ(ms.get(0).getStep(0), Step(11));
	EXPECT_EQ(ms.get(1).getStep(0), Step(20));
	EXPECT_EQ(ms.get(2).getStep(0), Step(29));
	EXPECT_EQ(ms.get(3).getStep(0), Step(38));
	EXPECT_EQ(ms.get(4).getStep(0), Step(47));
	EXPECT_EQ(ms.get(5).getStep(0), Step(9));
	EXPECT_EQ(ms.get(6).getStep(0), Step(16));
}

TEST(testPieceMove, aiTest)
{
	int8_t pA[12] = {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t pB[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kA[12] = {0};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Moves ms;
	ai.findMoves(b, ms, true, 2);
	
	EXPECT_EQ(ms.size(), 2);
	EXPECT_EQ(ms.get(0).size(), 1);
	EXPECT_EQ(ms.get(0).currentInd(), 11);
	EXPECT_EQ(ms.get(0).getFrom(), 2);
	EXPECT_EQ(ms.get(0).getStep(0), Step(11));
	
	EXPECT_EQ(ms.get(1).size(), 1);
	EXPECT_EQ(ms.get(1).currentInd(), 9);
	EXPECT_EQ(ms.get(1).getFrom(), 2);
	EXPECT_EQ(ms.get(1).getStep(0), Step(9));
}

TEST(testPieceHasNoMove, aiTest)
{
	int8_t pA[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t pB[12] = {9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kA[12] = {0};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Moves ms;
	ai.findMoves(b, ms, true, 0);
	
	EXPECT_EQ(ms.size(), 0);
}

TEST(testPieceOneMove, aiTest)
{
	int8_t pA[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t pB[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kA[12] = {0};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Moves ms;
	ai.findMoves(b, ms, true, 0);
	
	EXPECT_EQ(ms.size(), 1);
	
	EXPECT_EQ(ms.get(0).size(), 1);
	EXPECT_EQ(ms.get(0).currentInd(), 9);
	EXPECT_EQ(ms.get(0).getFrom(), 0);
	EXPECT_EQ(ms.get(0).getStep(0), Step(9));
}

TEST(boardIsItKingTEst, aiTest)
{
	int8_t pA[12] = {0, 1, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	int8_t pB[12] = {11, 27, 25, 9, -1, -1, -1, -1, -1, -1, -1};
	int8_t kA[12] = {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kB[12] = {0};

	Board b;
	b.initWithData(pA, pB, kA, kB);
	EXPECT_TRUE(b.isItKing(0));
	EXPECT_TRUE(b.isItKing(3));
	EXPECT_FALSE(b.isItKing(1));
	EXPECT_FALSE(b.isItKing(11));
}

TEST(testPieceNotTake, aiTest)
{
	int8_t pA[12] = {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t pB[12] = {20, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kA[12] = {0};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Move2 m = ai.findLongestTake(b, true, 2);
	EXPECT_EQ(m.size(), 0);
}

TEST(testPieceFindLongestTake, aiTest)
{
	int8_t pA[12] = {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t pB[12] = {25, 11, 9, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kA[12] = {0};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Move2 m = ai.findLongestTake(b, true, 2);
	EXPECT_EQ(m.size(), 2);
}

TEST(testPieceRoundTake, aiTest)
{
	int8_t pA[12] = {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t pB[12] = {25, 11, 9, 27, 0, 0, 0, 0, 0, 0, 0};
	int8_t kA[12] = {0};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Move2 m = ai.findLongestTake(b, true, 2);
	EXPECT_EQ(m.size(), 4);
	EXPECT_EQ(m.getStep(0), Step(20, 11));
	EXPECT_EQ(m.getStep(1), Step(34, 27));
	EXPECT_EQ(m.getStep(2), Step(16, 25));
	EXPECT_EQ(m.getStep(3), Step(2, 9));
}

TEST(testNewKingCircularTakes, aiTest) {
	int8_t pA[12] = {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t pB[12] = {11, 27, 25, 9, 0, 0, 0, 0, 0, 0, 0};
	int8_t kA[12] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Move2 m = ai.findLongestTake(b, true, 2);
	EXPECT_EQ(m.size(), 4);
	//EXPECT_EQ(m.getStep(0), Step(45,27));
	//EXPECT_EQ(m.getStep(1), Step(59,52));
}

TEST(testNewKingTakeCornerWithGap, aiTest) {
	int8_t pA[12] = {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	int8_t pB[12] = {27, 52, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	int8_t kA[12] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Move2 m = ai.findLongestTake(b, true, 0);
	EXPECT_EQ(m.size(), 2);
	EXPECT_EQ(m.getStep(0), Step(45,27));
	EXPECT_EQ(m.getStep(1), Step(59,52));
}

TEST(testNewKingTakeCorner, aiTest) {
	int8_t pA[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t pB[12] = {27, 43, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kA[12] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Move2 m = ai.findLongestTake(b, true, 0);
	EXPECT_EQ(m.size(), 2);
	EXPECT_EQ(m.getStep(0), Step(36,27));
	EXPECT_EQ(m.getStep(1), Step(50,43));
}

TEST(testNewKingTakeWithGap, aiTest) {
	int8_t pA[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t pB[12] = {45, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kA[12] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Move2 m = ai.findLongestTake(b, true, 0);
	EXPECT_EQ(m.size(), 1);
	EXPECT_EQ(m.getStep(0), Step(54,45));
}

TEST(testNewKingTakeTwice, aiTest) {
	int8_t pA[12] = {0, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t pB[12] = {36, 54, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kA[12] = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Move2 m = ai.findLongestTake(b, true, 27);
	EXPECT_EQ(m.size(), 2);
	EXPECT_EQ(m.getStep(0), Step(45,36));
	EXPECT_EQ(m.getStep(1), Step(63,54));
}

TEST(testNewKingTake, aiTest) {
	int8_t pA[12] = {0, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t pB[12] = {36, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kA[12] = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Move2 m = ai.findLongestTake(b, true, 27);
	EXPECT_EQ(m.size(), 1);
	EXPECT_EQ(m.getStep(0), Step(45,36));
}

TEST(testNoNewKingTake, aiTest) {
	int8_t pA[12] = {0, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t pB[12] = {29, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kA[12] = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Move2 m = ai.findLongestTake(b, true, 27);
	EXPECT_EQ(m.size(), 0);
}

TEST(testWinCondition, gameTest) {
	int8_t pA[12] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	int8_t pB[12] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	int8_t pA1[12] = {-1, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	int8_t pB1[12] = {-1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	int8_t kA[12] = {0};
	int8_t kB[12] = {0};

	Game game;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	EXPECT_FALSE(game.doIWin());
	EXPECT_FALSE(game.doTheirWin());
	
	game.b = b;
	EXPECT_TRUE(game.doIWin());
	EXPECT_TRUE(game.doTheirWin());
	
	b.initWithData(pA1, pB, kA, kB);
	game.b = b;
	EXPECT_FALSE(game.doIWin());
	EXPECT_TRUE(game.doTheirWin());
	
	b.initWithData(pA, pB1, kA, kB);
	game.b = b;
	EXPECT_TRUE(game.doIWin());
	EXPECT_FALSE(game.doTheirWin());
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

	EXPECT_TRUE(ai.canGoDirection(CheckersAI::Right, 59, false));
	EXPECT_TRUE(ai.canGoDirection(CheckersAI::Left, 59, false));
	EXPECT_TRUE(ai.canGoDirection(CheckersAI::RightBack, 59, true));
	EXPECT_TRUE(ai.canGoDirection(CheckersAI::LeftBack, 59, true));

	EXPECT_TRUE(ai.canGoDirection(CheckersAI::Right, 38, true));

	EXPECT_FALSE(ai.canGoDirection(CheckersAI::Right, 32, false));
	EXPECT_TRUE(ai.canGoDirection(CheckersAI::Left, 32, false));
	EXPECT_FALSE(ai.canGoDirection(CheckersAI::RightBack, 32, false));
	EXPECT_TRUE(ai.canGoDirection(CheckersAI::LeftBack, 32, false));

	EXPECT_FALSE(ai.canGoDirection(CheckersAI::Right, 2, false));
	EXPECT_FALSE(ai.canGoDirection(CheckersAI::Left, 2, false));

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
