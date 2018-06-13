#pragma once
#include "Player.h"

class P2017112238 : public Player
{
public:
	void gameStart(int board[BOARD_SIZE][BOARD_SIZE]);
	Action nextMove();
	void ableToMove(Action prevAction, int board[BOARD_SIZE][BOARD_SIZE]);
	void notAbleToMove(Action prevAction, int board[BOARD_SIZE][BOARD_SIZE]);

private:

	// ������� ���� ���ڿ��� ��ȯ.
	char* Action_Debug[4] = { "MOVE_UP, ���� �̵�", "MOVE_LEFT, �������� �̵�" , "MOVE_RIGHT, ���������� �̵�" , "MOVE_DOWN, �Ʒ��� �̵�" };
};
