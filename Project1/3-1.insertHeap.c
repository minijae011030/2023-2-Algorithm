#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int H[100];
int n = 0;

void insertItem(int key);	// Ű�� ���� �����ϰ� 0�� �μ��ϴ� �Լ�
int removeMax();	// Ű�� ������ �����ϰ� ��ȯ�� Ű�� �μ��ϴ� �Լ�
void printHeap();	// ���� ������ �μ��ϴ� �Լ� -> ����Ʈ���� ���������� �μ�
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