#include "P2017112238.h"

void P2017112238::gameStart(int board[BOARD_SIZE][BOARD_SIZE])
{
	// ����
	//std::cout << "����" << std::endl;
}

Action P2017112238::nextMove()
{
	// ����
	//return (Action)(rand() % 4);
	if (up)
	{
		up = false;
		return MOVE_UP;
	}
	else if (left)
	{
		left = false;
		return MOVE_LEFT;
	}
	else if (right)
	{
		right = false;
		left = true;
		return MOVE_RIGHT;
	}
	else
	{
		return MOVE_DOWN;
	}
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
	switch (prevAction)
	{
	case MOVE_UP:

		break;
	case MOVE_LEFT:
		right = true;
		break;
	case MOVE_RIGHT:
		up = true;
		break;
	case MOVE_DOWN:
		left = true;
		break;
	/*default:
		break;*/
	}
}
