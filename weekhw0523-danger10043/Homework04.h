#pragma once
#include <string>

std::string number2Card(int card);

void shuffleArray(int* array, int length);

int selectRandomCard();

void selectDealerCard(int& card1, int& card2, int& card3);

void printCard(int* cardList, bool* cardReveal);

void playCardGame(int& playerMoney, int& gameMoney);

void Homework04_Run();