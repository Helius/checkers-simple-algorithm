#include <iostream>

#include "gtest/gtest.h"
//#include "checkers.h"

#include "checkersAI.cpp"
/*
void printBoard()
{
	for(int i = 0; i < 12; ++i)
	{
		std::cout << piecesA[i] << " ";
	}
	std::cout << std::endl;
	for(int i = 0; i < 12; ++i)
	{
		std::cout << piecesB[i] << " ";
	}
	std::cout << std::endl;
	for(int i = 0; i < 12; ++i)
	{
		std::cout << kingsA[i] << " ";
	}
	std::cout << std::endl;
	for(int i = 0; i < 12; ++i)
	{
		std::cout << kingsB[i] << " ";
	}
	std::cout << std::endl << std::endl;
}

TEST(first_test_case, AI_test)
{
	printBoard();
	StartSelect();
	printBoard();
}
*/
/*

TEST(stepValid_test_case, step_test)
{
	Step s;
	EXPECT_FALSE(s.isValid());
	Step s1(1,1);
	EXPECT_FALSE(s1.isValid());
	Step s2(1,2);
	EXPECT_TRUE(s2.isValid());
}

TEST(moveInitWithSteps_test_case, move_test)
{
	Move move(Step(1,2));
	move.addStep(Step(2,3));
	move.addStep(Step(3,4));
	move.addStep(Step(4,5));
	move.addStep(Step(5,6));
	for(int i = 0; i < 5; i++)
	{
		ASSERT_TRUE(move.getStep(i).isValid());
	}
	ASSERT_FALSE(move.getStep(6).isValid());
	ASSERT_EQ(move.getStep(0).from, 1);
	ASSERT_EQ(move.getStep(0).to, 2);
	ASSERT_EQ(move.getStep(3).from, 4);
	ASSERT_EQ(move.getStep(3).to, 5);
}

::testing::AssertionResult checkBoardInitState(const Board & b)
{
	if(b.get(0) != White) return ::testing::AssertionFailure();
	if(b.get(1) != White) return ::testing::AssertionFailure();
	if(b.get(2) != White) return ::testing::AssertionFailure();
	if(b.get(3) != White) return ::testing::AssertionFailure();
	if(b.get(4) != White) return ::testing::AssertionFailure();
	if(b.get(5) != White) return ::testing::AssertionFailure();
	if(b.get(6) != White) return ::testing::AssertionFailure();
	if(b.get(7) != White) return ::testing::AssertionFailure();
	if(b.get(8) != White) return ::testing::AssertionFailure();
	if(b.get(9) != White) return ::testing::AssertionFailure();
	if(b.get(10) != White) return ::testing::AssertionFailure(); 
	if(b.get(11) != White) return ::testing::AssertionFailure();
	
	if(b.get(12) != Empty) return ::testing::AssertionFailure();
	if(b.get(13) != Empty) return ::testing::AssertionFailure();
	if(b.get(14) != Empty) return ::testing::AssertionFailure();
	if(b.get(15) != Empty) return ::testing::AssertionFailure();
	if(b.get(16) != Empty) return ::testing::AssertionFailure();
	if(b.get(17) != Empty) return ::testing::AssertionFailure();
	if(b.get(18) != Empty) return ::testing::AssertionFailure();
	if(b.get(19) != Empty) return ::testing::AssertionFailure();

	if(b.get(20) != Black) return ::testing::AssertionFailure();
	if(b.get(21) != Black) return ::testing::AssertionFailure();
	if(b.get(22) != Black) return ::testing::AssertionFailure();
	if(b.get(23) != Black) return ::testing::AssertionFailure();
	if(b.get(24) != Black) return ::testing::AssertionFailure();
	if(b.get(25) != Black) return ::testing::AssertionFailure();
	if(b.get(26) != Black) return ::testing::AssertionFailure();
	if(b.get(27) != Black) return ::testing::AssertionFailure();
	if(b.get(28) != Black) return ::testing::AssertionFailure();
	if(b.get(29) != Black) return ::testing::AssertionFailure();
	if(b.get(30) != Black) return ::testing::AssertionFailure();
	if(b.get(31) != Black) return ::testing::AssertionFailure();

	return ::testing::AssertionSuccess();
}

TEST(boardInitWithData_test_case, board_test)
{
	Field f [Board::size()];
	for(int i = 0; i < Board::size(); ++i)
	{
		f[i] = i%2 ? White : Black;
	}
	
	Board b(f);

	for(int i = 0; i < Board::size(); ++i)
	{
		ASSERT_EQ(b.get(i), i%2 ? White : Black);
	}
}

TEST(boardInit_test_case, board_test)
{
	Board b;
	EXPECT_TRUE(checkBoardInitState(b));
}

TEST(boardReset_test_case, board_test)
{
	Board b;

	Step step(8,12);
	Move move(step);
	b.doMove(move);
	b.remove(1);
	b.remove(31);
	b.remove(18);
	b.remove(6);

	ASSERT_EQ(b.get(8), Empty);
	ASSERT_EQ(b.get(12), White);

	b.reset();
	EXPECT_TRUE(checkBoardInitState(b));
}

TEST(boardRemove_test_case, board_test)
{
	Board b;
	b.remove(1);
	ASSERT_EQ(b.get(1), Empty);
	b.remove(8);
	ASSERT_EQ(b.get(8), Empty);
	b.remove(31);
	ASSERT_EQ(b.get(31), Empty);
	b.remove(18);
	ASSERT_EQ(b.get(18), Empty);
}

TEST(boardOneStepMove_test_case, board_test)
{
	Board b;

	Step step(8,12);
	Move move(step);
	b.doMove(move);
	ASSERT_EQ(b.get(8), Empty);
	ASSERT_EQ(b.get(12), White);
}

TEST(boardMultiplyStepMove_test_case, board_test)
{
	Board b;

	Move move(Step(8,12));
	Step step1(12,17);
	Step step2(17,13);
	move.addStep(step1);
	move.addStep(step2);
	b.doMove(move);
	ASSERT_EQ(b.get(8), Empty);
	ASSERT_EQ(b.get(12), Empty);
	ASSERT_EQ(b.get(17), Empty);
	ASSERT_EQ(b.get(13), White);
}

TEST(checkFalseToMoveEmpty_test_case, checkersAi_test)
{
	Board b;
	Move move (Step(12,13));
	
	CheckersAI ai;
	
	EXPECT_FALSE(ai.checkMove(b, move));
}

TEST(checkFindAvailableFields, checkersAi_test)
{
	Field f [Board::size()] = {Empty};
	f[14] = White;
	Board b(f);

	CheckersAI ai;
	int cnt = ai.findAvailableFields(b, 14);	
	ASSERT_EQ(cnt, 2);
	const int * available = ai.getAvailable();
	ASSERT_EQ(available[0], 18);
	ASSERT_EQ(available[1], 19);
}

TEST(DISABLED_checkSingleMoveEmptyFields_test_case, checkersAi_test)
{
	Field f [Board::size()] = {Empty};
	f[13] = White;
	Board b(f);

	CheckersAI ai;

	Move move0(Step(13,9));
	Move move1(Step(13,10));
	Move move2(Step(12,14));
	Move move3(Step(13,17));

	Move move4(Step(13,21));
	Move move5(Step(13,15));
	Move move6(Step(13,4));
	Move move7(Step(13,5));
	Move move8(Step(13,6));
	
	Move move9(Step(13,17));
	Move move10(Step(13,18));

	EXPECT_FALSE(ai.checkMove(b, move0));
	EXPECT_FALSE(ai.checkMove(b, move1));
	EXPECT_FALSE(ai.checkMove(b, move2));
	EXPECT_FALSE(ai.checkMove(b, move3));

	EXPECT_FALSE(ai.checkMove(b, move4));
	EXPECT_FALSE(ai.checkMove(b, move5));
	EXPECT_FALSE(ai.checkMove(b, move6));
	EXPECT_FALSE(ai.checkMove(b, move7));
	EXPECT_FALSE(ai.checkMove(b, move8));

	EXPECT_TRUE(ai.checkMove(b, move9));
	EXPECT_TRUE(ai.checkMove(b, move10));
}

*/

