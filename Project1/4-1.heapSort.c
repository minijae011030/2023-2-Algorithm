#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int H[100];
int n = 0, s;

void inPlaceHeapSort();
void downHeap(int i);
void rBuildHeap(int i);	// 재귀 방식으로 상향식 힙 생성
void printArray();

int main() {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)	 {
		scanf("%d", &H[i]);
	}

	rBuildHeap(1);

	inPlaceHeapSort();
	printArray();

	return 0;
}

void inPlaceHeapSort() {
	int tmp;

	for (int i = n; i >= 2; i--) {
		tmp = H[1];
		H[1] = H[i];
		H[i] = tmp;
		n--;

		downHeap(1);
	}
}

void downHeap(int i) {
	int big, tmp;

	if (n < (i * 2)) {
		return;
	}

	big = i * 2;

	if (n >= i * 2 + 1) {
		if (H[i * 2 + 1] > H[big]) {
			big = i * 2 + 1;
		}
	}

	if (H[i] >= H[big]) {
		return;
	}
	tmp = H[i];
	H[i] = H[big];
	H[big] = tmp;

	downHeap(big);
	return;
}

void rBuildHeap(int i) { // 상향식 힙 생성 함수
	if (i > n) {
		return;
	}
	rBuildHeap(i * 2);
	rBuildHeap(i * 2 + 1);
	downHeap(i);

	return;
}

void printArray() {
	for (int i = 1; i <= s; i++) {
		printf(" %d", H[i]);
	}
	printf("\n");
	return;
}