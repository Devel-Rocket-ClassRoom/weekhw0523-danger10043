#include "Homework02.h"
#include <iostream>

int SumDigit(std::string Number)
{
	int result = 0;
	int Length = Number.length();
	for (int i = 0; i < Length; i++) {
		int temp = Number[i] - '0';
		result += temp;
	}
	return result;
}

void Homework02_Run() {
	printf("<< HOMEWORK - 02 >>\n\n");
	printf("정수 하나를 입력하세요. (자리 수 제한 없음) : ");
	std::string number; std::cin >> number;
	int sum = SumDigit(number);
	printf("\n 모든 자리수의 합 : [ %d ]\n\n", sum);
}