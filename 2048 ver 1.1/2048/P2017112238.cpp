#include "P2017112238.h"
using namespace std;

void P2017112238::gameStart(int board[BOARD_SIZE][BOARD_SIZE])
{
	board0.init(board);
	first_M = MOVE_UP;
	second_M = MOVE_UP;
	ableMove = true;
	samemove = 0;
}

Action P2017112238::nextMove()
{
	best_Value = 0;
	best_M = 0;
	alpha = INT_MIN;
	beta = INT_MAX;
	if (ableMove)
	{
		board0.setValue(alpha);
		for (int i = 0; i < 4; i++)
		{
			board1 = board0;
			beta = INT_MAX;
			board1.setValue(beta);
			if (board1.move((Action)first_M++))
			{
				board1.emptyCells = board1.getEmptyCells();
				for (int j = 0; j < board1.emptyCells.size() * 2; j++)
				{
					if (alpha > board1.getValue())
						break;
					board2 = board1;
					board2.putBlock();
					board2.setValue(INT_MIN);
					for (int k = 0; k < 4; k++)
					{
						board3 = board2;
						if (board2.getValue() > beta)
							break;
						if (board3.move((Action)second_M++))
						{
							if (alpha < board3.getTotalScore())
							{
								board2.setValue(board3.getTotalScore());
								alpha = board2.getValue();
							}
						}
					}
					second_M = MOVE_UP;
					if (board1.getValue()> board2.getValue())
					{
						board1.setValue(board2.getValue());
						beta = board2.getValue();
					}
					alpha = INT_MIN;
					board2.resetValue();
				}
				board2.numEmptyCells = 0;
				if (board0.getValue() < board1.getValue())
				{
					board0.setValue(board1.getValue());
					best_M = i;
					alpha = board0.getValue();
				}
				board1.resetValue();
			}
		}
		first_M = MOVE_UP;
		return (Action)best_M;
	}
	else
	{
		ableMove = true;
		return (Action)(rand() % 4);
	}
}

void P2017112238::ableToMove(Action prevAction, int board[BOARD_SIZE][BOARD_SIZE])
{
	// ����
	board0.init(board);
	ableMove = true;
	samemove = 0;
}

void P2017112238::notAbleToMove(Action prevAction, int board[BOARD_SIZE][BOARD_SIZE])
{
	// ����
	board0.init(board);
	samemove++;
	if (samemove > 20)
		ableMove = false;

}

//Ŭ�к���
CloneBoard::CloneBoard()
{
	// ���� �õ� ����.
	srand((int)board);
	score = 0;
	put2 = true;
	numEmptyCells = 0;
	value = 0;
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

//ȣ�� �� ���� ����� ���� ���
int CloneBoard::getTotalScore()
{
	calculateScore();
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

//������ 2,4 ����
bool CloneBoard::putBlock()
{
	emptyCells = getEmptyCells();

	// �� �� ������ �� �̻� �Ұ���.
	if (emptyCells.size() == 0)
		return false;

	if (put2)
		board[emptyCells[numEmptyCells].getX()][emptyCells[numEmptyCells].getY()] = 2;
	else
		board[emptyCells[numEmptyCells].getX()][emptyCells[numEmptyCells].getY()] = 4;


	return true;
}

//����� �� ����, ���, ����
void CloneBoard::setValue(double nodeValue)
{
	value = nodeValue;
}
double CloneBoard::getValue()
{
	return value;
}
void CloneBoard::resetValue()
{
	value = 0;
}

//��������Լ�
void CloneBoard::calculateScore()
{
	score = 0;
	for (int j = 0; j < 4; j++)
		score += board[0][j] * (120 - j * 10);
	for (int j = 0; j < 4; j++)
		score += board[1][j] * (80 - j * 10);
	for (int j = 0; j < 4; j++)
		score += board[2][j] * (60 - j * 10);
	for (int j = 0; j < 4; j++)
		score += board[3][j] * (40- j * 10);
}