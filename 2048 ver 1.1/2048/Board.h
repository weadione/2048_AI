#pragma once
#include "Action.h"
#include "Constants.h"
#include "Point.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <list>
#include <vector>

class Board
{
public:
	Board();

	// ���� �� �ʱ�ȭ
	void init();

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
	Board& operator = (const Board &b);

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