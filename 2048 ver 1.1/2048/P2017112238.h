#pragma once
#include "Player.h"
#include "Board.h"
#include <limits>
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

	//����ִ� ĭ�� ���������� 2 or 4��ϻ���
	bool putBlock();

	void setValue(double nodeValue);

	double getValue();

	void resetValue();

	bool put2;
	vector<Point> emptyCells;
	//��� ��ĭ�� 2or4�� �߰��غ������� �ʿ��� ����
	int numEmptyCells;
	// ���� ���� ��
	int board[BOARD_SIZE][BOARD_SIZE];
	// ����ִ� ĭ�� ����.
	std::vector<Point> getEmptyCells();

private:
	// ���� shift�ϴ� �Լ�.
	std::vector<int> shift(std::vector<int> cells);

	// ���� ����. ����� ��ġ�� ���� ������ �������� ����
	int score;

	double value;
	
	void calculateScore();
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
	
	CloneBoard board0, board1, board2, board3;
	int first_M, second_M, best_M, samemove;
	double best_Value;
	bool ableMove;
	int alpha, beta;
};

