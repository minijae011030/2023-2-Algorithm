#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int H[100];
int n = 0;

void rBuildHeap(int i);	// ��� ������� ����� �� ����
void buildHeap();	// ����� ������� ����� �� ����
void downHeap(int i);
void printHeap();

int main() {
	int keyN;
	scanf("%d", &keyN);

	for (int i = 1; i <= keyN; i++) {
		scanf("%d", &H[i]);
		n++;
	}
	rBuildHeap(1);
	printHeap();

}
void rBuildHeap(int i) {
	if (i > n) {
		return;
	}

	rBuildHeap(i * 2);	// ���� ��Ʈ���� �� ��Ʈ���� �� ����
	rBuildHeap(i * 2 + 1);	// ���� ��Ʈ���� �� ��Ʈ���� �� ����
	downHeap(i);	// ���� ��Ʈ���� ��Ʈ�� �¿� ��Ʈ���� ��ģ �� ����
	return;
}

void buildHeap() {
	for (int i = n / 2; i >= 1; i--) {
		downHeap(i);
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

void printHeap() {
	for (int i = 1; i <= n; i++) {
		printf(" %d", H[i]);
	}
	printf("\n");
	return;
}