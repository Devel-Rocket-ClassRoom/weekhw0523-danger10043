#pragma once

void printMap(int map[][20], int mazeRows, int mazeCols);

void checkMovableDirection(int map[][20], int mazeRows, int mazeCols, int playerPosR, int playerPosC);

void playerMove(int map[][20], int mazeRows, int mazeCols, int& playerPosR, int& playerPosC, char direction);

bool playBattle(int& playerHealth);

void Homework05_Run();
