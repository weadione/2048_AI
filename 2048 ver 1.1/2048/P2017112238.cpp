#include "P2017112238.h"

void P2017112238::gameStart(int board[BOARD_SIZE][BOARD_SIZE])
{
	// ����
	//std::cout << "����" << std::endl;
}

Action P2017112238::nextMove()
{
	// ����
	return (Action)(rand() % 4);
}

void P2017112238::ableToMove(Action prevAction, int board[BOARD_SIZE][BOARD_SIZE])
{
	// ����
	//std::cout << Action_Debug[prevAction] << "����" << std::endl;
}

void P2017112238::notAbleToMove(Action prevAction, int board[BOARD_SIZE][BOARD_SIZE])
{
	// ����
	//std::cout << Action_Debug[prevAction] << "����" << std::endl;
}
