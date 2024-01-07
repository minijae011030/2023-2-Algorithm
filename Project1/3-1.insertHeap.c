#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int H[100];
int n = 0;

void insertItem(int key);	// 키를 힙에 삽입하고 0을 인쇄하는 함수
int removeMax();	// 키를 힙에서 삭제하고 반환된 키를 인쇄하는 함수
void printHeap();	// 힙의 내용을 인쇄하는 함수 -> 이진트리의 레벨순서로 인쇄
void upHeap(int i);
void downHeap(int i);
int main() {
	char cmd;
	int key;

	while (1) {
		scanf("%c", &cmd);
		switch (cmd)
		{
		case 'i' :
			scanf("%d", &key);
			insertItem(key);
			printf("0\n");
			getchar();
			break;
		case 'd' :
			printf("%d\n", removeMax());
			getchar();
			break;
		case 'p' :
			printHeap();
			getchar();
			break;
		case 'q' :
			return;
		default:
			break;
		}
	}
}

void insertItem(int key) {
	n++;
	H[n] = key;

	upHeap(n);

	return;
}

int removeMax() {
	int key = H[1];

	H[1] = H[n];
	n--;

	downHeap(1);

	return key;
}

void printHeap() {
	for (int i = 1; i < n + 1; i++) {
		printf(" %d", H[i]);
	}
	printf("\n");
	return;
}

void upHeap(int i) {
	int tmp;
	if (i == 1) {
		return;
	}
	if (H[i / 2] >= H[i]) {
		return;
	}
	tmp = H[i];
	H[i] = H[i / 2];
	H[i / 2] = tmp;

	upHeap(i / 2);
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