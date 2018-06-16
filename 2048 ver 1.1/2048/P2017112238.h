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

	// 디버깅을 위한 문자열로 변환.
	char* Action_Debug[4] = { "MOVE_UP, 위로 이동", "MOVE_LEFT, 왼쪽으로 이동" , "MOVE_RIGHT, 오른쪽으로 이동" , "MOVE_DOWN, 아래로 이동" };
};
