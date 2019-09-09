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
	ai.findTakes(b, 11, true, m);
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
	ai.findTakes(b, 11, true, m);
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
	ai.findTakes(b, 11, true, m);
	m.toString();
	Move tm(Step(29, true));
	tm.addStep(Step(43, true));
	EXPECT_EQ(m, tm);
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
	EXPECT_FALSE(ai.canGoLeft(0, true));
	EXPECT_TRUE(ai.canGoRight(0, true));
	
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
	
	EXPECT_FALSE(ai.canGoDirection(CheckersAI::Right, 59, true));
	EXPECT_FALSE(ai.canGoDirection(CheckersAI::Left, 59, true));
	EXPECT_TRUE(ai.canGoDirection(CheckersAI::RightBack, 59, true));
	EXPECT_TRUE(ai.canGoDirection(CheckersAI::LeftBack, 59, true));
	
	EXPECT_FALSE(ai.canGoDirection(CheckersAI::Right, 32, false));
	EXPECT_TRUE(ai.canGoDirection(CheckersAI::Left, 32, false));
	EXPECT_FALSE(ai.canGoDirection(CheckersAI::RightBack, 32, false));
	EXPECT_TRUE(ai.canGoDirection(CheckersAI::LeftBack, 32, false));

	EXPECT_FALSE(ai.onKingSide(0, true));
	EXPECT_TRUE(ai.onKingSide(0, false));
	
	EXPECT_TRUE(ai.canGoLeft(2, true));
	EXPECT_TRUE(ai.canGoRight(2, true));
	
	EXPECT_TRUE(ai.canGoLeft(15, true));
	EXPECT_FALSE(ai.canGoRight(15, true));
	
	EXPECT_FALSE(ai.canGoLeft(15, false));
	EXPECT_TRUE(ai.canGoRight(15, false));

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
	Move m[4];

	EXPECT_EQ(ai.findMoves(b, 18, true,  m), 2);
	EXPECT_EQ(m[0], Move(Step(25, false)));
	EXPECT_EQ(m[1], Move(Step(27, false)));

	EXPECT_EQ(ai.findMoves(b, 16, true,  m), 1);
	EXPECT_EQ(m[0], Move(Step(25, false)));

	EXPECT_EQ(ai.findMoves(b, 9,  true,  m), 0);

	EXPECT_EQ(ai.findMoves(b, 43, false, m), 2);
	EXPECT_EQ(m[0], Move(Step(34, false)));
	EXPECT_EQ(m[1], Move(Step(36, false)));

	EXPECT_EQ(ai.findMoves(b, 47, false, m), 1);
	EXPECT_EQ(m[0], Move(Step(38, false)));

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
	Move m[4];

	// шашка заблокирована с одной диагонали и должна рубить 1раз по другой
	EXPECT_EQ(ai.findMoves(b, 18, true,  m), 1);
	EXPECT_EQ(m[0], Move(Step(36, true)));
	
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
	Move m[4];

	// шашка не рубит за пределы доски
	EXPECT_EQ(ai.findMoves(b, 22, true,  m), 1);
	EXPECT_EQ(m[0], Move(Step(29, false)));
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
	Move m[4];

	// шашка должна срубить дважды
	//EXPECT_EQ(ai.findMoves(b, 18, true,  m), 1);
	//m[0].toString();
	//m[1].toString();
	//Move em(Step(36,true));
	//em.addStep(Step(54, true));
	//EXPECT_EQ(m[0], em);
}


/*
 * Check initialized board moves
 */

struct SimpleMovementsTestData {
	int i;
	int who;
	int count;
	int m[4];
};

static std::array<SimpleMovementsTestData, 10> tdata
{{
	{	8, -1, 1, {25, 0, 0, 0} },
	{	9, -1, 2, {25, 27, 0, 0} },
	{	10, -1, 2,{27, 29, 0, 0} },
	{	11, -1, 2,{29, 31, 0, 0} },
	{	11, -1, 2,{29, 31, 0, 0} },
	{ 0, 1, 0,  {0, 0, 0, 0} },
	{	9, 1, 2,  {36, 38, 0, 0} },
	{	10, 1, 2, {34, 36, 0, 0} },
	{	11, 1, 2, {32, 34, 0, 0} },
	{	0, 1, 0,  {0, 0, 0, 0} }
}};

class FindMovesTestCase
	: public ::testing::TestWithParam<SimpleMovementsTestData>
{
};

bool compareMoves(Move * a, Move * b, int size)
{
	std::vector<Move> va;
	std::vector<Move> vb;
	for(int i = 0; i < size; ++i) {
	//	if(a[i].isValid()) {
			va.push_back(a[i]);
	//	}
	//	if(b[i].isValid()) {
			vb.push_back(b[i]);
	//	}
	}

	sort(va.begin(), va.end());
	sort(vb.begin(), vb.end());

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

/*
TEST_P(FindMovesTestCase, TestInitBoardMove)
{
	int pA[] = {0, 2, 4, 6, 9, 11, 13, 15, 16, 18, 20, 22};
	int pB[] = {63, 61, 59, 57, 54, 52, 50, 48, 47, 45, 43, 41};
	int kA[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int kB[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int m[4] = {0};

	SimpleMovementsTestData d = GetParam();
	
	EXPECT_EQ(options(d.i, m, pA, pB, kA, kB, d.who), d.count);

	EXPECT_EQ(compareMoves(d.m, m, 4), true);
}

INSTANTIATE_TEST_CASE_P(FindMovesTestCaseSet, 
		FindMovesTestCase, 
		testing::ValuesIn(tdata));

*/



/*
struct MovementsWithBoardTestData {
	int pA[12];
	int pB[12];
	int kA[12];
	int kB[12];
	int i;
	int who;
	int count;
	int m[4];
};

static std::array<MovementsWithBoardTestData, 7> bdata
{{
	{	// ход из угла, только один вариант
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		0, -1, 1, {9, 0, 0, 0} 
	},
	{	// запертая шашака, некуда ходить
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{9, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		0, -1, 0, {0, 0, 0, 0} 
	},
	{	// запертая шашака, только один ход
		{2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{11, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		0, -1, 1, {9, 0, 0, 0} 
	},
	{	// белая дамка по среди поля !!! ХЗ должна ходить дальше !!!
		{18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		0, -1, 4, {9, 11, 25, 27} 
	},
	{	// белая шашка которая должна срубить вперед !!! НЕВЕРНО, должна только рубить!!!
		{18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		0, -1, 2, {25, 36, 0, 0} 
	},
	{	// белая шашка которая должна срубить назад !!! НЕВЕРНО, должна только рубить назад!!!
		{18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		0, -1, 2, {25, 27, 0, 0} 
	},
	{	// белая шашка которая должна срубить два раза !!! НЕВЕРНО, должна только рубить дважды !!!
		{18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{27, 45, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		0, -1, 2, {25, 36, 0, 0} 
	}
 }};

class FindMovesWithBoardTestCase
	: public ::testing::TestWithParam<MovementsWithBoardTestData>
{
};

TEST_P(FindMovesWithBoardTestCase, TestBoardMove)
{
	int m[4] = {0};
	MovementsWithBoardTestData d = GetParam();
	EXPECT_EQ(options(d.i, m, d.pA, d.pB, d.kA, d.kB, d.who), d.count);
	EXPECT_EQ(compareMoves(d.m, m, 4), true);
}

INSTANTIATE_TEST_CASE_P(FindMovesTestCaseSet, 
		FindMovesWithBoardTestCase, 
		testing::ValuesIn(bdata));
*/
