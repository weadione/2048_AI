#pragma once
#include "Player.h"
#include "Board.h"
using namespace std;

class CloneBoard
{
public:
	CloneBoard();

	// 게임 판 초기화
	void init(int board[BOARD_SIZE][BOARD_SIZE]);

	// 랜덤 블럭 생성. 실패 시 false 리턴
	bool putRandomBlock();

	// 이동. (상 하 좌 우). 실패 시 false 리턴
	bool move(Action action);

	// 상 하 좌 우 다 움직이는 것이 불가능하면 호출.
	bool isGameOver();

	// 점수를 리턴.
	int getTotalScore();

	// 출력 편하게 하기 위함
	friend std::ostream& operator<<(std::ostream& os, const Board& b);

	// 대입 하기 위한 오버라이딩
	CloneBoard& operator = (const CloneBoard &b);


	// getter
	int getBoardXY(int x, int y);
private:
	// 비어있는 칸을 리턴.
	std::vector<Point> getEmptyCells();

	// 실제 shift하는 함수.
	std::vector<int> shift(std::vector<int> cells);

	// 실제 게임 판
	int board[BOARD_SIZE][BOARD_SIZE];

	// 게임 점수. 두 블럭을 합쳐서 새로운 블럭 생성 시마다 더해짐.
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
	// 디버깅을 위한 문자열로 변환.
	char* Action_Debug[4] = { "MOVE_UP, 위로 이동", "MOVE_LEFT, 왼쪽으로 이동" , "MOVE_RIGHT, 오른쪽으로 이동" , "MOVE_DOWN, 아래로 이동" };
	
	CloneBoard clone1;
	CloneBoard clone2;
};

