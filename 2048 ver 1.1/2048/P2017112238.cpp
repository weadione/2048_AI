#include "P2017112238.h"
using namespace std;

void P2017112238::gameStart(int board[BOARD_SIZE][BOARD_SIZE])
{
	// 시작
	//std::cout << "시작" << std::endl;
	
	clone1.init(board);
	clone2.init(board);

}

Action P2017112238::nextMove()
{
	// 랜덤
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
			// 이동 시도 및 성공
			if (clone1.move(nextAction))
			{
				if (fisrtMove)
				{
					curAction = nextAction;
					fisrtMove = false;
				}
				// 랜덤으로 블록 하나 생성.
				if (!clone1.putRandomBlock())
				{
					break;
				}
				// 블록 생성 불가능 하면 게임 종료.
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
	// 성공
	//std::cout << Action_Debug[prevAction] << "성공" << std::endl;
	clone2.init(board);
}

void P2017112238::notAbleToMove(Action prevAction, int board[BOARD_SIZE][BOARD_SIZE])
{
	// 실패
	//std::cout << Action_Debug[prevAction] << "실패" << std::endl;
	clone2.init(board);

}



//클론보드
CloneBoard::CloneBoard()
{
	// 랜덤 시드 설정.
	srand((int)board);
	//srand((unsigned int)time(NULL));
}

void CloneBoard::init(int board[BOARD_SIZE][BOARD_SIZE])
{
	// 초기화
	score = 0;

	for (int x = 0; x < BOARD_SIZE; x++)
	{
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			this->board[x][y] = board[x][y];
		}
	}
}

// 랜덤 블럭 생성. 실패 시 false 리턴
bool CloneBoard::putRandomBlock()
{
	std::vector<Point> emptyCells = getEmptyCells();

	// 꽉 차 있으면 더 이상 불가능.
	if (emptyCells.size() == 0)
	{
		return false;
	}

	// 빈 칸 중에서 랜덤으로 블럭 삽입.
	int insertIndex = rand() % emptyCells.size();

	// 4 블럭은 약 10퍼센트의 확률.
	// https://www.linkedin.com/pulse/20140613201532-7790303-probability-of-4-in-a-new-tile-in-2048
	int insertBlock = rand() % 10 < 9 ? 2 : 4;

	board[emptyCells[insertIndex].getX()][emptyCells[insertIndex].getY()] = insertBlock;

	return true;
}

// 이동. (상 하 좌 우). 실패 시 false 리턴
bool CloneBoard::move(Action action)
{
	bool isAbleToMove = false;
	// 탐색할 방향
	const int dir[][2] = { 1, 0, 0, 1, 0, -1, -1, 0 };
	int dx = dir[action][0], dy = dir[action][1];

	std::vector<int> results[BOARD_SIZE];

	// 게임 판을 움직인다...2048 게임 참고.
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		std::vector<int> cellsToMove, originalCells;

		int x = dx < 0 ? BOARD_SIZE - 1 : i * abs(dy), y = dy < 0 ? BOARD_SIZE - 1 : i * abs(dx);
		int zeroCount = 0;

		for (int j = 0; j < BOARD_SIZE; j++)
		{
			int nx = (x + dx * j + BOARD_SIZE) % BOARD_SIZE;
			int ny = (y + dy * j + BOARD_SIZE) % BOARD_SIZE;

			// 앞에 있는 0은 제거.
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

		// 이동.
		results[i] = shift(cellsToMove);

		// 움직이기 가능, 원래 게임 판과 달라짐.
		if (originalCells != results[i])
		{
			isAbleToMove = true;
		}
	}

	// 이동 불가능하면 false.
	if (isAbleToMove == false)
	{
		return false;
	}

	// 실제 이동
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
	// 원래 게임 판, 점수 복사
	int originalScore = score;
	int originalBoard[BOARD_SIZE][BOARD_SIZE];
	memcpy(originalBoard, board, sizeof(board));

	// 네 군데 이동 시도
	for (int i = 0; i < 4; i++)
	{
		// 이동 가능 -> 게임 오버 아님
		if (move((Action)i))
		{
			// 원래 게임 판, 점수로 복구
			score = originalScore;
			memcpy(board, originalBoard, sizeof(board));
			return false;
		}

		// 원래 게임 판, 점수로 복구
		score = originalScore;
		memcpy(board, originalBoard, sizeof(board));
	}

	// 아무 것도 이동할 수 없으면 게임 오버.
	return true;
}

int CloneBoard::getTotalScore()
{
	return score;
}

 //대입연산자
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

// 비어있는 칸을 리턴.
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

// 실제 shift하는 함수.
std::vector<int> CloneBoard::shift(std::vector<int> cells)
{
	std::vector<int> result;

	for (int i = 0; i < cells.size(); i++)
	{
		// 같으면 블럭을 합침.
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
