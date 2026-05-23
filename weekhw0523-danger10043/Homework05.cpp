#include <iostream>
#include <stdio.h>
#include <time.h>
#include "Homework05.h"


void printMap(int map[][20], int mazeRows, int mazeCols) {
	for (int row = 0; row < mazeRows; row++) {
		for (int col = 0; col < mazeCols; col++) {
			switch (map[row][col]) {
			case 0:
				printf(".");
				break;
			case 1:
				printf("#");
				break;
			case 2:
				printf("S");
				break;
			case 3:
				printf("E");
				break;
			case 4:
				printf("P");
				break;
			}
		}
		printf("\n");
	}
	printf("\n");
}

void checkMovableDirection(int map[][20], int mazeRows, int mazeCols, int playerPosR, int playerPosC) {
	// W, 위쪽
	printf("{ ");
	if (playerPosR > 0 && map[playerPosR - 1][playerPosC] != 1) {
		printf("W(↑) ");
	}
	
	// A, 왼쪽
	if (playerPosC > 0 && map[playerPosR][playerPosC - 1] != 1) {
		printf("A(←) ");
	}

	// S, 아래쪽
	if (playerPosR < mazeRows - 1 && map[playerPosR + 1][playerPosC] != 1) {
		printf("S(↓) ");
	}

	// D, 오른쪽
	if (playerPosC < mazeCols - 1 && map[playerPosR][playerPosC + 1] != 1) {
		printf("D(→) ");
	}
	printf("}");
}

void playerMove(int map[][20], int mazeRows, int mazeCols, int& playerPosR, int& playerPosC, char direction) {
	switch (direction) {
	case 'W':
	case 'w':
		if (playerPosR > 0 && map[playerPosR - 1][playerPosC] != 1) {
			map[playerPosR][playerPosC] = 0;
			map[playerPosR - 1][playerPosC] = 4;
			playerPosR--;
		}
		break;
	case 'A':
	case 'a':
		if (playerPosC > 0 && map[playerPosR][playerPosC - 1] != 1) {
			map[playerPosR][playerPosC] = 0;
			map[playerPosR][playerPosC - 1] = 4;
			playerPosC--;
		}
		break;
	case 'S':
	case 's':
		if (playerPosR < mazeRows - 1 && map[playerPosR + 1][playerPosC] != 1) {
			map[playerPosR][playerPosC] = 0;
			map[playerPosR + 1][playerPosC] = 4;
			playerPosR++;
		}
		break;
	case 'D':
	case 'd':
		if (playerPosC < mazeCols - 1 && map[playerPosR][playerPosC + 1] != 1) {
			map[playerPosR][playerPosC] = 0;
			map[playerPosR][playerPosC + 1] = 4;
			playerPosC++;
		}
	}
}

bool playBattle(int& playerHealth) {
	printf("[ == 적이 등장했습니다! == ]\n\n");
	int enemyHealth = rand() % 5 + 30;
	int damage = 0;

	printf("플레이어의 체력 : [ %d ] / 적의 체력 : [ %d ]\n\n", playerHealth, enemyHealth);
	while (true) {
		damage = rand() % 11 + 5;
		if (rand() % 10 == 0) {
			damage *= 2;
			enemyHealth = std::max(0, enemyHealth - damage);
			printf("플레이어가 치명타를 가하여 %d 의 피해를 입혔습니다! (적의 현재 체력 : %d)\n\n", damage, enemyHealth);
		}
		else {
		enemyHealth = std::max(0, enemyHealth - damage);
		printf("플레이어가 공격하여 %d 의 피해를 입혔습니다. (적의 현재 체력 : %d)\n\n", damage, enemyHealth);
		}

		if (enemyHealth <= 0) {
			printf("플레이어 승리! 적이 쓰러졌습니다!\n\n");
			return true;
		}

		damage = rand() % 1 + 2;
		playerHealth = std::max(0, playerHealth - damage);
		printf("적이 공격하여 %d 의 피해를 입었습니다. (플레이어의 현재 체력 : %d)\n\n", damage, playerHealth);

		if (playerHealth <= 0) {
			printf("체력이 모두 소진되었습니다. 전투에서 패배했습니다..\n\n");
			return false;
		}
	}
}

void Homework05_Run() {
	srand(time(0));

	// 미로 크기
	const int MazeRows = 10;
	const int MazeCols = 20;

	// 미로 배열
	int Maze[MazeRows][MazeCols] =
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,2,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,1,0,1},
		{1,1,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,0,1},
		{1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1},
		{1,0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
		{1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1},
		{1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1},
		{1,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,3,1},
		{1,0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	int playerPosR = 0, playerPosC = 0, startPosR = 0, startPosC = 0, exitPosR = 0, exitPosC = 0;
	int playerHealth = 100;

	for (int row = 0; row < MazeRows; row++) {
		for (int col = 0; col < MazeCols; col++) {
			if (Maze[row][col] == 2) {
				startPosR = row;
				startPosC = col;
			}
			if (Maze[row][col] == 3) {
				exitPosR = row;
				exitPosC = col;
			}
		}
	}
	playerPosR = startPosR;
	playerPosC = startPosC;
	Maze[playerPosR][playerPosC] = 4;

	while (true) {
		printMap(Maze, MazeRows, MazeCols);
		printf("이동할 수 있는 방향을 선택하세요 (w: 위, s: 아래, a: 왼쪽, d: 오른쪽):\n");
		checkMovableDirection(Maze, MazeRows, MazeCols, playerPosR, playerPosC);
		printf("\n\n방향 입력 : ");
		char direction; std::cin >> direction;
		playerMove(Maze, MazeRows, MazeCols, playerPosR, playerPosC, direction);
		if (rand() % 15 == 0) {
			if (!playBattle(playerHealth))
				break;
		}
		Maze[startPosR][startPosC] = 2;
		if (playerPosR == exitPosR && playerPosC == exitPosC) {
			printf("[ == 축하드립니다! 미로를 탈출했습니다! == ]");
			break;
		}
	}
}
