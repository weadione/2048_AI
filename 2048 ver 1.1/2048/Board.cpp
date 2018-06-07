#include "Board.h"

Board::Board()
{
	// ���� �õ� ����.
	srand((int)board);
}

void Board::init()
{
	// �ʱ�ȭ
	score = 0;

	for (int x = 0; x < BOARD_SIZE; x++)
	{
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			board[x][y] = 0;
		}
	}
}

// ���� �� ����. ���� �� false ����
bool Board::putRandomBlock()
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
bool Board::move(Action action)
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

bool Board::isGameOver()
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

int Board::getTotalScore()
{
	return score;
}

// ���Կ�����
Board & Board::operator=(const Board & b)
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
int Board::getBoardXY(int x, int y)
{
	return board[x][y];
}

// ����ִ� ĭ�� ����.
std::vector<Point> Board::getEmptyCells()
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
std::vector<int> Board::shift(std::vector<int> cells)
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

// ���
std::ostream & operator<<(std::ostream & os, const Board & b)
{
	for (int x = 0; x < BOARD_SIZE; x++)
	{
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			os << std::setw(8) << std::left << b.board[x][y];
		}
		os << '\n';
	}
	os << std::endl;

	return os;
}
