#pragma once
#include "Board.h"
#include "Player.h"

class GameManager
{
public:
	// ���� �ʱ�ȭ
	void init();
	// player �� ���� ���� �÷��� ����
	// -> �÷��̾ �̵��� �׼��� ����, �׿� ���� ������ ȣ��.
	// -> �� �̻� ������ �� ������ �ִ� ������ ����ϰ� ����.	
	void run(Player* player);

private:
	Board gameBoard;
};