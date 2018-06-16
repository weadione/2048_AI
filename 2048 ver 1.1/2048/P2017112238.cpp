#include "P2017112238.h"
using namespace std;

void P2017112238::gameStart(int board[BOARD_SIZE][BOARD_SIZE])
{
	// ����
	//std::cout << "����" << std::endl;
	
	clone1.init(board);
	clone2.init(board);

}

Action P2017112238::nextMove()
{
	// ����
	//return (Action)(rand() % 4);
	Action bestAction = MOVE_UP, curAction=MOVE_UP, nextAction;
	bool fisrtMove = true;
	int bestScore = 0, curScore = 0, turn = 100, depth;
	while(turn--)
	{
		clone1 = clone2;
		fisrtMove = true;
		depth = 7;
		while (depth--)
		{
			if (clone1.isGameOver())
			{
				break;
			}
			nextAction = (Action)(rand() % 4);
			// �̵� �õ� �� ����
			if (clone1.move(nextAction))
			{
				if (fisrtMove)
				{
					curAction = nextAction;
					fisrtMove = false;
				}
				// �������� ��� �ϳ� ����.
				if (!clone1.putRandomBlock())
				{
					break;
				}
				// ��� ���� �Ұ��� �ϸ� ���� ����.
				//else
				//{
				//	break;
				//}
			}
		}
		curScore = clone1.getTotalScore();
		if (curScore > bestScore)
		{
			bestScore = curScore;
			bestAction = curAction;
		}

	}
	return bestAction;

}

void P2017112238::ableToMove(Action prevAction, int board[BOARD_SIZE][BOARD_SIZE])
{
	// ����
	//std::cout << Action_Debug[prevAction] << "����" << std::endl;
	clone2.init(board);
}

void P2017112238::notAbleToMove(Action prevAction, int board[BOARD_SIZE][BOARD_SIZE])
{
	// ����
	//std::cout << Action_Debug[prevAction] << "����" << std::endl;
	clone2.init(board);

}



//Ŭ�к���
CloneBoard::CloneBoard()
{
	// ���� �õ� ����.
	srand((int)board);
	//srand((unsigned int)time(NULL));
}

void CloneBoard::init(int board[BOARD_SIZE][BOARD_SIZE])
{
	// �ʱ�ȭ
	score = 0;

	for (int x = 0; x < BOARD_SIZE; x++)
	{
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			this->board[x][y] = board[x][y];
		}
	}
}

// ���� �� ����. ���� �� false ����
bool CloneBoard::putRandomBlock()
{
	std::vector<Point> emptyCells = getEmptyCells();

	// �� �� ������ �� �̻� �Ұ���.
	if (emptyCells.size() == 0)
	{
		return false;
	}

	// �� ĭ �߿��� �������� �� ����.
	int insertIndex = rand() % emptyCells.size();

	// 4 ���� �� 10�ۼ�Ʈ�� Ȯ��.
	// https://www.linkedin.com/pulse/20140613201532-7790303-probability-of-4-in-a-new-tile-in-2048
	int insertBlock = rand() % 10 < 9 ? 2 : 4;

	board[emptyCells[insertIndex].getX()][emptyCells[insertIndex].getY()] = insertBlock;

	return true;
}

// �̵�. (�� �� �� ��). ���� �� false ����
bool CloneBoard::move(Action action)
{
	bool isAbleToMove = false;
	// Ž���� ����
	const int dir[][2] = { 1, 0, 0, 1, 0, -1, -1, 0 };
	int dx = dir[action][0], dy = dir[action][1];

	std::vector<int> results[BOARD_SIZE];

	// ���� ���� �����δ�...2048 ���� ����.
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		std::vector<int> cellsToMove, originalCells;

		int x = dx < 0 ? BOARD_SIZE - 1 : i * abs(dy), y = dy < 0 ? BOARD_SIZE - 1 : i * abs(dx);
		int zeroCount = 0;

		for (int j = 0; j < BOARD_SIZE; j++)
		{
			int nx = (x + dx * j + BOARD_SIZE) % BOARD_SIZE;
			int ny = (y + dy * j + BOARD_SIZE) % BOARD_SIZE;

			// �տ� �ִ� 0�� ����.
			if (board[nx][ny] == 0)
			{
				zeroCount++;
			}
			else
			{
				cellsToMove.push_back(board[nx][ny]);
			}

			originalCells.push_back(board[nx][ny]);
		}

		for (int z = 0; z < zeroCount; z++)
		{
			cellsToMove.push_back(0);
		}

		// �̵�.
		results[i] = shift(cellsToMove);

		// �����̱� ����, ���� ���� �ǰ� �޶���.
		if (originalCells != results[i])
		{
			isAbleToMove = true;
		}
	}

	// �̵� �Ұ����ϸ� false.
	if (isAbleToMove == false)
	{
		return false;
	}

	// ���� �̵�
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		int x = dx < 0 ? BOARD_SIZE - 1 : i * abs(dy), y = dy < 0 ? BOARD_SIZE - 1 : i * abs(dx);

		for (int j = 0; j < BOARD_SIZE; j++)
		{
			int nx = (x + dx * j + BOARD_SIZE) % BOARD_SIZE;
			int ny = (y + dy * j + BOARD_SIZE) % BOARD_SIZE;

			board[nx][ny] = results[i][j];
		}
	}

	return isAbleToMove;
}

bool CloneBoard::isGameOver()
{
	// ���� ���� ��, ���� ����
	int originalScore = score;
	int originalBoard[BOARD_SIZE][BOARD_SIZE];
	memcpy(originalBoard, board, sizeof(board));

	// �� ���� �̵� �õ�
	for (int i = 0; i < 4; i++)
	{
		// �̵� ���� -> ���� ���� �ƴ�
		if (move((Action)i))
		{
			// ���� ���� ��, ������ ����
			score = originalScore;
			memcpy(board, originalBoard, sizeof(board));
			return false;
		}

		// ���� ���� ��, ������ ����
		score = originalScore;
		memcpy(board, originalBoard, sizeof(board));
	}

	// �ƹ� �͵� �̵��� �� ������ ���� ����.
	return true;
}

int CloneBoard::getTotalScore()
{
	return score;
}

 //���Կ�����
CloneBoard & CloneBoard::operator=(const CloneBoard & b)
{
	for (int x = 0; x < BOARD_SIZE; x++)
	{
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			this->board[x][y] = b.board[x][y];
		}
	}
	return *this;
}

// getter
int CloneBoard::getBoardXY(int x, int y)
{
	return board[x][y];
}

// ����ִ� ĭ�� ����.
std::vector<Point> CloneBoard::getEmptyCells()
{
	std::vector<Point> emptyCells;

	for (int x = 0; x < BOARD_SIZE; x++)
	{
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			if (board[x][y] == 0)
			{
				emptyCells.push_back(Point(x, y));
			}
		}
	}

	return emptyCells;
}

// ���� shift�ϴ� �Լ�.
std::vector<int> CloneBoard::shift(std::vector<int> cells)
{
	std::vector<int> result;

	for (int i = 0; i < cells.size(); i++)
	{
		// ������ ���� ��ħ.
		if (i < cells.size() - 1 && cells[i] == cells[i + 1] && cells[i] != 0)
		{
			cells[i] *= 2;
			score += cells[i];

			result.push_back(cells[i]);
			cells.push_back(0);
			i++;
		}
		else
		{
			result.push_back(cells[i]);
		}
	}

	return result;
}
