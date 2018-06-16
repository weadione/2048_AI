#pragma once
#include "Player.h"
#include "Board.h"
using namespace std;

class CloneBoard
{
public:
	CloneBoard();

	// ���� �� �ʱ�ȭ
	void init(int board[BOARD_SIZE][BOARD_SIZE]);

	// ���� �� ����. ���� �� false ����
	bool putRandomBlock();

	// �̵�. (�� �� �� ��). ���� �� false ����
	bool move(Action action);

	// �� �� �� �� �� �����̴� ���� �Ұ����ϸ� ȣ��.
	bool isGameOver();

	// ������ ����.
	int getTotalScore();

	// ��� ���ϰ� �ϱ� ����
	friend std::ostream& operator<<(std::ostream& os, const Board& b);

	// ���� �ϱ� ���� �������̵�
	CloneBoard& operator = (const CloneBoard &b);


	// getter
	int getBoardXY(int x, int y);
private:
	// ����ִ� ĭ�� ����.
	std::vector<Point> getEmptyCells();

	// ���� shift�ϴ� �Լ�.
	std::vector<int> shift(std::vector<int> cells);

	// ���� ���� ��
	int board[BOARD_SIZE][BOARD_SIZE];

	// ���� ����. �� ���� ���ļ� ���ο� �� ���� �ø��� ������.
	int score;
};

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
	
	CloneBoard clone1;
	CloneBoard clone2;
};

