#pragma once
#include "Player.h"
#include "Board.h"
#include <limits>
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

	//비어있는 칸에 순차적으로 2 or 4블록생성
	bool putBlock();

	void setValue(double nodeValue);

	double getValue();

	void resetValue();

	bool put2;
	vector<Point> emptyCells;
	//모든 빈칸에 2or4를 추가해보기위해 필요한 변수
	int numEmptyCells;
	// 실제 게임 판
	int board[BOARD_SIZE][BOARD_SIZE];
	// 비어있는 칸을 리턴.
	std::vector<Point> getEmptyCells();

private:
	// 실제 shift하는 함수.
	std::vector<int> shift(std::vector<int> cells);

	// 게임 점수. 블록의 위치에 따른 점수를 기준으로 계산됨
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
	// 디버깅을 위한 문자열로 변환.
	char* Action_Debug[4] = { "MOVE_UP, 위로 이동", "MOVE_LEFT, 왼쪽으로 이동" , "MOVE_RIGHT, 오른쪽으로 이동" , "MOVE_DOWN, 아래로 이동" };
	
	CloneBoard board0, board1, board2, board3;
	int first_M, second_M, best_M, samemove;
	double best_Value;
	bool ableMove;
	int alpha, beta;
};

