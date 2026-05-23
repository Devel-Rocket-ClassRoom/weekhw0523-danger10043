#include <iostream>
#include <stdio.h>
#include <time.h>
#include <string>
#include "Homework03.h"
#include "Homework04.h"

std::string number2Card(int card)
{
	if (card == 1) {
		return "1";
	}
	else if (card == 2) {
		return "2";
	}
	else if (card == 3) {
		return "3";
	}
	else if (card == 4) {
		return "4";
	}
	else if (card == 5) {
		return "5";
	}
	else if (card == 6) {
		return "6";
	}
	else if (card == 7) {
		return "7";
	}
	else if (card == 8) {
		return "8";
	}
	else if (card == 9) {
		return "9";
	}
	else if (card == 10) {
		return "10";
	}
	else if (card == 11) {
		return "J";
	}
	else if (card == 12) {
		return "Q";
	}
	else if (card == 13) {
		return "K";
	}
	else {
		return "JOKER";
	}
}

void shuffleArray(int* array, int length) {
	for (int i = length - 1; i >= 0; i--) {
		int j = rand() % (i + 1);
		std::swap(array[i], array[j]);
	}
}

int selectRandomCard() {
	return rand() % 13 + 1;
}

void selectDealerCard(int& card1, int& card2, int& card3) {
	int cardList[3] = { 0, 0, 0 };
	cardList[0] = selectRandomCard();
	do {
		cardList[1] = selectRandomCard();
	} while (cardList[0] == cardList[1]);
	cardList[2] = -1;
	shuffleArray(cardList, 3);
	
	card1 = cardList[0];
	card2 = cardList[1];
	card3 = cardList[2];
}

void printCard(int* cardList, bool* cardReveal) {
	printf("[ %s | %s | %s ]",
		(cardReveal[0]) ? number2Card(cardList[0]).c_str() : "?",
		(cardReveal[1]) ? number2Card(cardList[1]).c_str() : "?",
		(cardReveal[2]) ? number2Card(cardList[2]).c_str() : "?"
		);
}

void playCardGame(int& playerMoney, int& gameMoney) {
	int dealerCard[3] = { 0, 0, 0 };
	bool cardReveal[3] = { false, false, false };
	selectDealerCard(dealerCard[0], dealerCard[1], dealerCard[2]);
	printf("딜러가 카드를 선택하였습니다. : ");
	printCard(dealerCard, cardReveal);
	printf("\n\n몇 번째 카드를 선택할 것인지를 정수로 입력하세요(1 / 2 / 3) : ");
	int playerSelect = 0; std::cin >> playerSelect;
	cardReveal[playerSelect - 1] = true;
	printf("\n딜러의 카드 :");
	printCard(dealerCard, cardReveal);
	printf("\n플레이어가 선택한 카드 : [%d번째 카드(%s)]\n\n", playerSelect, number2Card(dealerCard[playerSelect - 1]).c_str());

	if (dealerCard[playerSelect - 1] == -1) {
		printf("[ 플레이어의 승리입니다! 베팅 금액의 2배를 얻습니다.\n\n");
		playerMoney += gameMoney * 2;
		gameMoney = 0;
		return;
	}
	else {
		printf("[ 플레이어의 패배입니다. 둘 중 하나를 선택하세요.\n");
		printf("1. 다음 게임 시작하기\n");
		printf("2. 베팅 금액의 2배를 추가로 지불하고 한 번 더 선택하기\n\n");
		printf("입력 : ");
		std::cin >> playerSelect;
		if (playerSelect == 1) {
			gameMoney = 0;
			return;
		}
		else if (playerSelect == 2) {
			if (playerMoney < 2 * gameMoney) {
				printf("소지금이 베팅 금액의 2배보다 적습니다.\n\n");
				return;
			}
			playerMoney -= 2 * gameMoney;
			gameMoney *= 3;
			printf("\n딜러의 카드 :");
			printCard(dealerCard, cardReveal);
			while (true) {
				printf("\n\n몇 번째 카드를 선택할 것인지를 정수로 입력하세요(1 / 2 / 3) : ");
				std::cin >> playerSelect;
				if (cardReveal[playerSelect - 1]) {
					printf("이미 이전에 선택한 카드입니다. 다른 카드를 선택하세요.\n\n");
					continue;
				}
				break;
			}
			cardReveal[0] = true;
			cardReveal[1] = true;
			cardReveal[2] = true;
			printf("\n딜러의 카드 :");
			printCard(dealerCard, cardReveal);
			printf("\n플레이어가 선택한 카드 : [%d번째 카드(%s)]\n\n", playerSelect, number2Card(dealerCard[playerSelect - 1]).c_str());

			if (dealerCard[playerSelect - 1] == -1) {
				printf("[ 플레이어의 승리입니다! 베팅 금액의 2배를 얻습니다.\n\n");
				playerMoney += gameMoney * 2;
				gameMoney = 0;
				return;
			}
			else {
				printf("[ 플레이어의 패배입니다.. ]\n\n");
				gameMoney = 0;
				return;
			}
		}
	}
}


void Homework04_Run() {
	srand(time(0));

	printf("<< HOMEWORK - 04 >>\n\n");

	int playerMoney = 10000;
	int gameMoney = 0;
	printf("[ 도둑 잡기 게임 ]\n\n");

	while (playerMoney > 100) {
		printf("현재 소지금 : [ %d원 ]\n", playerMoney);
		gameMoney = setBetAmount(playerMoney);
		printf("\n플레이어가 설정한 베팅 금액 : [ %d원 ]\n", gameMoney);
		playerMoney -= gameMoney;
		playCardGame(playerMoney, gameMoney);
	}
	printf("소지금이 부족하여 게임이 종료되었습니다.\n\n");
}
