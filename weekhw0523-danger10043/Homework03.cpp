#include <iostream>
#include <stdio.h>
#include <time.h>
#include "Homework03.h"

int playSlotGame()
{
	int Number1 = 0, Number2 = 0, Number3 = 0;
	Number1 = rand() % 9 + 1;
	Number2 = rand() % 9 + 1;
	Number3 = rand() % 9 + 1;

	printf("슬롯 머신 결과 : [ %d | %d | %d ]\n", Number1, Number2, Number3);

	if (Number1 == 7 && Number2 == 7 && Number3 == 7) {
		printf("잭팟 입니다! 베팅액의 10,000 배를 획득합니다.\n\n");
		return 10000;
	}
	else if (Number1 == Number2 && Number1 == Number3) {
		printf("같은 번호 3개가 등장했습니다! 베팅액의 50 배를 획득합니다.\n\n");
		return 50;
	}
	else {
		printf("꽝입니다! 아쉽군요..\n\n");
		return 0;
	}
}
int setBetAmount(int playerMoney) {
	int result = 0;
	while (true) {
		printf("이번 게임에 베팅할 금액을 입력하세요.(최소 100원) : ");
		std::cin >> result;
		if (result < 100) {
			printf("최소 100원 이상을 베팅해야 합니다.\n\n");
			continue;
		}
		if (result > playerMoney) {
			printf("소지금 이상의 돈을 베팅할 수 없습니다.\n\n");
			continue;
		}
		break;
	}
	return result;
}

void Homework03_Run() {
	srand(time(0));

	printf("<< HOMEWORK - 03 >>\n\n");

	int playerMoney = 10000;
	int gameMoney = 0;
	printf("[ 슬롯 머신 게임 ]\n\n");

	while (playerMoney > 100) {
		printf("현재 소지금 : [ %d원 ]\n", playerMoney);
		gameMoney = setBetAmount(playerMoney);
		printf("\n플레이어가 설정한 베팅 금액 : [ %d원 ]\n", gameMoney);
		playerMoney -= gameMoney;
		gameMoney *= playSlotGame();
	}
	printf("소지금이 부족하여 게임이 종료되었습니다.\n\n");
}