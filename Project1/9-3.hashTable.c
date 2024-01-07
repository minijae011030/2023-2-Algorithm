#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int findHashIdx(int M, int key);
int findSecondHashIdx(int q, int key);

int insertHashIdx(int* arr, int M, int q, int key);
int findHashKey(int* arr, int M, int key);
void printHashTable(int* arr, int M);

int main() {
	int M, n, q;
	scanf("%d %d %d", &M, &n, &q);

	int* arr = (int*)malloc(sizeof(int) * M);
	for (int i = 0; i < M; i++) arr[i] = 0;

	while (1) {
		char cmd;
		int key;
		scanf("%c", &cmd);
		switch (cmd)
		{
		case 'i':
			scanf("%d", &key);
			int idx = insertHashIdx(arr, M, q, key);
			printf("%d\n", idx);
			break;
		case 's':
			scanf("%d", &key);
			int result = findHashKey(arr, M, key);
			if (result == -1)
				printf("%d\n", result);
			else
				printf("%d %d\n", result, key);
			break;
		case 'p':
			printHashTable(arr, M);
			break;
		case 'e':
			free(arr);
			return;
		default:
			break;
		}
	}
}

int findHashIdx(int M, int key) {
	return key % M;
}

int findSecondHashIdx(int q, int key) {
	return q - (key % q);
}

int insertHashIdx(int* arr, int M, int q, int key) {
	int idx = findHashIdx(M, key);
	if (arr[idx] == 0) {
		arr[idx] = key;
		return idx;
	}
	else {
		idx = findSecondHashIdx(q, key);
		while (1) {
			printf("C");
			if (arr[idx] == 0) {
				arr[idx] = key;
				return idx;
			}
			else {
				idx++;
			}
		}
	}
}

int findHashKey(int* arr, int M, int key) {
	for (int i = 0; i < M; i++)
		if (arr[i] == key)
			return i;

	return -1;
}

void printHashTable(int* arr, int M) {
	for (int i = 0; i < M; i++)
		printf(" %d", arr[i]);
	printf("\n");
}