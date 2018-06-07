#pragma once
#include "Action.h"
#include "Constants.h"
#include "Point.h"

class Player
{
public:
	Player() {}

	// ���� ó�� ���� �� ȣ��˴ϴ�.
	// ���� ���� ���� ���°� 2���� �迭�� �־����ϴ�.
	virtual void gameStart(int board[BOARD_SIZE][BOARD_SIZE]) = 0;

	// ������ "������ ����"�� ��ȯ�ϼ���. 
	// �ش� �������� �̵� �õ� �� �Ʒ� ableToMove, notAbleToMove �Լ� �� �ϳ��� ȣ��˴ϴ�.
	//
	// Action enum�ȿ��� { MOVE_UP, MOVE_LEFT, MOVE_RIGHT, MOVE_DOWN } �� ��� �ֽ��ϴ�.
	// ex) return Action::MOVE_LEFT; // �������� �̵�
	virtual Action nextMove() = 0;

	// ������ �������ٸ� �� �Լ��� ȣ��˴ϴ�.
	// prevAction: �������� �õ��� ����
	// board: ���� ���� ���� ����. �������� �� ����� ������ �����Դϴ�.
	virtual void ableToMove(Action prevAction, int board[BOARD_SIZE][BOARD_SIZE]) = 0;

	// ������ �������� ���ߴٸ� �� �Լ��� ȣ��˴ϴ�.
	// prevAction: �������� �õ��� ����
	// board: ���� ���� ���� ����. ���ο� ����� �������� �ʽ��ϴ�.
	virtual void notAbleToMove(Action prevAction, int board[BOARD_SIZE][BOARD_SIZE]) = 0;
};