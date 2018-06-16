#include "GameManager.h"
#include <Windows.h>

// ���� �ʱ�ȭ
void GameManager::init()
{
	// �ʱ�ȭ.
	gameBoard.init();

	// ó���� 2���� ���
	gameBoard.putRandomBlock();
	gameBoard.putRandomBlock();
}

// player �� ���� ���� �÷��� ����
// -> �÷��̾ �̵��� �׼��� ����, �׿� ���� ������ ȣ��.
// -> �ִ� ������ ������ ���� Ŭ����
void GameManager::run(Player * player)
{
	// �ʱ�ȭ.
	init();

	// ���� ����.
	// ���� �� ������ �����Ͽ� �÷��̾�� �����ش�.
	int board[BOARD_SIZE][BOARD_SIZE];
	for (int x = 0; x < BOARD_SIZE; x++)
	{
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			board[x][y] = gameBoard.getBoardXY(x, y);
		}
	}
	player->gameStart(board);

	// 10000�� ���� �ش�.
	// 10000�� ���� ������ ������ ���� ����.
	int limitTurn = MAX_TURN;
	while (limitTurn--)
	{
		// ���� ���� ȭ�鿡 ���
		if (DEBUG)
		{
			system("cls");
			
			std::cout << gameBoard << std::endl;
			Sleep(100);
		}


		// ������ �̵��� ��ǥ
		Action nextAction = player->nextMove();

		// ���� �� ������ �����Ѵ�.
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			for (int y = 0; y < BOARD_SIZE; y++)
			{
				board[x][y] = gameBoard.getBoardXY(x, y);
			}
		}

		// �� �̻� ������ ���� ������ ���� ����.
		if (gameBoard.isGameOver())
		{
			break;
		}

		// �̵� �õ� �� ����
		if (gameBoard.move(nextAction))
		{
			// �������� ��� �ϳ� ����.
			if (gameBoard.putRandomBlock())
			{
				// ���� �� ������ �����Ѵ�.
				for (int x = 0; x < BOARD_SIZE; x++)
				{
					for (int y = 0; y < BOARD_SIZE; y++)
					{
						board[x][y] = gameBoard.getBoardXY(x, y);
					}
				}
				
				player->ableToMove(nextAction, board);
			}
			// ��� ���� �Ұ��� �ϸ� ���� ����.
			else
			{
				break;
			}
		}
		// �̵� �õ� ����
		else
		{
			player->notAbleToMove(nextAction, board);
		}
	}

	// ���� ���� ȭ�鿡 ���	
	std::cout << gameBoard << std::endl;

	// ������ �� ������ ������ ���� Ŭ���� �� ���� ���
	if (limitTurn >= 0)
	{
		std::cout << MAX_TURN - limitTurn << "ȸ ���� ���� ����. >,<\n������ " << gameBoard.getTotalScore() << std::endl;
	}
	// ���� ���� �� ���� ���.
	else
	{
		std::cout << MAX_TURN << "ȸ �ȿ� ���� ���ᰡ �� �Ǿ� ���� �����մϴ�. T^T\n������" << gameBoard.getTotalScore() << std::endl;
	}


	delete player;
}
