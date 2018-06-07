#include "P2013111995.h"

void P2013111995::gameStart(int board[BOARD_SIZE][BOARD_SIZE])
{
	// 시작
	//std::cout << "시작" << std::endl;
}

Action P2013111995::nextMove()
{
	// 랜덤
	return (Action)(rand() % 4);
}

void P2013111995::ableToMove(Action prevAction, int board[BOARD_SIZE][BOARD_SIZE])
{
	// 성공
	//std::cout << Action_Debug[prevAction] << "성공" << std::endl;
}

void P2013111995::notAbleToMove(Action prevAction, int board[BOARD_SIZE][BOARD_SIZE])
{
	// 실패
	//std::cout << Action_Debug[prevAction] << "실패" << std::endl;
}
