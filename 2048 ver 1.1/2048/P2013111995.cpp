#include "P2013111995.h"

void P2013111995::gameStart(int board[BOARD_SIZE][BOARD_SIZE])
{
	// ����
	//std::cout << "����" << std::endl;
}

Action P2013111995::nextMove()
{
	// ����
	return (Action)(rand() % 4);
}

void P2013111995::ableToMove(Action prevAction, int board[BOARD_SIZE][BOARD_SIZE])
{
	// ����
	//std::cout << Action_Debug[prevAction] << "����" << std::endl;
}

void P2013111995::notAbleToMove(Action prevAction, int board[BOARD_SIZE][BOARD_SIZE])
{
	// ����
	//std::cout << Action_Debug[prevAction] << "����" << std::endl;
}
