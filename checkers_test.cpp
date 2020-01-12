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

TEST(testFindAllTakes, aiTest)
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
	EXPECT_EQ(ms.get(0).hasTakes(), false);
	EXPECT_EQ(ms.get(0).getStep(0), Step(11));
	
	EXPECT_EQ(ms.get(1).size(), 1);
	EXPECT_EQ(ms.get(1).currentInd(), 9);
	EXPECT_EQ(ms.get(1).getFrom(), 2);
	EXPECT_EQ(ms.get(1).hasTakes(), false);
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
	EXPECT_EQ(ms.get(0).hasTakes(), false);
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
/*
TEST(testKingCircularTakes, aiTest)
{
	int8_t pA[12] = {0, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t pB[12] = {36, 52, 50, 34, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kA[12] = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	CheckersAI::Enimy e(27);
	b.initWithData(pA, pB, kA, kB);
	Moves m;
	ai.findAllKingTakes(b, 27, true, m, e);
	m.toString();
	EXPECT_EQ(m.size(), 2);
	m.toString();
	EXPECT_EQ(m.get(0).getStep(0), Step(45,true));
	EXPECT_EQ(m.get(0).getStep(1), Step(59,true));
	EXPECT_EQ(m.get(0).getStep(1), Step(41,true));
	EXPECT_EQ(m.get(0).getStep(1), Step(27,true));
}

TEST(testKingOneNearTake, aiTest)
{
	int8_t pA[12] = {0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t pB[12] = {0, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kA[12] = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	CheckersAI::Enimy e(11);
	b.initWithData(pA, pB, kA, kB);
	Moves m;
	ai.findAllKingTakes(b, 11, true, m, e);
	m.toString();
	EXPECT_EQ(m.size(), 1);
	EXPECT_EQ(m.get(0), Move(Step(29, true)));
}

TEST(testKingOneFarTake, aiTest)
{
	int8_t pA[12] = {0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t pB[12] = {0, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kA[12] = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	CheckersAI::Enimy e(11);
	b.initWithData(pA, pB, kA, kB);
	Moves m;
	ai.findAllKingTakes(b, 11, true, m, e);
	m.toString();
	EXPECT_EQ(m.size(), 1);
	EXPECT_EQ(m.get(0), Move(Step(38, true)));
}

TEST(testKingTwoDirectionTakes, aiTest)
{
	int8_t pA[12] = {0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t pB[12] = {0, 20, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kA[12] = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	CheckersAI::Enimy e(11);
	b.initWithData(pA, pB, kA, kB);
	Moves m;
	ai.findAllKingTakes(b, 11, true, m, e);
	m.toString();
	EXPECT_EQ(m.size(), 2);
	EXPECT_EQ(m.get(0), Move(Step(29, true)));
	EXPECT_EQ(m.get(1), Move(Step(25, true)));
}

TEST(testKingTwoHopeNearTakes, aiTest)
{
	int8_t pA[12] = {0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t pB[12] = {0, 20, 38, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kA[12] = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	CheckersAI::Enimy e(11);
	b.initWithData(pA, pB, kA, kB);
	Moves m;
	ai.findAllKingTakes(b, 11, true, m, e);
	m.toString();
	EXPECT_EQ(m.size(), 1);
	EXPECT_EQ(m.get(0).getStep(0), Step(29,true));
	EXPECT_EQ(m.get(0).getStep(1), Step(47,true));
}


TEST(testKingFindFirstEnimy, aiTest)
{
	int8_t pA[12] = {0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t pB[12] = {0, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kA[12] = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	CheckersAI::Enimy e(11);
	b.initWithData(pA, pB, kA, kB);
	EXPECT_EQ(ai.takeFirstEnimy(b, CheckersAI::Right, 11, true, e),29);
	EXPECT_EQ(ai.takeFirstEnimy(b, CheckersAI::Left, 11, true, e),-1);
	EXPECT_EQ(ai.takeFirstEnimy(b, CheckersAI::RightBack, 11, true, e),-1);
	EXPECT_EQ(ai.takeFirstEnimy(b, CheckersAI::LeftBack, 11, true, e),-1);


	pB[1] = 29;
	b.initWithData(pA, pB, kA, kB);
	EXPECT_EQ(ai.takeFirstEnimy(b, CheckersAI::Right, 11, true, e),38);
	EXPECT_EQ(ai.takeFirstEnimy(b, CheckersAI::Left, 11, true, e),-1);
	EXPECT_EQ(ai.takeFirstEnimy(b, CheckersAI::RightBack, 11, true, e),-1);
	EXPECT_EQ(ai.takeFirstEnimy(b, CheckersAI::LeftBack, 11, true, e),-1);

	pB[1] = 25;
	b.initWithData(pA, pB, kA, kB);
	EXPECT_EQ(ai.takeFirstEnimy(b, CheckersAI::Right, 11, true, e),-1);
	EXPECT_EQ(ai.takeFirstEnimy(b, CheckersAI::Left, 11, true, e),32);
	EXPECT_EQ(ai.takeFirstEnimy(b, CheckersAI::RightBack, 11, true, e),-1);
	EXPECT_EQ(ai.takeFirstEnimy(b, CheckersAI::LeftBack, 11, true, e),-1);

	pB[1] = 20;
	pB[2] = 29;
	b.initWithData(pA, pB, kA, kB);
	EXPECT_EQ(ai.takeFirstEnimy(b, CheckersAI::Right, 11, true, e),-1);
	EXPECT_EQ(ai.takeFirstEnimy(b, CheckersAI::Left, 11, true, e),-1);
	EXPECT_EQ(ai.takeFirstEnimy(b, CheckersAI::RightBack, 11, true, e),-1);
	EXPECT_EQ(ai.takeFirstEnimy(b, CheckersAI::LeftBack, 11, true, e),-1);

}

TEST(testMoves, aiTest)
{
	Moves mvs;
	Move & m = mvs.addNew(Step(3,true));
	Move & m1 = mvs.clone(m, Step(5, false));
	EXPECT_EQ(m.size(), 1);
	EXPECT_EQ(m1.size(), 2);
	EXPECT_EQ(mvs.size(), 2);
	EXPECT_EQ(mvs.get(0).getStep(0), Step(3, true));
	EXPECT_EQ(mvs.get(1).getStep(0), Step(3, true));
	EXPECT_EQ(mvs.get(1).getStep(1), Step(5, false));
}

TEST(testFindNoTakesEmptyBoard, aiTest)
{
	int8_t pA[12] = {0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t pB[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kA[12] = {0};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Move m;
	ai.findAnyTake(b, 11, true, m);
	EXPECT_EQ(m, Move());
}

TEST(testFindOneTakes, aiTest)
{
	int8_t pA[12] = {0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t pB[12] = {20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kA[12] = {0};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Move m;
	ai.findAnyTake(b, 11, true, m);
	//m.toString();
	EXPECT_EQ(m, Move(Step(29, true)));
}

TEST(testFindTwoTakes, aiTest)
{
	int8_t pA[12] = {0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t pB[12] = {20, 0, 18, 0, 36, 0, 0, 0, 0, 0, 0, 0};
	int8_t kA[12] = {0};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Move m;
	ai.findAnyTake(b, 11, true, m);
	//m.toString();
	Move tm(Step(29, true));
	tm.addStep(Step(43, true));
	EXPECT_EQ(m, tm);
}

TEST(testFindAllTakes, aiTest)
{
	int8_t pA[12] = {0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t pB[12] = {20, 2, 18, 0, 36, 0, 52, 50, 0, 0, 0, 0};
	int8_t kA[12] = {0};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Moves ms;
	ai.findAllTake(b, 11, true, ms);

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

TEST(testFindAllTakesReturnSamePlace, aiTest)
{
	int8_t pA[12] = {0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t pB[12] = {0, 20, 36, 34, 18, 0, 0, 0, 0, 0, 0};
	int8_t kA[12] = {0};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Moves ms;
	ai.findAllTake(b, 11, true, ms);
	//ms.toString();

	EXPECT_EQ(ms.size(), 2);

	Move m1(Step(29, true));
	m1.addStep(Step(43, true));
	m1.addStep(Step(25, true));
	m1.addStep(Step(11, true));

	EXPECT_EQ(ms.get(0), m1);
	EXPECT_EQ(ms.get(0).size(), 4);
	//EXPECT_EQ(ms.get(1).size(), 4);
}

TEST(testFindAllTakesWithouLoop, aiTest)
{
	int8_t pA[12] = {0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t pB[12] = {0, 11, 29, 45, 43, 27, 0, 0, 0, 0, 0, 0};
	int8_t kA[12] = {0};
	int8_t kB[12] = {0};

	CheckersAI ai;
	Board b;
	b.initWithData(pA, pB, kA, kB);
	Moves ms;
	ai.findAllTake(b, 2, true, ms);
	//ms.toString();

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
*/
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

	EXPECT_TRUE(ai.canGoDirection(CheckersAI::Right, 38, true));

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

/*
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
	int8_t pA[12] = {0, 18, 25, 9, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t pB[12] = {0, 27, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kA[12] = {0};
	int8_t kB[12] = {0};

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
	int8_t pA[12] = {0, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t pB[12] = {0, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kA[12] = {0};
	int8_t kB[12] = {0};

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
	int8_t pA[12] = {0, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t pB[12] = {0, 27, 45, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int8_t kA[12] = {0};
	int8_t kB[12] = {0};

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
*/
