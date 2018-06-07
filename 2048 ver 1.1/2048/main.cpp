#include "GameManager.h"
#include "P2013111995.h"

int main()
{
	// 게임 선언
	GameManager game;

	// 게임 시작
	game.run(new P2013111995());

	return 0;
}